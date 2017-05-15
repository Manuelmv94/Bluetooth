/*! **********************************************************************************************
 * 2016  ITESM Campus Guadalajara. Laboratorio de Microcontroladores
 *
 * @file:      SCI.h
 * @author(s):    Manuel Madrigal Valenzuela; Efraín Duarte López    
 *
 * @brief (User's Manual):
 *   This is a SCI driver for the 9S08QG8 MCU. It also provides macro-like functions to
 *   reduce code footprint.
 *
 **************************************************************************************************/

#ifndef SCI_H_
#define SCI_H_


/*************************************************************************************************/
/*********************                 Includes                **********************/
/*************************************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "types.h"

/*************************************************************************************************/
/*********************                 Defines                    **********************/
/*************************************************************************************************/

/* Driver configuration. The user should modify these values */
#define SCI_BAUD_RATE   9600 /*Amount of bit transfers per second*/
#define SCI_MAX_MSG_SIZE    30  /*The maximum number of characters allowed to be sent and received*/

/* These should not be modified by the user */

#if ((SCI_BAUD_RATE < 9600) || (SCI_BAUD_RATE > 115200))
#error "SCI.h. SCI_BAUD_RATE  must be between 9,600 and 115,200 BPS";
#endif

#ifdef SCI_BAUD_RATE
#define SCALED_BR	(SCI_BAUD_RATE/100)
#define BIT_TIME_uS	10000/SCALED_BR
#endif

/*************************************************************************************************/
/*********************                 Typedefs                **********************/
/*************************************************************************************************/
typedef void (*FnPtr)(char); /*function pointer data type that receives a char and returns nothing*/

/*************************************************************************************************/
/*********************            Functions Like Macros              **********************/
/*************************************************************************************************/

/*The next Macros are used to control various optional features of the SCI system.*/

/*************************************************************************************************/
/*********************              Extern Variables              **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Extern Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************              Function Prototypes              **********************/
/*************************************************************************************************/

/*!*-----------------------------------------------------------------------------------------------
* \name     SCI_InitTx
* \brief    Configures the Baud Rate and enables the transmission
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void SCI_InitTx(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     SCI_SendMessage
* \brief    It buffers the message to be sent, enables interruptions and transmit the first character
*           of the message. The rest is done by interruptions. A flag indicating that the tansmission
*           is busy is set.
* \param    char[],u8
* \return   void
-------------------------------------------------------------------------------------------------*/
void SCI_SendMessage(const unsigned char msg[], u8 size);

/*!*-----------------------------------------------------------------------------------------------
* \name     SCI_TxIsBusy
* \brief    Returns TRUE if the transmission is busy sending a previous message, and FALSE if the
*           transmission is free to send a new message
* \param    void
* \return   bool
-------------------------------------------------------------------------------------------------*/
bool SCI_TxIsBusy(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     SCI_InitRx
* \brief    Enables the reception of messages. It also enables the interruptions upon reception
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void SCI_InitRx(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     SCI_RxSetCallback
* \brief    Registers a function to be called whenever the Rx Interruption is rised. In the SCI_Rx ISR, 
*           this function will be called.
* \param    FnPtr (Function pointer to the callback function)
* \return   void
-------------------------------------------------------------------------------------------------*/
void SCI_RxSetCallback(FnPtr);
/*************************************************************************************************/





#endif /* SCI_H_ */
