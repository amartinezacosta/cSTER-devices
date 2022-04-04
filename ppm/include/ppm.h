#ifndef PPM_H_
#define PPM_H_

#include <Capture_HAL.h>

#define PPM_CHANNELS_COUNT  8

typedef struct
{
    dev_t *dev;
    uint32_t channels[PPM_CHANNELS_COUNT];
    uint32_t index;
}ppm_t;

void ppm_ctor(ppm_t * const me, dev_t * const dev);
void ppm_get_channels(ppm_t * const me, uint32_t *channels, uint32_t size);

#endif
