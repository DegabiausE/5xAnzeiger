/************************* WiFi Access Point *********************************/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"

//Simple WEB Server https://handyman.dulare.com/handle-website-forms-on-esp8266/
// und https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
#define WLAN_SSID       "1234"
#define WLAN_PASS       "1234"
const char* SensorName   =   "Display2";

WiFiClient client;

int status = WL_IDLE_STATUS;
//WiFiManager wifiManager;
ESP8266WebServer server(80);  //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer

void handle_root() {
  String head = HTML_header;
  String foot = HTML_footer;
  String formhead = HTML_form_header;
  String formfoot = HTML_form_footer;
  String content = "<p>Konfigurierte Displays f&uumlr " + String(SensorName) + "</p>";
  String formcontent1 = "Enter Display 1: <input type=\"text\" name=\"display1\" value=\"" + Display1Json + "\"><br />";
  String formcontent2 = "Enter Display 2: <input type=\"text\" name=\"display2\" value=\"" + Display2Json + "\"><br />";
  String formcontent3 = "Enter Display 3: <input type=\"text\" name=\"display3\" value=\"" + Display3Json + "\"><br />";
  String formcontent4 = "Enter Display 4: <input type=\"text\" name=\"display4\" value=\"" + Display4Json + "\"><br />";
  String formcontent5 = "Enter Display 5: <input type=\"text\" name=\"display5\" value=\"" + Display5Json + "\"><br />";
  Serial.println("Server HAndle root");
  server.send(200, "text/html", head + content + formhead + formcontent1 +formcontent2 + formcontent3 + formcontent4 + formcontent5 + formfoot + foot);
}
void handle_form() {
  Serial.println("Server HAndle Form");
  String head = HTML_header;
  String foot = HTML_footer;
  String link = HTML_saved_link;
  
  if ( server.hasArg( "display1" ) && server.arg( "display1" ) != NULL ) {
    Display1Json = server.arg( "display1" );
    bool IsItDone = write_to_file (Display1FileName, Display1Json);
    Serial.println("Server HAndle Form neues Display 1");
  }
  if ( server.hasArg( "display2" ) && server.arg( "display2" ) != NULL ) {
    Display2Json = server.arg( "display2" );
    bool IsItDone = write_to_file (Display2Filename, Display2Json);
    Serial.println("Server HAndle Form neues Display 2");
  }
  if ( server.hasArg( "display3" ) && server.arg( "display3" ) != NULL ) {
    Display3Json = server.arg( "display3" );
    bool IsItDone = write_to_file (Display3Filename, Display3Json);
    Serial.println("Server HAndle Form neues Display 3");
  }
  if ( server.hasArg( "display4" ) && server.arg( "display4" ) != NULL ) {
    Display4Json = server.arg( "display4" );
    bool IsItDone = write_to_file (Display4Filename, Display4Json);
    Serial.println("Server HAndle Form neues Display 4");
  }
  if ( server.hasArg( "display5" ) && server.arg( "display5" ) != NULL ) {
    Display5Json = server.arg( "display5" );
    bool IsItDone = write_to_file (Display5Filename, Display5Json);
    Serial.println("Server HAndle Form neues Display 5");
  }

  server.send(200, "text/html", head + link + foot);
}
void handle_not_found() {
  server.send(404, "text/plain", "Page not found");
}

void initialize_www() {
  server.on("/", handle_root);
  server.on("/save", HTTP_POST, handle_form);
  server.onNotFound(handle_not_found);
  Serial.println("Server Init");
  server.begin(); 
}

void connectWifi() {
  
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  WiFi.setHostname(SensorName);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //server.begin();  
  //wifiManager.autoConnect();
  initialize_www();
}



//end connect