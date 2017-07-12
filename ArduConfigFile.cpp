/*
 * SD card configuration file reading library
 *
 * Copyright (c) 2017 Victor Torre
 * Licensed under GPL version 3
 * a version of which should have been supplied with this file.
 *
 */


#include "ArduConfigFile.h"


/*
 * Opens the given file on the SD card.
 * Returns true if successful, false if not.
 *
 * configFileName = the name of the configuration file on the SD card.
 *
 */
bool ArduConfigFile::begin(const char *configFileName) {
  this->_file = SD.open(configFileName, FILE_READ);
  if (!this->_file) {
#ifdef ARDUCONFIGFILE_DEBUG
    Serial.print("File ");
    Serial.print(configFileName);
    Serial.println("not found");
#endif
    return false;
  }
#ifdef ARDUCONFIGFILE_DEBUG
    Serial.print("File ");
    Serial.print(configFileName);
    Serial.println(" loaded");
#endif
  return true;
}


ArduConfigFile::~ArduConfigFile() {
  this->.close();
}


void ArduConfigFile::close() {
  if (this->_file) {
    this->_file.close();
  }
}


int ArduConfigFile::find(const char c, const int start){
  int pos = -1;
  if (this->_file) {
    _file.seek(start);
    int next = _file.read();
    while(next != -1 && ((char)next != c)){
      next = this->_file.read();
    }
    if ((char)next == c){
      pos = this->_file.position();
    }
  }
  return pos;
}


int ArduConfigFile::find_section(const char *section, const int start){
  int found_at = -1;
  if (this->_file) {
#ifdef ARDUCONFIGFILE_DEBUG
    Serial.print("Finding section ");
    Serial.println(section);
#endif
    const int length = strlen(section);
    int start_at = -1;
    int end_at = -1;
    int pos = start;

    while(found_at == -1){
      start_at = this->find('[', pos);
      if(start_at == -1)
        break;
      end_at = this->find(']', start_at);
      if(end_at == -1)
        break;

#ifdef ARDUCONFIGFILE_DEBUG
      Serial.print("Section found size:");
      Serial.print(end_at - start_at -1);
      Serial.print(" expected:");
      Serial.print(length);
      Serial.print(" is:");
      _file.seek(start_at);
      String str = _file.readStringUntil(']');
      Serial.println(str);
#endif
      if(length == (end_at - start_at -1)){
        _file.seek(start_at);
        String str = _file.readStringUntil(']');
        if(str.equalsIgnoreCase(section)){
          found_at = _file.position();
        }
      }
      pos = end_at;
    }
  }
#ifdef ARDUCONFIGFILE_DEBUG
  else {
    Serial.print("Find section ");
    Serial.print(section);
    Serial.println(" > Error!");
  }
#endif
  return found_at;
}


int ArduConfigFile::find_option(const char *option, const int start){
  int found_at = -1;
  if (this->_file) {
#ifdef ARDUCONFIGFILE_DEBUG
    Serial.print("Finding option ");
    Serial.println(option);
#endif
    const int length = strlen(option);
    int start_at = -1;
    int end_at = -1;
    int pos = start;
    int next_section_at = this->find('[', start);

    while(found_at == -1){
      if(next_section_at!=-1 && pos > next_section_at)
        break;
      start_at = this->find('\n', pos);
      if(start_at == -1)
        break;
      end_at = this->find('=', start_at);
      if(end_at == -1)
        break;

#ifdef ARDUCONFIGFILE_DEBUG
      Serial.print("Option found size:");
      Serial.print(end_at - start_at -1);
      Serial.print(" expected:");
      Serial.print(length);
      Serial.print(" is:");
      _file.seek(start_at);
      String str = _file.readStringUntil('=');
      Serial.println(str);
#endif

      if(length == (end_at - start_at -1)){
        _file.seek(start_at);
        String str = _file.readStringUntil('=');
        if(str.equalsIgnoreCase(option)){
          found_at = _file.position();
        }
      }
      pos = end_at;
    }
  }
#ifdef ARDUCONFIGFILE_DEBUG
  else {
    Serial.print("Finding option ");
    Serial.print(option);
    Serial.println(" > Error");
  }
#endif
  return found_at;
}


/*
 * Returns the value part of the most-recently-read setting,
 * or null if there was an error.
 */
String ArduConfigFile::getValue(const char *section, const char *option) {
  String ret;
  if (this->_file) {
#ifdef ARDUCONFIGFILE_DEBUG
    Serial.print("Finding [");
    Serial.print(section);
    Serial.print("] = ");
    Serial.println(option);
#endif
    int start_at = this->find_section(section);
    if(start_at != -1){
      start_at = this->find_option(option, start_at);
      if(start_at != -1){
        _file.seek(start_at+1);
        ret = _file.readStringUntil('\n');
#ifdef ARDUCONFIGFILE_DEBUG
    Serial.print("Found ");
    Serial.print(ret);;
#endif
      }
#ifdef ARDUCONFIGFILE_DEBUG
      else{
        Serial.println("Not Found option!");
      }
#endif
    }
#ifdef ARDUCONFIGFILE_DEBUG
    else{
      Serial.println("Not Found section!");
    }
#endif
  }
#ifdef ARDUCONFIGFILE_DEBUG
  else {
    Serial.print("Finding [");
    Serial.print(section);
    Serial.print("] = ");
    Serial.print(option);
    Serial.println(" > Error!");
  };
#endif
  return ret;
}

/*
 * Returns the value part of the most-recently-read setting
 * as a boolean.
 * The value "true" or "on" corresponds to true;
 * all other values correspond to false.
 */
bool ArduConfigFile::getBoolean(const char* section, const char* option) {
  String str = this->getValue(section, option);
  bool ret = false;
  if (str) {
#ifdef ARDUCONFIGFILE_ON_BOOL
    if (str.equalsIgnoreCase("true") || str.equalsIgnoreCase("on")) {
      ret = true;
    }
#else
    if (str.equalsIgnoreCase("true")) {
      ret = true;
    }
#endif
  }
  return ret;
}
