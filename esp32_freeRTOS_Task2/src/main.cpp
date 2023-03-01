// four task parameters

#include <Arduino.h>

int a = 8;
int num[] = {7, 9, 8};
typedef struct A_STRUCT
{
  int iMem1;
  int iMem2;
} xStruct;
xStruct strTest = {1, 2};
static const char* name = "Bsgbsg7";

void mytask(void *pvParam)
{
  // int *intArray;
  // intArray = (int *)pvParam;
  // Serial.println('\n');
  // Serial.println(*intArray);
  // Serial.println(*(intArray+1));
  // Serial.println(*(intArray+2));

  // xStruct *pStrTest;
  // pStrTest = (xStruct *)pvParam;
  // Serial.println(pStrTest->iMem1);
  // Serial.println(pStrTest->iMem2);

  char* pName;
  pName = (char*)pvParam;
  Serial.println("\n");
  Serial.println(pName);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  vTaskDelete(NULL); // delete itself
}

void setup()
{
  Serial.begin(9600);
  TaskHandle_t myhandle = NULL;
  //xTaskCreate(mytask, "LedBlink", 2048, (void *)num, 1, &myhandle);
  // xTaskCreate(mytask, "LedBlink", 1024, (void *)&a, 1, &myhandle);
  //xTaskCreate(mytask, "LedBlink", 2048, (void *)&strTest, 1, &myhandle);
  xTaskCreate(mytask, "LedBlink", 2048, (void *)name, 1, &myhandle);
}

void loop()
{
}