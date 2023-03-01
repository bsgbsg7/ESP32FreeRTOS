// task priorities

#include <Arduino.h>

void mytask1(void *pvParam)
{
  while (1)
  {
    Serial.println("mytask111");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void mytask2(void *pvParam)
{
  while (1)
  {
    Serial.println("mytask222");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(9600);
  //then Ready state tasks of equal priority will share the available processing time 
  //using a time sliced round robin scheduling scheme,按照创建顺序执行相同时间
  // xTaskCreate(mytask1, "LedBlink", 1024, NULL, 1, NULL);
  // xTaskCreate(mytask2, "LedBlink", 1024, NULL, 1, NULL);

  //the task which has higher priority will start first
  // xTaskCreate(mytask1, "LedBlink", 1024, NULL, 1, NULL);
  // xTaskCreate(mytask2, "LedBlink", 1024, NULL, 2, NULL);  
  UBaseType_t vTaskPriority = 0;
  TaskHandle_t task1 = NULL;
  Serial.print("\n");
  xTaskCreate(mytask1, "LedBlink", 1024, NULL, 1, &task1);
  xTaskCreate(mytask2, "LedBlink", 1024, NULL, 2, NULL);
  vTaskPriority = uxTaskPriorityGet(task1);
  Serial.println(vTaskPriority);
  vTaskPrioritySet(task1,3);
  vTaskPriority = uxTaskPriorityGet(task1);
  Serial.println(vTaskPriority);
}

void loop()
{
}