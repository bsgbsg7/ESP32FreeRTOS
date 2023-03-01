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
SemaphoreHandle_t mutexHandle;

void Task1(void *pvParam){
    BaseType_t iRet;
    printf("task1 begin!\n");
    while(1){
        iRet = xSemaphoreTake(mutexHandle,1000); //试图取得获得互斥量
        if(iRet == pdPASS){
            printf("task1 take!\n");
            for(int i = 0;i<50;i++){
                printf("task1 i=%d!\n",i);
                vTaskDelay(pdMS_TO_TICKS(1000)); 
            }
            xSemaphoreGive(mutexHandle);
            printf("task1 give!\n");
            vTaskDelay(pdMS_TO_TICKS(5000)); //阻塞自身让其他任务有时间执行
        }
        else{
            printf("task1 didn't take!\n");
        }
    }
}

void Task2(void *pvParam){
    printf("task2 begin!\n");
    vTaskDelay(pdMS_TO_TICKS(1000));//阻塞，让Task1有时间执行
    while(1){
        ; //无阻塞，只有Task3可以剥夺运行时间 
    }
}

void Task3(void *pvParam){
    BaseType_t iRet;
    printf("task3 begin!\n");
    vTaskDelay(pdMS_TO_TICKS(1000)); //阻塞，让Task2，Task1有时间执行
    while (1)
    {
        iRet = xSemaphoreTake(mutexHandle,1000); //试图取得获得互斥量
        if(iRet == pdPASS){
            printf("task3 take!\n");
            for(int i=0;i<10;i++){
                printf("task3 i=%d",i);
                vTaskDelay(pdMS_TO_TICKS(1000)); //模拟程序处理
            }
            xSemaphoreGive(mutexHandle); //处理完，释放互斥量
            printf("task3 give!\n");
            vTaskDelay(pdMS_TO_TICKS(5000)); //阻塞自身让其他任务有时间执行
        }
        else{
            printf("task3 did't take!\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
    
}

void app_main(void)
{
    //二选一观察现象：
    //1-
    //mutexHandle = xSemaphoreCreateBinary();//创建二进制信号量
    //2-
    mutexHandle = xSemaphoreCreateMutex();//创建互斥量

    vTaskSuspendAll();//挂起所有任务，任务创建完再按照优先级依次操作

    xTaskCreate(Task1,"Task1",1024*5,NULL,1,NULL);
    xTaskCreate(Task2,"Task2",1024*5,NULL,2,NULL);
    xTaskCreate(Task3,"Task3",1024*5,NULL,3,NULL);

    xTaskResumeAll();//开启任务调度器
}
