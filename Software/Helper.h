// 5	Pixel Height		u8g2_font_4x6_mf X11
// 7 	Pixel Height		u8g2_font_6x10_mf X11
// 9 	Pixel Height 		u8g2_font_6x13_mf X11
// 10	Pixel Height		u8g2_font_7x14_mf X11
// 13 Pixel Height 		u8g2_font_10x20_mf X11

const uint8_t* GetFont(const char* TargetFont){
  //Serial.print("GetFont");
  if (TargetFont!= NULL){
    if (strcmp(TargetFont,"u8g2_font_6x13_mr") == 0){
      return u8g2_font_6x13_mr;
    }
    else if (strcmp(TargetFont,"u8g2_font_4x6_mf") == 0){
      return u8g2_font_4x6_mf;
    }
    else if (strcmp(TargetFont,"u8g2_font_6x10_mf") == 0){
      return u8g2_font_6x10_mf;
    }  
    else if (strcmp(TargetFont,"u8g2_font_6x13_mf") == 0){
      return u8g2_font_6x13_mf;
    }  
    else if (strcmp(TargetFont,"u8g2_font_7x14_mf") == 0){
      return u8g2_font_7x14_mf;
    }  
    else if (strcmp(TargetFont,"u8g2_font_10x20_mf") == 0){
      return u8g2_font_10x20_mf;
    }  
    else {
      Serial.println(" GetFontEnd");
      return u8g2_font_maniac_tr;
    }
  }
  else {
    Serial.println(" GetFontEnd");
    return u8g2_font_maniac_tr;
  }
}


uint16_t ConvertColor(const char* Color){
  //https://www.barth-dev.de/online/rgb565-color-picker/
 // Serial.print("ConvertColor");
  uint16_t  x= 0x0;

  if (Color != NULL){
    if (strlen(Color) == 4){
      x = strtol (Color, NULL, 16);
    }
  }
  else {
    x= 0x0;
  }
  //Serial.println(" EndConvertColor");
  return x;  
}

int GetDisplayNr(int DiplayNr){
  Serial.print("GetDisplayNr");
  if (DiplayNr > 0){
    return DiplayNr;
  }
  else {
    Serial.print("No Display");
    return 1;
  }
}

//end