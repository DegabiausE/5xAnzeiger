#include "HardwareSerial.h"
const uint16_t HTTP_TIMEOUT = 30000; // in ms, wait a while for server processing

void ProcessJason(String filename){
  int httpCode;
  int error;
  //Serial.println( "Download: " + filename);

  if (WiFi.status() != WL_CONNECTED) connectWifi();
  http.setTimeout(HTTP_TIMEOUT);
  http.begin(client, "http://192.168.1.20:8000/" + filename);

  int httpResponseCode = http.GET();
  int lenHttp = http.getSize();

  if (httpResponseCode <= 0){
    Serial.println("Http Code <=0");
    Serial.println(httpResponseCode);
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
  }
  else if (httpResponseCode != 200){
    Serial.printf("[HTTP] Not OK!\n");
  }
  else if (httpResponseCode == 200 and lenHttp > 0 ){
    int lenHttp = http.getSize();

    DynamicJsonDocument doc(3048);
    DeserializationError DesError = deserializeJson(doc, http.getStream());
    http.end();

    //int SizeDoc = doc.size();
    //Serial.printf("SizeDoc: %d\n", SizeDoc);

    if (DesError == DeserializationError::Ok) {
      
      JsonArray repos2 = doc["elements"];
      int SizeRepos = repos2.size();

      for (JsonObject repos : repos2) {

          if (repos["type"] == "Text") {
            //Serial.println("Display Text");
            DrawTextLine(1,repos["value"].as<const char*>(),repos["X"].as<int>(),repos["Y"].as<int>(), GetFont(repos["font"].as<const char*>()), ConvertColor(repos["color"].as<const char*>()));      
          }
          else if (repos["type"] == "Bild") {
            //Serial.println("Display Bild");
            DrawBmp(1,repos["value"].as<const char*>(),repos["X"].as<int>(),repos["Y"].as<int>());
          }
          else if (repos["type"] == "BildPng") {
           // Serial.println("Display BildPng");
           // DrawMyJpg(1,repos["value"].as<const char*>(),repos["X"].as<int>(),repos["Y"].as<int>());
          }  
          else if (repos["type"] == "Init") {

            SetBackground(1,ConvertColor(repos["color"].as<const char*>()));
          }
          else if (repos["type"] == "Debug") {
            Serial.println(repos["value"].as<const char*>());
          }
          else if (repos["type"] == "Line") {
            DrawLineOnDisplay(1,repos["X1"].as<int>(),repos["Y1"].as<int>(),repos["X2"].as<int>(),repos["Y2"].as<int>(),ConvertColor(repos["color"].as<const char*>()));
          }
          else if (repos["type"] == "Time") {
            DrawTextLine(1,String(digitalClockDisplay()),repos["X"].as<int>(),repos["Y"].as<int>(), GetFont(repos["font"].as<const char*>()), ConvertColor(repos["color"].as<const char*>()));    
          }
       }
    }
    else {
      Serial.printf("DeserializationError: %s\n", DesError.f_str());
    }
    yield();
    FlushCanvas();
    doc.clear();

    //Serial.printf("Done");
  } else {
    if (lenHttp <= 0) {
      Serial.printf("[HTTP] Unknow content size: %d\n", lenHttp);
    }   
  }
  
} 


void TestJason(String filename){
  Serial.println(F("Start TestJason"));
  File file = LittleFS.open(filename, "r");
  Serial.println(F("Opne"));
  DynamicJsonDocument doc(1024);

  Serial.println(F("Doc"));
  DeserializationError error = deserializeJson(doc, file);
  Serial.println(F("Deserial"));


 
  // Get a reference to the array
  JsonArray repos = doc["data"]["elements"];
  
  // Print the values
   for (JsonObject repo : repos) {
     Serial.print(repo.size());
     Serial.print(" - ");
     Serial.print(repo["type"].as<const char*>());
     Serial.print(repo["X"].as<int>());
     Serial.println(repo["Y"].as<int>());
   }

  if (error)
    Serial.println(F("Failed to read file, using default configuration"));
  file.close();
}


//Prints the content of a file to the Serial
void Jsonprint2(String filename) {
  // Open file for reading
  File file = LittleFS.open(filename, "w");
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
}



//end