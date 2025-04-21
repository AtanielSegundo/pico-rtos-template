#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

const uint8_t led_pin = 13;

void vBlinkTask() {
   for (;;) {
      gpio_put(led_pin, 1);
      vTaskDelay(250);
      gpio_put(led_pin, 0);
      vTaskDelay(250);
   }

}

void main() {
   stdio_init_all();
   gpio_init(led_pin);
   gpio_set_dir(led_pin, GPIO_OUT);
   xTaskCreate(vBlinkTask, "Blink Task", 128, NULL, 1, NULL);
   vTaskStartScheduler();
}