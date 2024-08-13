/*
 * hal_gpio.c
 *
 *  Created on: Aug 13, 2024
 *      Author: Mohammed
 */

#include "hal_gpio.h"


volatile uint8 *dir_registers[] = {&DDRA, &DDRB, &DDRC, &DDRD};
volatile uint8 *output_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD};
volatile uint8 *input_registers[] = {&PINA, &PINB, &PINC, &PIND};


/**
 * @brief 	Resets the output pin to remove the previously initialized pin by any module
 * @param 	pin_config pointer to the configuration @ref gpio_pin_config_t
 * @return	Status of the function
 * 			 (E_OK):     The function done successfully
 * 			 (E_NOT_ON): The function has issue to perform this action
 */
static Std_ReturnType pinLogicReset(const gpio_pinConfig_t *pin_config)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL != pin_config && ((PORT_PINS_MAX) > pin_config->pinIndex))
	{
		CLR_BIT(*output_registers[pin_config->portIndex], pin_config->pinIndex);
		ret = E_OK;
	}

	return ret;
}


/**
 * @brief	Initialize the direction of a specific pin @ref pinDirection_t
 * @param 	pin_config pointer to the configuration @ref gpio_pinConfig_t
 * @param 	pinDirection
 * @return	Status of the function
 * 			(E_OK):     The function done successfully
 * 			(E_NOT_OK): The function has issue
 */
Std_ReturnType gpio_pinWriteDir(const gpio_pinConfig_t *pin_config, pinDirection_t pin_direction)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL != pin_config && ((PORT_PINS_MAX) > pin_config->pinIndex) && ((PORT_MAX_NUM) > pin_config->portIndex))
	{
		switch(pin_direction)
		{
			case PIN_DIRECTION_INPUT:
				CLR_BIT(*dir_registers[pin_config->portIndex], pin_config->pinIndex);
				ret = E_OK;
				break;
			case PIN_DIRECTION_OUTPUT:
				SET_BIT(*dir_registers[pin_config->portIndex], pin_config->pinIndex);
				ret = E_OK;
				break;
		}
	}

	return ret;
}


/**
 * @brief	Get the direction of a specific pin @ref pinDirection_t
 * @param 	pin_config pointer to the configuration @ref gpio_pinConfig_t
 * @param 	pinDirection
 * @return	Status of the function
 * 			(E_OK):     The function done successfully
 * 			(E_NOT_OK): The function has issue
 */
Std_ReturnType gpio_pinReadDir(const gpio_pinConfig_t *pin_config, pinDirection_t *pin_direction)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL != pin_config && ((PORT_PINS_MAX) > pin_config->pinIndex) && ((PORT_MAX_NUM) > pin_config->portIndex))
	{
		*pin_direction = READ_BIT(*dir_registers[pin_config->portIndex], pin_config->pinIndex);
		ret = E_OK;
	}

	return ret;
}


/**
 * @brief	Initialize a specific pin to be High or Low @ref pinLogic_t
 * @param 	pin_config pointer to the configuration @ref gpio_pinConfig_t
 * @param 	logic
 * @return	Status of the function
 * 			(E_OK):     The function done successfully
 * 			(E_NOT_OK): The function has issue
 */
Std_ReturnType gpio_pinWriteLogic(const gpio_pinConfig_t *pin_config, pinLogic_t logic)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL != pin_config && ((PORT_PINS_MAX) > pin_config->pinIndex) && ((PORT_MAX_NUM) > pin_config->portIndex))
	{
		switch(logic)
		{
		case PIN_LOW:
			CLR_BIT(*output_registers[pin_config->portIndex], pin_config->pinIndex);
			ret = E_OK;
			break;
		case PIN_HIGH:
			SET_BIT(*output_registers[pin_config->portIndex], pin_config->pinIndex);
			ret = E_OK;
		}
	}

	return ret;
}


/**
 * @brief	Get the status of a specific pin @ref pinLogic_t
 * @param 	pin_config pointer to the configuration @ref gpio_pinConfig_t
 * @param 	logic pointer to return the status of the specific pin
 * @return	Status of the function
 * 			(E_OK):     The function done successfully
 * 			(E_NOT_OK): The function has issue
 */
Std_ReturnType gpio_pinReadLogic(const gpio_pinConfig_t *pin_config, pinLogic_t *logic)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL != pin_config && ((PORT_PINS_MAX) > pin_config->pinIndex) && ((PORT_MAX_NUM) > pin_config->portIndex))
	{
		*logic = READ_BIT(*input_registers[pin_config->portIndex], pin_config->pinIndex);
		ret = E_OK;
	}

	return ret;
}


/**
 * @brief	Toggle the status of a specific pin @ref TOGGLE_BIT
 * @param 	pin_config pointer to the configuration @ref gpio_pinConfig_t
 * @return	Status of the function
 * 			(E_OK):     The function done successfully
 * 			(E_NOT_OK): The function has issue
 */
Std_ReturnType gpio_pinToggleLogic(const gpio_pinConfig_t *pin_config)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL != pin_config && ((PORT_PINS_MAX) > pin_config->pinIndex) && ((PORT_MAX_NUM) > pin_config->portIndex))
	{
		TOGGLE_BIT(*output_registers[pin_config->portIndex], pin_config->pinIndex);
		ret = E_OK;
	}

	return ret;
}


/**
 * @brief	reset status of the pin and Initialize pin direction and logic
 * @param 	pin_config pointer to the configuration @ref gpio_pin_config_t
 * @return	Status of the function
 * 			 (E_OK):     The function done successfully
 * 			 (E_NOT_ON): The function has issue to perform this action
 */
Std_ReturnType gpio_pinInitialize(const gpio_pinConfig_t *pin_config, pinLogic_t logic)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL != pin_config && ((PORT_PINS_MAX) > pin_config->pinIndex) && ((PORT_MAX_NUM) > pin_config->portIndex))
	{
		ret |= pinLogicReset(pin_config);
		ret |= gpio_pinWriteDir(pin_config, pin_config->pinDirection);
		ret |= gpio_pinWriteLogic(pin_config, logic);
	}

	return ret;
}


/**
 * @brief	Initialize the port direction
 * @param 	port_index
 * @param 	direction
 * @return	Status of the function
 * 			 (E_OK):     The function done successfully
 * 			 (E_NOT_ON): The function has issue to perform this action
 */
Std_ReturnType gpio_portWriteDir(portIndex_t port_index, uint8 direction)
{
	Std_ReturnType ret = E_NOT_OK;

	if((PORT_MAX_NUM) > port_index)
	{
		*dir_registers[port_index] = direction;
		ret = E_OK;
	}

	return ret;
}


/**
 * @brief	Get the port direction
 * @param 	port_index
 * @param 	direction pointer to return the direction of port
 * @return	Status of the function
 * 			 (E_OK):     The function done successfully
 * 			 (E_NOT_ON): The function has issue to perform this action
 */
Std_ReturnType gpio_portReadDir(portIndex_t port_index, uint8 *direction)
{
	Std_ReturnType ret = E_NOT_OK;

	if((PORT_MAX_NUM) > port_index && NULL != direction)
	{
		*direction = *dir_registers[port_index];
		ret = E_OK;
	}

	return ret;
}


/**
 * @brief	Write logic High or low on a set of bits in the port
 * @param 	port_index
 * @param 	logic
 * @return	Status of the function
 * 			 (E_OK):     The function done successfully
 * 			 (E_NOT_ON): The function has issue to perform this action
 */
Std_ReturnType gpio_portWriteLogic(portIndex_t port_index, uint8 logic)
{
	Std_ReturnType ret = E_NOT_OK;

	if((PORT_MAX_NUM) > port_index)
	{
		*output_registers[port_index] = logic;
		ret = E_OK;
	}

	return ret;
}


/**
 * @brief	Get the status of a port
 * @param	port_index
 * @param 	logic
 * @return	Status of the function
 * 			 (E_OK):     The function done successfully
 * 			 (E_NOT_ON): The function has issue to perform this action
 */
Std_ReturnType gpio_portReadLogic(portIndex_t port_index, uint8 *logic)
{
	Std_ReturnType ret = E_NOT_OK;

	if((PORT_MAX_NUM) > port_index && NULL != logic)
	{
		*logic = *input_registers[port_index];
		ret = E_OK;
	}

	return ret;
}


/**
 * @brief	Toggle the status of the port
 * @param 	port_index
 * @return	Status of the function
 * 			 (E_OK):     The function done successfully
 * 			 (E_NOT_ON): The function has issue to perform this action
 */
Std_ReturnType gpio_protToggleLogic(portIndex_t port_index)
{
	Std_ReturnType ret = E_OK;
	*output_registers[port_index] ^= PORT_MASK;

	return ret;
}
