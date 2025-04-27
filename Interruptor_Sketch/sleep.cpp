#include "sleep.h"

void goToDeepSleep(int wakeUpPin1) {
  pinMode(wakeUpPin1, INPUT_PULLUP);

  // Enable GPIO wakeup
  esp_sleep_enable_gpio_wakeup();
  gpio_wakeup_enable((gpio_num_t)wakeUpPin1, GPIO_INTR_LOW_LEVEL);

  Serial.println("Going to light sleep...");
  client.publish("interruptor/radar", "Dormindo");
  delay(100); // Allow publish to complete

  esp_light_sleep_start();
}
