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
#include "main.h"
unsigned char stateRobot;
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
    LED_BLEUE_2 = 0;
    LED_ORANGE_2 = 0;
    LED_ROUGE_2 = 0;
    LED_VERTE_2 = 0;
    
    PWM_ENABLE = 1;
  

    //
    // Boucle Principale
    // 
    InitPWM();
    InitTimer23();
    InitTimer1();
    InitADC1();
    InitTimer4();
    //PWMSetSpeedConsigne(-5, MOTEUR_DROIT);
    stateRobot= STATE_ARRET;

    while (1) {

        //unsigned int ADCValue0; 
        // unsigned int ADCValue1;
        //unsigned int ADCValue2;

        if (ADCIsConversionFinished() == 1) {
            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [0])* 3.3 / 4096;
            robotState.distanceTelemetreExtremeGauche = 34 / volts - 5;
            volts = ((float) result [1])* 3.3 / 4096;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [2])* 3.3 / 4096;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
             volts = ((float) result [3])* 3.3 / 4096;
            robotState.distanceTelemetreDroit = 34 / volts - 5;            
            volts = ((float) result [4])* 3.3 / 4096;
            robotState.distanceTelemetreExtremeDroit = 34 / volts - 5;           
        }
        if (robotState.distanceTelemetreGauche < 30) {
            LED_BLEUE_1 = 1;
        } else {
            LED_BLEUE_1 = 0;
        }

        if (robotState.distanceTelemetreCentre < 30) {
            LED_ORANGE_1 = 1;
        } else {
            LED_ORANGE_1 = 0;
        }
        if (robotState.distanceTelemetreDroit < 30) {
            LED_ROUGE_1 = 1;
        } else {
            LED_ROUGE_1 = 0;
        }
        if (robotState.distanceTelemetreExtremeGauche < 30) {
            LED_BLANCHE_1 = 1;
        } else {
            LED_BLANCHE_1 = 0;
        }
        if (robotState.distanceTelemetreExtremeDroit < 30) {
            LED_VERTE_1 = 1;
        } else {
            LED_VERTE_1 = 0;
        }
        if (Inter1 == 1 ){
            LED_BLANCHE_2 = 0;
        }
            
    }
    // fin main
}

//    void OperatingSystemLoop(void) {
//    
//    // Initialisation à 1 pour ne pas déclencher au démarrage (car bouton relâché = 1)
//    static unsigned char previousButtonState = 1; 
//    unsigned char currentButtonState = Inter1;    // Lecture de H0 (via _RH0)
//
//    // Détection d'un changement d'état
//    if (currentButtonState != previousButtonState) {
//        
//        // Si le bouton passe à 0 -> C'est un APPUI (Active Low)
//        if (currentButtonState == 0) { 
//            
//            if (stateRobot == STATE_ARRET) {
//                stateRobot = STATE_ATTENTE; // Démarrage
//            } else {
//                stateRobot = STATE_ARRET;   // Arrêt
//                // Sécurité : couper les moteurs immédiatement
//                PWMSetSpeedConsigne(0, MOTEUR_DROIT);
//                PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
//            }
//        }
//    }
//    // Mise à jour de la mémoire du bouton pour le prochain tour
//    previousButtonState = Inter1;
//    
//        switch (stateRobot) {
//            case STATE_ATTENTE:
//                timestamp = 0;
//                PWMSetSpeedConsigne(0, MOTEUR_DROIT);
//                PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
//                stateRobot = STATE_ATTENTE_EN_COURS;
//            case STATE_ATTENTE_EN_COURS:
//                if (timestamp > 1000)
//                    stateRobot = STATE_AVANCE;
//                break;
//            case STATE_AVANCE:
//                PWMSetSpeedConsigne(30, MOTEUR_DROIT);
//                PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
//                stateRobot = STATE_AVANCE_EN_COURS;
//                break;
//            case STATE_AVANCE_EN_COURS:
//                SetNextRobotStateInAutomaticMode();
//                break;
//            case STATE_TOURNE_GAUCHE:
//                PWMSetSpeedConsigne(30, MOTEUR_DROIT);
//                PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
//                stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
//                break;
//            case STATE_TOURNE_GAUCHE_EN_COURS:
//                SetNextRobotStateInAutomaticMode();
//                break;
//            case STATE_TOURNE_DROITE:
//                PWMSetSpeedConsigne(0, MOTEUR_DROIT);
//                PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
//                stateRobot = STATE_TOURNE_DROITE_EN_COURS;
//                break;
//            case STATE_TOURNE_DROITE_EN_COURS:
//                SetNextRobotStateInAutomaticMode();
//                break;
//            case STATE_TOURNE_SUR_PLACE_GAUCHE:
//                PWMSetSpeedConsigne(15, MOTEUR_DROIT);
//                PWMSetSpeedConsigne(-15, MOTEUR_GAUCHE);
//                stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
//                break;
//            case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
//                SetNextRobotStateInAutomaticMode();
//                break;
//            case STATE_TOURNE_SUR_PLACE_DROITE:
//                PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
//                PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
//                stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
//                break;
//            case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
//                SetNextRobotStateInAutomaticMode();
//                break;
//            default:
//                stateRobot = STATE_ATTENTE;
//                break;
//        }
//    }

void OperatingSystemLoop(void) {

    // --- GESTION DU BOUTON (ON/OFF avec mémoire) ---
    static int buttonTimer = 0;          // Compteur pour l'anti-rebond
    static unsigned char buttonState = 0; // 0: Attente Appui, 1: Validation, 2: Attente Relachement
    static unsigned long startTime = 0;   // Mémorise quand le robot a démarré

    switch (buttonState) {
        case 0: // ÉTAT : ATTENTE D'APPUI
            if (Inter1 == 0) { // Si on détecte un appui (0V)
                buttonTimer = 0;
                buttonState = 1; // On part vérifier si c'est un vrai appui
            }
            break;

        case 1: // ÉTAT : ANTI-REBOND (Validation)
            if (Inter1 == 0) { // Si le bouton est toujours appuyé
                buttonTimer++;
                if (buttonTimer > 20) { // Après 20ms de stabilité (20 cycles à 1kHz)
                    // --- C'EST ICI QUE LE BASCULEMENT SE FAIT ---
                    if (stateRobot == STATE_ARRET) {
                        stateRobot = STATE_ATTENTE; // Démarrer
                    } else {
                        stateRobot = STATE_ARRET;   // Arrêter
                        PWMSetSpeedConsigne(0, MOTEUR_DROIT);
                        PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                    }
                    // ---------------------------------------------
                    buttonState = 2; // On passe en attente de relâchement
                }
            } else {
                buttonState = 0; // C'était un parasite, on revient au début
            }
            break;

        case 2: // ÉTAT : ATTENTE DE RELÂCHEMENT
            if (Inter1 == 1) { // Une fois le bouton relâché (3.3V)
                 buttonState = 0; // On est prêt pour un nouvel appui
            }
            break;
    }

    // --- GESTION DU ROBOT (Votre machine à états principale) ---
    switch (stateRobot) {
        
        case STATE_ARRET:
            // On s'assure que les moteurs restent coupés
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            break;

        case STATE_ATTENTE:
            timestamp = 0;
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_ATTENTE_EN_COURS;
            break;

        case STATE_ATTENTE_EN_COURS:
            if (timestamp > 1000)
                stateRobot = STATE_AVANCE;
            break;

        case STATE_AVANCE:
            PWMSetSpeedConsigne(-30, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-30, MOTEUR_GAUCHE);
            stateRobot = STATE_AVANCE_EN_COURS;
            break;

        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_GAUCHE:
            PWMSetSpeedConsigne(-30, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;

        case STATE_TOURNE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_DROITE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-30, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
            break;

        case STATE_TOURNE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_SUR_PLACE_GAUCHE:
            PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
            PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
            break;

        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_SUR_PLACE_DROITE:
            PWMSetSpeedConsigne(15, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-15, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
            break;

        case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
            

        default:
            stateRobot = STATE_ARRET; // Sécurité par défaut
            break;
    }
    
    if (stateRobot != STATE_ARRET) {
        // Si le temps écoulé dépasse 60 000 ms (1 minute)
        if ((timestamp - startTime) > 60000) {
            stateRobot = STATE_ARRET; // Arrêt forcé
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
        }
    }
}



//    unsigned char nextStateRobot = 0;

//    void SetNextRobotStateInAutomaticMode() {
//        unsigned char positionObstacle = PAS_D_OBSTACLE;
//        //éDtermination de la position des obstacles en fonction des ééètlmtres
//        if (robotState.distanceTelemetreDroit < 30 &&
//                robotState.distanceTelemetreCentre > 20 &&
//                robotState.distanceTelemetreGauche > 30 &&
//                robotState.distanceTelemetreExtremeDroit < 20 &&
//                robotState.distanceTelemetreExtremeGauche > 30) //Obstacle àdroite
//            positionObstacle = OBSTACLE_A_DROITE;
//        else if (robotState.distanceTelemetreDroit > 30 &&
//                robotState.distanceTelemetreCentre > 20 &&
//                robotState.distanceTelemetreGauche < 30 &&
//                robotState.distanceTelemetreExtremeDroit > 30 &&
//                robotState.distanceTelemetreExtremeGauche < 20) //Obstacle àgauche
//            positionObstacle = OBSTACLE_A_GAUCHE;
//        else if (robotState.distanceTelemetreCentre < 20) //Obstacle en face
//            positionObstacle = OBSTACLE_EN_FACE;
//        else if (robotState.distanceTelemetreDroit > 30 &&
//                robotState.distanceTelemetreCentre > 20 &&
//                robotState.distanceTelemetreGauche > 30 &&
//                robotState.distanceTelemetreExtremeDroit > 30 &&
//                robotState.distanceTelemetreExtremeGauche > 30) //pas d?obstacle
//            positionObstacle = PAS_D_OBSTACLE;
//        //éDtermination de lé?tat àvenir du robot
//        if (positionObstacle == PAS_D_OBSTACLE)
//            nextStateRobot = STATE_AVANCE;
//        else if (positionObstacle == OBSTACLE_A_DROITE)
//            nextStateRobot = STATE_TOURNE_GAUCHE;
//        else if (positionObstacle == OBSTACLE_A_GAUCHE)
//            nextStateRobot = STATE_TOURNE_DROITE;
//        else if (positionObstacle == OBSTACLE_EN_FACE)
//            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
//        //Si l?on n?est pas dans la transition de l?étape en cours
//        if (nextStateRobot != stateRobot - 1)
//            stateRobot = nextStateRobot;
//    }

unsigned char nextStateRobot = 0;

void SetNextRobotStateInAutomaticMode() 
{
    // 1. Etape de "Normalisation" : On transforme les distances en 0 ou 1
    // Seuil de détection (ajustez 30 selon vos besoins réels comme dans votre code original)
    int seuil = 30; 
    
    // C1 change tous les pas (0,1,0,1) -> C'est le Bit 0 (Poids 1)
    int c1 = (robotState.distanceTelemetreExtremeGauche < seuil) ? 1 : 0;
    
    // C2 change tous les 2 pas -> C'est le Bit 1 (Poids 2)
    int c2 = (robotState.distanceTelemetreGauche < seuil) ? 1 : 0;
    
    // C3 change tous les 4 pas -> C'est le Bit 2 (Poids 4)
    int c3 = (robotState.distanceTelemetreCentre < seuil) ? 1 : 0; // Seuil 20 pour le centre selon votre code
    
    // C4 change tous les 8 pas -> C'est le Bit 3 (Poids 8)
    int c4 = (robotState.distanceTelemetreDroit < seuil) ? 1 : 0;
    
    // C5 change tous les 16 pas -> C'est le Bit 4 (Poids 16)
    int c5 = (robotState.distanceTelemetreExtremeDroit < seuil) ? 1 : 0;

    // 2. Calcul de la "Situation" (correspond à S1...S32 sur votre feuille)
    // Cela donne un nombre entre 0 et 31.
    // Exemple : Si C1 et C2 détectent, situation = 1 + 2 = 3.
    int situation = c1 + (c2 * 2) + (c3 * 4) + (c4 * 8) + (c5 * 16);

    // 3. Application de la logique de la Table de Vérité
    // Note : "situation" est décalé de -1 par rapport à votre feuille (S1 = 0, S32 = 31)

    // Cas SPIRALE (Demi-tour)
    // Correspond aux colonnes S25 à S32 (dès que C4 et C5 sont à 1, soit situation >= 24)
    if ((situation >= 18 && situation <= 19) || (situation >= 25 && situation <= 27) || (situation >= 21 && situation <= 23) || (situation >= 29 && situation <= 31) ) 
    {
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE; // Ou STATE_TOURNE_SUR_PLACE_GAUCHE 
    }
    else if  ((situation == 15)||(situation == 9)||(situation == 11))
    {
        nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE; // Ou STATE_TOURNE_SUR_PLACE_DROITE 
    }
    // Cas AVANCE (-)
    // Correspond à S1 (00000)
    else if (situation == 0 || situation == 1 || situation == 16 || situation == 17) 
    {
        nextStateRobot = STATE_AVANCE;
    }
    // Correspond aux colonnes S3, S4, S9, S10, S11, S12, S17, S18, S19, S20
    else if (situation == 2 || situation == 3 || situation == 13 || (situation >=5 && situation <=7) ||
             (situation == 8 )||(situation == 10))
    {
        nextStateRobot = STATE_TOURNE_DROITE;
    }
    // Tous les autres cas (S2, S5-S8, S13-S16, S21-S24)
    else 
    {
        nextStateRobot = STATE_TOURNE_GAUCHE;
    }

    // 4. Transition d'état (Code original conservé)
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}
