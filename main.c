#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t task4_handle;
TaskHandle_t task5_handle;
QueueHandle_t xmq;

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
   while(1)
   {
       printf("task3 started\n");
       vTaskDelay(5000 / portTICK_PERIOD_MS);
   }
}

void task4(void* data)
{
    int x = 0;
    while(1)
    {
        printf("task4 started\n");
        x++;
        //send
        xQueueSend(xmq, &x, 0);
        printf("task4 ended\n");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

void task5(void* data)
{
    int buff = 0;
    while(1)
    {
        printf("task5 started\n");
        xQueueReceive(xmq, &buff, 0);
        printf("Buff = %d\n",buff);
        printf("task5 ended\n");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}


void app_main(void)
{ 
    xmq = xQueueCreate(5, sizeof(int));
    xTaskCreate(task1, "task1", 2048, NULL, 1, NULL);
    xTaskCreate(task2, "task2", 2048, NULL, 2, NULL);
    xTaskCreate(task3, "task3", 2048, NULL, 3, NULL);
    xTaskCreate(task4, "task4", 2048, NULL, 4, &task4_handle);
    xTaskCreate(task5, "task5", 2048, NULL, 6, &task5_handle);
}
