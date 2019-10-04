
#ifndef _HEADER_H_
#define _HEADER_H_
#include <LPC214X.H>

typedef unsigned int U32;
typedef unsigned char U8;
typedef unsigned const char CU8;


#define OUTPUT 1
#define INPUT 0
#define PORT0 0 
#define PORT1 1
#define HIGH 1
#define LOW 0


/***********************************/
extern void gsm_init(void);
extern void send_msg(U8 *);


/***************IAP*****************/
//extern U32 GetSecNum(U32);
//extern int Init(U32,U32,U32);
//extern int Unit(U32);
//extern int Erasechip(void);
//extern int Erasesector(U32);
//extern int Erasesector(U32);
//extern int ProgramPage(U32 ,U32 ,U8*);
//extern void Prep_sec_for_write(void);
//extern void ram_2_flash(U32);
//extern void erase_sec(void);
//extern void print_rslt(U32 *);



/**********Password*********/
extern void inits(void);
extern void Menu(void);
extern void set(U32 *,U32 *);
extern void input(U32 *,U32,U32);
extern void Otp(U32);
extern void reset(U32 *,U32 *);
extern void enter(void);
extern void dob(void);
extern void login(void);
extern void login(void);



/**********Delay*********/
extern void tdelay_ms(U32);
extern void delay_ms(U32);





/************GPIO************/
extern void set_iodir(U32,U32,U32 );
extern void io_write(U32,U32,U32);
extern U32 io_read(U32,U32);






/*********Interrupt*********/
extern void config_vic(void);
extern void config_eint(void);




/************UART0**********/
extern void uart0_init(U32);
extern void uart0_tx(U8);
extern U8 uart0_rx (void);
extern void uart0_tx_string(CU8 *);
extern void config_uint(void);
extern void uart0_rx_string(U8 *,U32);
extern void dec_print(U32,U32);





/************UART1************/
extern void uart1_init(U32);
extern void uart1_tx(U8);
extern U8 uart1_rx (void);
extern void uart1_tx_string(CU8 *);
extern void uart1_rx_string(U8 *,U32);




/************KEYPAD**************/
extern U8 keyscan(void);
extern U8 col_scan(void);





/*************LCD************/
extern void lcd_init(void);
extern void lcd_data(U8);
extern void lcd_cmd(U8);
extern void lcd_string(CU8 *);






/*********ADC0*************/
extern void init_adc(void);
extern U32 adc_read(void);




/************RTC*************/
typedef struct time
{
 	U32 sec;
 	U32 min;
 	U32 hr;
 	U32 day_of_mnth;				// 1 - 30
	U32 day_of_week;				// 0(sunday) - 6(saturday)
	U32 day_of_year;			    // (1 - 365)
 	U32 mnth;						// 0 - 12 
	U32 yr;							// 2019
}ti;
extern void rtc_init(void);
extern void set_time(void);
extern ti get_time(void);
extern void pf_time_uart(ti);
extern void pf_time_lcd(ti);



/********************DAC******************/
extern void dac(void);



/*********************i2C**************/
extern void i2c_init(void);
extern void i2c_device_write(U8, U8 ,char);
extern U8 i2c_device_read(U8 ,U8 );




/*****************SPI**************/
extern void spi_init(void);
extern void spi_write(U8);
extern unsigned short int spi_read(U8);




/*************string func*************/
extern int my_strcmp(U32 *,U32 *);
extern void my_strcpy(U32 *,U32 *);





/*************ultrasonic****************/
extern void ultrasonic_init(void);
//extern void send_pulse(void);
//extern U32 get_range(void);
extern U32 distance(void);


/*****************************************************************/
/*****						PINS USED	 					******/

/*
P0.0  - (Tx)UART0
P0.1  - (rx)UART0
P0.2  - (SCL) I2c0
P0.3  - (SDL) I2c0
P0.4  - (CLK0) SPI0
P0.5  - (MISO) SPI0
P0.6  - (MOSI) SPI0
P0.7  - (SS) SPI0
P0.8  - 15 keypad.
P0.9  - Tx (UART1)
P0.10 - Rx (UART1)
P0.25 - (A.out) DAC 
P0.28 - for ADC channel 1 (ADC0.1)

P1.16 - 23 (data) For LCD data
P1.26 - (RS) LCD
P1.27 = (EN) LCD
*/

#endif

