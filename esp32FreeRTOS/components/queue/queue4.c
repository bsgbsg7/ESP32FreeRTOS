/*
 * @Descripttion: queue mail box
                mail box:   hold data, data does not pass through the mail box
                            sender overwrite the value of the box ,the receiver 
                            does not remove the value the data of the mail box
 * @version: 1.0
 * @Author: Bsgbsg7
 * @Date: 2023-02-23 20:25:41
 */
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

void writeTask(void *pvParm)
{
    QueueHandle_t Qhandle;
    Qhandle = (QueueHandle_t)pvParm;
    int i = 0;

    while (1)
    {
        // pdPASS is the only value that can be returned because xQueueOverwrite()
        // will write to the queue even when the queue is already full
        xQueueOverwrite(Qhandle, &i);
        printf("data overwrite successfully!\n");
        i++;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void readTask(void *pvParm)
{
    QueueHandle_t mailbox;
    mailbox = (QueueHandle_t)pvParm;
    BaseType_t state;
    int data;

    while (1)
    {
        state = xQueuePeek(mailbox, &data, 0);
        if (state != pdPASS)
        {
            printf("Receive failed!\n");
        }
        else
        {
            printf("Data received\n");
            printf("data : %d\n", data);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// void app_main(void)
// {
//     QueueHandle_t Mailbox;
//     Mailbox = xQueueCreate(1, sizeof(int));

//     if (Mailbox != NULL)
//     {
//         printf("Mailbox Creat Successfully!\n");

//         xTaskCreate(writeTask, "write", 1024 * 5, (void *)Mailbox, 1, NULL);
//         xTaskCreate(readTask, "read1", 1024 * 5, (void *)Mailbox, 2, NULL);
//         xTaskCreate(readTask, "read2", 1024 * 5, (void *)Mailbox, 2, NULL);
//         xTaskCreate(readTask, "read3", 1024 * 5, (void *)Mailbox, 2, NULL);
//     }
//     else
//     {
//         printf("Mailbox Creat Failed!\n");
//     }
// }
