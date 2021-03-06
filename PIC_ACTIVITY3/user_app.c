/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"
#define _XTAL_FREQ 16000000
/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;  
  /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{   
    LATA=0x80;
    T0CON0 = 0x90;
    T0CON1 = 0x54;

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    static u32 u16Count=0;
    static u8 toggle=0;
    u16Count+=1;
    u16 Temp=LATA;
    u8 au8Pattern[]={0x01,0x02,0x04,0x10,0x20};
    static u8 n=0;
    if(u16Count==500 && toggle==0){
        if(n<5){
                u16Count=0;
                LATA=au8Pattern[n]; 
                toggle=1;
                n+=1;
        } 
        else{
            n=0;
            u16Count=0;
            LATA=au8Pattern[n];
            toggle=1;
        }
    }
    else{
        toggle=0;
    }
    
} /* end UserAppRun */

void TimeXus(u16 u16Time_delay)
{
    T0CON0 &= 0x7F;//Disable the timer during configuration.
    
    //Set TMR0H and TMR0L to values specified by user.
    TMR0H = (u8)((0xFFFF - u16Time_delay) >> 8);
    TMR0L = (u8)((0xFFFF - u16Time_delay) & 0x00FF);
    
    //Clear TMR0IF and enables the timer.
    PIR3 &= 0x7F;
    T0CON0 |= 0x80;
}


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
