/* 
 * File:   ADC.h
 * Author: E306-PC4
 *
 * Created on 2 décembre 2025, 13:53
 */

#ifndef ADC_H
#define	ADC_H
void InitADC1(void);
void ADC1StartConversionSequence();
unsigned int * ADCGetResult(void);
unsigned char ADCIsConversionFinished(void);
void ADCClearConversionFinishedFlag(void);
void __attribute__((interrupt,np_auto_psv)) _AD1Interrupt(void);


#endif	/* ADC_H */

