#include <stdio.h>
#include "epaper.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/timer.h"

#define COLORED 	 (0)
#define UNCOLORED (1)

void app_main(void)
{
	Epd epd;
	
	// Instantiate e-paper frame_
	unsigned char* frame_ = (unsigned char*)malloc(epd.width * epd.height / 8);
	
	Paint paint(frame_, epd.width, epd.height);
	
	// Instantiate e-paper display and clear pixels
	ESP_LOGI("EPD", "e-Paper init and clear");
  epd.LDirInit();
  epd.Clear();

  while (1) {
		int d = 3;
    for (char i = '0'; i <= '9'; i++)
    {
      // paint_.Clear(UNCOLORED);
      paint_.DrawCharAt(d, d, i, &Font20, COLORED);
      epd.DisplayPart(frame_);
      d = d + 20;
      vTaskDelay(500);
    }
	}
	
	esp_restart();

}
