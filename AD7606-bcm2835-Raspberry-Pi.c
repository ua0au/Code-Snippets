// gcc -Wall 12.c -o 12 -lbcm2835

#include <bcm2835.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>


#define		CS1				BCM2835_SPI_CS1

#define		AD7606_CVAB		RPI_V2_GPIO_P1_18
#define		AD7606_RST		RPI_V2_GPIO_P1_22
#define		AD7606_BUSY		RPI_V2_GPIO_P1_37


char AD7606_send[16]={0};
char AD7606_rece[16]={0};

double V_num=0;

void AD7606_Reset(){	// AD7606 reset
		
	bcm2835_gpio_write(CS1,HIGH);
	bcm2835_gpio_write(AD7606_CVAB,HIGH);	// CVA/B
	
	bcm2835_gpio_write(AD7606_RST,LOW);	// RST
	bcm2835_delayMicroseconds(5);
		
	bcm2835_gpio_write(AD7606_RST,HIGH);
	bcm2835_delayMicroseconds(5);
		
	bcm2835_gpio_write(AD7606_RST,LOW);
}
	
	
void AD7606_StartConv(){
		
	bcm2835_gpio_write(AD7606_CVAB, LOW);
	bcm2835_delayMicroseconds(1);
	bcm2835_gpio_write(AD7606_CVAB, HIGH);
		
}
	
bool AD7606_StartAC(){
		
	if(bcm2835_gpio_lev(AD7606_BUSY) == 0){
			
		bcm2835_spi_setChipSelectPolarity(CS1, LOW);
			
		bcm2835_spi_transfernb(AD7606_send,AD7606_rece,16);
			
		bcm2835_spi_setChipSelectPolarity(CS1, HIGH);
		
		AD7606_StartConv();

		while(bcm2835_gpio_lev(AD7606_BUSY) == 0);
		return true;
	}
	else{
		
		printf("Value is not ready: %s\n", strerror(errno));
		return false;
	}
}


int main(int argc,char **argv)
{
	// initialize the library
	if(!bcm2835_init()){
		printf("bcm2835_init failed. Are you running as root??\n");
	return 1;
	}
	
	// begin the library
	if (!bcm2835_spi_begin()){
		printf("bcm2835_init failed. Are you running as root??\n");
	return 1;
	}
  

	// set the bit order
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);	
    // set the data mode
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE2);	//important
	// set the SPI clock divider
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);	//about 6.250MHz
	// set the chip select
	bcm2835_spi_chipSelect(CS1);					// AD7606:CE1	
	// set the chip selcet polarity
	// bcm2835_spi_setChipSelectPolarity(CS1, LOW);	// default:LOW，LOW is active
	
		//*************************************************************************
			// bcm2835_spi_begin();
				/*
				bcm2835_gpio_fsel(RPI_GPIO_P1_19, BCM2835_GPIO_FSEL_ALT0);	//MOSI
				bcm2835_gpio_fsel(RPI_GPIO_P1_21, BCM2835_GPIO_FSEL_ALT0);	//MISO
				bcm2835_gpio_fsel(RPI_GPIO_P1_23, BCM2835_GPIO_FSEL_ALT0);	//CLK
				bcm2835_gpio_fsel(RPI_GPIO_P1_24, BCM2835_GPIO_FSEL_ALT0);	//CE0
				bcm2835_gpio_fsel(RPI_GPIO_P1_26, BCM2835_GPIO_FSEL_ALT0);	//CE1
				*/
			// Set SPI data mode
				/*
				BCM2835_SPI_MODE0 	CPOL = 0, CPHA = 0	CPOL=0，时钟空闲idle时候的电平是低电平，所以当SCLK有效的时候，就是高电平
				BCM2835_SPI_MODE1 	CPOL = 0, CPHA = 1	
				BCM2835_SPI_MODE2 	CPOL = 1, CPHA = 0	CPHA=0，表示第一个边沿
				BCM2835_SPI_MODE3 	CPOL = 1, CPHA = 1 
				*/
			
			// Set SPI clock speed
				/*
				BCM2835_SPI_CLOCK_DIVIDER_65536 	6.1035156kHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_32768 	12.20703125kHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_16384 	24.4140625kHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_8192		48.828125kHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_4096		97.65625kHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_2048		195.3125kHz on RPI3 
				BCM2835_SPI_CLOCK_DIVIDER_1024 		390.625kHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_512 		781.25kHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_256 		1.5625MHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_128 		3.125MHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_64 		6.250MHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_32 		12.5MHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_16		25MHz on RPI3
				BCM2835_SPI_CLOCK_DIVIDER_8			50MHz on RPI3
				*/
				
 			// Set with CS pin
				/*
				BCM2835_SPI_CS0 	Chip Select 0
				CS1 	Chip Select 1
				BCM2835_SPI_CS2 	Chip Select 2 (ie pins CS1 and CS2 are asserted)
				BCM2835_SPI_CS_NONE 	No CS, control it yourself 
				*/
		//**************************************************************************

	bcm2835_gpio_fsel(AD7606_CVAB,BCM2835_GPIO_FSEL_OUTP);	// CVA/B
	bcm2835_gpio_fsel(AD7606_RST,BCM2835_GPIO_FSEL_OUTP);	// RST
		// bcm2835_gpio_fsel(AD7606_BUSY,BCM2835_GPIO_FSEL_INPT);	// BUSY	P1_37 default:input
		
		//bcm2835_gpio_write(AD7606_CVAB,LOW);	// Start conversion
			/*Conversion Start Input A and B. Logic inputs. These logic inputs are used to initiate conversions on the analog input channels.We shorted A&B for simultaneous sampling of all input channels.When the CONVST A or CONVST B pin transitions from low to high, the front-end track-and-holdcircuitry for the respective analog inputs is set to hold. .*/
		
		//bcm2835_gpio_write(AD7606_RST,LOW);	//set to reset AD7606
			/*When set to logic high, the rising edge of RESET resets the AD7606. The device should receive a RESET pulse directly after power-up.*/
	
		//AD7606_StartAC();
		AD7606_Reset();
		
	for(int i=0;i<1003;i++)	{
			
		if(AD7606_StartAC()){

			//bcm2835_spi_transfernb(AD7606_send,AD7606_rece,16);
	
			for(int j=0;j<8;j++){
					
				uint16_t merge_v;
				double v8_num;
					
				merge_v = AD7606_rece[2*j+1] + (AD7606_rece[2*j] << 8);
				v8_num= 1.0 * merge_v * 10 / 65535;
					
				if(v8_num >= 5){
					v8_num = 10 - v8_num;
				}

				if(i>2 && j==7){	// discard the first three times data 
					V_num += v8_num;
				}
				printf ("%9.8lf\t", v8_num);
					
			}
			// bcm2835_delayMicroseconds(10);

				
				
			// printf ("\n");
			// bcm2835_delay(1000);
				
		}
				
	}
		
	V_num /= 1000;	// average of 1000 times sample for little errors.
	printf ("平均%9.8lf\n", V_num);
	


	
	
	bcm2835_spi_end();
	bcm2835_close();
	return 0;
	
}