#include <ppm.h>

void ppm_callback(void **args, uint32_t argc);

/******************************************************************
 * \brief PPM constructor
 * 
 * Detailed description starts here 
 * @param me            pointer to PPM object
 * @param dev           generic capture device
 * @param count         count value
 * @return None
 *******************************************************************/
void ppm_ctor(ppm_t * const me, dev_t * const dev, uint32_t count)
{
    me->index = 0;
    me->dev = dev;
    me->count = count;

    for(uint32_t i = 0; i < me->count; i++)
    {
        me->channels[i] = 0;
    }

    Capture_open(me->dev, HAL_CONFIG_DEFAULT);
    Capture_ioctl(me->dev, HAL_IOCTL_EVENT_SET_CALLBACK, &ppm_callback);
    Capture_ioctl(me->dev, HAL_IOCTL_EVENT_SET_ARGS, me);
}

/******************************************************************
 * \brief PPM get channels
 * 
 * Detailed description starts here 
 * @param me            pointer to PPM object
 * @param channels      array of channels
 * @return None
 *******************************************************************/
void ppm_get_channels(ppm_t *me, uint32_t *channels)
{
    /*TODO: disable this interrupt?*/
    for(uint32_t i = 0; i < me->count; i++)
    {
        channels[i] = me->channels[i];
    }
}

void ppm_callback(void **args, uint32_t argc)
{
    if(argc < 2) return;

    ppm_t *me = (ppm_t*)args[0];
    uint32_t interval = *((uint32_t*)args[1]);

    if((me->index > me->count) || (interval > 2500))
    {
        me->index = 0;
        return;
    }

    me->channels[me->index++] = interval;
}


