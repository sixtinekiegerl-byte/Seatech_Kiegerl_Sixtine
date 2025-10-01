/* 
 * File:   Toolbox.h
 * Author: E306-PC4
 *
 * Created on 1 octobre 2025, 08:44
 */

#ifndef TOOLBOX_H
#define	TOOLBOX_H
#define PI 3.141592653589793

float Abs(float value);
float Max(float value, float value2);
float Min(float value, float value2);
float LimitToInterval(float value, float lowLimit, float highLimit);
float RadianToDegree(float value);
float DegreeToRadian(float value);

#endif