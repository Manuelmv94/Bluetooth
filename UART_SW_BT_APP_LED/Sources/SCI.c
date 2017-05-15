/*! **********************************************************************************************
* 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      SCI.c
* @author(s): Manuel Madrigal Valenzuela; Efraín Duarte López
*
* @brief (Theory of Operation)
*     Pretty straight forward. It configures the SCI hardware and implements the interruptions, on which
*     it calls the registered callback (if any)
*
**************************************************************************************************/


/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/
#include "SCI.h" 
#include "GPIO.h"
/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/
#define INIT_VALUE 0
#define BUS_CLK_scaledby100 40000  
#define ENABLE    1
#define DISABLE   0

/*************************************************************************************************/
/*********************                 Typedefs                **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Function Prototypes              **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/
static char    cTxMsg[SCI_MAX_MSG_SIZE];
static u8      u8TxSize;
static u8      u8TxIndex;
static bool    bTxIsBusy;
static u8 	   u8TxbitCount;
static char	   cTxData;

static u16 	   u16RxTime;
static u8	   u8RxbitCount;
static bool    bFrameError;
static bool	   bDataReady;

static FnPtr   fnRxCallback;
static char    cRxData;


/*************************************************************************************************/
/*********************              Global Variables              **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Static Constants                    **********************/
/*************************************************************************************************/


/*************************************************************************************************/
/*********************                  Global Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Exported Functions               **********************/
/*************************************************************************************************/

void SCI_InitTx(void)
{
   GPIO_SET(A,0);
   GPIO_CONFIG_OUT(A,0);
   TPMSC=0b00001010;//CLK 1 MHz
   
}

void SCI_SendMessage(const unsigned char msg[], u8 size)
{
   u8 i;//used to traverse the transmission buffer
   
   if(size>SCI_MAX_MSG_SIZE)  //if the size of the message is bigger than the buffer, the message is reduced to the buffer size
   {
      size=SCI_MAX_MSG_SIZE;
   }

   for(i=0;i<size;i++)  //saves the message into a buffer
   {
       cTxMsg[i]=msg[i];
   }
   u8TxSize=size;

   u8TxIndex=INIT_VALUE;
   
   TPMC0SC=0x58; //0101 1000   start bit hab interrupc oc
   TPMC0V=TPMCNT+BIT_TIME_uS;
   
   cTxData=cTxMsg[u8TxIndex++];   //send first character of the message
   u8TxbitCount=10;
   
   
   bTxIsBusy=TRUE;
   
}

bool SCI_TxIsBusy(void)
{
   return bTxIsBusy;
}

void SCI_InitRx(void)
{
   GPIO_CONFIG_IN(B,5);
   TPMC1SC=0b01001000;//Interrupts enabled, input capture, falling edge
}

void SCI_RxSetCallback(FnPtr f)
{
   if(f)
   {
      fnRxCallback=f;
   }
}


//-------------------------------------------------------------------------------------------------


/*************************************************************************************************/
/*********************               Private Functions               **********************/
/*************************************************************************************************/

/*!*-----------------------------------------------------------------------------------------------
* \name     Tx Interruption
* \brief    It sends a new character if there are some left to be sent. Otherwise, it disables
*           the interruption and clears the busy flag
-------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtpmch0 void CH0_ISR ()
{
	(void) TPMC0SC;
	 TPMC0SC_CH0F=0;
	 TPMC0V+=BIT_TIME_uS;
	 u8TxbitCount--;
	 
	 if(u8TxbitCount<10 && u8TxbitCount>1)
	 {
		 if(cTxData & 0x01)
	 	 {
			 TPMC0SC=0x5C;//interrupciones set
	 	 }
	 	 else
	 	 {
	 		 TPMC0SC=0x58;//interrupciones clear
	 	 }
	 	 cTxData>>=1;
	 }
	 if(u8TxbitCount==1)
	 {
		 TPMC0SC=0x5C;//interrupciones set
	 }
	 if(u8TxbitCount==0)
	 {
		 cTxData=cTxMsg[u8TxIndex++];//send new character
	 	 	 
	 	 if(u8TxIndex<=u8TxSize)
	 	 {
	 		 u8TxbitCount=10;
	 		 TPMC0SC=0x58;//clear
	 	 }
	 	 else
	 	 {
	 		 TPMC0SC=0x1C;
	 		 bTxIsBusy=FALSE;	 
	 	 }
 	 }	 
}

/*!*-----------------------------------------------------------------------------------------------
* \name     Interruption
* \brief    It calls a pre-set function(if any) to do something with the received character
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
interrupt VectorNumber_Vtpmch1 void CH1_ISR ()
{
   (void) TPMC1SC;
   TPMC1SC_CH1F=0;
   
   if(TPMC1SC_MS1B==0 && TPMC1SC_MS1A==0)//INPUT CAPTURE
   {
	   u16RxTime=TPMC1V;
	   TPMC1SC=0b01010000;//Configurar Output compare
	   TPMC1V=u16RxTime+3*BIT_TIME_uS/2;
	   u8RxbitCount=0;
   }
   else
   {
	   if(u8RxbitCount<8)
	   {
		   cRxData>>=1;
		   if(GPIO_IS_SET(B,5))
		   {
			   cRxData|=0x80;
		   }
		   
		   u8RxbitCount++;
		   TPMC1V+=BIT_TIME_uS;
		   
	   }
	   else
	   {
		   if(GPIO_IS_CLR(B,5))
		   {
			   bFrameError=TRUE;
		   }
		   else
		   {
			   bFrameError=FALSE;
			   bDataReady=TRUE;
			   TPMC1SC=0b01001000;//CONFIGURAR INPUT CAPTURE
			   
			   if(fnRxCallback)
			   {
			      (*fnRxCallback)(cRxData);
			   }
		   }
	   }
   }
   
   
}


	 

