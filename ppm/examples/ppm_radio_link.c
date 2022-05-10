#include <ppm.h>
#include <logger.h>
#include <SysTick_HAL.h>

int main(void)
{
    dev_t *capture = HAL_find_name("CAP_0");
    HAL_ASSERT_MODULE_NAME(capture, "main");

    ppm_t ppm;
    ppm_ctor(&ppm , capture, 8);

    uint32_t channels[8];
    while(1)
    {
        ppm_get_channels(&ppm, channels);

        log_info("%i,%i,%i,%i,%i,%i,%i,%i",
                 channels[0], channels[1],
                 channels[2], channels[3],
                 channels[4], channels[5],
                 channels[6], channels[7]);

        SysTick_delay(10);
    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {

    }
}
