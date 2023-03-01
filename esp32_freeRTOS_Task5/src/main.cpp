// task trace
//there is something wrong that i dont know now

#include <Arduino.h>
#define LED 2
#define configUSE_STATS_FORMATTING_FUNCTIONS 1
#define configUSE_TRACE_FACILITY 1

void mytask1(void *pvParam)
{
	pinMode(LED, OUTPUT);
	while (1)
	{
		digitalWrite(LED, !digitalRead(LED));
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void mytask2(void *pvParam)
{
	while (1)
	{
		Serial.println("Bsgbsg7");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void setup()
{
	Serial.begin(9600);
	static char cBuffer[512] = {0};
	xTaskCreate(mytask1, "LedBlink", 1024, NULL, 1, NULL);
	xTaskCreate(mytask2, "Serial", 1024, NULL, 1, NULL);

	while (1)
	{
		vTaskList(cBuffer);
		Serial.println("Name	Priority	State	Stack	Num");
		Serial.println(cBuffer);
	}
}

void loop()
{
}