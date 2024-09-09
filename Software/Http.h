#include "HardwareSerial.h"

//https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient
#include <ESP8266HTTPClient.h> //https://links2004.github.io/Arduino/dd/d8d/class_h_t_t_p_client.html

HTTPClient http;  //Declare an object of class HTTPClient

String HttpGet(){

  String payload;
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    if (WiFi.status() != WL_CONNECTED) connectWifi();
    http.begin(client, "http://192.168.1.20:8000/test.txt");  //Specify request destination
    int httpCode = http.GET();                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      payload = http.getString();   //Get the request response payload
      //Serial.println(payload);             //Print the response payload
      
    }
 
    http.end();   //Close connection
 
  }

  return payload;
}

bool DownloadFile(String FileName){

  int httpCode= 0;
  int error = 0;
  bool result = false;

  FileName = "/" + FileName;
 // Serial.println( "Download: " + FileName);

  if (LittleFS.exists(FileName) == false) {
    Serial.println("Does not exist: " + FileName);
    f = LittleFS.open(FileName, "w");
    if (f ) {
      if (WiFi.status() != WL_CONNECTED) connectWifi();
      http.begin(client, "http://192.168.1.20:8000/" + FileName);
      httpCode = http.GET();
      int lenHttp = http.getSize();
      Serial.printf("[HTTP] size: %d\n", lenHttp);
      
      FSInfo fs_info;
      LittleFS.info(fs_info);
      Serial.print("FS Toatal Bytes: ");
      Serial.println(fs_info.totalBytes);
      Serial.println("FA Used Bytes: ");
      Serial.println(fs_info.usedBytes);

      if (lenHttp>=0 && (size_t)lenHttp + 10000 > (fs_info.totalBytes - fs_info.usedBytes)){
        Serial.println("passt nicht rein");
        DeletePictures();
      }

      switch (httpCode) {
        case HTTP_CODE_OK:
          error = http.writeToStream(&f);
          //Serial.println( "Download finished: " + FileName);
          result = true;
          break;

        default:
          Serial.println(F("[HTTP] GET failed, error: "));
          Serial.printf("%i - %s\r\n", httpCode, http.errorToString(httpCode).c_str());
          LittleFS.remove(FileName);
          result = false;
          break;
      }
      f.close();
    }
    http.end();
    
  }
  else {
   // Serial.println( "Exist: " + FileName);
    result = true;
  }

  return result;
}


