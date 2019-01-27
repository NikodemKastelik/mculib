#ifndef _PID_H_
#define _PID_H_

#include <stdint.h>

#define PID_SIGNAL_MAX  32768

typedef enum
{
    PID_SAT_NONE  =  0,
    PID_SAT_UPPER =  1,
    PID_SAT_LOWER = -1,
} pid_sat_dir_t;

typedef struct
{
    int32_t       point_desired;
    int32_t       kp_q;
    int32_t       ki_q;
    int32_t       kd_q;
    uint32_t      q;
    int32_t       last_point;
    int32_t       integral_sum;
    pid_sat_dir_t saturation;
    uint32_t      output_min;
    uint32_t      output_max;
} pid_t;

typedef struct
{
    uint32_t q;
    int32_t  kp_q;
    int32_t  ki_q;
    int32_t  kd_q;
    uint32_t output_min;
    uint32_t output_max;
} pid_cfg_t;

void pid_init(pid_t * pid, const pid_cfg_t * cfg);

void pid_point_set(pid_t * pid, int32_t point);

int32_t pid_positional_proc(pid_t * pid, int32_t point_current);

/*
pid_sat_dir_t pid_limit(int32_t * val, int32_t upper_lim, int32_t lower_lim);

pid_sat_dir_t pid_deadzone_limit(int32_t * val, uint32_t out_limit, uint32_t deadzone_limit);

uint32_t pid_scale(uint32_t val,
                   uint32_t input_min,
                   uint32_t input_max,
                   uint32_t output_min,
                   uint32_t output_max);
*/

#endif // _PID_H_
