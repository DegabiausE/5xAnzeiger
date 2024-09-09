//https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html#file-system-object-spiffs-littlefs-sd-sdfs

void OpenDir() {
  Serial.println(F("Open Dir ---"));
  Dir dir = LittleFS.openDir("/");
  while (dir.next()) {
      Serial.print(dir.fileName());
      if(dir.fileSize()) {
          File f = dir.openFile("r");
          Serial.println(f.size());
      }
  }
  Serial.println(F("---"));
}

void initFileSystem(){
  // init file system
  if (!LittleFS.begin()) {
    Serial.println(F("File system mount failed"));
  }
  else {
    Serial.println(F("File system mount successful"));
  }

}

void DeletePictures(){
  //LittleFS.remove("/SavedFile.txt"); 
  Serial.println(F("DeletePictures"));
  Dir dir = LittleFS.openDir("/");
  while (dir.next()) {
      String FileName = dir.fileName();
      String FileExtension = ".bmp";

      if (FileName.indexOf(".bmp") > 0){
        Serial.println(F("File deletion: "));
        Serial.print(dir.fileName());
        LittleFS.remove("/" + FileName);

      }

  } 
  Serial.println(F("DeletePictures Done"));
}


void Format (){
  if (LittleFS.format()==true){
    Serial.println(F("File formated"));
  }
  else {
    Serial.println(F("File system format failed"));
  }

}

// Kopiert von https://handyman.dulare.com/save-configuration-data-in-the-file-system-of-esp8266/

String load_from_file(String file_name) {
  String result = "";
  
  File this_file = LittleFS.open(file_name, "r");
  if (!this_file) { // failed to open the file, retrn empty result
    return "result1.json";
  }
  while (this_file.available()) {
      result += (char)this_file.read();
  }
  
  this_file.close();
  return result;
}

bool write_to_file(String file_name, String contents) {  
  File this_file = LittleFS.open(file_name, "w");
  if (!this_file) { // failed to open the file, return false
    return false;
  }
  int bytesWritten = this_file.print(contents);
 
  if (bytesWritten == 0) { // write failed
      return false;
  }
   
  this_file.close();
  return true;
}

///end