/*
 * mcal_std_types.h
 *
 *  Created on: Aug 13, 2024
 *      Author: Mohammed
 */

#ifndef MCAL_STD_TYPES_H_
#define MCAL_STD_TYPES_H_

/* ------------------------------ Includes ---------------------------------- */
#include "std_libraries.h"
#include "avr/io.h"

/* ------------------------------ Data Type declarations -------------------- */
typedef unsigned char	uint8;
typedef char			int8;
typedef unsigned short	uint16;
typedef short			int16;
typedef unsigned int 	uint32;
typedef int				int32;
typedef unsigned long 	uint64;
typedef long			int64;

typedef uint8_t Std_ReturnType;

/* ------------------------------- Macro Declarations ------------------------*/
#define STD_HIGH		0x01
#define STD_LOW			0x00

#define STD_ON			0x01
#define STD_OFF			0x00

#define E_OK			(Std_ReturnType)0x01
#define E_NOT_OK		(Std_ReturnType)0x00

#define ZERO_INIT		0x00u

/* ------------------------------- Macro function declarations -------------- */

/* ------------------------------- Function declarations -------------------- */

#endif /* MCAL_STD_TYPES_H_ */
