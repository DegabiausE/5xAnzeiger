//https://arduino-esp8266.readthedocs.io/en/latest/index.html
#include <stdbool.h>
#include "Const.h"
#include <LittleFS.h>  // https://github.com/esp8266/Arduino/issues/8408

#include <ArduinoJson.h> //https://arduinojson.org/v6
//#include <PNGdec.h> // https://github.com/bitbank2/PNGdec

File f;

//https://www.electrosoftcloud.com/en/debug-with-serial-print/
#define DEBUG false
#define Serial if(DEBUG)Serial

#include "Disk.h"
#include "Wifi.h"
#include "Http.h" 
#include "Clock.h"
#include "BmpClass.h"
#include "Jpeg.h"
#include "Display.h"
#include "Helper.h"
#include "Json.h"


void setup(void) {

  pinMode(4, OUTPUT); //Display 1
  digitalWrite(4, 1);

  if(DEBUG == false){
  pinMode(2, OUTPUT); //Display 2
  digitalWrite(2, 1);
  }

  pinMode(0, OUTPUT); //Display 3
  digitalWrite(0, 1);

  pinMode(16, OUTPUT); //Display 4
  digitalWrite(16, 1);

  if(DEBUG == false){
  pinMode(1, OUTPUT); //Display 5
  digitalWrite(1, 1);
  }

  Serial.begin(115200);

  connectWifi();

  Serial.println("Init Display");
  InitDisplay();

  //Format ();
  initFileSystem();
  OpenDir();

  InitTime();
  TimeLoop();

  //Init File von Disk
  Display1Json = load_from_file(Display1FileName);
  Display2Json = load_from_file(Display2Filename);
  Display3Json = load_from_file(Display3Filename);
  Display4Json = load_from_file(Display4Filename);
  Display5Json = load_from_file(Display5Filename);

  Serial.println(Display1FileName);
}

uint32_t beginWait = 0;

void loop() {

  if (second() == 0  || millis() - beginWait > 2000) {
    //Serial.println("Loop Start");
    beginWait = millis();

    // Display 1
    digitalWrite(4, 0);
    delay(50);
    Serial.println("Display1Json");
    ProcessJason(Display1Json);
    digitalWrite(4, 1);
    delay(50);
  //  Serial.println("Sodel");

    if(DEBUG == false){
    // Display 2
    digitalWrite(2, 0);
    delay(50);
    Serial.println("Display2Json");
    ProcessJason(Display2Json);
    digitalWrite(2, 1);
    delay(50);
    }

    // Display 3
    digitalWrite(0, 0);
    delay(50);
    Serial.println("Display3Json");
    ProcessJason(Display3Json);
    digitalWrite(0, 1);
    delay(50);

    // Display 4
    digitalWrite(16, 0);
    delay(50);
    Serial.println("Display4Json");
    ProcessJason(Display4Json);
    digitalWrite(16, 1); 
    delay(50);

    if(DEBUG == false){
    // Display 5
    digitalWrite(1, 0);
    delay(50);
    ProcessJason(Display5Json);
    digitalWrite(1, 1);
    delay(50);
    }
  }
  server.handleClient();
 
}




//end