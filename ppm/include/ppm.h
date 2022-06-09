/**
 * @dir ppm/include
 * @brief PPM library
 * @details More details to be displayed on the folder's page.
 * 
 * @file ppm.h
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief PPM device library
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PPM_H_
#define PPM_H_

#include <Capture_HAL.h>

#define MAX_PPM_CHANNEL_COUNT  16   /*!< MAX PPM Channels */

/******************************************************************
 * \struct ppm_t ppm.h 
 * \brief PPM object
 * 
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.c
 * typedef struct{
 *      dev_t *dev;
 *      uint32_t channels[MAX_PPM_CHANNEL_COUNT];
 *      volatile uint32_t index;
 *      uint32_t count;
 * }ppm_t;
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
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
