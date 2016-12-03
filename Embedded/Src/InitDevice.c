//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	InitDevice.h
// Brief:	Header file initialisation 
//-----------------------------------------------------------------------------

#include <SI_C8051F850_Register_Enums.h>
#include "InitDevice.h"

void initDevice(void) {
	U8 TCON_save;
	U8 TMR2CN_TR2_save;
	// Watchdog
		// Disable the watchdog timer
		WDTCN = 0xDE; //First key
		WDTCN = 0xAD; //Second key
	// Clock
		// Processor off RC clock at full speed
		CLKSEL = CLKSEL_CLKSL__HFOSC | CLKSEL_CLKDIV__SYSCLK_DIV_1;
	// Port 0
		P0MDOUT = 
			P0MDOUT_B0__PUSH_PULL 	| 
			P0MDOUT_B1__OPEN_DRAIN 	| 
			P0MDOUT_B2__OPEN_DRAIN	| 
			P0MDOUT_B3__OPEN_DRAIN 	| 
			P0MDOUT_B4__PUSH_PULL 	| 
			P0MDOUT_B5__OPEN_DRAIN	| 
			P0MDOUT_B6__OPEN_DRAIN 	| 
			P0MDOUT_B7__OPEN_DRAIN;
	// Port 1
		P1MDOUT = 
			P1MDOUT_B0__PUSH_PULL 	| 
			P1MDOUT_B1__OPEN_DRAIN 	| 
			P1MDOUT_B2__OPEN_DRAIN	| 
			P1MDOUT_B3__OPEN_DRAIN 	| 
			P1MDOUT_B4__PUSH_PULL 	| 
			P1MDOUT_B5__OPEN_DRAIN	| 
			P1MDOUT_B6__OPEN_DRAIN 	| 
			P1MDOUT_B7__OPEN_DRAIN;
		P1MDIN = 
			P1MDIN_B0__DIGITAL 	| 
			P1MDIN_B1__DIGITAL 	| 
			P1MDIN_B2__ANALOG	| 
			P1MDIN_B3__DIGITAL 	| 
			P1MDIN_B4__DIGITAL 	| 
			P1MDIN_B5__DIGITAL	| 
			P1MDIN_B6__DIGITAL 	| 
			P1MDIN_B7__DIGITAL;
		P1SKIP = 
			P1SKIP_B0__NOT_SKIPPED 	| 
			P1SKIP_B1__NOT_SKIPPED 	| 
			P1SKIP_B2__SKIPPED		| 
			P1SKIP_B3__NOT_SKIPPED 	| 
			P1SKIP_B4__NOT_SKIPPED 	| 
			P1SKIP_B5__NOT_SKIPPED	| 
			P1SKIP_B6__NOT_SKIPPED 	| 
			P1SKIP_B7__NOT_SKIPPED;
	// Port crossbar
		XBR0 = 
			XBR0_URT0E__ENABLED 	| 
			XBR0_SPI0E__DISABLED 	| 
			XBR0_SMB0E__DISABLED	| 
			XBR0_CP0E__DISABLED 	| 
			XBR0_CP0AE__DISABLED 	| 
			XBR0_CP1E__DISABLED		| 
			XBR0_CP1AE__DISABLED 	|
			XBR0_SYSCKE__DISABLED;
		XBR1 = 
			XBR1_PCA0ME__CEX0_CEX1 	| 
			XBR1_ECIE__DISABLED 	| 
			XBR1_T0E__DISABLED		| 
			XBR1_T1E__DISABLED 		|
			XBR1_T2E__DISABLED;

		XBR2 = 
			XBR2_WEAKPUD__PULL_UPS_ENABLED 	| 
			XBR2_XBARE__ENABLED;
	// ADC
		ADC0MX = 
			ADC0MX_ADC0MX__ADC0P10;
		ADC0CF = 
			(1 << ADC0CF_ADSC__SHIFT) 	| 
			ADC0CF_AD8BE__NORMAL 		| 
			ADC0CF_ADGN__GAIN_1 		|
			ADC0CF_ADTM__TRACK_NORMAL;
		ADC0CN0 &=
			~ADC0CN0_ADCM__FMASK;
		ADC0CN0 |= 
			ADC0CN0_ADEN__ENABLED		|
			ADC0CN0_ADCM__ADBUSY;
	// Timer 0
		TCON_save = 
			TCON;
			TCON &= 
			TCON_TR0__BMASK 	&	 
			TCON_TR1__BMASK;
		TH1 = 
			(150 << TH1_TH1__SHIFT);
		TL1 = 
			(150 << TL1_TL1__SHIFT);
		TCON = 
			TCON_save;
	// Timer setup
		CKCON = 
			CKCON_SCA__SYSCLK_DIV_12 	| 
			CKCON_T0M__PRESCALE 		| 
			CKCON_T3MH__EXTERNAL_CLOCK 	| 
			CKCON_T3ML__EXTERNAL_CLOCK	| 
			CKCON_T1M__SYSCLK;
		TMOD = 
			TMOD_T0M__MODE0 		| 
			TMOD_CT0__TIMER 		| 
			TMOD_GATE0__DISABLED	| 
			TMOD_T1M__MODE2 		| 
			TMOD_CT1__TIMER 		| 
			TMOD_GATE1__DISABLED;
		TCON |= 
			TCON_TR1__RUN;
	// UART
		SCON0 |= 
			SCON0_REN__RECEIVE_ENABLED;
	// VREF
		REF0CN = 
			REF0CN_REFSL__VDD_PIN 		| 
			REF0CN_IREFLVL__1P65 		| 
			REF0CN_GNDSL__GND_PIN		| 
			REF0CN_TEMPE__TEMP_DISABLED;
	// RSTSRC
		RSTSRC = 
			RSTSRC_C0RSEF__NOT_SET 	| 
			RSTSRC_MCDRSF__SET 		| 
			RSTSRC_PORSF__SET		| 
			RSTSRC_SWRSF__NOT_SET;
	// Interrupt
		EIE1 = 
			EIE1_EADC0__DISABLED 	| 
			EIE1_ECP0__DISABLED 	| 
			EIE1_ECP1__DISABLED		| 
			EIE1_EMAT__DISABLED 	| 
			EIE1_EPCA0__DISABLED 	| 
			EIE1_ESMB0__DISABLED 	| 
			EIE1_ET3__DISABLED 		| 
			EIE1_EWADC0__DISABLED;
		IE = 
			IE_EA__ENABLED 		| 
			IE_EX0__DISABLED 	| 
			IE_EX1__DISABLED 	| 
			IE_ESPI0__DISABLED	| 
			IE_ET0__DISABLED 	| 
			IE_ET1__ENABLED 	| 
			IE_ET2__DISABLED 	| 
			IE_ES0__DISABLED;
	// PCA
		PCA0CN_CR =
			PCA0CN_CR__STOP;
			
		PCA0CPH0 = 
			(128 << PCA0CPH0_PCA0CPH0__SHIFT);
		PCA0CPM0 = 
			PCA0CPM0_CAPN__DISABLED 	| 
			PCA0CPM0_ECCF__ENABLED 		| 
			PCA0CPM0_MAT__ENABLED		| 
			PCA0CPM0_CAPP__DISABLED 	| 
			PCA0CPM0_ECOM__ENABLED		| 
			PCA0CPM0_PWM__ENABLED 		| 
			PCA0CPM0_TOG__DISABLED;
		PCA0CPH1 = 
			(128 << PCA0CPH0_PCA0CPH0__SHIFT);
		PCA0CPM1 = 
			PCA0CPM1_CAPN__DISABLED 	| 
			PCA0CPM1_ECCF__ENABLED 		| 
			PCA0CPM1_MAT__ENABLED		| 
			PCA0CPM1_CAPP__DISABLED 	| 
			PCA0CPM1_ECOM__ENABLED		| 
			PCA0CPM1_PWM__ENABLED 		| 
			PCA0CPM1_TOG__DISABLED;
		//PCA0POL = 
		//	PCA0POL_CEX1POL__INVERT;
		PCA0MD = 
			PCA0MD_CIDL__NORMAL 			| 
			PCA0MD_ECF__OVF_INT_DISABLED 	| 
			PCA0MD_CPS__SYSCLK;		
		PCA0CN |= 
			PCA0CN_CR__RUN;
		
		// $[Timer Initialization]
	// Save Timer Configuration
	//TMR2CN_TR2_save = TMR2CN & TMR2CN_TR2__BMASK;
	// Stop Timer
	//TMR2CN &= ~(TMR2CN_TR2__BMASK);
	// [Timer Initialization]$

	// $[TMR2CN - Timer 2 Control]
	/*
	// TF2LEN (Timer 2 Low Byte Interrupt Enable) = ENABLED (Enable low byte
	//     interrupts.)
	// T2SPLIT (Timer 2 Split Mode Enable) = 8_BIT_RELOAD (Timer 2 operates
	//     as two 8-bit auto-reload timers.)
	*/
	//TMR2CN |= TMR2CN_TF2H__SET ;
	// [TMR2CN - Timer 2 Control]$

	// $[TMR2H - Timer 2 High Byte]
	// [TMR2H - Timer 2 High Byte]$

	// $[TMR2L - Timer 2 Low Byte]
	// [TMR2L - Timer 2 Low Byte]$

	// $[TMR2RLH - Timer 2 Reload High Byte]
	/*
	// TMR2RLH (Timer 2 Reload High Byte) = 1
	*/
	//TMR2RLH = (1 << TMR2RLH_TMR2RLH__SHIFT);
	// [TMR2RLH - Timer 2 Reload High Byte]$

	// $[TMR2RLL - Timer 2 Reload Low Byte]
	/*
	// TMR2RLL (Timer 2 Reload Low Byte) = 1
	*/
	//TMR2RLL = (1 << TMR2RLL_TMR2RLL__SHIFT);
	// [TMR2RLL - Timer 2 Reload Low Byte]$

	// $[TMR2CN]
	/*
	// TR2 (Timer 2 Run Control) = RUN (Start Timer 2 running.)
	*/
	//TMR1CN |= TMR2CN_TR2__RUN;
	// [TMR2CN]$

	// $[Timer Restoration]
	// Restore Timer Configuration
	//TMR2CN |= TMR2CN_TR2_save;
	// [Timer Restoration]$


}
