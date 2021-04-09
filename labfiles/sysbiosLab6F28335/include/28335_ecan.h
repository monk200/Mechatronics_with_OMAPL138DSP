/* ECAN.H: This code is designed to act as a low-level eCAN driver for
	higher-level programming.  One should initialize the eCAN module
	in the following order: init_can(), mbox_set_id(), mbox_set_TX/RX(),
	mbox_enable().

	WRITTEN BY : Paul Miller <pamiller@uiuc.edu>
	$Id: ecan.h,v 1.2 2003/08/08 18:50:32 paul Exp $
*/

#ifndef __28335_ECAN_H__
#define __28335_ECAN_H__

#include <coecsl.h>

#define CANMODE_ECAN		1
#define CANMODE_SCC			0


enum mbox_e {
	MBOX0		= 0,
	MBOX1,
	MBOX2,
	MBOX3,
	MBOX4,
	MBOX5,
	MBOX6,
	MBOX7,
	MBOX8,
	MBOX9,
	MBOX10,
	MBOX11,
	MBOX12,
	MBOX13,
	MBOX14,
	MBOX15,
	MBOX16,
	MBOX17,
	MBOX18,
	MBOX19,
	MBOX20,
	MBOX21,
	MBOX22,
	MBOX23,
	MBOX24,
	MBOX25,
	MBOX26,
	MBOX27,
	MBOX28,
	MBOX29,
	MBOX30,
	MBOX31,
	MBOXES
};


int16 init_can(int32 baud, int16 opt_bt, int16 opt_sp, int16 sjw, bool mode);
void uninit_can(void);

void mbox_set_id(enum mbox_e mbox, Uint32 id, bool ide, bool ame);
Uint32 mbox_get_id(enum mbox_e mbox);
void mbox_set_RX(enum mbox_e mbox, void (*func)(Uint32 d0, Uint32 d1));
void mbox_set_TX(enum mbox_e mbox, void (*func)(void));
void mbox_set_RTR(enum mbox_e mbox);
void mbox_set_AA(enum mbox_e mbox, void (*func)(void));
void mbox_set_RML(enum mbox_e mbox, void (*func)(void));
void mbox_set_LAM(enum mbox_e mbox, Uint32 lam, bool lami);
void mbox_enable(enum mbox_e mbox);
bool mbox_txready(enum mbox_e mbox);
int16 mbox_txreset(enum mbox_e mbox);
void can_request(enum mbox_e mbox);
void can_send(enum mbox_e mbox, Uint32 d0, Uint32 d1, Uint16 len, Uint16 pri);
void can_send_str(enum mbox_e mbox, char *data, Uint16 len, Uint16 pri);
void mbox_update(enum mbox_e mbox, Uint32 d0, Uint32 d1, Uint16 len, Uint16 pri);

#define can_send_int8(MBOX,DATA,PRI)	can_send(MBOX,(Uint32)(DATA)<<24,0x0,0x1,PRI)
#define can_send_int16(MBOX,DATA,PRI)	can_send(MBOX,(Uint32)(DATA)<<16,0x0,0x2,PRI)
#define can_send_int32(MBOX,DATA,PRI)	can_send(MBOX,DATA,0x0,0x4,PRI)

#endif /* __2812_ECAN_H__ */
