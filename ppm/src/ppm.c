#include <ppm.h>

void ppm_callback(void **args, uint32_t argc);

void ppm_ctor(ppm_t * const me, dev_t * const dev)
{
    for(uint32_t i = 0; i < PPM_CHANNELS_COUNT; i++) me->channels[i] = 0;

    me->index = 0;
    me->dev = dev;

    Capture_open(me->dev, HAL_CONFIG_DEFAULT);
    Capture_ioctl(me->dev, HAL_IOCTL_EVENT_SET_CALLBACK, &ppm_callback);
    Capture_ioctl(me->dev, HAL_IOCTL_EVENT_SET_ARGS, me);
}

void ppm_get_channels(ppm_t *me, uint32_t *channels, uint32_t size)
{
    /*Only allow to read the number of channels*/
    if(size != PPM_CHANNELS_COUNT) return;

    /*TODO: disable this interrupt?*/
    for(uint32_t i = 0; i < size; i++) channels[i] = me->channels[i];
}

void ppm_callback(void **args, uint32_t argc)
{
    if(argc < 2) return;

    ppm_t *me = (ppm_t*)args[0];
    uint32_t interval = *((uint32_t*)args[1]);

    if((me->index > 8) || (interval > 1500)) me->index = 0;

    me->channels[me->index++] = interval;
}


