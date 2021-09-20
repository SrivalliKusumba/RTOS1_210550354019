#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

void *const timer_id;

TimerHandle_t oneshot;
BaseType_t timer;

static void oneshotcallback(TimerHandle_t Timer);

void task1(void *data)
{
   while(1)
   {
       printf("task1 started\n");
       vTaskDelay(1000 / portTICK_PERIOD_MS);
   }
}

void task2(void *data)
{
   while(1)
   {
       printf("task2 started\n");
       vTaskDelay(2000 / portTICK_PERIOD_MS);
   }
}
void task3(void *data)
{
   oneshot = xTimerCreate("timer",(10000 / portTICK_PERIOD_MS),pdFALSE,timer_id, oneshotcallback);

    xTimerStart(timer, 1);
    while (1)
    {
        printf("task3\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }

}

static void oneshotcallback(TimerHandle_t Timer)
{

    printf("one shot timer\n");
}

void app_main(void)
{ 
    oneshot = xTimerCreate("Oneshot", pdMS_TO_TICKS(4000), pdFALSE, 0, oneshotcallback);

    xTaskCreate(task1, "task1", 2048, NULL, 1, NULL);
    xTaskCreate(task2, "task2", 2048, NULL, 2, NULL);
    xTaskCreate(task3, "task3", 2048, NULL, 3, NULL);
}
