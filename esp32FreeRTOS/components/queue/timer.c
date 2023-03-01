/*
 * @Descripttion: 软定时器
        基于Daemon Task，命令通过Timer Command Queue发送命令队列，
        软定时器通过回调函数执行中断
        1.与平台无关（不同MCU），与硬件无关
        2.会根据TIMER_TASK_STACK_DEPTH设置可以使用许多软件定时器
 * @version: 1.0
 * @Author: Bsgbsg7
 * @Date: 2023-02-25 22:25:41
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

//主义函数的接收参数的类型是 TimerHandle_t
void timer_call_back(TimerHandle_t xTimer)
{
    //获取并且输出定时器的各项属性
    TickType_t time;
    const char *timer_name =  pcTimerGetName(xTimer);
    const int *timer_id = pvTimerGetTimerID(xTimer);
    time = xTimerGetPeriod(xTimer);
    /*注意：
        “ * ”是解引用操作符
        timer_id 指针用于接收void *pvTimerGetTimerID( TimerHandle_t xTimer );函数返回的void指针
                指向其id
                只有指向字符串的时候可以使用%s不直接解引用直接传入地址
                对于int类型的指针，需要解引用取出其数据然后 %d 打印
    */
    printf("name : %s\tid : %d\ttime : %d\n",timer_name,*timer_id,time);
}

int id1 = 1;
int id2 = 2;

// void app_main(void)
// {
//     //1.用于存储定时器的句柄
//     TimerHandle_t timer1,timer2;
//     //2.创建两个软定时器，使用timer_call_back作为回调函数
//     timer1=xTimerCreate("timer1",pdMS_TO_TICKS(500),pdTRUE,(void *)&id1,timer_call_back);
//     timer2=xTimerCreate("timer2",pdMS_TO_TICKS(1000),pdTRUE,(void *)&id2,timer_call_back);
//     //3.开启两个软定时器
//     xTimerStart(timer1,0);
//     xTimerStart(timer2,0);

//     vTaskDelay(6000/portTICK_PERIOD_MS);
//     //停止定时器1
//     xTimerStop(timer1,0);
//     printf("timer1 stop running!\n");
    
//     //改变定时器2的循环周期
//     xTimerChangePeriod(timer2,pdMS_TO_TICKS(200),0);
// }
