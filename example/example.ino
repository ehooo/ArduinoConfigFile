/*
 * SD card configuration file reading library
 *
 * Copyright (c) 2017 Victor Torre
 * Licensed under GPL version 3
 * a version of which should have been supplied with this file.
 *
 * The library supports one #define:
 *   #define ARDUCONFIGFILE_DEBUG // to print file error messages.
 */


#include "ArduConfigFile.h"

const char CONFIG_FILE[] = "config.cfg";

String wifi_name;
String wifi_password;

String host;
int port;
String path;

void readConfiguration();

void setup() {
  Serial.begin(9600);

  if (!SD.begin()) {
    Serial.println("SD Fail!!");
    return;
  }

  readConfiguration();
  Serial.println("Config loaded");
}

void loop() {
  // TODO connect to wifi and send data to remote server
}

void readConfiguration() {
  Serial.println("Loading conf");
  ArduConfigFile cfg = ArduConfigFile();
  const char* wifi_section = "wifi";
  const char* sever_section = "server";
  String str;

  if (!cfg.begin(CONFIG_FILE)) {
    Serial.print("Failed to open configuration file: ");
    Serial.println(CONFIG_FILE);
  }

  wifi_name = cfg.getValue(wifi_section, "name");
  wifi_password = cfg.getValue(wifi_section, "password");

  str = cfg.getValue(sever_section, "port");
  if(str){
    port = str.toInt();
  } else {
    port = 80;
  }
  host = cfg.getValue(sever_section, "host");
  path = cfg.getValue(sever_section, "path");
}

