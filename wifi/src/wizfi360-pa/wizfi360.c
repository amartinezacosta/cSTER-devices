#include "wizfi360.h"

#define IS_NUMBER(a)    ((a > 47) && (a < 58))      /*!<Verifed it a number*/

const char *WIZFI360TAGS[] =
{
     "\r\nOK\r\n",
     "\r\nERROR\r\n",
     "\r\nFAIL\r\n",
     "\r\nSEND OK\r\n",
     " CONNECT\r\n",
};

const uint32_t tags_count = sizeof(WIZFI360TAGS)/sizeof(WIZFI360TAGS[0]); /*!< Total  tag count*/

#ifdef WIZFI360_LOG_ENABLE
    static void wizfi_log_result(int32_t result);
#endif



/******************************************************************
 * \brief Wizfi360 constructor
 * 
 * Detailed description starts here 
 * @param me            pointer to wizfi object
 * @param dev           pointer to device
 * @return None
 *******************************************************************/
void wizfi360_ctor(wizfi_t * const me, dev_t * const dev)
{
    /*Initialize UART character device for printf support*/
    char_devio_ctor(&me->com, &UART_write, &UART_read, dev);

    /*Inialize UART device*/
    UART_open(me->com.dev, UART_MODE_ASYCHRONOUS  |
                    UART_DATA_BITS_8       |
                    UART_PARITY_NONE       |
                    UART_STOP_BITS_1       |
                    UART_FLOW_CONTROL_NONE |
                    UART_INTERRUPT_ENABLE);

    /*Set UART timeout to 100ms*/
    UART_ioctl(me->com.dev, HAL_IOCTL_SET_TIMEOUT, (uint32_t*)100);

    /*Intialize wizfi360*/
    /*Test communication*/
    wizfi360_send_wait(me, "AT", NULL, 100);
    /*Disable command echo*/
    wizfi360_send_wait(me, "ATE0", NULL, 100);
    /*Set station mode*/
    wizfi360_send_wait(me, "AT+CWMODE_CUR=1", NULL, 100);
    /*Enable DHCP*/
    wizfi360_send_wait(me, "AT+CWDHCP_CUR=1,1", NULL, 100);
}

/******************************************************************
 * \brief Wizfi360 send wait
 * 
 * Detailed description starts here 
 * @param me            pointer to wizfi object
 * @param cmd           command
 * @param delimiter     string delimiter
 * @param timeout       timeout
 * @return int32_t      status
 *******************************************************************/
int32_t wizfi360_send_wait(wizfi_t *const me,
                           const char *cmd,
                           char const *delimiter,
                           uint32_t timeout)
{
    /*Send command*/
    #ifdef WIZFI360_LOG_ENABLE
        if(cmd) log_debug("SENDING: %s", cmd);
    #endif

    /*Print command if requested*/
    if(cmd) uprintf(&me->com, "%s\r\n", cmd);

    /*Now wait for a response*/
    char c;
    char buff[128];
    uint32_t index = 0;
    int32_t status = WIZFI360_ERROR;
    uint32_t tag_found = 0;

    uint32_t t0 = SysTick_millis();

    while(1)
    {
        uint32_t count = UART_read(me->com.dev, (uint8_t*)&c, 1);

        /*Was there anything on the buffer?*/
        if(count)
        {
            /*Save into buffer and terminate string, important to check tags*/
            if(index < (sizeof(buff) - 2))
            {
                buff[index++] = c;
                buff[index] = 0;
            }
            else
            {
                status = WIZFI360_ERROR_BUFFER_OVERRRUN;
                break;
            }

            /*Are we looking for a delimiter?*/
            if(delimiter)
            {
                /*Try to find it on the buffer*/
                if(strstr(buff, delimiter))
                {
                    status = WIZFI360_DELIMITER_FOUND;
                    tag_found = 1;
                    break;
                }
            }
            /*Are we looking for a tag?*/
            else
            {
                /*if we find any tags exit*/
                for(uint32_t i = 0; i < tags_count; i++)
                {
                    if(strstr(buff, WIZFI360TAGS[i]))
                    {
                        status = i;
                        tag_found = 1;
                        break;
                    }
                }
            }
        }

        if(tag_found) break;

        /*Have we timed out?*/
        if((SysTick_millis() - t0) > timeout)
        {

            status = WIZFI360_TIMEOUT_ERROR;
            break;
        }
    }

    #ifdef WIZFI360_LOG_ENABLE
        log_debug("REPLY: %s", buff);
    #endif

    return status;
}

int32_t wizfi360_connect(wizfi_t * const me, char const *ssid, char const *password)
{
    #ifdef WIZFI360_LOG_ENABLE
        log_debug("Connecting to \"%s\"...", ssid);
    #endif

    char buff[64];
    usprintf(NULL, buff, "AT+CWJAP_CUR=\"%s\",\"%s\"", ssid, password);
    int32_t result = wizfi360_send_wait(me, buff, NULL, 10000);

    #ifdef WIZFI360_LOG_ENABLE
        wizfi_log_result(result);
    #endif

    return result;
}


/******************************************************************
 * \brief Wizfi360 start server
 * 
 * Detailed description starts here 
 * @param me            pointer to wizfi object
 * @param port          port number
 * @param sock          socket
 * @return int32_t      status
 *******************************************************************/
int32_t wizfi360_start_server(wizfi_t * const me, uint16_t port, uint8_t sock)
{
    #ifdef WIZFI360_LOG_ENABLE
        log_debug("Starting server on port %i socket %i", port, sock);
    #endif

    char buff[64];
    usprintf(NULL, buff, "AT+CIPSERVER=%i,%i", port, sock);
    int32_t result = wizfi360_send_wait(me, buff, NULL, 2000);

    #ifdef WIZFI360_LOG_ENABLE
        wizfi_log_result(result);
    #endif

    return result;
}

/******************************************************************
 * \brief Wizfi360 start client
 * 
 * Detailed description starts here 
 * @param me            pointer to wizfi object
 * @param address       address
 * @param port          port number
 * @return int32_t      status
 *******************************************************************/
int32_t wizfi360_start_client(wizfi_t * const me, char const *address, uint16_t port)
{
    #ifdef WIZFI360_LOG_ENABLE
        log_debug("Connecting to %s:%i", address, port);
    #endif

    char buff[64];
    usprintf(NULL, buff, "AT+CIPSTART=\"TCP\",\"%s\",%i", address, port);
    int32_t result = wizfi360_send_wait(me, buff, NULL, 2000);

    #ifdef WIZFI360_LOG_ENABLE
        wizfi_log_result(result);
    #endif

    return result;
}

/******************************************************************
 * \brief Wizfi360 write
 * 
 * Detailed description starts here 
 * @param me            pointer to wizfi object
 * @param data          data array
 * @param size          size of data
 * @return uint32_t     status
 *******************************************************************/
uint32_t wizfi360_write(wizfi_t * const me, uint8_t const *data, uint32_t size)
{
    #ifdef WIZFI360_LOG_ENABLE
        log_debug("Sending %i bytes", size);
    #endif

    char buff[32];
    usprintf(NULL, buff, "AT+CIPSEND=%i", size);
    /*Wait until we receive the '>' character*/
    int32_t result = wizfi360_send_wait(me, buff, ">", 100);

    #ifdef WIZFI360_LOG_ENABLE
        wizfi_log_result(result);
    #endif

    /*Did we fail?*/
    uint32_t sent = 0;
    if(result == WIZFI360_DELIMITER_FOUND)
    {
        log_info("WIZFI360 sending data...");
        /*No, send data*/
        sent = UART_write(me->com.dev, data, size);
        /*Wait for SEND OK tag*/
        result = wizfi360_send_wait(me, NULL, NULL, 1000);

        #ifdef WIZFI360_LOG_ENABLE
            wizfi_log_result(result);
        #endif

       if(result == WIZFI360_SEND_OK) log_info("WIZFI360 data sent successfully");
       else                           log_error("WIZFI360 failed to send data");
    }
    else
    {
        /*We failed, just log it*/
        log_error("WIZFI360 failed to send data");
    }

    return sent;
}

/******************************************************************
 * \brief Wizfi360 read
 * 
 * Detailed description starts here 
 * @param me            pointer to wizfi object
 * @param data          data array
 * @param size          size of data
 * @return uint32_t     status
 *******************************************************************/
uint32_t wizfi360_read(wizfi_t * const me, uint8_t *data, uint32_t size)
{
    /*Now wait for a response*/
    char c;
    char buff[12];
    char int_buff[6];
    char *str_match;
    uint32_t index = 0;
    uint32_t int_index = 0;
    uint32_t available = 0;

    uint32_t t0 = SysTick_millis();

    /*Wait until "+IPD," string is found or timeout happens*/
    while(1)
    {
        uint32_t count = UART_read(me->com.dev, (uint8_t*)&c, 1);

        if(count > 0)
        {
            /*Check if buffer overrun*/
            if(index < sizeof(buff) - 2)
            {
                buff[index++] = c;
                buff[index] = 0;
            }
            else
            {
                /*We could not fit the entire message,
                 * highly unlikely but just in case*/
                break;
            }

            /*Check if we have found the "+IPD," string*/
            str_match = strstr(buff, "+IPD,");
            if(str_match)
            {
                /*Read until we don't find a numeric character*/
                do
                {
                    UART_read(me->com.dev, (uint8_t*)&c, 1);
                    int_buff[int_index++] = c;
                }while(IS_NUMBER(c));

                /*Convert from ascii to integer*/
                int_buff[int_index] = 0;
                available = atoi(int_buff);

                break;
            }
        }
        /*If timeout, just break. The available data will be zero
         * and we won't be reading the UART buffer
         */
        if((SysTick_millis() - t0) > 1000) break;
    }

    /*Any data available?*/
    if(available)
    {
        /*Clamp available to buffer size
         * if available data is bigger
         */
        if(available > size) available = size;
        UART_read(me->com.dev, data, available);
    }

    return available;
}

/*TODO: This function does not work as intended!
 * it will take out the data packet from the buffer.
 * Need to fix it to look like
 */
/*
uint32_t wizfi360_available(wizfi_t * const me)
{
    char buff[64];
    char str_int[6];
    uint32_t str_int_index = 0;

    uint32_t count;
    UART_ioctl(me->com.dev, UART_IOCTL_AVAILABLE_DATA, &count);

    uint32_t available = 0;
    if(count)
    {
        UART_read(me->com.dev, (uint8_t*)buff, count);
        char *str = strstr(buff, "+IPD,");

        if(str)
        {
            str += 5;
            while(IS_NUMBER(*str))
            {
                str_int[str_int_index++] = *str++;
            }

            available = atoi(str_int);
        }
    }

    return available;
}
*/

#ifdef WIZFI360_LOG_ENABLE
/******************************************************************
 * \brief Wizfi360 write
 * 
 * Detailed description starts here 
 * @param result    wizfi status result
 * @return None
 *******************************************************************/
static void wizfi_log_result(int32_t result)
{
    switch(result)
    {
    case WIZFI360_ERROR:
        log_error("WIZFI_ERROR: %i", result);
        break;
    case WIZFI360_OK:
        log_info("WIZFI_OK: %i", result);
        break;
    case WIZFI360_FAIL:
        log_error("WIZFI_FAIL: %i", result);
        break;
    case WIZFI360_TIMEOUT_ERROR:
        log_error("WIZFI360_TIMEOUT_ERROR: %i", result);
        break;
    case WIZFI360_SEND_OK:
        log_info("WIZFI_SEND: %i", result);
        break;
    case WIZFI360_CONNECT:
        log_info("WIZFI_CONNECT: %i", result);
        break;
    case WIZFI360_ERROR_BUFFER_OVERRRUN:
        log_fatal("WIZFI_ERROR_BUFFER_OVERRUN: %i", result);
        break;
    case WIZFI360_DELIMITER_FOUND:
        log_info("WIZFI_DELIMITER_FOUND: %i", result);
        break;
    default:
        log_fatal("WIZFI invalid return code: %i", result);
        break;
    }
}
#endif
