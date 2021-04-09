//-----------------------------------------------------------------------------
// \file    evmomapl138_raster.c
// \brief   implementation of the raster LCD driver for the OMAP-L138 EVM.
//
//-----------------------------------------------------------------------------
#include "stdio.h"
#include "evmomapl138.h"
#include "evmomapl138_timer.h"
#include "evmomapl138_gpio.h"
#include "evmomapl138_lcdc.h"
#include "evmomapl138_lcd_raster.h"

//-----------------------------------------------------------------------------
// Private Defines and Macros
//-----------------------------------------------------------------------------
#define PINMUX_LCD_D_BUS_0_REG      16
#define PINMUX_LCD_D_BUS_1_REG      17
#define PINMUX_LCD_D_BUS_2_REG      18
#define PINMUX_LCD_CONTROL_0_REG    18
#define PINMUX_LCD_CONTROL_1_REG    19

#define PINMUX_LCD_D_BUS_0_MASK     (0xFFFFFF00)
#define PINMUX_LCD_D_BUS_1_MASK     (0xFFFFFFFF)
#define PINMUX_LCD_D_BUS_2_MASK     (0x000000FF)
#define PINMUX_LCD_CONTROL_0_MASK   (0xFF000000)
#define PINMUX_LCD_CONTROL_1_MASK   (0x000000FF)

#define PINMUX_LCD_D_BUS_0_VALUE    (0x22222200)
#define PINMUX_LCD_D_BUS_1_VALUE    (0x22222222)
#define PINMUX_LCD_D_BUS_2_VALUE    (0x00000022)
#define PINMUX_LCD_CONTROL_0_VALUE  (0x22000000)
#define PINMUX_LCD_CONTROL_1_VALUE  (0x02000022)

#define PINMUX_LCD_PWR_0_REG        (5)
#define PINMUX_LCD_PWR_0_MASK       (0x0000000F)
#define PINMUX_LCD_PWR_0_VALUE      (0x00000008)

#define PINMUX_LCD_PWR_1_REG        (18)
#define PINMUX_LCD_PWR_1_MASK       (0xF0000000)
#define PINMUX_LCD_PWR_1_VALUE      (0x80000000)

#define PINMUX_LCD_PWR_1_REG_B 		(5)				//
#define PINMUX_LCD_PWR_1_MASK_B		(0xF0000000)	// Pinmux defs for beta 
#define PINMUX_LCD_PWR_1_VALUE_B	(0x80000000)	// 


#define LCD_PWR_GPIO_BANK              (2)      //BETA (2) Alpha (8)
#define LCD_PWR_GPIO_PIN               (8)     //BETA (8) Alpha (10)
#define LCD_BACKLIGHT_PWR_GPIO_BANK    (2)
#define LCD_BACKLIGHT_PWR_GPIO_PIN     (15)

//-----------------------------------------------------------------------------
// Private Function Prototypes
//-----------------------------------------------------------------------------
static uint32_t raster_config(void);
static uint32_t enable_lcdc(void);
static uint32_t disable_lcdc(void);
static uint32_t disable_lcd_power(void);
static uint32_t disable_lcd_backlight(void);
static uint32_t enable_lcd_power(void);
static uint32_t enable_lcd_backlight(void);

//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// \brief   initialize the lcd controller for raster use.
//
// \param   none.
//
// \return  uint32_t
//    ERR_NO_ERROR - everything is ok...lcdc ready to use.
//    ERR_INIT_FAIL - something happened during initialization.
//-----------------------------------------------------------------------------
uint32_t RASTER_init(void)
{
   uint32_t rtn = ERR_NO_ERROR;

   /* Set MUX_MODE on UI GPIO expander to LCD */
   EVMOMAPL138_pinmuxConfig(PINMUX_LCD_D_BUS_0_REG, PINMUX_LCD_D_BUS_0_MASK, PINMUX_LCD_D_BUS_0_VALUE);
   EVMOMAPL138_pinmuxConfig(PINMUX_LCD_D_BUS_1_REG, PINMUX_LCD_D_BUS_1_MASK, PINMUX_LCD_D_BUS_1_VALUE);
   EVMOMAPL138_pinmuxConfig(PINMUX_LCD_D_BUS_2_REG, PINMUX_LCD_D_BUS_2_MASK, PINMUX_LCD_D_BUS_2_VALUE);
   EVMOMAPL138_pinmuxConfig(PINMUX_LCD_CONTROL_0_REG, PINMUX_LCD_CONTROL_0_MASK, PINMUX_LCD_CONTROL_0_VALUE);
   EVMOMAPL138_pinmuxConfig(PINMUX_LCD_CONTROL_1_REG, PINMUX_LCD_CONTROL_1_MASK, PINMUX_LCD_CONTROL_1_VALUE);

   // configure the gpio pins used for lcd and backlight power.
   EVMOMAPL138_pinmuxConfig(PINMUX_LCD_PWR_0_REG, PINMUX_LCD_PWR_0_MASK, PINMUX_LCD_PWR_0_VALUE);
   EVMOMAPL138_pinmuxConfig(PINMUX_LCD_PWR_1_REG_B, PINMUX_LCD_PWR_1_MASK_B, PINMUX_LCD_PWR_1_VALUE_B);
   GPIO_setDir(LCD_PWR_GPIO_BANK, LCD_PWR_GPIO_PIN, GPIO_OUTPUT);
   GPIO_setDir(LCD_BACKLIGHT_PWR_GPIO_BANK, LCD_BACKLIGHT_PWR_GPIO_PIN, GPIO_OUTPUT);

   // enable power and setup lcdc.
   enable_lcdc();
   raster_config();
   
   // power down the display kit.
   disable_lcd_backlight();
   disable_lcd_power();
 //  #warn Dan Block changed from 300000 to 600000
   USTIMER_delay(600000);

   disable_lcdc();
//   #warn Dan Block changed from 100000 to 200000  
   USTIMER_delay(200000);
   
   // power-up the display kit following the correct sequence.
   enable_lcd_power();
   enable_lcdc();
//   #warn Dan Block changed from 300000 to 600000
   USTIMER_delay(600000);
   enable_lcd_backlight();

   return (rtn);
}

//-----------------------------------------------------------------------------
// \brief   plot an x, y pixel on the graphics LCD.
//
// \param   uint16_t x - .
//
// \param   uint16_t y - .
//
// \param   uint16_t pixel_data - .
//
// \return  none.
//-----------------------------------------------------------------------------
void RASTER_plot(uint16_t x, uint16_t y, uint16_t pixel_data)
{
// Dan try
//   *((uint8_t *)(FRAMEBUF_BASE + 32 + y * (LCD_WIDTH * 2) + (x << 1))) = pixel_data;
//   *((uint8_t *)(FRAMEBUF_BASE + 32 + y * (LCD_WIDTH * 2) + (x << 1)+1)) = pixel_data>>8;
   *((uint16_t *)(FRAMEBUF_BASE + 32 + y * (LCD_WIDTH * 2) + (x << 1))) = pixel_data;   
}

//-----------------------------------------------------------------------------
// \brief   clear the graphics LCD to the input color.
//
// \param   uint16_t color - .
//
// \return  none.
//-----------------------------------------------------------------------------
void RASTER_clear(uint16_t color)
{
   uint32_t x, y;

   // Paint the background
   for (x = 0; x < LCD_WIDTH; x++)
      for (y = 0; y < LCD_HEIGHT; y++)
         RASTER_plot(x, y, color);
}

//-----------------------------------------------------------------------------
// Private Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
uint32_t raster_config( void )
{
   uint32_t x;
   uint16_t *pdata;

   /*
   *  LCD Panel
   */
   LCDC->RASTER_CTRL       &= 0xfffffffe;         // Turn raster controller off

   LCDC->LCD_STAT           = 0x000003ff;         // Clear status bits

#ifdef DISPLAY_3_6
    // 18.75 MHz, raster mode pixel clock, 320 x 240 viewable frame
   LCDC->LCD_CTRL           = 0x00001101;		// PCLK = 150MHz / 8 = 8.824 MHz, raster mode
   LCDC->RASTER_TIMING_0    = (0x14 << 24)
   								| (0x14 << 16)
   								| (0x14 << 10)
   								| (0x13 << 4);	// HBP = 0x14; HFP = 0x14; HSW = 0x14; PPL = 0x13
   LCDC->RASTER_TIMING_1    = (0x03 << 24) 
   								| (0x03 << 16) 
   								| (0x02 << 10) 
   								| (0xEF);		// VBP = 0x3; VFP = 0x3; VSW = 0x2: LPP = 0xEF;  
   LCDC->RASTER_TIMING_2    = 0x02700000;
#endif



#ifdef DISPLAY_4_3
   // 8.824 MHz, raster mode pixel clock, 480 x 272 viewable frame
//   LCDC->LCD_CTRL           = 0x00001101;    	 // PCLK = 150MHz / 17 = 8.824 MHz, raster mode
//#warn DAN BLOCK changed 3/22/10 from "/17" to /34  LCD looks like it behaves better 
// This also seems to work well.
   LCDC->LCD_CTRL           = 0x00001401;    	 // PCLK = 150MHz / 17 = 8.824 MHz, raster mode
//   LCDC->LCD_CTRL           = 0x00002201;    	 // PCLK = 150MHz / 17 = 8.824 MHz, raster mode
   LCDC->RASTER_TIMING_0    = (0x01 << 24)
   								| (0x02 <<16)
   								| (0x29 << 10)
   								| (0x1D << 4);	// HBP = 0x01; HFP = 0x02; HSW = 0x29; PPL = 0x1D
   LCDC->RASTER_TIMING_1    = (0x03 << 24)
   								| (0x02 << 16)
   								| (0x0A << 10)
   								| (0x10F);		// VBP = 0x3; VFP = 0x2; VSW = 0xA: LPP = 0x10F;
   LCDC->RASTER_TIMING_2    = 0x02700000;

/*  Tried different timing no help with red edges
   LCDC->RASTER_TIMING_0    = (0x00 << 24)
   								| (0x00 <<16)
   								| (0xA << 10)
   								| (0x1D << 4);	// HBP = 0x01; HFP = 0x02; HSW = 0x29; PPL = 0x1D
   LCDC->RASTER_TIMING_1    = (0x00 << 24)
   								| (0x00 << 16)
   								| (0x02 << 10)
   								| (0x10F);		// VBP = 0x3; VFP = 0x2; VSW = 0xA: LPP = 0x10F;
   LCDC->RASTER_TIMING_2    = 0x02700000;
*/
#endif

#ifdef DISPLAY_6_4
   // 18.75 MHz, raster mode pixel clock, 640 x 480 viewable frame
   LCDC->LCD_CTRL           = 0x00000801;		// PCLK = 150MHz / 8 = 18.75 MHz, raster mode
   LCDC->RASTER_TIMING_0    = (0x19 << 24)
   								| (0x89 << 16)
   								| (0x31 << 10)
   								| (0x27 << 4);	// HBP = 0x19; HFP = 0x89; HSW = 0x31; PPL = 0x27
   LCDC->RASTER_TIMING_1    = (0x1F << 24)
   								| (0x20 <<16)
   								| (0x02 <<10)
   								| (0x1DF);		// VBP = 0x1F; VFP = 0x20; VSW = 0x2: LPP = 0x1DF;
   LCDC->RASTER_TIMING_2    = 0x02700000;
#endif

   LCDC->LCDDMA_CTRL        = 0x00000020;

   LCDC->LCDDMA_FB0_BASE    = FRAMEBUF_BASE;  	 // Frame buffer start
   LCDC->LCDDMA_FB0_CEILING = FRAMEBUF_BASE + (32 + (LCD_WIDTH * LCD_HEIGHT * 2) - 2); // Frame buffer end
//   LCDC->RASTER_CTRL        = 0x01000080;         // 6-5-6 mode,
   LCDC->RASTER_CTRL        = 0x00000080;         // 6-5-6 mode,
   LCDC->RASTER_CTRL       |= 0x00000001;         // Enable controller

   /* Palette */
   pdata = (uint16_t *)FRAMEBUF_BASE;
   *pdata++ = 0x4000;
   for (x = 0; x < 15; x++)
      *pdata++ = 0x0000;

   return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
uint32_t enable_lcdc( void )
{
   /* Enable the LCD Hardware */
   EVMOMAPL138_lpscTransition(PSC1, DOMAIN0, LPSC_LCDC, PSC_ENABLE);
   
   return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
uint32_t disable_lcdc( void )
{
   /* Disable the LCD Hardware */
   EVMOMAPL138_lpscTransition(PSC1, DOMAIN0, LPSC_LCDC, PSC_DISABLE);

   return (ERR_NO_ERROR);
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
uint32_t disable_lcd_power( void )
{
   return (GPIO_setOutput(LCD_PWR_GPIO_BANK, LCD_PWR_GPIO_PIN, OUTPUT_LOW));
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
uint32_t disable_lcd_backlight( void )
{
   return (GPIO_setOutput(LCD_BACKLIGHT_PWR_GPIO_BANK, LCD_BACKLIGHT_PWR_GPIO_PIN, OUTPUT_LOW));
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
uint32_t enable_lcd_power( void )
{
   uint32_t i;

   GPIO_setOutput(LCD_PWR_GPIO_BANK, LCD_PWR_GPIO_PIN, OUTPUT_HIGH);

   /* For 4.3" display, we need a few ms before we turn on backlight, or */
   /* the display panel logic goes out to lunch.                         */
   for (i = 0; i < 300; i++)
//   #warn Dan Block changed from 1000 to 2000
      USTIMER_delay(2000);

   return(ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
uint32_t enable_lcd_backlight( void )
{
   return (GPIO_setOutput(LCD_BACKLIGHT_PWR_GPIO_BANK, LCD_BACKLIGHT_PWR_GPIO_PIN, OUTPUT_HIGH));
}

