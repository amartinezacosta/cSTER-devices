#ifndef PPM_H_
#define PPM_H_

#include <Capture_HAL.h>

#define MAX_PPM_CHANNEL_COUNT  16

typedef struct
{
    dev_t *dev;
    uint32_t channels[MAX_PPM_CHANNEL_COUNT];
    volatile uint32_t index;
    uint32_t count;
}ppm_t;

void ppm_ctor(ppm_t * const me, dev_t * const dev, uint32_t count);
void ppm_get_channels(ppm_t * const me, uint32_t *channels);

#endif
