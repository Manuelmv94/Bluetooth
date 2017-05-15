//Tx-->PTA0--> pin15 tarjeta
//Rx-->PTB5--> pin 23 tarjeta

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "SCI.h"
#include "MessageManager.h"
#include "StringUtilis.h"
#define START_TIMER_RTI SRTISC = 0b00000110 //Start counting to 512 ms
#define TIMER_RTI_NOT_FINISHED SRTISC_RTIF==0 //Timer finish indicator flag is off
#define TIMER_RTI_RESET_FLAG SRTISC_RTIACK = 1 //Turning timer finish indicator flag off again
#define STOP_TIMER_RTI SRTISC=0b00000000 //Stop timer
u8 u8MessageSize;
unsigned char cMainMessage[MESSAGE_MANAGER_MAX_MSG_SIZE];
char array[]={0b01010101};
u8 blink;
u8 done;
//Function that uses the SRTISC register to count for 512 ms and then stop 
void timer_half_a_second(void)
{
	
   /* Configuring intern clock register settings to use the MC without the development kit */
   ICSTRM=NVICSTRM;		
   ICSSC_FTRIM=NVFTRIM;
	
   START_TIMER_RTI; 
   do
   {
      __RESET_WATCHDOG();
		
   }while(TIMER_RTI_NOT_FINISHED);
	
   TIMER_RTI_RESET_FLAG;
   STOP_TIMER_RTI; 
}

void main(void) {
  EnableInterrupts;
  /* include your code here */
  MessageManager_Init();
  PTBDD_PTBDD6=1;
  blink=0;
  done=0;
  
  

  for(;;) {
	  
    __RESET_WATCHDOG();	/* feeds the dog */
    if(blink==1)
    {
    	PTBD_PTBD6=!PTBD_PTBD6;
    	timer_half_a_second();
    	
    }
    if(MessageManager_IsMessageReady())
    {
    	MessageManager_getMessage(cMainMessage,&u8MessageSize);
    	if(StringUtils_strcmp(cMainMessage,"onz",3))
    	{
    		done=1;
    		PTBD_PTBD6=0;
    		blink=0;
    		
    	}
    	else if(StringUtils_strcmp(cMainMessage,"offz",4))
    	{
    		PTBD_PTBD6=1;
    		blink=0;
    		done=1;
    		
    	}
    	else if(StringUtils_strcmp(cMainMessage,"blinkz",6))
    	{
    		blink=1;
    		done=1;
    	}
    	else
    	{
    		done=0;
    	}
    	if(!MessageManager_TxIsBusy())
    	{
    		MessageManager_SendMessage("\n\rDONE",6);
    		
    		if(done)
    		{
    			MessageManager_SendMessage("\n\rDONE",6);
    		}
    		else
    		{
    			MessageManager_SendMessage("\n\rNOPE",6);
    		}
    		
    		
    	}
    }
    
  } /* loop forever */
  /* please make sure that you never leave main */
}
