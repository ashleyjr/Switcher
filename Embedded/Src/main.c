//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.h	
// Brief:	Header file for PID controller 
//-----------------------------------------------------------------------------

#include "main.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

volatile U8 	uart_in[UART_IN_SIZE];
volatile U8 	uart_out[UART_SIZE_OUT];
volatile U8 	head;
volatile U8 	tail;
volatile int 	integral;
volatile U16 	target_mV;

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void uartLoadOut(U8 tx);
U16 uartNumbers(U16 toSend,bool transmit);
void main (void){
	// Start of peripheral setup
	U8 TCON_save;
	// Watchdog 
		WDTCN = 0xDE; 								// First key
		WDTCN = 0xAD; 								// Second key - Watchdog now disabled
	// Clock
		CLKSEL = 
			CLKSEL_CLKSL__HFOSC 				| 	// Use 24.5MHz interal clock
			CLKSEL_CLKDIV__SYSCLK_DIV_1;			// Do not divide
	// Port 0
		P0MDOUT = 
			P0MDOUT_B0__PUSH_PULL 				| 	// PWM1 output
			P0MDOUT_B1__PUSH_PULL 				| 	// PWM2 output
			P0MDOUT_B2__OPEN_DRAIN				| 
			P0MDOUT_B3__OPEN_DRAIN 				| 
			P0MDOUT_B4__PUSH_PULL 				| 	// UART TX
			P0MDOUT_B5__OPEN_DRAIN				| 	// UART RX
			P0MDOUT_B6__OPEN_DRAIN 				| 
			P0MDOUT_B7__OPEN_DRAIN;
	// Port 1
		P1MDOUT = 
			P1MDOUT_B0__OPEN_DRAIN 				| 
			P1MDOUT_B1__OPEN_DRAIN 				| 
			P1MDOUT_B2__OPEN_DRAIN				| 
			P1MDOUT_B3__PUSH_PULL 				| 	// TEST2
			P1MDOUT_B4__PUSH_PULL 				| 	// TEST1
			P1MDOUT_B5__OPEN_DRAIN				| 
			P1MDOUT_B6__OPEN_DRAIN 				| 
			P1MDOUT_B7__OPEN_DRAIN;
		P1MDIN = 
			P1MDIN_B0__ANALOG 					|	// ADC1
			P1MDIN_B1__ANALOG 					| 	// ADC2
			P1MDIN_B2__ANALOG					| 	// ADC3
			P1MDIN_B3__DIGITAL 					| 
			P1MDIN_B4__DIGITAL 					| 
			P1MDIN_B5__DIGITAL					| 
			P1MDIN_B6__DIGITAL 					| 
			P1MDIN_B7__DIGITAL;
	// Port crossbar
		XBR0 = 
			XBR0_URT0E__ENABLED 				| 	// Route out UART
			XBR0_SPI0E__DISABLED 				| 
			XBR0_SMB0E__DISABLED				| 
			XBR0_CP0E__DISABLED 				| 
			XBR0_CP0AE__DISABLED 				| 
			XBR0_CP1E__DISABLED					| 
			XBR0_CP1AE__DISABLED 				|
			XBR0_SYSCKE__DISABLED;
		XBR1 = 
			XBR1_PCA0ME__CEX0_CEX1 				| 	// Route out PCA0 and PCA1
			XBR1_ECIE__DISABLED 				| 
			XBR1_T0E__DISABLED					| 
			XBR1_T1E__DISABLED 					|
			XBR1_T2E__DISABLED;
		XBR2 = 
			XBR2_WEAKPUD__PULL_UPS_ENABLED 		| 	// Weak pull ups
			XBR2_XBARE__ENABLED;					// Enable cross bar
	// ADC
		//ADC0MX = 									// Mux set in application
		//	ADC0MX_ADC0MX__ADC0P10;
		ADC0CF = 
			(1 << ADC0CF_ADSC__SHIFT) 			| 
			ADC0CF_AD8BE__NORMAL 				| 	// ADC set to 10 bit
			ADC0CF_ADGN__GAIN_1 				|	// ADC gain set to 1
			ADC0CF_ADTM__TRACK_NORMAL;				// Immediate covert
		ADC0CN0 &=
			~ADC0CN0_ADCM__FMASK;
		ADC0CN0 |= 
			ADC0CN0_ADEN__ENABLED				|
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
			CKCON_SCA__SYSCLK_DIV_12 			| 
			CKCON_T0M__PRESCALE 				| 
			CKCON_T3MH__EXTERNAL_CLOCK 			| 
			CKCON_T3ML__EXTERNAL_CLOCK			| 
			CKCON_T1M__SYSCLK;
		TMOD = 
			TMOD_T0M__MODE0 					| 
			TMOD_CT0__TIMER 					| 
			TMOD_GATE0__DISABLED				| 
			TMOD_T1M__MODE2 					| 
			TMOD_CT1__TIMER 					| 
			TMOD_GATE1__DISABLED;
		TCON |= 
			TCON_TR1__RUN ;
	// UART
		SCON0 |= 
			SCON0_REN__RECEIVE_ENABLED;
	// VREF
		REF0CN = 
			REF0CN_REFSL__VDD_PIN 				| 
			REF0CN_IREFLVL__1P65 				| 
			REF0CN_GNDSL__GND_PIN				| 
			REF0CN_TEMPE__TEMP_DISABLED;
	// RSTSRC
		RSTSRC = 
			RSTSRC_C0RSEF__NOT_SET 				| 
			RSTSRC_MCDRSF__SET 					| 
			RSTSRC_PORSF__SET					| 
			RSTSRC_SWRSF__NOT_SET;
	// Interrupt
		IE = 
			IE_EA__ENABLED 						| 
			IE_EX0__DISABLED 					| 
			IE_EX1__DISABLED 					| 
			IE_ESPI0__DISABLED					| 
			IE_ET0__DISABLED 					| 
			IE_ET1__ENABLED						| 	// Timer 1 enabled
			IE_ET2__ENABLED 					| 	// Timer 2 enabled
			IE_ES0__ENABLED;
		IP = 
			IP_PX0__LOW 						| 
			IP_PX1__LOW 						| 
			IP_PSPI0__LOW 						| 
			IP_PT0__LOW 						| 
			IP_PT1__LOW							|
			IP_PT2__HIGH 						| 	// Timer 2 highest priority
			IP_PS0__LOW;
	// PCA
		PCA0CN_CR =
			PCA0CN_CR__STOP;
		PCA0CPH0 = 
			(128 << PCA0CPH0_PCA0CPH0__SHIFT);
		PCA0CPM0 = 
			PCA0CPM0_CAPN__DISABLED 			| 
			PCA0CPM0_ECCF__ENABLED 				| 
			PCA0CPM0_MAT__ENABLED				| 
			PCA0CPM0_CAPP__DISABLED 			| 
			PCA0CPM0_ECOM__ENABLED				| 
			PCA0CPM0_PWM__ENABLED 				| 
			PCA0CPM0_TOG__DISABLED;
		PCA0CPH1 = 
			(128 << PCA0CPH0_PCA0CPH0__SHIFT);
		PCA0CPM1 = 
			PCA0CPM1_CAPN__DISABLED 			| 
			PCA0CPM1_ECCF__ENABLED 				|		 
			PCA0CPM1_MAT__ENABLED				| 
			PCA0CPM1_CAPP__DISABLED 			| 
			PCA0CPM1_ECOM__ENABLED				| 
			PCA0CPM1_PWM__ENABLED 				| 
			PCA0CPM1_TOG__DISABLED;
		PCA0MD = 
			PCA0MD_CIDL__NORMAL 				| 
			PCA0MD_ECF__OVF_INT_DISABLED 		| 
			PCA0MD_CPS__SYSCLK;		
		PCA0CN |= 
			PCA0CN_CR__RUN;
	// Timer 2
		TMR2CN |= TMR2CN_TR2__RUN;
	// End of peripheral setup
	
	integral 	= 0;
	target_mV 	= 5250;
	
	SCON0_TI 	= 1; 
	SCON0_RI 	= 0;
	
	while (1){
		if(SCON0_RI){
			SCON0_RI = 0;
			uart_in[4] = uart_in[3];					// Small buffer, less code not to use loop
			uart_in[3] = uart_in[2];
			uart_in[2] = uart_in[1];
			uart_in[1] = uart_in[0];
			uart_in[0] = SBUF0;
			
			uartLoadOut(uart_in[0]);
			
			if('v' == uart_in[4]){
				target_mV = uartNumbers(target_mV,false);
			}
			if('a' == uart_in[0]){
				uartNumbers(target_mV,true);
			}
		}
	}
}

void uartLoadOut(U8 tx){
	uart_out[head] = tx;		// Buffer outgoing
	head++;						
	head %= UART_SIZE_OUT;		// Wrap around
}

U16 uartNumbers(U16 toSend, bool transmit){		// Send up to 16-bit number over UART
	U16 out = toSend;
	U16 num = 0;
	U16 scale = 10000;
	U8 i = 4;
	while(i){									// On zero done
		scale /= 10;							// Shift
		i--;									// Move through UART array
		num += (uart_in[i]-48)*scale;			// ascii to number
		if(transmit){							// Put if statement at back of loop to save on jumps 
			num = out / scale;					// 10 powers
			uartLoadOut(num + 48);				// Number to ascii
			out %= scale;						// Remainder for next time
		}
	}
	uartLoadOut('\n');
	uartLoadOut('\r');
	return num;
}