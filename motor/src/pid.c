/**
 * @file pid.c
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief PID controller source code
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pid.h"

/******************************************************************
 * \brief Pid initialization
 * 
 * Detailed description starts here 
 * @param me           pointer to PID object
 * @param params       PID parameters
 * @return None
 *******************************************************************/
void pid_init(PID_t * const me, PID_params_t *params)
{
    me->params = params;
    me->reference = 0.0;
    me->integral = 0.0;
    me->derivative = 0.0;
    me->proportional = 0.0;
    me->prev_measurement = 0.0;
}

/******************************************************************
 * \brief Pid initialization
 * 
 * Detailed description starts here 
 * @param me            pointer to PID object
 * @param measurement   measurement for adjustmnet 
 * @param dt            delta time
 * @return float       pid update output
 *******************************************************************/
float pid_update(PID_t * const me, float measurement, float dt)
{
    me->error = me->reference - measurement;

    //Proportional 
    me->proportional = me->params->kp*me->error;
   
    //Integral term
    me->integral +=  me->params->ki*(me->error*dt);
    //clamp integral term
    me->integral = (me->integral > me->params->max_integral) ? me->params->max_integral : me->integral;
    me->integral = (me->integral < me->params->min_integral) ? me->params->min_integral : me->integral;

    //Derivative term
    me->derivative = me->params->kd*((measurement - me->prev_measurement)/dt);
    me->prev_measurement = measurement;

    //output
    float output = me->proportional + me->integral + me->derivative;

    //clamp output
    output = (output > me->params->max_output) ? me->params->max_output : output;
    output = (output < me->params->min_output) ? me->params->max_output : output;

    return output;
}

/******************************************************************
 * \brief Pid set reference point
 * 
 * Detailed description starts here 
 * @param   me          pointer to PID object
 * @param   reference   value to set PID controller
 * @return None
 *******************************************************************/
void pid_set_reference(PID_t * const me, float reference)
{
    me->reference = reference;
}


/******************************************************************
 * \brief PID reached
 * 
 * Detailed description starts here 
 * @param   me          pointer to PID object
 * @return  bool        PID reached
 *******************************************************************/
bool pid_reached(PID_t * const me)
{
    bool result = false;

    if((me->error >  me->params->error_min_threshold) && 
       (me->error < me->params->error_max_threshold))
    {
        result = true;
    }

    return result;
}
