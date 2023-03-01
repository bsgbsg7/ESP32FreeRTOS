/*
 * @Descripttion: mutex 互斥信号量

    文档解释：
        互斥锁是包含优先级继承机制的二进制信号量。 
        二进制信号量 能更好实现实现同步（任务间或任务与中断之间）， 而互斥锁有助于更好实现简单互斥（即相互排斥）。
        
    作用：
        用于互斥时， 互斥锁就像用于保护资源的令牌。 任务希望访问资源时，必须首先 获取 ('take') 令牌。 
        使用资源后，必须“返回”令牌，这样其他任务就有机会访问 相同的资源。

        互斥锁使用相同的信号量访问 API 函数，因此也能指定模块时间。 
        阻塞时间表示如果互斥锁不是立即可用， 则在尝试“获取”互斥锁时任务应进入阻塞状态的最大“滴答”数。 
        然而，与二进制信号量不同 互斥锁采用优先继承。 
        这意味着，如果高优先级任务在尝试获取当前由较低优先级任务持有的互斥锁（令牌）时阻塞， 则持有令牌的任务的优先级会暂时提高到阻塞任务的优先级。

        这一机制 旨在确保较高优先级的任务保持阻塞状态的时间尽可能短， 从而最大限度地减少已经发生的“优先级反转”现象！！！！！！！！！！！！！！

        优先级继承无法解决优先级反转！ 只是在某些情况下将影响降至最低。 硬实时应用程序的设计应首先 确保不会发生优先级反转。

    不应在中断中使用互斥锁，因为：
            互斥锁使用的优先级继承机制要求 从任务中（而不是从中断中）拿走和放入互斥锁。
            中断无法保持阻塞来等待一个被互斥锁保护的资源 由互斥锁保护的资源变为可用。

    个人理解：
        优先级：
            task3
            task2（并不会阻塞自身）
            task1
        执行过程：
            task3启动之后阻塞自身-->task2启动并且阻塞自身-->由于前两者的阻塞task1得以执行-->task1获得互斥锁 并 执行超时操作
            -->task3拿互斥量，由于task1并没有释放信号量-->task3继续阻塞-，task1被提到task3的优先级->因为task2是第二优先级，轮到task2和task1轮换执行
            -->task1在释放信号量之后会降低优先级-->task3执行，阻塞自身之后task2会执行-->由于task2并未阻塞自身，优先级降低之后的task1之后再也无法被执行
            （task2并非不会执行，而是会执行，而没有阻塞自身，会触发idle的看门狗）
        如果使用二进制互斥量：
            task3会一直无法取到互斥量，无法执行
        问题：
                vTaskSuspendAll();
                xTaskCreate(task1, "task1", 1024 * 5, NULL, 1, NULL);
                xTaskCreate(task2, "task2", 1024 * 5, NULL, 2, NULL);
                xTaskCreate(task3, "task2", 1024 * 5, NULL, 3, NULL);
                xTaskResumeAll();
            在执行以上代码的时候发现vTaskSuspendAll之后，任务首次执行的先后顺序是2,3,1，不符合优先级，并且task3取得互斥量的时候，task1还会执行，与task3抢夺互斥量
        原因：
            不同任务被放置到不同的核心了，使用xTaskCreatePinnedToCore放置到同一个核心可以解决以上所有问题

 * @version: 1.0
 * @Author: Bsgbsg7
 * @Date: 2023-02-26 10:40:41
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

SemaphoreHandle_t mutexHandle;


void task1(void *pvParm)
{
    BaseType_t xResult;
    while (1)
    {
        printf("task1 begin!\n");
        xResult = xSemaphoreTake(mutexHandle, 1000);
        if (xResult == pdPASS)
        {
            printf("task1 take!\n");
            // 成为互斥量的所有者，执行超时操作
            for (int i = 0; i < 20; i++)
            {
                printf("task1 : %d\n", i);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
            xSemaphoreGive(mutexHandle);
            printf("task1 give!\n");
            vTaskDelay(pdMS_TO_TICKS(5000));
        }
        else
        {
            printf("task1 didn't take!\n");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

void task2(void *pvParm)
{
    printf("task2 begin!\n");
    // 阻塞task2，使得优先级最低的task1有机会执行
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    while (1)
    {
        while(1)
        {
            ;;;
        }
    }
}

void task3(void *pvParm)
{
    BaseType_t xResult;
    printf("task3 begin!\n");
    // 阻塞task3，使得优先级最低的task2和task1有机会执行
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    while (1)
    {
        xResult = xSemaphoreTake(mutexHandle, 1000);
        if (xResult == pdPASS)
        {
            printf("task3 take!\n");
            // 用for循环模拟程序处理，处理完毕之后释放互斥量
            for (int i = 0; i < 10; i++)
            {
                printf("task3 : %d\n", i);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
            xSemaphoreGive(mutexHandle);
            printf("task3 give!\n");
            vTaskDelay(pdMS_TO_TICKS(5000));
        }
        else
        {
            printf("task3 didn't take!\n");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}


// void app_main(void)
// {
//     mutexHandle = xSemaphoreCreateMutex();
//     //mutexHandle = xSemaphoreCreateBinary();
//     xSemaphoreGive(mutexHandle);
//     vTaskSuspendAll();

//     xTaskCreatePinnedToCore(task1, "task1", 1024 * 5, NULL, 1, NULL,0);
//     xTaskCreatePinnedToCore(task2, "task2", 1024 * 5, NULL, 2, NULL,0);
//     xTaskCreatePinnedToCore(task3, "task2", 1024 * 5, NULL, 3, NULL,0);

//     xTaskResumeAll();
// }
