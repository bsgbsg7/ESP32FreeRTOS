// task watchdog
/*
	任务看门狗定时器 (TWDT) 负责检测运行的任务在长时间没有让出 CPU 的情况
	通常是由一个高优先级任务不让出 CPU 资源的循环引起，
	从而使较低优先级任务无法获得 CPU 资源。这可能是外围设备上的代码写得不好，也可能是陷入无限循环的任务。

	中断看门狗负责检测 FreeRTOS 任务切换被长时间阻塞的情况。TWDT 负责检测任务长时间不让步 CPU 运行的情况。

	每个核心都只有一个看门狗，IDLE表示空闲任务，需要清除的任务，每个CPU都有一个IDLE

	Core1中看门狗除了IDLE（0）之外，还有loop_back（1）[即setup和loop的总和]

	默认情况下只有核心0开启看门狗，核心1不开启看门狗，故Core1中的程序卡死不会重启

*/
#include <Arduino.h>
#include "esp_task_wdt.h"

#define LED 2

void mytask1(void *pvParam)
{
	pinMode(LED, OUTPUT);
	while (1)
	{
		/*
			核心由系统选择，如果选择核心1，则不会重启

			由于此时任务内没有阻塞函数vTaskDelay,此任务由于优先级高，将一直占用CPU，IDLE超时
			有两种解决方法：
				1.添加vTaskDelay(1000 / portTICK_PERIOD_MS)或者suspend()函数，退还资源
				2.将task优先级调整为0（与IDLE一致）
		*/
		;
		// digitalWrite(LED, !digitalRead(LED));
		// Serial.println(digitalRead(LED));
		// vTaskDelay(1000 / portTICK_PERIOD_MS);//让任务进入blocked状态，退让资源；
		// 也可以让任务进入suspend状态，退让资源
	}
}

void mytask2(void *pvParam)
{
	esp_task_wdt_add(NULL);
	while (1)
	{
		// 1.
		//  ;

		// the first thing is to feed the dog
		esp_task_wdt_reset();
		Serial.println("task_222");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void setup()
{
	int state1, state2;
	TaskHandle_t task1, task2;
	Serial.begin(9600);
	esp_task_wdt_init(5, NULL); // Timeout period of TWDT in seconds
	xTaskCreatePinnedToCore(mytask1, "task1", 1024, NULL, 1, &task1, 1);//此时执行task1即使卡死也不会重启
	xTaskCreate(mytask2, "task2", 1024, NULL, 1, &task2);
	// while(1)
	// {
	// 	state1=esp_task_wdt_status(task1);//"261" refers to ESP_ERR_NOT_FOUND
	// 	state2=esp_task_wdt_status(task2);//"0" refers to ESP_OK
	// 	Serial.print("state1\t");
	// 	Serial.println(state1);
	// 	Serial.print("state2\t");
	// 	Serial.println(state2);
	// 	vTaskDelay(500 / portTICK_PERIOD_MS);

	// 关闭核心的看门狗，慎用（去除了保护）
	//  disableCore0WDT();
	//  disableCore1WDT();

	// }
}

void loop()
{
}
