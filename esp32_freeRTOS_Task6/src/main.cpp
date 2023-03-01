// task stack

#include <Arduino.h>
#define LED 2

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
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(9600);
  UBaseType_t task1Stack = 0, task2Stack = 0;
  TaskHandle_t task1 = NULL, task2 = NULL;
  Serial.print("\n");
  xTaskCreate(mytask1, "LedBlink", 1024, NULL, 1, &task1);
  xTaskCreate(mytask2, "LedBlink", 1024, NULL, 1, &task2); // 此时已经执行了两次task1,2
  while (1)
  {

    task1Stack = uxTaskGetStackHighWaterMark(task1);
    task2Stack = uxTaskGetStackHighWaterMark(task2);

    Serial.println("Task1   Task2");
    Serial.print(task1Stack);
    Serial.print('\t');
    Serial.println(task2Stack);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void loop()
{
}