/*
 * @Descripttion: queue set
 * @version: 1.0
 * @Author: Bsgbsg7
 * @Date: 2023-02-23 20:25:41
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

void sendTask1(void *pvParm)
{
    QueueHandle_t Qhandle;
    Qhandle = (QueueHandle_t)pvParm;
    BaseType_t state;
    int i = 111;

    while (1)
    {
        state = xQueueSend(Qhandle, &i, 0);
        if (state != pdPASS)
        {
            printf("data sent failed!\n");
        }
        else
        {
            printf("data sent successfully!\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void sendTask2(void *pvParm)
{
    QueueHandle_t Qhandle;
    Qhandle = (QueueHandle_t)pvParm;
    BaseType_t state;
    int i = 222;

    while (1)
    {
        state = xQueueSend(Qhandle, &i, 0);
        if (state != pdPASS)
        {
            printf("data sent failed!\n");
        }
        else
        {
            printf("data sent successfully!\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void receTask(void *pvParm)
{
    QueueSetHandle_t Qsethandle;
    //定义取出的menmbenr queue的handle类型
    QueueSetMemberHandle_t Qselect;
    Qsethandle = (QueueSetHandle_t)pvParm;

    BaseType_t state;
    int data;

    while (1)
    {
        Qselect = xQueueSelectFromSet(Qsethandle,portMAX_DELAY);
        state = xQueueReceive(Qselect,&data,portMAX_DELAY);
        if (state != pdPASS)
        {
            printf("Receive failed!\n");
        }
        else
        {
            printf("Data received\n");
            printf("data : %d\n", data);
        }
    }
}

// void app_main(void)
// {
//     QueueHandle_t Qhandle1;
//     Qhandle1 = xQueueCreate(5,sizeof(int));
//     QueueHandle_t Qhandle2;
//     Qhandle2 = xQueueCreate(5,sizeof(int));
//     QueueSetHandle_t Qsethandle;
//     Qsethandle = xQueueCreateSet(10);

//     xQueueAddToSet(Qhandle1,Qsethandle);
//     xQueueAddToSet(Qhandle2,Qsethandle);
    
//     if (Qhandle1 != NULL && Qhandle2 != NULL  && Qsethandle != NULL)
//     {
//         printf("Qsethandle Creat Successfully!\n");
//         xTaskCreate(sendTask1, "sendTask1", 1024 * 5, (void *)Qhandle1, 1, NULL);
//         xTaskCreate(sendTask2, "sendTask2", 1024 * 5, (void *)Qhandle2, 1, NULL);
//         xTaskCreate(receTask, "receTask", 1024 * 5, (void *)Qsethandle, 2, NULL);
//     }
//     else
//     {
//         printf("Qhandle Creat Failed!\n");
//     }
// }
