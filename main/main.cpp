#include "esp_log.h"
#include "fonts.h"
#include "ssd1306.hpp"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

OLED oled = OLED(GPIO_NUM_4, GPIO_NUM_5, SSD1306_128x64);

void myTask(void *pvParameters) {
	uint16_t counter = 0;
	ostringstream os;
	while (1) {
		os.str("");
		oled.clear();

		os << counter;

		oled.select_font(4);
		oled.draw_string(0, 0, os.str(), WHITE, BLACK);

		oled.refresh(true);
		vTaskDelay(100 / portTICK_PERIOD_MS);
		counter++;
	}
}

#ifdef __cplusplus
extern "C" {
#endif
void app_main() {

	if (oled.init()) {
		ESP_LOGI("OLED", "oled inited");
		oled.select_font(3);
		oled.draw_string(0, 20, "Connecting...", WHITE, BLACK);
		oled.refresh(true);
		xTaskCreatePinnedToCore(&myTask, "clocktask", 2048, NULL, 5, NULL, 1);
	} else {
		ESP_LOGE("OLED", "oled init failed");
	}
}
#ifdef __cplusplus
}
#endif
