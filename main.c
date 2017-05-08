// this code sets up counter1 A output at 25% AND b OUTPUT AT 75%
// USING ICR1 AS TOP (16bit), Fast PWM:

#include <stdlib.h>
#include <avr/io.h>
#define RELOAD 2
#include <avr/interrupt.h>


int main(void)

{


	while(1)
	
	{
		void TWIInit(void)
		{
			//set SCL to 400kHz
			TWSR = 0x00;
			TWBR = 0x0C;
			//enable TWI
			TWCR = (1<<TWEN);
		}
		void TWIStart(void)
		{
			TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
			while ((TWCR & (1<<TWINT)) == 0);
		}
		//send stop signal
		void TWIStop(void)
		{
			TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
		}
				int8_t EEWriteByte(uint16_t u16addr, uint8_t u8data)
		{
			TWIStart();
			if (TWIGetStatus() != 0x08)
				return ERROR;
			//select devise and send A2 A1 A0 address bits
			TWIWrite((EEDEVADR)|(uint8_t)((u16addr & 0x0700)>>7));
			if (TWIGetStatus() != 0x18)
				return ERROR;  
			//send the rest of address
			TWIWrite((uint8_t)(u16addr));
			if (TWIGetStatus() != 0x28)
				return ERROR;
			//write byte to eeprom
			TWIWrite(u8data);
			if (TWIGetStatus() != 0x28)
				return ERROR;
			TWIStop();
			return SUCCESS;
		}


	} // end of while
		
}

	

		

