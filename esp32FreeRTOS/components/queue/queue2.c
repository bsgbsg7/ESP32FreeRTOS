/*
 * @Descripttion: queue many in (send) and one out (receive) 
 * @version: 1.0
 * @Author: Bsgbsg7
 * @Date: 2023-02-23 20:25:41
 */
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// 创建两个任务分别向Queue中发送数据
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
    QueueHandle_t Qhandle;
    Qhandle = (QueueHandle_t)pvParm;

    BaseType_t state;
    int data;

    while (1)
    {
        //使用portMAX_DELAY阻塞无穷时间，结合优先级只有当queue中被存入数据的时候才开始接收数据
        state = xQueueReceive(Qhandle, &data,portMAX_DELAY);
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
//     QueueHandle_t Qhandle;

//     // 创建队列，如果创建成功，则开启任务
//     Qhandle = xQueueCreate(5, sizeof(int));
//     if (Qhandle != NULL)
//     {
//         printf("Qhandle Creat Successfully!\n");
//         //经测试，Receive的优先级较高时，只有当数据从queue中取出来之后才能好继续Send，否则会sent failed
//         xTaskCreate(sendTask1, "sendTask1", 1024 * 5, (void *)Qhandle, 1, NULL);
//         xTaskCreate(sendTask2, "sendTask2", 1024 * 5, (void *)Qhandle, 1, NULL);
//         xTaskCreate(receTask, "receTask", 1024 * 5, (void *)Qhandle, 2, NULL);
//     }
//     else
//     {
//         printf("Qhandle Creat Failed!\n");
//     }
// }
