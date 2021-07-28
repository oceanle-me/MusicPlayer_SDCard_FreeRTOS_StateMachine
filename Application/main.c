
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#define TARGET_IS_BLIZZARD_RB1
#include "driverlib/rom.h"



#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                          char * pcTaskName )
//void
//vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}



//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************




static void Main_Task(void *pvParameters );
static void UpdateStateOfSystem_Task(void *pvParameters);

/*****************************************************************/
/*******************************************************************/
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"
#include "debug.h"
#include "driverlib/udma.h"
#include "driverlib/timer.h"
#include "driverlib/ssi.h"
#include "ff.h"
#include "driverlib/pwm.h"

#include "Init.h"
#include "SW_StateMachine.h"

//! - SoftSSIClk - PA2      PushPull
//! - SoftSSIFss - PA3      Pull up
//! - SoftSSIRx  - PA4      DO Pull-up  MISO
//! - SoftSSITx  - PA5      DI PushPull MOSI
//!  PB6 - PinOut PWM

void    PWM0Gen0IntHandler(void);

void    PlayMusic(uint8_t * p_songName, uint8_t num);

void    GPIOIntHandler(void);

void Timer0A_Int(void);


FATFS FatFs;        /* FatFs work area needed for each volume */
FIL Fil;            /* File object needed for each open file */
DIR DirMusic;
FILINFO FileInfo;



UINT out_stream (   /* Returns number of bytes sent or stream status */
        const BYTE *p,  /* Pointer to the data block to be sent */
        UINT btf        /* >0: Transfer call (Number of bytes to be sent). 0: Sense call */
);

#define BUFFER_SIZE 500

bool timeOutTimer0 = true;

uint8_t allSongName[10][13]; //this array is used to store all the file names had been read by FatFs, we can use it to play a previous song.
                            // each song name will be stored into 13 bytes.. of this array

uint8_t  totalSongs = 0 ; // ordinal number of song is playing (stt)
uint8_t  numOrderOfSong;

//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
xSemaphoreHandle    BiSemap_PWM;
xSemaphoreHandle    BiSemap_UpdateStateMachine;
xQueueHandle        QueueMainBuffer;

//*****************************************************************************
int main(void)
{

        SysCtlClockSet(SYSCTL_SYSDIV_3 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
            GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
            InitGPIO();
            InitDebug();
            InitPWM();
            vSemaphoreCreateBinary(BiSemap_PWM);
            vSemaphoreCreateBinary(BiSemap_UpdateStateMachine);
            QueueMainBuffer = xQueueCreate(BUFFER_SIZE,1);
            if(QueueMainBuffer==0) DBG("creating queue failed  \n");

           if(pdPASS != xTaskCreate(Main_Task, "Main_Task", 1024, NULL, 2, NULL) ) {
               DBG("create Main task failed");
           }

           if(pdPASS != xTaskCreate(UpdateStateOfSystem_Task,
                                    "UpdateStateOfSystem_Task", 1024, NULL, 3, NULL) ) {
               DBG("create UpdateStateOfSystem_Task failed");
           }

            vTaskStartScheduler();

        while(1);

}

static void Main_Task(void *pvParameters )
{
    FRESULT fr;
    if(f_mount(&FatFs, "", 0)==FR_OK)     /* Give a work area to the default drive */{
        fr = f_findfirst(&DirMusic,&FileInfo, "0:","?*.WAV");
        if(fr==FR_OK)
        {
            numOrderOfSong =1;  // we have at least 1 .wav file(s) in this SD card
            DBG("Connection succeed! Open 0: directory  \n");
            //This below while loop is used to save all .wav file names into   allSongName[500], and count the number of songs.
            while (fr == FR_OK && FileInfo.fname[0]) {         /* Repeat while an item is found */
                uint8_t ovcmh;
                for(ovcmh=0; ovcmh<13;ovcmh++ ){  //save file name to have the ability to play previous song
                    allSongName[totalSongs][ovcmh] = FileInfo.fname[ovcmh];
                }

                totalSongs++;  //increase number of songs (stt)
                DBG("Song %d: %s\n",totalSongs, &allSongName[totalSongs-1][0]);                /* Print the object name */

                fr = f_findnext(&DirMusic, &FileInfo);               /* Search for next item */
                //should add a condition if having too many files then inform user
            }


/******************************************************************************************/
/*Endless loop of playing all the songs*/
            while (1){
                while( (0 < numOrderOfSong) && (numOrderOfSong <= totalSongs) ){
                    PlayMusic( &allSongName[numOrderOfSong-1][0]  ,  numOrderOfSong);
                    numOrderOfSong++;
                }
                numOrderOfSong=1;
            }
        }
/*********************************************************************************************/
    }

    DBG("Connection failed! Please Check your hardware and reset it!\n");
    for (;;) { //blink LED when encountering fault
        GPIO_PORTF_DATA_R ^= 0b10;
        SysCtlDelay(SysCtlClockGet()/3/5);
    }

}

static void UpdateStateOfSystem_Task(void *pvParameters)
{   xSemaphoreTake(BiSemap_UpdateStateMachine,0);
    InitState();
    while(1){
        xSemaphoreTake(BiSemap_UpdateStateMachine,portMAX_DELAY);
        UpdateStateMachine();
    }
}

UINT out_stream (   /* Returns number of bytes sent or stream status */
        const BYTE *p,  /* Pointer to the data block to be sent */
        UINT btf        /* >0: Transfer call (Number of bytes to be sent). 0: Sense call */
)
{
    UINT cnt = 0;
    if (btf == 0) {     /* Sense call */
        /* Return stream status (0: Busy, 1: Ready) */
        /* When once it returned ready to sense call, it must accept a byte at least */
        /* at subsequent transfer call, or f_forward will fail with FR_INT_ERR. */
        //        if (FIFO_READY) cnt = 1;
        cnt = 1;
    }
    else {              /* Transfer call */
        do {    /* Repeat while there is any data to be sent and the stream is ready */
            //           FIFO_PORT = *p++;
            xQueueSend(QueueMainBuffer,p,portMAX_DELAY);
            p++;
            cnt++;
            while(0);

        }
        while ((cnt < btf)  /*&& (audioState != CHANGE_AUDIO)*/ /*&& FIFO_READY*/);
    }

    if( (mainState == STATE_NEXT) || (mainState == STATE_PREVIOUS) ){
        xSemaphoreGive(BiSemap_UpdateStateMachine);
        DBG("change song \n");
        cnt = 0;
    }
    return cnt;
}


void    PWM0Gen0IntHandler(void){
    //each 1/16KHz , PWM will reload the 8-bit value into PWM pulse width register.
    portBASE_TYPE xHigherPriorityTaskWoken;
    uint8_t u8ReceiverData;
    PWMGenIntClear(PWM0_BASE, PWM_GEN_0, PWM_INT_CNT_LOAD);

    xQueueReceiveFromISR(QueueMainBuffer, &u8ReceiverData, &xHigherPriorityTaskWoken);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, u8ReceiverData);
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken); //this is not necessary
}




void    PlayMusic(uint8_t * p_songName, uint8_t num){
    uint32_t rx_32;
    if (f_open(&Fil, p_songName, FA_READ) == FR_OK) {
        DBG("Open File Num.%d %s\n",num, p_songName);
        mainState = STATE_ON;
        PWMGenEnable(PWM0_BASE, PWM_GEN_0);

        f_forward(&Fil, out_stream, f_size(&Fil) ,(UINT*) &rx_32);

        f_close(&Fil);                         /* Close the file */
        PWMGenDisable(PWM0_BASE, PWM_GEN_0);
        mainState = STATE_OFF;
    }
    else {
        DBG("Could not open file %s\n", p_songName);
        for(;;){    //blink LED when encountering fault
            GPIO_PORTF_DATA_R ^= 0b10;
            SysCtlDelay(SysCtlClockGet()/3/5);
        }
    }
}


//Interrupt service routine
void GPIOIntHandler(void){
    // On/Off audio if press switch 1
    // play next song if press switch 2
    // play previous song if press doubly switch 2
    uint32_t intGPIOStatus;
    IntMasterDisable();
    intGPIOStatus = GPIOIntStatus(GPIO_PORTF_BASE, true);

    if (intGPIOStatus == GPIO_INT_PIN_4 ){//SW1
        swState = STATE_SW1;
        GPIO_PORTF_DATA_R ^= 0b100;
    }
    else if (intGPIOStatus == GPIO_INT_PIN_0 ){//SW2
        GPIO_PORTF_DATA_R ^= 0b10;
        swState = STATE_SW2;
    }


    while(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0))) ; //wait here until the button is released. press=0
    SysCtlDelay((SysCtlClockGet()/3/1000)*40); //avoid vibration of buttons within 40ms

    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(BiSemap_UpdateStateMachine, &xHigherPriorityTaskWoken);
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    GPIOIntClear(GPIO_PORTF_BASE, intGPIOStatus);
    IntMasterEnable();
}

void Timer0A_Int(void)
    {  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);    // Clear the timer interrupt
        timeOutTimer0=true;
        DBG("Ti\n");
        portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(BiSemap_UpdateStateMachine, &xHigherPriorityTaskWoken);
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }



