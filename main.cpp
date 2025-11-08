#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <FreeRTOS.h>
#include <task.h>

#define MY_TASK_PRIORITY  2

#define LED_DELAY_MS 1000

// gpio pin numbers
const int gpio_led = 15;
const int gpio_pushbutton = 14;

TaskHandle_t handle_task_led = nullptr;

// Perform initialisation
void pico_led_init(void) {
    gpio_init(gpio_led);
    gpio_set_dir(gpio_led, GPIO_OUT);
}

// Perform initialisation
void pico_button_init(void) {
    gpio_init(gpio_pushbutton);
    gpio_set_dir(gpio_pushbutton, GPIO_IN);
    gpio_pull_up (gpio_pushbutton);
}

// Turn the led on or off
void pico_set_led(bool led_on) {
    gpio_put(gpio_led, led_on);
}

// Task handling all the non-deterministic or long lasting operations
// such as switching on and off the LED and doing the delay.
static void my_task(void*) {
    for (;;) {
	// We wait for the notification from the ISR
 	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	// LED on
	pico_set_led(true);
	// Delay
        vTaskDelay(pdMS_TO_TICKS(LED_DELAY_MS));
	// LED off
	pico_set_led(false);
    }
    vTaskDelete(NULL);
}

// The ISR does nothing else than notifying the task
// and returns as quickly as possible.
void gpio_isr(uint gpio, uint32_t events) {
    // notify task
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(handle_task_led, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

int main() {
    // init the GPIO for the LED
    pico_led_init();
    pico_button_init();

    // create an freeRTOS task
    xTaskCreate(my_task,
		"application_task",
		configMINIMAL_STACK_SIZE,
		NULL,
		MY_TASK_PRIORITY,
		&handle_task_led);

    gpio_set_irq_enabled_with_callback(gpio_pushbutton,
				       GPIO_IRQ_EDGE_FALL,
				       true,
				       &gpio_isr);

    // this starts effectively freeRTOS and should never return.
    vTaskStartScheduler();
    
    // we should have never returned from FreeRTOS!
    panic_unsupported();
}
