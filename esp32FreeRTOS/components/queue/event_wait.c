/*
 * @Descripttion: event 的创建和等待
 * @version: 1.0
 * @Author: Bsgbsg7
 * @Date: 2023-02-27 11:14:41
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#define BIT_0 (1 << 0)
#define BIT_4 (1 << 4)
EventGroupHandle_t xEventHandle;

void task1(void *pvParm)
{
    EventBits_t uxBits;
    while (1)
    {
        printf("task1 begin!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        uxBits = xEventGroupWaitBits(
            xEventHandle,   /* The event group being tested. */
            BIT_0 | BIT_4,  /* The bits within the event group to wait for. */
            pdTRUE,         /* BIT_0 and BIT_4 should be cleared before returning.

                             If set to pdTRUE, the set bit will cause waitbits to execute all the time without blocking
                             
                             */
            pdFALSE,        /* Don't wait for both bits, either bit will do. 

                            if used with the following code, it should be set pdFALSE:
                                if( ( uxBits & ( BIT_0 | BIT_4 ) ) == ( BIT_0 | BIT_4 ) )
                                else if( ( uxBits & BIT_0 ) != 0 )
                                else if( ( uxBits & BIT_4 ) != 0 )
                            and the result:
                                task2 begin!
                                task1 begin!
                                task2 set bits_0
                                Task1 get event
                                Bit_0 set
                                ---------------
                                task1 begin!
                                task2 set bits_4
                                Task1 get event
                                Bit_4 set
                            */
            portMAX_DELAY); /* Wait a maximum time for either bit to be set. */
            
        printf("Task1 get event\n");
        if ((uxBits & (BIT_0 | BIT_4)) == (BIT_0 | BIT_4))
        {
            /* xEventGroupWaitBits() returned because both bits were set. */
            printf("All bits were set\n");
        }
        else if ((uxBits & BIT_0) != 0)
        {
            /* xEventGroupWaitBits() returned because just BIT_0 was set. */
            printf("Bit_0 set\n");
        }
        else if ((uxBits & BIT_4) != 0)
        {
            /* xEventGroupWaitBits() returned because just BIT_4 was set. */
            printf("Bit_4 set\n");
        }
        else
        {
            /* xEventGroupWaitBits() returned because xTicksToWait ticks passed
            without either BIT_0 or BIT_4 becoming set. */
            printf("Without either bits beconming set\n");
        }
        printf("---------------\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task2(void *pvParm)
{
    printf("task2 begin!\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    /*
        test if set pdFALSE wiil cause waitbits to execute all the time without blocking
    */
    // printf("task2 set bits!\n");
    // xEventGroupSetBits(xEventHandle,BIT_0 | BIT_4 );
    while (1)
    {
        xEventGroupSetBits(xEventHandle, BIT_0);
        printf("task2 set bits_0\n");
        vTaskDelay(6000 / portTICK_PERIOD_MS);
        xEventGroupSetBits(xEventHandle, BIT_4);
        printf("task2 set bits_4\n");
        vTaskDelay(6000 / portTICK_PERIOD_MS);
    }
}

// void app_main(void)
// {
//     xEventHandle = xEventGroupCreate();
//     vTaskSuspendAll();

//     xTaskCreatePinnedToCore(task1, "task1", 1024 * 5, NULL, 1, NULL, 0);
//     xTaskCreatePinnedToCore(task2, "task2", 1024 * 5, NULL, 2, NULL, 0);

//     xTaskResumeAll();
// }
