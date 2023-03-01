// task suspension

#include <Arduino.h>

void mytask1(void *pvParam)
{
  Serial.println("suspension start");


  //if the internal code is time-critical , this method will be useful 
  //(the only thing to be thought is that the internal code should not be related to "task")

  vTaskSuspendAll();
  for (int i = 0; i < 99999; i++)
  {
    for (int j = 0; j < 99999; j++)
    {
      for (int k = 0; k < 9999; k++)
      {
        ;;
      }
    }
  }
  xTaskResumeAll();
  //if this method is not used, part of a --> part of b --> part of a --> part of b , resulting in the separate internal code 
  //when the method is used,part of a --> part of b --> the internal code of a --> part of b

  Serial.println("suspension end");

  // while (1)
  // {
  // Serial.println("mytask111");
  // vTaskDelay(1000 / portTICK_PERIOD_MS);

  // 内部挂起注意要小心再次挂起后resume失去作用
  //  vTaskSuspend(NULL);//internal suspension
  // }
  vTaskDelete(NULL);
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
  UBaseType_t vTaskPriority = 0;
  TaskHandle_t task1 = NULL;
  Serial.print("\n");
  xTaskCreate(mytask1, "LedBlink", 1024, NULL, 1, &task1);
  xTaskCreate(mytask2, "LedBlink", 1024, NULL, 1, NULL); // 此时已经执行了两次task1,2
  // 外部挂起可以先挂起再执行
  // vTaskResume(task1);
  //  vTaskDelay(500 / portTICK_PERIOD_MS);
  //  vTaskSuspend(task1);                                   // external suspension
  //  vTaskDelay(4000 / portTICK_PERIOD_MS);
  //  vTaskResume(task1);
}

void loop()
{
}