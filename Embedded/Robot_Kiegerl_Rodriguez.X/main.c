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
    //PWMSetSpeed(-20, MOTEUR_DROIT);
    _T3Interrupt();
   
    
    while(1)
    {
        
    }
    // fin main
}


