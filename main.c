#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <FreeRTOS.h>
#include <task.h>

#define MY_TASK_PRIORITY  2

#define LED_DELAY_MS 250

// gpio pin number
const int n = 15;

// Perform initialisation
int pico_led_init(void) {
    gpio_init(n);
    gpio_set_dir(n, GPIO_OUT);
}

// Turn the led on or off
void pico_set_led(bool led_on) {
    gpio_put(n, led_on);
}

static void my_task(void *data) {
    (void)data; // unused parameter
    bool b = false;
    
    for (;;) {
        // Do something interesting and not just one task with a delay in it.
	// We supposed to be doing multitasking!
        vTaskDelay(pdMS_TO_TICKS(LED_DELAY_MS));
	pico_set_led(b);
	b = !b;
    }
    vTaskDelete(NULL);
}

int main() {
    // init the GPIO for the LED
    pico_led_init();

    // create an freeRTOS task
    xTaskCreate(my_task, "application_task", configMINIMAL_STACK_SIZE, NULL, MY_TASK_PRIORITY, NULL);

    // this starts effectively freeRTOS and should never return.
    vTaskStartScheduler();

    // we should have never returned from FreeRTOS!
    panic_unsupported();
}
