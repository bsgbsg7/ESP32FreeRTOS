// // task create and delete

#include <Arduino.h>
// #define LED 2

// void mytask(void *pvParam)
// {
//   pinMode(LED, OUTPUT);
//   while (1)
//   {
//     digitalWrite(LED, !digitalRead(LED));
//     Serial.println(digitalRead(LED));
//     vTaskDelay(1000 / portTICK_PERIOD_MS);
//   }
//   //vTaskDelete(NULL);//delete itself
// }

// void setup()
// {
//   TaskHandle_t myhandle = NULL;
//   Serial.begin(9600);
//   xTaskCreate(mytask, "LedBlink", 1024, NULL, 1, &myhandle);

//   // vTaskDelay(5000 / portTICK_PERIOD_MS);
//   // if (myhandle != NULL)
//   // {
//   //   vTaskDelete(myhandle);
//   // }
// }

// void loop()
// {
// }

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println("Bsgbsg7");
}

