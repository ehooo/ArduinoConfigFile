#ifndef __ArduConfigFile_h__
#define __ArduConfigFile_h__

#define ARDUCONFIGFILE_ON_BOOL

/*
 * SD card configuration file reading library
 *
 * Copyright (c) 2017 Victor Torre
 * Licensed under GPL version 3
 * a version of which should have been supplied with this file.
 *
 */

#include <Arduino.h>
#include <SD.h>

class ArduConfigFile {
  private:
    File _file;
    int find(const char c, const int start=0);
    int find_section(const char *section, const int start=0);
    int find_option(const char *option, const int start=0);

  public:
    ~ArduConfigFile();
    bool begin(const char *configFileName);
    void close();
    String getValue(const char *section, const char *option);
    bool getBoolean(const char *section, const char *option);
};
#endif
