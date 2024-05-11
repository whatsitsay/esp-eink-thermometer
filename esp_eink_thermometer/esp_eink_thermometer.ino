#include <SPI.h>
#include <EPD1in54.h>
#include <EPDPaint.h>

#define COLORED   (0)
#define UNCOLORED (1)

EPDPaint* paint_;
EPD1in54* epd;
unsigned char* frame_;
char strBuf[50];

void setup() {
  Serial.begin(115200);
  Serial.println("Simple counting test for Waveshare 1.54\" display");
  Serial.println(strBuf);
  // Instantiate EPD
  epd = new EPD1in54(26,27,15,25); // RST, DC, CS, BSY
  // Restart SPI bus with new pins
  SPI.begin(14, MISO, 13, SS);

  // Instantiate painter
	frame_ = (unsigned char*)malloc((epd->width * epd->height) / 8);
	paint_ = new EPDPaint(frame_, epd->width, epd->height);

  // Clear pixels
  Serial.println("e-Paper init & clear");
  if (epd->init(lutFullUpdate) != 0) {
    Serial.print("Failed to init ePaper");
    return;
  }

  // Clear code from EPD1in54ShowRunningTime.ino example
  epd->clearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd->displayFrame();
  epd->clearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd->displayFrame();

  Serial.println("Frame cleared! Starting loop");
}

void loop() {
  int d = 3;
  for (char i = '0'; i <= '9'; i++)
  {
    // paint_.Clear(UNCOLORED);
    sprintf(strBuf, "Drawing \#%d at (%d, %d)", i, d, d);
    Serial.println(strBuf);
    paint_->drawCharAt(d, d, i, &Font20, COLORED);
    epd->setFrameMemory(frame_);
    epd->displayFrame();
    d = d + 20;
    delay(1000);
  }
}
