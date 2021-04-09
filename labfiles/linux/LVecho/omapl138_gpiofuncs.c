#include "omapl138_gpiofuncs.h"

unsigned long GPIO_setDir(volatile GPIOregs *mygpio, unsigned long in_bank, unsigned long in_pin_num, unsigned char in_dir)
{
	unsigned long rtn = ERR_INVALID_PARAMETER;
	
	if ((in_bank < MAX_GPIO_BANK_NUM) && (in_pin_num < MAX_GPIO_PIN_NUM))
	{
		switch(in_bank)
		{
			case GPIO_BANK0:
				if (in_dir) 
				{
					mygpio->dir01 |= in_pin_num;
				}
				else
				{
					mygpio->dir01 &= ~in_pin_num;
				}
				break;

			case GPIO_BANK1:
				if (in_dir) 
				{
					mygpio->dir01 |= (in_pin_num<<0x10);
				}
				else
				{
					mygpio->dir01 &= ~(in_pin_num<<0x10);
				}
				break;

			case GPIO_BANK2:
				if (in_dir) 
				{
					mygpio->dir23 |= in_pin_num;
				}
				else
				{
					mygpio->dir23 &= ~in_pin_num;
				}
				break;

			case GPIO_BANK3:
				if (in_dir) 
				{
					mygpio->dir23 |= (in_pin_num<<0x10);
				}
				else
				{
					mygpio->dir23 &= ~(in_pin_num<<0x10);
				}
				break;

			case GPIO_BANK4:
				if (in_dir) 
				{
					mygpio->dir45 |= in_pin_num;
				}
				else
				{
					mygpio->dir45 &= ~in_pin_num;
				}
				break;

			case GPIO_BANK5:
				if (in_dir) 
				{
					mygpio->dir45 |= (in_pin_num<<0x10);
				}
				else
				{
					mygpio->dir45 &= ~(in_pin_num<<0x10);
				}
				break;

			case GPIO_BANK6:
				if (in_dir) 
				{
					mygpio->dir67 |= in_pin_num;
				}
				else
				{
					mygpio->dir67 &= ~in_pin_num;
				}
				break;

			case GPIO_BANK7:
				if (in_dir) 
				{
					mygpio->dir67 |= (in_pin_num<<0x10);
				}
				else
				{
					mygpio->dir67 &= ~(in_pin_num<<0x10);
				}
				break;
		
			case GPIO_BANK8:
				if (in_dir) 
				{
					mygpio->dir8 |= in_pin_num;
				}
				else
				{
					mygpio->dir8 &= ~in_pin_num;
				}
				break;
		}
		rtn = ERR_NO_ERROR;
	}
	return (rtn);
}

unsigned long GPIO_setOutput(volatile GPIOregs *mygpio, unsigned long in_bank, unsigned long in_pin_num, unsigned char in_dir)
{
	unsigned long rtn = ERR_INVALID_PARAMETER;
	
	if ((in_bank < MAX_GPIO_BANK_NUM) && (in_pin_num < MAX_GPIO_PIN_NUM))
	{
		switch(in_bank)
		{
			case GPIO_BANK0:
				if (in_dir) 
				{
					mygpio->out_data01 |= in_pin_num;
				}
				else
				{
					mygpio->out_data01 &= ~in_pin_num;
				}
				break;

			case GPIO_BANK1:
				if (in_dir) 
				{
					mygpio->out_data01 |= (in_pin_num<<0x10);
				}
				else
				{
					mygpio->out_data01 &= ~(in_pin_num<<0x10);
				}
				break;

			case GPIO_BANK2:
				if (in_dir) 
				{
					mygpio->out_data23 |= in_pin_num;
				}
				else
				{
					mygpio->out_data23 &= ~in_pin_num;
				}
				break;

			case GPIO_BANK3:
				if (in_dir) 
				{
					mygpio->out_data23 |= (in_pin_num<<0x10);
				}
				else
				{
					mygpio->out_data23 &= ~(in_pin_num<<0x10);
				}
				break;

			case GPIO_BANK4:
				if (in_dir) 
				{
					mygpio->out_data45 |= in_pin_num;
				}
				else
				{
					mygpio->out_data45 &= ~in_pin_num;
				}
				break;

			case GPIO_BANK5:
				if (in_dir) 
				{
					mygpio->out_data45 |= (in_pin_num<<0x10);
				}
				else
				{
					mygpio->out_data45 &= ~(in_pin_num<<0x10);
				}
				break;

			case GPIO_BANK6:
				if (in_dir) 
				{
					mygpio->out_data67 |= in_pin_num;
				}
				else
				{
					mygpio->out_data67 &= ~in_pin_num;
				}
				break;

			case GPIO_BANK7:
				if (in_dir) 
				{
					mygpio->out_data67 |= (in_pin_num<<0x10);
				}
				else
				{
					mygpio->out_data67 &= ~(in_pin_num<<0x10);
				}
				break;
		
			case GPIO_BANK8:
				if (in_dir) 
				{
					mygpio->out_data8 |= in_pin_num;
				}
				else
				{
					mygpio->out_data8 &= ~in_pin_num;
				}
				break;
		}
		rtn = ERR_NO_ERROR;
	}
	return (rtn);
}

unsigned long GPIO_getInput(volatile GPIOregs *mygpio, unsigned long in_bank, unsigned long in_pin_num)
{
	unsigned long rtn = ERR_INVALID_PARAMETER;
	
	if ((in_bank < MAX_GPIO_BANK_NUM) && (in_pin_num < MAX_GPIO_PIN_NUM))
	{
		switch(in_bank)
		{
			case GPIO_BANK0:
				if ((mygpio->in_data01 & in_pin_num) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK1:
				if ((mygpio->in_data01 & (in_pin_num<<0x10)) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK2:
				if ((mygpio->in_data23 & in_pin_num) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK3:
				if ((mygpio->in_data23 & (in_pin_num<<0x10)) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK4:
				if ((mygpio->in_data45 & in_pin_num) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK5:
				if ((mygpio->in_data45 & (in_pin_num<<0x10)) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK6:
				if ((mygpio->in_data67 & in_pin_num) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK7:
				if ((mygpio->in_data67 & (in_pin_num<<0x10)) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;
		
			case GPIO_BANK8:
				if ((mygpio->in_data8 & in_pin_num) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;
		}
	}
	return (rtn);
}

unsigned long GPIO_getOutput(volatile GPIOregs *mygpio, unsigned long in_bank, unsigned long in_pin_num)
{
	unsigned long rtn = ERR_INVALID_PARAMETER;
	
	if ((in_bank < MAX_GPIO_BANK_NUM) && (in_pin_num < MAX_GPIO_PIN_NUM))
	{
		switch(in_bank)
		{
			case GPIO_BANK0:
				if ((mygpio->out_data01 & in_pin_num) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK1:
				if ((mygpio->out_data01 & (in_pin_num<<0x10)) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK2:
				if ((mygpio->out_data23 & in_pin_num) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK3:
				if ((mygpio->out_data23 & (in_pin_num<<0x10)) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK4:
				if ((mygpio->out_data45 & in_pin_num) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK5:
				if ((mygpio->out_data45 & (in_pin_num<<0x10)) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK6:
				if ((mygpio->out_data67 & in_pin_num) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;

			case GPIO_BANK7:
				if ((mygpio->out_data67 & (in_pin_num<<0x10)) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;
		
			case GPIO_BANK8:
				if ((mygpio->out_data8 & in_pin_num) > 0) 
				{
					rtn = 1;
				}
				else
				{
					rtn = 0;
				}
				break;
		}
	}
	return (rtn);
}

unsigned long GPIO_toggleBit(volatile GPIOregs *mygpio, unsigned long in_bank, unsigned long in_pin_num)
{
	unsigned long rtn = ERR_INVALID_PARAMETER;
	
	if ((in_bank < MAX_GPIO_BANK_NUM) && (in_pin_num < MAX_GPIO_PIN_NUM))
	{
		switch(in_bank)
		{
			case GPIO_BANK0:
				if ((mygpio->out_data01 & in_pin_num) > 0) 
				{
					mygpio->out_data01 &= ~in_pin_num;
				}
				else
				{
					mygpio->out_data01 |= in_pin_num;
				}
				break;

			case GPIO_BANK1:
				if ((mygpio->out_data01 & (in_pin_num<<0x10)) > 0) 
				{
					mygpio->out_data01 &= ~(in_pin_num<<0x10);
				}
				else
				{
					mygpio->out_data01 |= (in_pin_num<<0x10);
				}
				break;

			case GPIO_BANK2:
				if ((mygpio->out_data23 & in_pin_num) > 0) 
				{
					mygpio->out_data23 &= ~in_pin_num;
				}
				else
				{
					mygpio->out_data23 |= in_pin_num;
				}
				break;

			case GPIO_BANK3:
				if ((mygpio->out_data23 & (in_pin_num<<0x10)) > 0) 
				{
					mygpio->out_data23 &= ~(in_pin_num<<0x10);
				}
				else
				{
					mygpio->out_data23 |= (in_pin_num<<0x10);
				}
				break;

			case GPIO_BANK4:
				if ((mygpio->out_data45 & in_pin_num) > 0) 
				{
					mygpio->out_data45 &= ~in_pin_num;
				}
				else
				{
					mygpio->out_data45 |= in_pin_num;
				}
				break;

			case GPIO_BANK5:
				if ((mygpio->out_data45 & (in_pin_num<<0x10)) > 0) 
				{
					mygpio->out_data45 &= ~(in_pin_num<<0x10);
				}
				else
				{
					mygpio->out_data45 |= (in_pin_num<<0x10);
				}
				break;

			case GPIO_BANK6:
				if ((mygpio->out_data67 & in_pin_num) > 0) 
				{
					mygpio->out_data67 &= ~in_pin_num;
				}
				else
				{
					mygpio->out_data67 |= in_pin_num;
				}
				break;

			case GPIO_BANK7:
				if ((mygpio->out_data67 & (in_pin_num<<0x10)) > 0) 
				{
					mygpio->out_data67 &= ~(in_pin_num<<0x10);
				}
				else
				{
					mygpio->out_data67 |= (in_pin_num<<0x10);
				}
				break;
		
			case GPIO_BANK8:
				if ((mygpio->out_data8 & in_pin_num) > 0) 
				{
					mygpio->out_data8 &= ~in_pin_num;
				}
				else
				{
					mygpio->out_data8 |= in_pin_num;
				}
				break;
		}
		rtn = ERR_NO_ERROR;
	}
	return (rtn);
}
