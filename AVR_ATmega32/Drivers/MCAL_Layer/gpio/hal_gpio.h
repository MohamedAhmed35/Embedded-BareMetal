/*
 * hal_gpio.h
 *
 *  Created on: Aug 13, 2024
 *      Author: Mohammed
 */

#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

/* ----------------------------- Includes section --------------------------- */
#include "../mcal_std_types.h"

/* ----------------------------- Data type declarations --------------------- */
typedef enum {
	PIN_DIRECTION_INPUT,
	PIN_DIRECTION_OUTPUT
}pinDirection_t;
#
#
typedef enum {
	PORTA_INDEX = 0,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX
}portIndex_t;
#
#
typedef enum {
	PIN0_INDEX = 0,
	PIN1_INDEX = 1,
	PIN2_INDEX = 2,
	PIN3_INDEX = 3,
	PIN4_INDEX = 4,
	PIN5_INDEX = 6,
	PIN6_INDEX = 7
}pinIndex_t;
#
#
typedef enum {
	PIN_LOW,
	PIN_HIGH
}pinLogic_t;
#
#
typedef struct
{
	pinDirection_t pinDirection		:1;		/* @ref pinDirection_t  */
	portIndex_t	   portIndex		:2;		/* @ref	portIndex_t		*/
	pinIndex_t	   pinIndex			:3;		/* @ref pinIndex_t		*/
	uint8_t							:2;
}gpio_pinConfig_t;
/* ----------------------------- Macro declarations ------------------------- */
#define _BIT_MASK			(uint8) 0x1
#define PORT_PINS_MAX		8
#define PORT_MAX_NUM		4
#define PORT_MASK			0xFF

/* ----------------------------- Macro functions ---------------------------- */
#define BIT_MASK(BIT_POS)			((_BIT_MASK) << (BIT_POS))
#define SET_BIT(SFR, BIT_POS)		(SFR |= (BIT_MASK(BIT_POS)))
#define CLR_BIT(SFR, BIT_POS)		(SFR &= ~(BIT_MASK(BIT_POS)))
#define TOGGLE_BIT(SFR, BIT_POS)	(SFR ^= (BIT_MASK(BIT_POS)))
#define READ_BIT(SFR, BIT_POS)		((SFR >> (BIT_POS)) & (_BIT_MASK))


/* ----------------------------- Function declarations ---------------------- */
Std_ReturnType gpio_pinWriteDir(const gpio_pinConfig_t *pin_config, pinDirection_t pin_direction);
Std_ReturnType gpio_pinReadDir(const gpio_pinConfig_t *pin_config, pinDirection_t *pin_direction);
Std_ReturnType gpio_pinWriteLogic(const gpio_pinConfig_t *pin_config, pinLogic_t logic);
Std_ReturnType gpio_pinReadLogic(const gpio_pinConfig_t *pin_config, pinLogic_t *logic);
Std_ReturnType gpio_pinToggleLogic(const gpio_pinConfig_t *pin_config);

Std_ReturnType gpio_pinInitialize(const gpio_pinConfig_t *pin_config, pinLogic_t logic);
Std_ReturnType gpio_portWriteDir(portIndex_t port_index, uint8 direction);
Std_ReturnType gpio_portReadDir(portIndex_t port_index, uint8 *direction);
Std_ReturnType gpio_portWriteLogic(portIndex_t port_index, uint8 logic);
Std_ReturnType gpio_portReadLogic(portIndex_t port_index, uint8 *logic);
Std_ReturnType gpio_protToggleLogic(portIndex_t port_index);


#endif /* HAL_GPIO_H_ */
