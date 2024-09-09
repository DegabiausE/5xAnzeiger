
#define TFT_CS5        1
#define TFT_CS4        16
#define TFT_CS3        0
#define TFT_CS2        2
#define TFT_CS1        4
#define TFT_RST        16                                            
#define TFT_DC         5

#define TFT_MOSI 13  // Data out
#define TFT_SCLK 14  // Clock out
// was zum lesen https://simple-circuit.com/draw-bmp-images-arduino-sd-card-st7735/



//#include <SPI.h>
//#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735  https://github.com/adafruit/Adafruit-ST7735-Library
//Adafruit_ST7735 tft[5] = {Adafruit_ST7735(TFT_CS1, TFT_DC, TFT_RST), Adafruit_ST7735(TFT_CS2, TFT_DC, TFT_RST),Adafruit_ST7735(TFT_CS3, TFT_DC, TFT_RST),Adafruit_ST7735(TFT_CS4, TFT_DC, TFT_RST),Adafruit_ST7735(TFT_CS5, TFT_DC, TFT_RST)};

#include <U8g2lib.h> //https://github.com/olikraus/u8g2
#include <Arduino_GFX_Library.h> // https://github.com/moononournation/Arduino_GFX

//#include <PNGdec.h>
//PNG png;
//#define PNG_FILENAME "/clear.png"
//#include "PNG.h"

Arduino_DataBus *bus1 = new Arduino_ESP8266SPI(5 /* DC */);//, 4 /* CS */);
//Arduino_DataBus *bus2 = new Arduino_ESP8266SPI(5 /* DC */, 2 /* CS */);
//https://stackoverflow.com/questions/56742556/how-do-i-use-an-array-of-abstract-objects-invalid-abstract-type-error 

Arduino_GFX *Display1 = new Arduino_ST7735(
  bus1, GFX_NOT_DEFINED  /* RST */, 1 /* rotation */, false /* IPS */,
  80 /* width */, 160 /* height */,
  24 /* col offset 1 */, 0 /* row offset 1 */,
  24 /* col offset 2 */, 0 /* row offset 2 */);

Arduino_GFX *gfx1 = new Arduino_Canvas(160 /* width */, 80 /* height */, Display1);

static BmpClass bmpClass;

// pixel drawing callback
static void bmpDrawCallback1(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h)
{
  gfx1->draw16bitRGBBitmap(x, y, bitmap, w, h);
}
// Mit Pointer
static int jpegDrawCallback(JPEGDRAW *pDraw)
{
  gfx1->draw16bitRGBBitmap(pDraw->x, pDraw->y, pDraw->pPixels, pDraw->iWidth, pDraw->iHeight);
  return 1;
}



void InitDisplay( ){
  Serial.println("InitDisplay ");
  //Display 1
  digitalWrite(4, 0);
  gfx1->begin();
  gfx1->fillScreen(BLACK);
  gfx1->flush();
  digitalWrite(4, 1);



  //Display 2
  if(DEBUG == false){
  digitalWrite(2, 0);
  gfx1->begin();
  gfx1->fillScreen(BLACK);
  gfx1->flush();
  digitalWrite(2, 1);
  }

  //Display 3
  digitalWrite(0, 0);
  gfx1->begin();
  gfx1->fillScreen(BLACK);
  gfx1->flush();
  digitalWrite(0, 1);

  //Display 4
  digitalWrite(16, 0);
  gfx1->begin();
  gfx1->fillScreen(BLACK);
  gfx1->flush();
  digitalWrite(16, 1);

  //Display 5
  if(DEBUG == false){
  digitalWrite(1, 0);
  gfx1->begin();
  gfx1->fillScreen(BLACK);
  gfx1->flush();
  digitalWrite(1, 1);
  }
  Serial.println("InitDisplay Done the new");
}

void DrawTextLine(int DisplayNumber, String TextLine, int x, int y ,const uint8_t *Font,uint16_t Color ) {
  gfx1->setCursor(x, y);
  gfx1->setFont(Font);
  gfx1->setTextColor(Color);
  gfx1->println(TextLine);
 // Serial.println(TextLine);
}

void DrawBmp(int DisplayNumber, String PictureFile, int x, int y){
 // Serial.println("DrawBmp");
  bool DownloadResult = false;
  int tries = 0;
  do {
    DownloadResult = DownloadFile(PictureFile);
    tries ++;
  } while (DownloadResult == false and tries <= 3);

  File bmpFile = LittleFS.open(PictureFile, "r");
  bmpClass.draw(&bmpFile, bmpDrawCallback1, false /* useBigEndian */,x /* x */, y /* y */, gfx1->width() /* widthLimit */, gfx1->height() /* heightLimit */);    
  bmpFile.close();
 // Serial.println("EndDrawBmp");
}

void DrawMyJpg(int DisplayNumber, String PictureFile, int x, int y){
 Serial.printf("DrawJpg");
 // stürzt ab wegen speichermangel
//  http.begin(client, "http://192.168.1.20:8000//cat.jpg");
// //  //http.begin(client, HTTP_HOST, HTTP_PORT, http_path);
//  int httpCode = http.GET();
//  Serial.printf("[HTTP] GET... code: %d\n", httpCode);
//  int jpeg_result = 0;
//  int len = http.getSize();
//  Serial.printf("[HTTP] size: %d\n", len);
// uint8_t *buf = (uint8_t *)malloc(len);
//  if (buf) {
    //  static WiFiClient *http_stream = http.getStreamPtr();
    //  jpeg_result = jpegOpenHttpStreamWithBuffer(http_stream, buf, len, jpegDrawCallback);
//       if (jpeg_result)
//       {
//         jpeg_result = jpegDraw(false /* useBigEndian */,
//                                 0 /* x */, 0 /* y */, gfx1->width() /* widthLimit */, gfx1->height() /* heightLimit */);
//       }
//       free(buf);
      
//  }
//  else {
  //      static WiFiClient *http_stream = http.getStreamPtr();
  //      jpeg_result = jpegOpenHttpStream(http_stream, len, jpegDrawCallback);

      //  if (jpeg_result)
      // {
      //   jpeg_result = jpegDraw(false /* useBigEndian */,
      //                           0 /* x */, 0 /* y */, gfx1->width() /* widthLimit */, gfx1->height() /* heightLimit */);
      // }

//  }
// http.end();
}

void SetBackground(int DisplayNumber, uint16_t Color){
   // Serial.println("Init");
    gfx1->fillScreen(Color);
}

void DrawLineOnDisplay(int DisplayNumber, int16_t  x1, int16_t  y1, int16_t  x2, int16_t  y2, uint16_t Color){
  gfx1->drawLine(x1,y1,x2,y2,Color);
}

void FlushCanvas(void){
  gfx1->flush();
}







//end

