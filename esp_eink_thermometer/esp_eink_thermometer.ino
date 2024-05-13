#include <SPI.h>
#include <EPD1in54B.h>
#include <EPDPaint.h>

#define COLORED   (0)
#define UNCOLORED (1)

#define EPD_MOSI  (33)
#define EPD_SCK   (32)
#define EPD_MISO  (23) // Not actually used
#define EPD_CS    (14)

EPDPaint* paint_;
EPD1in54B* epd;
unsigned char* frame_;
char strBuf[50];

void setup() {
  Serial.begin(115200);
  Serial.println("Simple counting test for Waveshare 1.54\" display");
  Serial.println(strBuf);
  // Instantiate EPD
  epd = new EPD1in54B(26,27, EPD_CS, 25); // RST, DC, CS, BSY
  // Change SPI pins
  SPI.begin(EPD_SCK, EPD_MISO, EPD_MOSI, EPD_CS);

  // Instantiate painter
	frame_ = (unsigned char*)calloc((epd->width * epd->height) / 8, sizeof(unsigned char)); // Zero-out
	paint_ = new EPDPaint(frame_, epd->width, epd->height);

  // Clear pixels
  Serial.println("e-Paper init & clear");
  if (epd->init() != 0) {
    Serial.print("Failed to init ePaper");
    return;
  }

  Serial.println("Frame cleared! Starting loop");
}

void loop() {
  int d = 3;
  for (char i = '0'; i <= '9'; i++)
  {
    paint_->clear(UNCOLORED);
    sprintf(strBuf, "Drawing \#%d at (%d, %d)", i, d, d);
    Serial.println(strBuf);
    paint_->drawCharAt(d, d, i, &Font20, COLORED);
    epd->displayFrame(frame_, NULL);
    d = d + 20;
    delay(1000);
  }
}
