//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.h	
// Brief:	Header file for PID controller 
//-----------------------------------------------------------------------------

#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"

#define SYSCLK      		24500000   				// SYSCLK frequency in Hz
#define BAUDRATE   			115200					// Baud rate of UART in bps

#define P					5
#define I					2

#define UART_IN_SIZE		5
#define UART_SIZE_OUT 		8

#define ADC1				0x08
#define ADC2				0x09
#define ADC3				0x0A

#define SCALE_MUL			6068					// When combined with >> 10 will scale by 5.926 to compensate for potential divider

#define DEFAULT_OUT_MV		5000

SBIT(TEST2, SFR_P1, 3);                 			// DS5 P1.0 LED
SBIT(TEST1, SFR_P1, 4);                 			// DS5 P1.0 LED

U16 readAdc(U8 sel);
void uartLoadOut(U8 tx);
U16 uartNumbers(U16 toSend,bool transmit);

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

volatile U8 	uart_in[UART_IN_SIZE];
volatile U8 	uart_out[UART_SIZE_OUT];
volatile U8 	head;
volatile U8 	tail;
volatile int 	integral;
volatile U8 	duty;
volatile U16 	target_mV;
volatile bool	enabled;
volatile U16	adc1;
volatile U16	adc2;
volatile U16	adc3;
volatile U16 	current;

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

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
		PCA0CPM0 = 
			PCA0CPM0_CAPN__DISABLED 			| 
			PCA0CPM0_ECCF__ENABLED 				| 
			PCA0CPM0_MAT__ENABLED				| 
			PCA0CPM0_CAPP__DISABLED 			| 
			PCA0CPM0_ECOM__ENABLED				| 
			PCA0CPM0_PWM__ENABLED 				| 
			PCA0CPM0_TOG__DISABLED;
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
	
	enabled 	= false;
	integral 	= 0;
	target_mV 	= DEFAULT_OUT_MV;
	
	SCON0_TI 	= 1; 
	SCON0_RI 	= 0;
	
	while (1){
		if(SCON0_RI){
			SCON0_RI = 0;
			uart_in[4] = uart_in[3];										// Small buffer, less code not to use loop
			uart_in[3] = uart_in[2];
			uart_in[2] = uart_in[1];
			uart_in[1] = uart_in[0];
			uart_in[0] = SBUF0;
			
			uartLoadOut(uart_in[0]);
			
			switch(uart_in[0]){
				case 'a': 	uartNumbers(target_mV,true);
							break;
				case 'c': 	uartNumbers(current,true);
							break;
				case 'd': 	uartNumbers(duty,true);
							break;
				case 'g': 	enabled 	= true;
							integral 	= 0;
							break;
				case 's': 	enabled 	= false;
							break;
				case 'x': 	uartNumbers(adc1,true);
							break;
				case 'y': 	uartNumbers(adc2,true);
							break;
				case 'z': 	uartNumbers(adc3,true);
							break;
				default:	if('v' == uart_in[4]){
								target_mV 	= uartNumbers(target_mV,false);
								integral 	= 0;
							}
							break;
			}
		}
	}
} 

void uartLoadOut(U8 tx){							// Handle buffering out Tx UART
	uart_out[head] = tx;							// Buffer outgoing
	head++;						
	head %= UART_SIZE_OUT;							// Wrap around
}

U16 uartNumbers(U16 toSend, bool transmit){			// Tx/Rx up to 4 length numbers over UART
	U16 out = toSend;
	U16 num = 0;
	U16 scale = 10000;
	U8 test;
	U8 i = 4;
	bool bad = false;
	while(i){										// On zero done
		scale /= 10;								// Shift
		i--;										// Move through UART array
		test = uart_in[i] - 48;						// ascii to num
		if( (test < 0)||(test > 10) ){				// check is 0 to 9
			bad = true;
		}
		num += test*scale;							// shift in to position
		if(transmit){								// Put if statement at back of loop to save on jumps 
			num = out / scale;						// 10 powers
			uartLoadOut(num + 48);					// Number to ascii
			out %= scale;							// Remainder for next time
		}
	}
	uartLoadOut('\n');
	uartLoadOut('\r');
	if(bad){
		num = DEFAULT_OUT_MV;						// Not all valid numbers so set output as default
		enabled = false;							// Stop running
	}
	return num;
}

U16 readAdc(U8 sel){
	U8 i;
	ADC0MX = sel;
	for(i=0;i<2;i++){
		ADC0CN0 |= ADC0CN0_ADBUSY__SET;
		while(ADC0CN0 & ADC0CN0_ADBUSY__SET);		// Wait for sample to complete
	}
	return (((U32)ADC0)*SCALE_MUL) >> 10;			// Scale to mV
}

INTERRUPT (TIMER1_ISR, TIMER1_IRQn){}				// Needed for UART timing
	
INTERRUPT (TIMER2_ISR, TIMER2_IRQn){	
	int out;
	int error;
	TEST1 = 1;	
	

	adc1 = readAdc(ADC1);
	adc2 = readAdc(ADC2);
	adc3 = readAdc(ADC3);
	current = (adc2 - adc3)*10;
	

	error = (int)target_mV - (int)adc3;				// PID controller
	integral += error;
	out = ((error*P) + (integral*I)) >> 10;			// Divide by 1024
	if((out < 0) || (!enabled)){
		out = 0;
	}
	duty = out;
	PCA0CPH0 = PCA0CPH1 = 0xFF - out;
	


	if(head != tail){
		SBUF0 = uart_out[tail];						// Timer tuned so no need to check
		tail++;										// Transmit UART
		tail %= UART_SIZE_OUT;						// Wrap around
	}
	
	
	TMR2H = 255;									// Runs at 4KHz
	TMR2CN_TF2H = 0;								// Enable interrupt again
	TEST1 = 0;										// Timing debug
}
