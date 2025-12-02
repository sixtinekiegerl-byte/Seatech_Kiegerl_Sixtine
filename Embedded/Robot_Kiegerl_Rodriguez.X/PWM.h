/* 
 * File:   PWM.h
 * Author: E306-PC4
 *
 * Created on 1 octobre 2025, 08:47
 */

#ifndef PWM_H
#define	PWM_H
#define MOTEUR1_IN1 _LATB14
#define MOTEUR1_IN2 _LATB15
#define MOTEUR_DROIT 0
#define MOTEUR_GAUCHE 1


//Configuration spécifique du moteur gauche
#define MOTEUR_GAUCHE_H_IO_OUTPUT MOTEUR1_IN1
#define MOTEUR_GAUCHE_L_IO_OUTPUT MOTEUR1_IN2
#define MOTEUR_GAUCHE_L_PMW_ENABLE IOCON1bits.PENL
#define MOTEUR_GAUCHE_H_PMW_ENABLE IOCON1bits.PENH
#define MOTEUR_GAUCHE_DUTY_CYCLE PDC1


//Configuration spécifique du moteur droit
#define MOTEUR_DROITE_L_IO_OUTPUT MOTEUR2_IN2
#define MOTEUR_DROITE_L_PMW_ENABLE IOCON1bits.PENL
#define MOTEUR_DROITE_H_PMW_ENABLE IOCON1bits.PENH
#define MOTEUR_DROITE_DUTY_CYCLE PDC2

void InitPWM(void);
//void PWMSetSpeed(float , int);  
void PWMUpdateSpeed();
void PWMSetSpeedConsigne(float, char);
#endif	/* PWM_H */

