/* 
 * File:   Robot.h
 * Author: E306-PC4
 *
 * Created on 1 octobre 2025, 08:41
 */

#ifndef ROBOT_H
#define ROBOT_H
#define PWMPER
typedef struct robotStateBITS {
union {
struct {
unsigned char taskEnCours;
float vitesseGaucheConsigne;
float vitesseGaucheCommandeCourante;
float vitesseDroiteConsigne;
float vitesseDroiteCommandeCourante;


};
};
} ROBOT_STATE_BITS;
extern volatile ROBOT_STATE_BITS robotState;
#endif /* ROBOT_H */

