/*
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 *  \file   GPIO_evmAM572x_board.c
 *
 *  \brief  AM572x GP EVM board specific GPIO parameters.
 *
 */

#include <stdio.h>
#include <ti/drv/gpio/GPIO.h>
#include <ti/csl/soc.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>

#define GPIO_USER0_LED_PIN_NUM    (0x08)
#define GPIO_USER0_LED_PORT_NUM   (0x07)

#define GPIO_USER1_LED_PIN_NUM    (0x09)
#define GPIO_USER1_LED_PORT_NUM   (0x07)

#define GPIO_DAN_LED0_PIN_NUM   (0x05)
#define GPIO_DAN_LED0_PORT_NUM  (0x02)

#define GPIO_DAN_LED1_PIN_NUM   (0x06)
#define GPIO_DAN_LED1_PORT_NUM  (0x02)

#define GPIO_DAN_LED2_PIN_NUM   (0x08)
#define GPIO_DAN_LED2_PORT_NUM  (0x02)

#define GPIO_DAN_LED3_PIN_NUM   (19)
#define GPIO_DAN_LED3_PORT_NUM  (0x02)

#define GPIO_DAN_LED4_PIN_NUM   (20)
#define GPIO_DAN_LED4_PORT_NUM  (0x02)

#define GPIO_DAN_LED5_PIN_NUM   (24)
#define GPIO_DAN_LED5_PORT_NUM  (0x02)



/* GPIO Driver board specific pin configuration structure */
GPIO_PinConfig gpioPinConfigs[8] = {
    /* Input pin with interrupt enabled : AM57X_IDK_GRN_LED */
    GPIO_DEVICE_CONFIG(GPIO_USER0_LED_PORT_NUM, GPIO_USER0_LED_PIN_NUM) |
    GPIO_CFG_IN_INT_RISING | GPIO_CFG_INPUT,

    /* Output pin : AM57X_IDK_YEL_LED */
    GPIO_DEVICE_CONFIG(GPIO_USER0_LED_PORT_NUM, GPIO_USER0_LED_PIN_NUM) |
    GPIO_CFG_OUTPUT,

    /* Output pin : P2_5 */
    GPIO_DEVICE_CONFIG(GPIO_DAN_LED0_PORT_NUM, GPIO_DAN_LED0_PIN_NUM) |
    GPIO_CFG_OUTPUT,

    /* Output pin : P2_5 */
    GPIO_DEVICE_CONFIG(GPIO_DAN_LED1_PORT_NUM, GPIO_DAN_LED1_PIN_NUM) |
    GPIO_CFG_OUTPUT,

    /* Output pin : P2_5 */
    GPIO_DEVICE_CONFIG(GPIO_DAN_LED2_PORT_NUM, GPIO_DAN_LED2_PIN_NUM) |
    GPIO_CFG_OUTPUT,

    /* Output pin : P2_5 */
    GPIO_DEVICE_CONFIG(GPIO_DAN_LED3_PORT_NUM, GPIO_DAN_LED3_PIN_NUM) |
    GPIO_CFG_OUTPUT,

    /* Output pin : P2_5 */
    GPIO_DEVICE_CONFIG(GPIO_DAN_LED4_PORT_NUM, GPIO_DAN_LED4_PIN_NUM) |
    GPIO_CFG_OUTPUT,

    /* Output pin : P2_5 */
    GPIO_DEVICE_CONFIG(GPIO_DAN_LED5_PORT_NUM, GPIO_DAN_LED5_PIN_NUM) |
    GPIO_CFG_OUTPUT
};

/* GPIO Driver call back functions */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/* GPIO Driver configuration structure */
GPIO_v1_Config GPIO_v1_config = {
    gpioPinConfigs,
    gpioCallbackFunctions,
    sizeof(gpioPinConfigs) / sizeof(GPIO_PinConfig),
    sizeof(gpioCallbackFunctions) / sizeof(GPIO_CallbackFxn),
    0x20,
    };
