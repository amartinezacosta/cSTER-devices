#include "pid.h"

void pid_init(PID_t * const me, PID_params_t *params)
{
    me->params = params;
    me->reference = 0.0;
    me->integral = 0.0;
    me->prev_measurement = 0.0;
}

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

void pid_set_reference(PID_t * const me, float reference)
{
    me->reference = reference;
}

bool pid_reached(PID_t * const me)
{
    bool result = false;

    if((me->error <  me->params->error_min_threshold) && 
       (me->error > me->params->error_max_threshold))
    {
        result = true;
    }

    return result;
}
