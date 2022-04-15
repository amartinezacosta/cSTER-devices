#ifndef _PID_H_
#define _PID_H_

#include <stdbool.h>

typedef struct
{
    float kp, ki, kd;
    float max_integral, min_integral;
    float error_max_threshold, error_min_threshold;
    float max_output, min_output;
}PID_Params_t;

typedef struct
{
    float error;
    float reference;
    float integral, derivative, proportional;
    float prev_measurement;
    PID_Params_t params;
}PID_t;


void pid_init(PID_t *me, PID_Params_t params);
float pid_update(PID_t *me, float reference, float dt);
void pid_set_reference(PID_t *me, float reference);
bool pid_reached(PID_t *me);

#endif