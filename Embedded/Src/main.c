//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	main.c	
// Brief:	Entry point for switcher power supply
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <SI_C8051F850_Register_Enums.h>
#include "InitDevice.h"
#include "Pid.h"							// Holds controller configuration

//-----------------------------------------------------------------------------
// Pin Declarations
//-----------------------------------------------------------------------------

SBIT(LED1, SFR_P1, 0);                 // DS5 P1.0 LED
SBIT(LED2, SFR_P1, 1);                 // DS6 P1.1 LED
SBIT(S1, SFR_P1, 7);
SBIT(S2, SFR_P2, 1);

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define SYSCLK      24500000/8         // Clock speed in Hz (default)

#define SW_PRESSED           0
#define SW_NOT_PRESSED       1

#define LED_ON               0
#define LED_OFF              1

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void main (void)
{
	uint16_t	adc;
	uint16_t	pwm;

		
	enter_DefaultMode_from_RESET();
	
   while (1)
   {
//      // Set the state of LED1
//      if (S1 == SW_PRESSED)
//      {
//         LED1 = LED_OFF;
//      }
//      else
//      {
//         LED1 = LED_ON;
//      }

//      // Set the state of LED2
//      if (S2 == SW_PRESSED)
//      {
//         LED2 = LED_OFF;
//      }
//      else
//      {
//         LED2 = LED_ON;
//      }
	   
		pwm = pidUpdate(adc);
		pwm++;
   }
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
