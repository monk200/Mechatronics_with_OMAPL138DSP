/* ECAN.C: This code is designed to act as a low-level eCAN driver for
	higher-level programming.  One should initialize the eCAN module
	in the following order: init_can(), mbox_set_id(), mbox_set_TX/RX(),
	mbox_enable().

	WRITTEN BY : Paul Miller <pamiller@uiuc.edu>
	$Id: ecan.c,v 1.4 2003/08/21 00:18:39 paul Exp $
*/

#include <coecsl.h>
#include <28335_ecan.h>

interrupt void ECAN0INTA_mbox_cb(void);
interrupt void ECAN1INTA_err_cb(void);

static void (*CanAA_func[MBOXES])(void);
static void (*CanRML_func[MBOXES])(void);
static void (*CanRMP_func[MBOXES])(Uint32 d0, Uint32 d1);
static void (*CanTA_func[MBOXES])(void);





/***************************************************************************
 * INIT_CAN_BTC()
 *
 * Initialize the CAN bit timing control register.  This function calculates
 * the proper bit timings in time quanta based on a requested baud rate (kHz),
 * bit time (TQ), sampling point (percent*100), and sychronization jump
 * width (TQ).  If there is no possible configuration, the return is <0.
 *
 * For verification, see: http://www.port.de/engl/canprod/sv_req_form.html
 ***************************************************************************/

/*
try to choose the "best" bit timing register settings...

baud = baud rate (kHz)
opt_bt = optimal bit timing (time quantums)
opt_sp = optimal sampling point (percent*100)
sjw = synchro jump width (time quantums)

For verification, see: http://www.port.de/engl/canprod/sv_req_form.html
*/

/* register limits (actual value is 1 greater) */
#define TSEG1_MIN			3
#define TSEG1_MAX			16
#define TSEG2_MIN			2
#define TSEG2_MAX			8
#define BRP_MIN				0
#define BRP_MAX				255
#define CAN_SAM				1
#define BAUD_MAX			1000

#define COST_BAUD_UNDER		100
#define COST_BAUD_OVER		100
#define COST_BT_UNDER		10
#define COST_BT_OVER		15
#define COST_SP_UNDER		10
#define COST_SP_OVER		12

#define DEFAULT_BTC			0x0

static int32 init_can_btc(int32 baud, int16 opt_bt, int16 opt_sp, int16 sjw, struct ECAN_REGS *regs)
{
	int32 tseg, tseg1, tseg2, brp, bt;
	int32 baud_err, bt_err, sp_err;
	int32 cost, best_cost;
	int32 khz;
	int32 i;

	best_cost = INT_MAX;
	khz = SYSCLKOUT_KHZ;

	if (baud > BAUD_MAX)
		baud = BAUD_MAX;

	for (tseg=(TSEG1_MIN+1+TSEG2_MIN+1); tseg<=(TSEG1_MAX+1+TSEG2_MAX+1); tseg++) {

		/* search one time quantum above and below sample point */
		for (i = -1; i <= 1; i++) {

			/* calculate bit timing for given segment length in TQ */
			tseg1 = opt_sp*(tseg+sjw)/100 - sjw + i;
			tseg2 = tseg - tseg1;
			bt = tseg1 + tseg2 + sjw;

			/* eliminate illegal combinations */
			if (tseg1 < TSEG1_MIN || tseg1 > TSEG1_MAX) continue;
			if (tseg2 < TSEG2_MIN || tseg2 > TSEG2_MAX) continue;
			if (tseg1 < tseg2) continue;
			if (sjw > tseg2) continue;

			/* calculate baud rate prescaler */
			brp = khz/baud/bt;
			if (brp < BRP_MIN+1 || brp > BRP_MAX+1) continue;

			/* calculate errors */
			baud_err = khz/brp/bt - baud;
			bt_err = bt - opt_bt;
			sp_err = 100*(tseg1+sjw)/bt - opt_sp;

			/* calculate cost of errors */
			cost = 0;
			cost += (baud_err < 0) ? -baud_err*COST_BAUD_UNDER : baud_err*COST_BAUD_OVER;
			cost += (bt_err < 0) ? -bt_err*COST_BT_UNDER : bt_err*COST_BT_OVER;
			cost += (sp_err < 0) ? -sp_err*COST_SP_UNDER : sp_err*COST_SP_OVER;

			if (cost <= best_cost) {
				best_cost = cost;

				/* store best configuration */
				regs->CANBTC.all = 0x0;
				regs->CANBTC.bit.TSEG2REG = tseg2-1;
				regs->CANBTC.bit.TSEG1REG = tseg1-1;
				regs->CANBTC.bit.SAM = CAN_SAM;
				regs->CANBTC.bit.SJWREG = sjw-1;
				regs->CANBTC.bit.BRPREG = brp-1;
			}
		}
	}

	if (best_cost >= INT_MAX || regs->CANBTC.bit.TSEG1REG == 0 || regs->CANBTC.bit.TSEG2REG == 0)
		return -1;

	return best_cost;
}










/***************************************************************************
 * INIT_CAN()
 *
 * Initialize the TMS320F28xx CAN controller.
 *
 * Parameters:
 *    baud = CAN bus baud rate (kHz)
 *    opt_bt = optimal bit time length (TQ)
 *    opt_sp = optimal sampling timing (percent*100)
 *    sjw = synchronization jump width (TQ)
 *    mode = select HECC (=1) or standard/SCC (=0) mode
 *
 * Return:
 *    rtn < 0 = initialization error
 ***************************************************************************/

int16 init_can(int32 baud, int16 opt_bt, int16 opt_sp, int16 sjw, bool mode)
{
	int32 i;

	struct ECAN_REGS ECanShadow;

	memset(&ECanShadow,0,sizeof(ECanShadow));

	/* Configure eCAN bit timings */
	if (init_can_btc(baud,opt_bt,opt_sp,sjw, &ECanShadow) < 0)
		return -1;

	/* Configure eCAN for HECC or SCC mode */
	ECanShadow.CANMC.bit.SCB = mode;

	/* Master Control Register */
	ECanShadow.CANMC.bit.DBO = 1;			// data byte order 0,1,2,3,4,5,6,7

	/* Global Interrupt Mask */
	ECanShadow.CANGIM.bit.I0EN = 1;		// 0   Interrupt 0 enable
	ECanShadow.CANGIM.bit.I1EN = 1;		// 1   Interrupt 1 enable
	ECanShadow.CANGIM.bit.GIL = 1;		// 2   Global Interrupt Level
	ECanShadow.CANGIM.bit.WLIM = 1;		// 8   Warning level interrupt mask
	ECanShadow.CANGIM.bit.EPIM = 1;		// 9   Error-passive interrupt mask
	ECanShadow.CANGIM.bit.BOIM = 1;		// 10  Bus-off interrupt mask
	ECanShadow.CANGIM.bit.RMLIM = 1;		// 11  Received message lost interrupt mask
	ECanShadow.CANGIM.bit.WUIM = 1;		// 12  Wakeup interrupt mask
	ECanShadow.CANGIM.bit.WDIM = 1;		// 13  Write denied interrupt mask
	ECanShadow.CANGIM.bit.AAIM = 1;		// 14  Abort Ack interrupt mask
	ECanShadow.CANGIM.bit.TCOM = 1;		// 16  TSC overflow interrupt mask
	ECanShadow.CANGIM.bit.MTOM = 1;		// 17  MBX Timeout interrupt mask

	for (i = 0; i < MBOXES; i++) {
		CanAA_func[i] = NULL;
		CanRML_func[i] = NULL;
		CanRMP_func[i] = NULL;
		CanTA_func[i] = NULL;

		(&ECanaMboxes.MBOX0+i)->MSGCTRL.all = 0x00000000;
	}

	EALLOW;

	/* Configure eCAN pins using GPIO regs*/
	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;
	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;
	/* Configure eCAN RX and TX pins for eCAN transmissions using eCAN regs*/
	ECanaRegs.CANTIOC.bit.TXFUNC = 1;
	ECanaRegs.CANRIOC.bit.RXFUNC = 1;

	/* Interrupt Callback Functions */
#ifndef DSP28_BIOS
	PieVectTable.ECAN0INTA = &ECAN0INTA_mbox_cb;
	PieVectTable.ECAN1INTA = &ECAN1INTA_err_cb;
#endif

	/* Request configuration mode */
	ECanaRegs.CANMC.bit.CCR = 1;
	while (ECanaRegs.CANES.bit.CCE != 1) {}

	/* Configure eCAN bit timings */
	ECanaRegs.CANBTC.all = ECanShadow.CANBTC.all;

	/* Initialize MCR and mailboxes */
	ECanaRegs.CANMC.all = ECanShadow.CANMC.all;

	/* Leave configuration mode */
	while (ECanaRegs.CANES.bit.CCE != 1) {}

	/* Clear all TAn bits */
	ECanaRegs.CANTA.all	= 0xFFFFFFFF;
	ECanaRegs.CANTRR.all = 0xFFFFFFFF;

	/* Clear all RMPn bits */
	ECanaRegs.CANRMP.all = 0xFFFFFFFF;

	/* Global interrupts */
	ECanaRegs.CANGIM.all = ECanShadow.CANGIM.all;

	/* Mailbox Enable: disable all mailboxes */
	ECanaRegs.CANME.all = 0x0;

	/* Mailbox Interrupt Mask: disable all mailbox interrupt masks*/
	ECanaRegs.CANMIM.all = 0x0;

	/* Mailbox Interrupt Levels (0=CAN0INT, 1=CAN1INT) */
	ECanaRegs.CANMIL.all = 0x0;

	/* Overwrite Protection Control (0=allow overwrite; 1=no overwrite) */
	ECanaRegs.CANOPC.all = 0x0;

	EDIS;

	/* Clear all interrupt flag bits */
	ECanaRegs.CANGIF0.all = 0xFFFFFFFF;
	ECanaRegs.CANGIF1.all = 0xFFFFFFFF;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
	PieCtrlRegs.PIEIER9.bit.INTx5 = 1;
	PieCtrlRegs.PIEIER9.bit.INTx6 = 1;
	IER |= M_INT9;

	return 0;
}


/***************************************************************************
 * UNINIT_CAN()
 *
 * Uninitialize the TMS320F28xx CAN controller.
 ***************************************************************************/
void uninit_can(void)
{
	/* transmission request reset */
	ECanaRegs.CANTRR.all = 0xFFFFFFFF;

	/* disable interrupts */
	PieCtrlRegs.PIEIER9.bit.INTx5 = 0;
	PieCtrlRegs.PIEIER9.bit.INTx6 = 0;
	EALLOW;
	ECanaRegs.CANGIM.all = 0x0;

	EDIS;
}


/***************************************************************************
 * MBOX_SET_ID()
 *
 * Set mailbox identification.  For standard identifier (11-bit), set
 * ide=0.  Extended identifers are 29-bits.
 ***************************************************************************/

void mbox_set_id(enum mbox_e mbox, Uint32 id, bool ide, bool ame)
{
	struct ECAN_REGS ECanaShadow;
	volatile struct MBOX *mboxes = &ECanaMboxes.MBOX0+mbox;

	/* mailbox must be disabled before changing id */
	ECanaShadow.CANME.all = ECanaRegs.CANME.all;
	ECanaShadow.CANME.all &= ~(1UL<<mbox);
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;

	/* configure mailbox id */
	mboxes->MSGID.all = 0x0;
	mboxes->MSGID.bit.AME = ame;	// acceptance mask enable bit
	mboxes->MSGID.bit.IDE = ide;	// identifier extension bit
	mboxes->MSGID.bit.EXTMSGID_L = (id >> 13) & 0xFFFF;		// ID 0:15
	mboxes->MSGID.bit.EXTMSGID_H = (id >> 11) & 0x0003;		// ID 16:17
	mboxes->MSGID.bit.STDMSGID = id & 0x7FFF;				// ID 18:28
}


/***************************************************************************
 * MBOX_GET_ID()
 *
 * Get mailbox identification.
 ***************************************************************************/

Uint32 mbox_get_id(enum mbox_e mbox)
{
	volatile struct MBOX *mboxes = &ECanaMboxes.MBOX0+mbox;
	Uint32 id;

	id =  (Uint32)(mboxes->MSGID.bit.EXTMSGID_L);			// ID 0:15
	id |= (Uint32)(mboxes->MSGID.bit.EXTMSGID_H) << 16;		// ID 16:17
	id |= (Uint32)(mboxes->MSGID.bit.STDMSGID) << 18;		// ID 18:28

	return id;
}

/***************************************************************************
 * MBOX_SET_RX()
 *
 * Configure mailbox for receive.
 ***************************************************************************/

void mbox_set_RX(enum mbox_e mbox, void (*func)(Uint32 d0, Uint32 d1))
{
	struct ECAN_REGS ECanaShadow;

	CanRMP_func[mbox] = func;

	/* Mailbox Direction (0=Transmit, 1=Receive) */
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
	ECanaShadow.CANMD.all |= 1UL<<mbox;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;
}


/***************************************************************************
 * MBOX_SET_TX()
 *
 * Configure mailbox for transmit.
 ***************************************************************************/

void mbox_set_TX(enum mbox_e mbox, void (*func)(void))
{
	struct ECAN_REGS ECanaShadow;

	CanTA_func[mbox] = func;

	/* Mailbox Direction (0=Transmit, 1=Receive) */
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
	ECanaShadow.CANMD.all &= ~(1UL<<mbox);
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;
}


/***************************************************************************
 * MBOX_SET_RTR()
 *
 * Configure mailbox for remote frame requests.  This function should be
 * called after the mailbox is configured for RX/TX.  If the mailbox is
 * configured for RX, the RTR bit is set, allowing sending remote frame
 * requests.  If the mailbox is configured for TX, the AAM (auto answer
 * mode) bit is set, allowing transmit mailboxes to reply to remote frame
 * requests.
 ***************************************************************************/

void mbox_set_RTR(enum mbox_e mbox)
{
	volatile struct MBOX *mboxes = &ECanaMboxes.MBOX0+mbox;
	struct ECAN_REGS ECanaShadow;

	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
	if (ECanaShadow.CANMD.all &= (1UL<<mbox) == 0) {	// transmit mailbox
		/* Auto Answer Mode */
		mboxes->MSGID.bit.AAM = 1;
	} else {											// receive mailbox
		/* Remote Transmission Request */
		mboxes->MSGCTRL.bit.RTR = 1;
	}
}


/***************************************************************************
 * MBOX_SET_AA()
 *
 * Set Abort Acknowledge callback function.
 ***************************************************************************/

void mbox_set_AA(enum mbox_e mbox, void (*func)(void))
{
	CanAA_func[mbox] = func;
}



/***************************************************************************
 * MBOX_SET_RML()
 *
 * Set Receive-Message-Lost callback function.
 ***************************************************************************/

void mbox_set_RML(enum mbox_e mbox, void (*func)(void))
{
	CanRML_func[mbox] = func;
}


/***************************************************************************
 * MBOX_SET_LAM()
 *
 * Set local acceptance mask. ~ This function sets the "don't care" bits of
 * the receive mailbox identifier.  Set LAMI=1 to accept both standard and
 * extended message ids, other use mbox settings.
 ***************************************************************************/
void mbox_set_LAM(enum mbox_e mbox, Uint32 lam, bool lami)
{
	volatile union CANLAM_REG *lamregs = &ECanaLAMRegs.LAM0+mbox;

	lamregs->all = lam & 0x1FFFFFFF;
	lamregs->bit.LAMI = lami;
}


/***************************************************************************
 * MBOX_ENABLE()
 *
 * Enable mailbox.  This function should be called after the mailbox has
 * been setup (identifier, RX/TX, etc.)
 ***************************************************************************/

void mbox_enable(enum mbox_e mbox)
{
	struct ECAN_REGS ECanaShadow;

	/* Mailbox Interrupt Mask */
	EALLOW;
	ECanaShadow.CANMIM.all = ECanaRegs.CANMIM.all;
	ECanaShadow.CANMIM.all |= 1UL<<mbox;
	ECanaRegs.CANMIM.all = ECanaShadow.CANMIM.all;
	EDIS;

	/* Mailbox Enable */
	ECanaShadow.CANME.all = ECanaRegs.CANME.all;
	ECanaShadow.CANME.all |= 1UL<<mbox;
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;
}


/***************************************************************************
 * MBOX_TXREADY()
 *
 * Check if mailbox is ready to send.  Returns TRUE if ready.
 ***************************************************************************/

bool mbox_txready(enum mbox_e mbox)
{
	if (ECanaRegs.CANTRS.all & (1UL<<mbox)) return FALSE;	// check TSR
	if (ECanaRegs.CANTRR.all & (1UL<<mbox)) return FALSE;	// check TRR
	return TRUE;
}


/***************************************************************************
 * MBOX_TXRESET()
 *
 * Request transmission reset.
 ***************************************************************************/

int16 mbox_txreset(enum mbox_e mbox)
{
	struct ECAN_REGS ECanaShadow;

	if (ECanaRegs.CANTRR.all & (1UL<<mbox)) return -1;	// check TRR

	ECanaShadow.CANTRR.all = ECanaRegs.CANTRR.all;
	ECanaShadow.CANTRR.all |= 1UL<<mbox;
	ECanaRegs.CANTRR.all = ECanaShadow.CANTRR.all;
	return 0;
}


/***************************************************************************
 * CAN_REQUEST()
 *
 * Send remote frame request.
 ***************************************************************************/

void can_request(enum mbox_e mbox)
{
	struct ECAN_REGS ECanaShadow;

	/* wait for write access to mailbox */
	while (!mbox_txready(mbox));

	/* Transmission-Request Set */
	ECanaShadow.CANTRS.all = ECanaRegs.CANTRS.all;
	ECanaShadow.CANTRS.all |= 1UL<<mbox;
	ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;
}


/***************************************************************************
 * MBOX_LOAD_MSG()
 *
 * Load message into a transmit mailbox.
 ***************************************************************************/

static void mbox_load_msg(enum mbox_e mbox, Uint32 d0, Uint32 d1, Uint16 len, Uint16 pri)
{
	volatile struct MBOX *mboxes = &ECanaMboxes.MBOX0+mbox;

	/* wait for write access to mailbox */
	while (!mbox_txready(mbox));

	mboxes->MSGCTRL.all = 0x0;
	mboxes->MSGCTRL.bit.DLC = len;
	mboxes->MSGCTRL.bit.TPL = pri;

	/* Mailbox Data Registers (Low and High) */
	mboxes->MDL.all = d0;
	mboxes->MDH.all = d1;
}


/***************************************************************************
 * MBOX_SEND()
 *
 * Send CAN message.
 ***************************************************************************/

void can_send(enum mbox_e mbox, Uint32 d0, Uint32 d1, Uint16 len, Uint16 pri)
{
	struct ECAN_REGS ECanaShadow;

	mbox_load_msg(mbox,d0,d1,len,pri);

	/* Transmission-Request Set */
	ECanaShadow.CANTRS.all = ECanaRegs.CANTRS.all;
	ECanaShadow.CANTRS.all |= 1UL<<mbox;
	ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;
}


/***************************************************************************
 * MBOX_SEND_STR()
 *
 * Send CAN message.
 ***************************************************************************/

void can_send_str(enum mbox_e mbox, char *data, Uint16 len, Uint16 pri)
{
	Uint32 d0 = 0;
	Uint32 d1 = 0;
	int16 i;

	if (len > 8) len = 8;
	for (i = 0; i < len; i++) {
		if (i < 4) {
			d0 |= (Uint32)(data[i] & 0xFF) << ((3-i)*8);
		} else {
			d1 |= (Uint32)(data[i] & 0xFF) << ((7-i)*8);
		}
	}
	can_send(mbox,d0,d1,len,pri);
}


/***************************************************************************
 * MBOX_UPDATE()
 *
 * Update data in mailbox.  This function is used to update the date
 * contained in an auto answer transmit mailbox or a mailbox for which the
 * TRS flag is set.
 ***************************************************************************/

void mbox_update(enum mbox_e mbox, Uint32 d0, Uint32 d1, Uint16 len, Uint16 pri)
{
	struct ECAN_REGS ECanaShadow;

	/* request data write access to mailbox mbox */
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.all &= ~(0x0003);
	ECanaShadow.CANMC.all |= 0x0100 + mbox;
	EALLOW;
	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
	EDIS;

	/* load new message */
	mbox_load_msg(mbox,d0,d1,len,pri);

	/* clear data write access */
	ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.all &= ~(0x0100 + 0x0003);
	ECanaShadow.CANMC.all |= mbox;
	EALLOW;
	ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
	EDIS;
}


/***************************************************************************
 * ECAN0INTA_MBOX_CB()
 *
 * eCAN Interrupt Level 0.  This interrupt function handles the receipt
 * and transmission of message objects (MIL=0).  The message timeout
 * interrupt is also handled (HECC mode).
 ***************************************************************************/
#ifndef USEJUST_INTERNAL_MEM
#pragma CODE_SECTION(ECAN0INTA_mbox_cb, "ramfuncs");
#endif
#if DSP28_BIOS
void ECAN0INTA_mbox_cb(void)
#else
interrupt void ECAN0INTA_mbox_cb(void)
#endif
{
	Uint16 mbox = ECanaRegs.CANGIF0.bit.MIV0;
	Uint32 mask = 1UL<<mbox;
	volatile struct MBOX *mboxes = &ECanaMboxes.MBOX0+mbox;

	/* Global Mailbox Interrupt Flag */
	if (ECanaRegs.CANGIF0.bit.GMIF0) {

		/* check Receive-Message-Pending flag */
		if (ECanaRegs.CANRMP.all & mask) {
			if (CanRMP_func[mbox]) CanRMP_func[mbox](mboxes->MDL.all,mboxes->MDH.all);
			ECanaRegs.CANRMP.all = mask;

		/* check Transmission-Acknowledge flag */
		} else if (ECanaRegs.CANTA.all & mask) {
			if (CanTA_func[mbox]) CanTA_func[mbox]();
			ECanaRegs.CANTA.all = mask;
		}
	}

	/* Mailbox Timeout Flag */
	if (ECanaRegs.CANGIF0.bit.MTOF0) {
	}

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}


/***************************************************************************
 * ECAN1INTA_ERR_CB()
 *
 * eCAN Interrupt Level 1.  This interrupt function handles error messages
 * (GIL=1).
 ***************************************************************************/
#ifndef USEJUST_INTERNAL_MEM
#pragma CODE_SECTION(ECAN1INTA_err_cb, "ramfuncs");
#endif
#if DSP28_BIOS
void ECAN1INTA_err_cb(void)
#else
interrupt void ECAN1INTA_err_cb(void)
#endif
{
	Uint32 mask;
	int16 i;

	/* Warning Level Interrupt flag */
	if (ECanaRegs.CANGIF1.bit.WLIF1) {
		ECanaRegs.CANGIF1.bit.WLIF1 = 1;
	}
	/* Error-Passive Interrupt flag */
	if (ECanaRegs.CANGIF1.bit.EPIF1) {
		ECanaRegs.CANGIF1.bit.EPIF1 = 1;
	}
	/* Bus-Off Interrupt flag */
	if (ECanaRegs.CANGIF1.bit.BOIF1) {
		ECanaRegs.CANGIF1.bit.BOIF1 = 1;
	}
	/* Receive-Message-Lost Interrupt flag */
	if (ECanaRegs.CANGIF1.bit.RMLIF1) {
		mask = 1UL;
		for (i = MBOXES-1; i >= 0; i--) {
			if (ECanaRegs.CANRML.all & mask) {
				if (CanRML_func[i]) CanRML_func[i]();
				ECanaRegs.CANRML.all = mask;
				break;
			}
			mask <<= 1;
		}
	}
	/* Wakeup Interrupt flag */
	if (ECanaRegs.CANGIF1.bit.WUIF1) {
		ECanaRegs.CANGIF1.bit.WUIF1 = 1;
	}
	/* Write Denied Interrupt flag */
	if (ECanaRegs.CANGIF1.bit.WDIF1) {
		ECanaRegs.CANGIF1.bit.WDIF1 = 1;
	}
	/* Abort Acknowledgement Interrupt flag */
	if (ECanaRegs.CANGIF1.bit.AAIF1) {
		mask = 1UL;
		for (i = MBOXES-1; i >= 0; i--) {
			if (ECanaRegs.CANAA.all & mask) {
				if (CanAA_func[i]) CanAA_func[i]();
				ECanaRegs.CANAA.all = mask;
				break;
			}
			mask <<= 1;
		}
	}
	/* TSC Overflow flag */
	if (ECanaRegs.CANGIF1.bit.TCOF1) {
		ECanaRegs.CANGIF1.bit.TCOF1 = 1;
	}

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

