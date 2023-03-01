/*
 * @Descripttion: queue one in one out ,include pstr, struct, int ...
 * @version: 1.0
 * @Author: Bsgbsg7
 * @Date: 2023-02-23 20:25:41
 */
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

typedef struct A_STRUCT
{
    char id;
    char data;
}PERSON;


void sendTask(void * pvParm)
{
    QueueHandle_t Qhandle;
    Qhandle = (QueueHandle_t)pvParm;
    
    PERSON bsg={123,2021};
    BaseType_t state;

    while(1)
    {
        /*
        //queue中保存和传递的是复制的指向的数据
        //1---创建一个指针，并且指向字符串
        char * pStrToSend = (char *)malloc(50);
        snprintf(pStrToSend,50,"This is the test print!\r\n");
        //2---此处传递的是pStrToSend指针指向的字符串的首地址
        state = xQueueSend(Qhandle,&pStrToSend,0);
        */
        state= xQueueSend(Qhandle,&bsg,0);
        if (state != pdPASS)
        {
            printf("data sent failed!\n");
        }
        else
        {
            printf("data sent successfully!\n");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void receTask(void * pvParm)
{
    QueueHandle_t Qhandle;
    Qhandle = (QueueHandle_t)pvParm;
    
    BaseType_t state;
    //3---用于接收传递过来的指针地址
    char * pStrToRec;
    PERSON Rec;

    while(1)
    {
        //4---检测队列中是否有元素，没有则跳过不执行
        if (uxQueueMessagesWaiting(Qhandle)==0)
        {
            printf("no data !\n");
        }
        else
        {
            //5---将传递过来的指针指向的内容存储到pStrToRec指针中，
            //故pStrToRec指向的是传输过来的指针指向的数据
            //即字符串的首地址
            // state = xQueueReceive(Qhandle,&pStrToRec,0);
            state = xQueueReceive(Qhandle,&Rec,0);
            if (state != pdPASS)
            {
                printf("Receive failed!\n");
            }
            else
            {
                printf("Data received\n");
                printf("data : %d\t id: %d\n",Rec.id,Rec.data);
            //6---使用完毕之后释放内存
                // free(pStrToRec);
            }
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}


// void app_main(void)
// {
//     TaskHandle_t send_task,rece_task;
//     QueueHandle_t Qhandle;
    
//     //创建队列，如果创建成功，则开启任务
//     //Qhandle = xQueueCreate(5,sizeof(char *));
//     Qhandle = xQueueCreate(5,sizeof(PERSON));
//     if (Qhandle != NULL)
//     {
//         printf("Qhandle Creat Successfully!\n");
//         xTaskCreate(sendTask,"sendTask",1024*5,(void *)Qhandle,1,&send_task);
//         xTaskCreate(receTask,"receTask",1024*5,(void *)Qhandle,1,&rece_task);       
//     }
//     else
//     {
//         printf("Qhandle Creat Failed!\n");
//     }
// }
