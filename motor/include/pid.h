#ifndef _PID_H_
#define _PID_H_

#include <stdbool.h>

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
