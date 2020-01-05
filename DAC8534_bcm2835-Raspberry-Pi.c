// DAC8534
// gcc -Wall 12.c -o 12 -lbcm2835 -lm

#define	DAC8534_VERSION	0


#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <stdint.h>

#define	CS0	RPI_V2_GPIO_P1_24

#define zero_voltage	0.0	// minimum output voltage
#define	Vref		4.49   // Regreding circuit designing(REF5045), reference voltage = input voltage
#define	DAC_data	16    // 16bit data

#define	MAX_V	4.4	
// #define	MAX_V	Vref-Vref/(1<<(DAC_data-1))	// output cannot exceed Vref (2**16- 1b)/2**16, change if lower value is necessary


void	write_one_DAC8534(char ch,float voltage);
void	write_all_DAC8534(float voltage);


int  main(int argc, char **argv){
	
	float voltage;

	#if DAC8534_VERSION==1
		char ch;
		printf("choose one channel from A B C or D, and the output voltage, example:\nA,1.2\n");
		scanf("%c,%f",&ch,&voltage);
	#else
		printf(" input the output voltage, example:\n1.2\n");
		scanf("%f",&voltage);
	#endif
	
	
	if (voltage > MAX_V){
		printf("voltage designation: %.2f exceeds MAX_VOLTAGE spec: %.6f \n", voltage, MAX_V);
		voltage = MAX_V;
		} 
		else if (voltage < 0){
				printf("voltage designation: %.2f exceeds MIN_VOLTAGE spec: %f \n", voltage, zero_voltage);
				voltage = zero_voltage;
			}

	if(!bcm2835_init()){
		printf("bcm2835_init failed. Are you running as root??\n");
		return 1;
	}
  
	if(!bcm2835_spi_begin()){
		printf("bcm2835_init failed. Are you running as root??\n");
		return 1;
	}	

	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);	//about 6.250MHz

	// bcm2835_gpio_write(CS0, HIGH);
	
	#if DAC8534_VERSION==1
		write_one_DAC8534(ch,voltage);
	#else
		write_all_DAC8534(voltage);
	#endif

	bcm2835_spi_end();
	bcm2835_close();
  
	return 0;
}

/*	单通道独自输出
Write to Data Buffer A and Load DAC A: DAC A output settles to specified value upon completion, so does B, C or D.
After completion of each write cycle, DAC analog output settles to the voltage specified.
that is to say: you can choose one channel to output the voltage which level you like, at the same time, other channel can be silence.

*/
void write_one_DAC8534(char ch,float voltage){
	
	// choose channel 
	uint8_t channel;
	switch(ch){
		
		case 'A': channel = 0x10; break;	// channel A address
		case 'B': channel = 0x12; break;	// channel B address
		case 'C': channel = 0x14; break;	// channel C address
		case 'D': channel = 0x16; break;	// channel D address
		default : printf("input error!!!\n");exit(0); 
	}
	
	// write data and output voltage
	uint16_t Data;
	Data = (uint16_t)round(65536 * voltage / Vref);	// output voltage range:0~Vref
	
	bcm2835_gpio_fsel(CS0,BCM2835_GPIO_FSEL_OUTP);
	
	// When SYNC goes LOW, it enables the input shift register and data is transferred in on the falling edges of the following clocks. before work, intialize DAC8534_SYNC
	bcm2835_gpio_write(CS0,HIGH);
	bcm2835_gpio_write(CS0,LOW);
	// DIN Serial Data Input. Data is clocked into the 24-bit input shift register on each falling edge of the serial clock input.
	bcm2835_spi_transfer(channel);
	bcm2835_spi_transfer((Data>>8));	// high 8 bit
	bcm2835_spi_transfer((Data&0xff));	// low 8 bit
	bcm2835_gpio_write(CS0,HIGH);
}

/*	所有通道一起输出
Write to Data Buffer A; Through Buffer D; Load DAC A Through DAC D Simultaneously.
The DAC A, DAC B, DAC C, and DAC D analog outputs simultaneously settle to the specified values upon completion of the 4th write sequence. 
(The “Load” command moves the digital data from the data buffer to the DAC register at which time the conversion takes place and the analog output is updated. “Completion” occurs on the 24th falling SCLK edge after SYNC LOW.)

*/
void write_all_DAC8534(float voltage){
	
	uint16_t Data;
	Data= (uint16_t)round(65536 * voltage / Vref);		// output voltage range:0~Vref
	
	uint8_t channel;
	channel = 0x34;
	
	bcm2835_gpio_fsel(CS0,BCM2835_GPIO_FSEL_OUTP);
	
	bcm2835_gpio_write(CS0,HIGH);
	bcm2835_gpio_write(CS0,LOW);
	bcm2835_spi_transfer(channel);
	bcm2835_spi_transfer((Data>>8));	// high 8 bit
	bcm2835_spi_transfer((Data&0xff));	// low 8 bit
	bcm2835_gpio_write(CS0,HIGH);
	
	/*	second method, a little fooish :)
	for(int i=0; i<4; i++){
		
		switch(i){
		
			case 0:
				channel = 0x00; break;	// Buffer A address
			case 1:
				channel = 0x02; break;	// Buffer B address
			case 2:
				channel = 0x04; break;	// Buffer C address
			case 3:
				channel = 0x26; break;	// Buffer D and update address
		}
		
		bcm2835_gpio_write(CS0,HIGH);
		bcm2835_gpio_write(CS0,LOW);
		bcm2835_spi_transfer(channel);
		bcm2835_spi_transfer((Data>>8));	// high 8 bit
		bcm2835_spi_transfer((Data&0xff));	// low 8 bit
		bcm2835_gpio_write(CS0,HIGH);

	}
	*/
	
}

/*	初始化，全部清零
initialize all channel zero level.

*/
void init_dac8534(){
	
	uint16_t Data;
	Data = 0x0000;
	
	uint8_t channel;
	
	channel = 0x34;
	
	bcm2835_gpio_write(CS0, HIGH);
	bcm2835_gpio_write(CS0, LOW);
	bcm2835_spi_transfer(channel);
	bcm2835_spi_transfer((Data>>8));	// 高八位
	bcm2835_spi_transfer((Data&0xff));	// 低八位
	bcm2835_gpio_write(CS0, HIGH);
	
}
