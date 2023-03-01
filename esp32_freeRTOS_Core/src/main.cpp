// task core

#include <Arduino.h>
#define LED 2

void mytask(void *pvParam)
{
  pinMode(LED, OUTPUT);
  while (1)
  {
    digitalWrite(LED, !digitalRead(LED));
    Serial.println(digitalRead(LED));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println(xPortGetCoreID());
  }
}

void setup()
{
  Serial.begin(9600);
  xTaskCreatePinnedToCore(mytask, "LedBlink", 1024, NULL, 1, NULL,0);
}

void loop()
{
  // Serial.println(xPortGetCoreID());
}