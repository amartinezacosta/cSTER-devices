/**
 * @file pid.h
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief PID controller library
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _PID_H_
#define _PID_H_

#include <stdbool.h>

/******************************************************************
 * \struct PID_params_t pid.h 
 * \brief PID parameter object
 * 
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.c
 * typedef struct{
 *      float kp;
 *      float ki;
 *      float kd;
 *      float max_integral;
 *      float error_max_threshold;
 *      float error_min_threshold;
 *      float max_output;
 *      float min_output;
 * }PID_params_t;
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
typedef struct
{
    float kp;
    float ki;
    float kd;
    float max_integral;
    float min_integral;
    float error_max_threshold;
    float error_min_threshold;
    float max_output;
    float min_output;
}PID_params_t;


/******************************************************************
 * \struct PID_t pid.h 
 * \brief PID object
 * 
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.c
 * typedef struct{
 *      float error;
 *      float reference;
 *      float integral;
 *      float derivative;
 *      float proportional;
 *      float prev_measurement;
 *      PID_params_t *params;
 * }PID_t;
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
typedef struct
{
    float error;
    float reference;
    float integral;
    float derivative;
    float proportional;
    float prev_measurement;
    PID_params_t *params;
}PID_t;

void pid_init(PID_t * const me, PID_params_t *params);
float pid_update(PID_t * const me, float reference, float dt);
void pid_set_reference(PID_t * const me, float reference);
bool pid_reached(PID_t * const me);

#endif
