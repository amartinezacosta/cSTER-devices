#include <Capture_HAL.h>
#include "ppm.h"

int main(void)
{
    dev_t *capture = HAL_find_name("CAP_0");
    HAL_ASSERT_MODULE_NAME(capture, "main");

    ppm_t ppm;
    ppm_ctor(&ppm , capture);

    uint32_t channels[8];
    while(1)
    {
        ppm_get_channels(&ppm, channels, 8);
    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {

    }
}
