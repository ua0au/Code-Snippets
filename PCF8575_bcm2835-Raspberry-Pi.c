//******************************************************************
//PCF8575所有io输出默认高电平且没有寄存器
//编译使用命令： gcc 123.c -o 123 -l bcm2835

/*
Copyright:

File name:	PCF8575_bcm2835.c
Create Data:	2018-9-26
Description:	PCF8575模块的独立测试程序

Author:	X_V
Email:	
Phone:

Version:0.1
Update Data:
History:
*/

/*	GPIO define from RaspbertPi 3B

	 +-----+-----+---------+------+---+---Pi 3---+---+------+---------+-----+-----+
	 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
	 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
	 |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
	 |   2 |   8 |   SDA.1 | ALT0 | 1 |  3 || 4  |   |      | 5v      |     |     |
	 |   3 |   9 |   SCL.1 | ALT0 | 1 |  5 || 6  |   |      | 0v      |     |     |
	 |   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 0 | IN   | TxD     | 15  | 14  |
	 |     |     |      0v |      |   |  9 || 10 | 1 | IN   | RxD     | 16  | 15  |
	 |  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 0 | ALT0 | GPIO. 1 | 1   | 18  |
	 |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
	 |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
	 |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
	 |  10 |  12 |    MOSI | ALT0 | 0 | 19 || 20 |   |      | 0v      |     |     |
	 |   9 |  13 |    MISO | ALT0 | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
	 |  11 |  14 |    SCLK | ALT0 | 0 | 23 || 24 | 1 | OUT  | CE0     | 10  | 8   |
	 |     |     |      0v |      |   | 25 || 26 | 1 | OUT  | CE1     | 11  | 7   |
	 |   0 |  30 |   SDA.0 |   IN | 1 | 27 || 28 | 1 | IN   | SCL.0   | 31  | 1   |
	 |   5 |  21 | GPIO.21 |   IN | 1 | 29 || 30 |   |      | 0v      |     |     |
	 |   6 |  22 | GPIO.22 |   IN | 1 | 31 || 32 | 0 | IN   | GPIO.26 | 26  | 12  |
	 |  13 |  23 | GPIO.23 |   IN | 0 | 33 || 34 |   |      | 0v      |     |     |
	 |  19 |  24 | GPIO.24 | ALT0 | 0 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |
	 |  26 |  25 | GPIO.25 |   IN | 0 | 37 || 38 | 0 | ALT0 | GPIO.28 | 28  | 20  |
	 |     |     |      0v |      |   | 39 || 40 | 0 | ALT0 | GPIO.29 | 29  | 21  |
	 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
	 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
	 +-----+-----+---------+------+---+---Pi 3---+---+------+---------+-----+-----+

*/

/*	GPIO define from bcm2835.h 

	// RPi Version 2 
    RPI_V2_GPIO_P1_03     =  2,  // Pin P1-03 
    RPI_V2_GPIO_P1_05     =  3,  // Pin P1-05 
    RPI_V2_GPIO_P1_07     =  4,  // Pin P1-07 
    RPI_V2_GPIO_P1_08     = 14,  // Pin P1-08, defaults to alt function 0 UART0_TXD 
    RPI_V2_GPIO_P1_10     = 15,  // Pin P1-10, defaults to alt function 0 UART0_RXD 
    RPI_V2_GPIO_P1_11     = 17,  // Pin P1-11 
    RPI_V2_GPIO_P1_12     = 18,  // Pin P1-12, can be PWM channel 0 in ALT FUN 5 
    RPI_V2_GPIO_P1_13     = 27,  // Pin P1-13 
    RPI_V2_GPIO_P1_15     = 22,  // Pin P1-15 
    RPI_V2_GPIO_P1_16     = 23,  // Pin P1-16 
    RPI_V2_GPIO_P1_18     = 24,  // Pin P1-18 
    RPI_V2_GPIO_P1_19     = 10,  // Pin P1-19, MOSI when SPI0 in use 
    RPI_V2_GPIO_P1_21     =  9,  // Pin P1-21, MISO when SPI0 in use 
    RPI_V2_GPIO_P1_22     = 25,  // Pin P1-22 
    RPI_V2_GPIO_P1_23     = 11,  // Pin P1-23, CLK when SPI0 in use 
    RPI_V2_GPIO_P1_24     =  8,  // Pin P1-24, CE0 when SPI0 in use 
    RPI_V2_GPIO_P1_26     =  7,  // Pin P1-26, CE1 when SPI0 in use 
    RPI_V2_GPIO_P1_29     =  5,  // Pin P1-29 
    RPI_V2_GPIO_P1_31     =  6,  // Pin P1-31 
    RPI_V2_GPIO_P1_32     = 12,  // Pin P1-32 
    RPI_V2_GPIO_P1_33     = 13,  // Pin P1-33 
    RPI_V2_GPIO_P1_35     = 19,  // Pin P1-35, can be PWM channel 1 in ALT FUN 5  
    RPI_V2_GPIO_P1_36     = 16,  // Pin P1-36 
    RPI_V2_GPIO_P1_37     = 26,  // Pin P1-37 
    RPI_V2_GPIO_P1_38     = 20,  // Pin P1-38 
    RPI_V2_GPIO_P1_40     = 21,  // Pin P1-40 
 
 
*/

//******************************************************************


#include <stdio.h>
#include <bcm2835.h>

char PCF8575_WriteBuf_init[2] = {0x00,0x00};

char PCF8575_WriteBuf_0[2]={0x01,0x00};
char PCF8575_WriteBuf_1[2]={0x02,0x00};
char PCF8575_WriteBuf_2[2]={0x04,0x00};
char PCF8575_WriteBuf_3[2]={0x08,0x00};
char PCF8575_WriteBuf_4[2]={0x10,0x00};
char PCF8575_WriteBuf_5[2]={0x20,0x00};
char PCF8575_WriteBuf_6[2]={0x40,0x00};
char PCF8575_WriteBuf_7[2]={0x80,0x00};

char PCF8575_WriteBuf_10[2]={0x00,0x01};
char PCF8575_WriteBuf_11[2]={0x00,0x02};
char PCF8575_WriteBuf_12[2]={0x00,0x04};
char PCF8575_WriteBuf_13[2]={0x00,0x08};
char PCF8575_WriteBuf_14[2]={0x00,0x10};
char PCF8575_WriteBuf_15[2]={0x00,0x20};
char PCF8575_WriteBuf_16[2]={0x00,0x40};
char PCF8575_WriteBuf_17[2]={0x00,0x80};

int main(int argc, char **argv)
{
    if (!bcm2835_init())
    return 1;
    
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x20);
    bcm2835_i2c_set_baudrate(200000);
	bcm2835_i2c_write(PCF8575_WriteBuf_init, 2);

	int numc;
	printf("input number:0-7，10-17\n");
	scanf("%d",&numc);
   
   switch(numc){
		//P0-P7			7 6 5 4 3 2 1 0;	0000 0001, 0000 0000
		case 0:bcm2835_i2c_write(PCF8575_WriteBuf_0,2);break;
		case 1:bcm2835_i2c_write(PCF8575_WriteBuf_1,2);break;
		case 2:bcm2835_i2c_write(PCF8575_WriteBuf_2,2);break;
		case 3:bcm2835_i2c_write(PCF8575_WriteBuf_3,2);break;
		case 4:bcm2835_i2c_write(PCF8575_WriteBuf_4,2);break;
		case 5:bcm2835_i2c_write(PCF8575_WriteBuf_5,2);break;
		case 6:bcm2835_i2c_write(PCF8575_WriteBuf_6,2);break;
		case 7:bcm2835_i2c_write(PCF8575_WriteBuf_7,2);break;
		//P10-P17		17 16 15 14 13 12 11 10;	0000 0000, 0000 0001
		case 10:bcm2835_i2c_write(PCF8575_WriteBuf_10,2);break;
		case 11:bcm2835_i2c_write(PCF8575_WriteBuf_11,2);break;
		case 12:bcm2835_i2c_write(PCF8575_WriteBuf_12,2);break;
		case 13:bcm2835_i2c_write(PCF8575_WriteBuf_13,2);break;
		case 14:bcm2835_i2c_write(PCF8575_WriteBuf_14,2);break;
		case 15:bcm2835_i2c_write(PCF8575_WriteBuf_15,2);break;
		case 16:bcm2835_i2c_write(PCF8575_WriteBuf_16,2);break;
		case 17:bcm2835_i2c_write(PCF8575_WriteBuf_17,2);break;

		default: bcm2835_i2c_write(PCF8575_WriteBuf_init,2);break;  
   }
   
   
		
    bcm2835_delay(5000);
		
	bcm2835_i2c_write(PCF8575_WriteBuf_init, 2);
    
   
    bcm2835_i2c_end();
    bcm2835_close();

    return 0;
}



/*
#include <stdio.h>
#include <bcm2835.h>

char PCF8575_PCF8575_WriteBuf_init[2] = {0x00,0x00};	//定义所有io口置为低电平

char PCF8575_WriteBuf_now[2];

int main(int argc, char **argv)
{
    if (!bcm2835_init())
    return 1;
    
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x20);
    bcm2835_i2c_set_baudrate(200000);
	bcm2835_i2c_write(PCF8575_PCF8575_WriteBuf_init, 2);

	int numc;
	printf("input number:0-7，10-17\n");
	scanf("%d",&numc);
   
   switch(numc){
		//P0-P7,7 6 5 4 3 2 1 0;0000 0001, 0000 0000
		case 0:PCF8575_WriteBuf_now={0x01,0x00};break;
		case 1:PCF8575_WriteBuf_now={0x02,0x00};break;  
		case 2:PCF8575_WriteBuf_now={0x04,0x00};break;  
		case 3:PCF8575_WriteBuf_now={0x08,0x00};break;  
		case 4:PCF8575_WriteBuf_now={0x10,0x00};break;  
		case 5:PCF8575_WriteBuf_now={0x20,0x00};break;  
		case 6:PCF8575_WriteBuf_now={0x40,0x00};break;  
		case 7:PCF8575_WriteBuf_now={0x80,0x00};break;  
		//P10-P17,17 16 15 14 13 12 11 10;0000 0000, 0000 0001
		case 10:PCF8575_WriteBuf_now={0x00,0x01};break;
		case 11:PCF8575_WriteBuf_now={0x00,0x02};break;  
		case 12:PCF8575_WriteBuf_now={0x00,0x04};break;  
		case 13:PCF8575_WriteBuf_now={0x00,0x08};break;  
		case 14:PCF8575_WriteBuf_now={0x00,0x10};break;  
		case 15:PCF8575_WriteBuf_now={0x00,0x20};break;  
		case 16:PCF8575_WriteBuf_now={0x00,0x40};break;  
		case 17:PCF8575_WriteBuf_now={0x00,0x80};break;  
		default: PCF8575_WriteBuf_now=PCF8575_PCF8575_WriteBuf_init;break;  
   }
   
   
	bcm2835_i2c_write(PCF8575_WriteBuf_now, 2);
		
    bcm2835_delay(5000);
		
	bcm2835_i2c_write(PCF8575_PCF8575_WriteBuf_init, 2);
    
   
    bcm2835_i2c_end();
    bcm2835_close();

    return 0;
}
*/



