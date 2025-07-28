#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <FreeRTOS.h>
#include <task.h>

#define MY_TASK_PRIORITY  2

static void my_task(void *data);

int main() {
    stdio_init_all();

    xTaskCreate(my_task, "application_task", configMINIMAL_STACK_SIZE, NULL, MY_TASK_PRIORITY, NULL);

    vTaskStartScheduler();
    // we should never return from FreeRTOS
    panic_unsupported();
}

void my_task(void *data) {
    (void)data; // unused parameter

    printf("user task started\n");

    for (;;) {
        // Do something interesting here
        printf("My task is running!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    // Do not let a task procedure return
    vTaskDelete(NULL);
}

/*
* These functions are requried for FreeRTOS to work in static memory mode.
*/

#if configSUPPORT_STATIC_ALLOCATION
static StaticTask_t idle_task_tcb;
static StackType_t idle_task_stack[mainIDLE_TASK_STACK_DEPTH];
void vApplicationGetIdleTaskMemory(
    StaticTask_t **ppxIdleTaskTCBBuffer,
    StackType_t **ppxIdleTaskStackBuffer,
    uint32_t *pulIdleTaskStackSize
) {
    *ppxIdleTaskTCBBuffer = &idle_task_tcb;
    *ppxIdleTaskStackBuffer = idle_task_stack;
    *pulIdleTaskStackSize = mainIDLE_TASK_STACK_DEPTH;
}

static StaticTask_t timer_task_tcb;
static StackType_t timer_task_stack[configMINIMAL_STACK_SIZE];
void vApplicationGetTimerTaskMemory(
    StaticTask_t **ppxTimerTaskTCBBuffer,
    StackType_t **ppxTimerTaskStackBuffer,
    uint32_t *pulTimerTaskStackSize
) {
    *ppxTimerTaskTCBBuffer = &timer_task_tcb;
    *ppxTimerTaskStackBuffer = timer_task_stack;
    *pulTimerTaskStackSize = configMINIMAL_STACK_SIZE;
}
#endif
