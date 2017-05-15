/*! **********************************************************************************************
* 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores 
*  
*
* @file:      GPSManager.c
* @author(s): Manuel Madrigal Valenzuela; Efraín Duarte López
*
* @brief (Theory of Operation)
*     This driver uses the SCI driver to receive and transmit data through the serial port.
*     The receiving part is done by the MessageManager_buildMessage function, which is called
*     from an interruption of the SCI, buffering the message in a bi-dimensional array.
*     When the message is ready, it is hold by the cMessage char array.
*     The transmitting part is done by just passing the parameters to the SCI driver.
*     
**************************************************************************************************/


/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "GPSManager.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define INIT_VALUE   0

/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/
static const u8 u8HashKeyToMatch=(u8)'M'+(u8)'C'; 
static const char cMessagesArray[11][23]={"\n\rUTC Time (HhMmSs): ",
									  "\n\rData Status: ",
									  "\n\rLatitude: ",
									  "\n\rDirection: ",
									  "\n\rLongitude: ",
									  "\n\rDirection: ",
									  "\n\rSpeed in knots: ",
									  "\n\rHeading in degrees: ",
									  "\n\rDate UTC(DdMmAa): ",
									  "\n\rMagnetic variation: ",
									  "\n\rDirection: "
									 };
static const u8 u8SizesArray[]={21,15,12,13,13,13,18,22,20,22,13};

/*************************************************************************************************/
/*********************					Global Variables					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Static Constants                    **********************/
/*************************************************************************************************/
static bool bValidString;
static u8 	u8StringPosition;
static u8 u8HashKey;
static u8 u8CommaCounter;

/*************************************************************************************************/
/*********************                  Global Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************				   Exported Functions					**********************/
/*************************************************************************************************/

void GPSManager_Init(void)
{
   SCI_InitTx();
   SCI_InitRx();
   SCI_RxSetCallback(&GPSManager_validateMessage);//Sets the function to be called when an interruption of the SCI reception is rised
   bValidString=FALSE;
   u8StringPosition=0;
   u8HashKey=0;
   u8CommaCounter=0;
}

void GPSManager_validateMessage(char cReceivedChar)
{
   
   if(bValidString==TRUE)
   {
	  if(u8HashKey==u8HashKeyToMatch)
	  {
		  if(cReceivedChar==',')
		  {
			  SCI_SendMessage(cMessagesArray[u8CommaCounter],u8SizesArray[u8CommaCounter++]);
		  }
		  else
		  {
			  SCI_SendMessage(&cReceivedChar,1);
		  }
	  }
	  
	  if(u8StringPosition==4 || u8StringPosition==5)
	  {
		  u8HashKey+=(u8)cReceivedChar;
	  }
	  
	  u8StringPosition++;
	  
	  if(cReceivedChar == ASCII_ENTER_CODE)
	  {
		 bValidString=FALSE;
		 u8StringPosition=0;
		 u8HashKey=0;
		 u8CommaCounter=0;
		 
	  } 
   }
   else
   {
	   if(cReceivedChar == '$')
	   {
		   bValidString=TRUE;
		   u8StringPosition++;
	   }
   }
}





//-------------------------------------------------------------------------------------------------


/*************************************************************************************************/
/*********************				    Private Functions					**********************/
/*************************************************************************************************/

