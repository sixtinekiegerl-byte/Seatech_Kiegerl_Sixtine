/* 
 * File:   main.c
 * Author: E306-PC4
 *
 * Created on September 29, 2025, 2:33 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "Robot.h"
#include "Toolbox.h"
#include "PWM.h"
#include "ADC.h"

int main(void) {
    //
    //Initialisation oscillateur
    //
    InitOscillator();

    //
    // Configuration des input et output (IO)
    //
    InitIO();
    InitTimer1();
    LED_BLANCHE_1 = 1;
    LED_BLEUE_1 = 1;
    LED_ORANGE_1 = 1;
    LED_ROUGE_1 = 1;
    LED_VERTE_1 = 1;
    LED_BLANCHE_2 = 1;
    LED_BLEUE_2 = 1;
    LED_ORANGE_2 = 1;
    LED_ROUGE_2 = 1;
    LED_VERTE_2 = 1;

    //
    // Boucle Principale
    // 
    InitPWM();
    InitTimer23();
    InitTimer1();
    InitADC1(); 
    //PWMSetSpeedConsigne(-5, MOTEUR_DROIT);
   

    while(1)
    {
        //unsigned int ADCValue0; 
       // unsigned int ADCValue1;
        //unsigned int ADCValue2;
        
        if (ADCIsConversionFinished() == 1)
        {
            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [0])* 3.3 / 4096;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [1])* 3.3 / 4096;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [2])* 3.3 / 4096;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
        }
        if (robotState.distanceTelemetreGauche < 30 ){
            LED_BLEUE_1 = 0;
        }else{
            LED_BLEUE_1 = 1;
        }
        
        if (robotState.distanceTelemetreCentre < 30){
            LED_ORANGE_1 = 0;
        }else{
            LED_ORANGE_1 = 1;                
        }
        if (robotState.distanceTelemetreDroit < 30){
            LED_ROUGE_1 = 0;
        }else{
            LED_ROUGE_1 = 1;                
        }
                
            
    }
    // fin main
}


