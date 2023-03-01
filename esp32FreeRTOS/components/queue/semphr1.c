/*
 * @Descripttion: 二进制信号量
    作用 ： 信号量实际使用中更多充当标志位，提示任务进行与否之类
            用于锁住信号，使某个任务对变量连续执行一段时间之后再释放交给其他任务执行
 * @version: 1.0
 * @Author: Bsgbsg7
 * @Date: 2023-02-25 22:30:41
*/

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

SemaphoreHandle_t semaphore_handle;
int a=0;

void task1(void * pvParm)
{
    while(1)
    {   
        //此处取得信号量之后，如果没有执行完for进而释放信号量
        //则task2无法取得信号量，进而对其操作
        //如果没有使用信号量，则task1和task2会轮询执行，
        //两者的for或占用相同时间轮换着执行
        xSemaphoreTake(semaphore_handle,portMAX_DELAY);
        for (int i=0;i<10;i++)
        {
            a++;
            printf("task1 : %d\n",a);
        }
        xSemaphoreGive(semaphore_handle);
        //注意此处一定要加vtaskdelay用于阻塞task，进而执行task2，否则会报错或者无法执行
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void task2(void * pvParm)
{
    while(1)
    {   
        xSemaphoreTake(semaphore_handle,portMAX_DELAY);
        for (int i=0;i<10;i++)
        {
            a++;
            printf("task2 : %d\n",a);
        }
        xSemaphoreGive(semaphore_handle);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

// void app_main(void)
// {
//     //注意创建之后，一定要立刻释放semaphore，否则任务将无法执行
//     semaphore_handle = xSemaphoreCreateBinary();
//     xSemaphoreGive(semaphore_handle);

//     xTaskCreate(task1,"task1",1024*5,NULL,1,NULL);
//     xTaskCreate(task2,"task2",1024*5,NULL,1,NULL);
// }
