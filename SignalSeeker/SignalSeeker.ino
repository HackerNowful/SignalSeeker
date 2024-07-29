#include <ESP8266WiFi.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <SdFat.h>
#include "icons.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SdFat SD;
SdFile dataFile;
TinyGPSPlus gps;
SoftwareSerial gpsSerial(3, 1); // RX, TX pins for GPS module
bool gpsValid = false;
const int chipSelect = D8;


U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
    Serial.begin(9600);
    u8g2.begin();
    gpsSerial.begin(9600);
    u8g2.setBitmapMode(1);
    u8g2.setFlipMode(1);
    WiFi.mode(WIFI_STA);
    if (!SD.begin(chipSelect, SPI_HALF_SPEED)) {
        Serial.println("SD card initialization failed!");
        u8g2.clearBuffer();
        u8g2.drawXBMP(-40, 0, 128, 45, failedSD); 
        u8g2.setFont(u8g2_font_6x10_tf);
        u8g2.drawStr(50, 15, "Please Insert");
        u8g2.drawStr(65, 25, "Sd-Card");
        u8g2.sendBuffer();
        delay(2000);
        while (1);
    }   
    Serial.println("SD card initialized.");
}

void saveNetworkDetails(const String& ssid, float latitude, float longitude, int rssi, int channel, const String& bssid, const String& encryption) {
  if (dataFile.open("/networks.csv", O_RDWR | O_CREAT | O_APPEND)) {
    dataFile.print(ssid);
    dataFile.print(",");
    dataFile.print(latitude, 6);
    dataFile.print(",");
    dataFile.println(longitude, 6);
    dataFile.print(",");
    dataFile.print(rssi);
    dataFile.print(",");
    dataFile.print(channel);
    dataFile.print(",");
    dataFile.print(bssid);
    dataFile.print(",");
    dataFile.print(encryption);  
    dataFile.close();
  } else {
    Serial.println("Error opening data file!");
  }
}

void icons() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_7x14_tn);
    u8g2.setCursor(110, 12);
    u8g2.print(WiFi.scanNetworks());
    u8g2.drawXBMP(90, 0, 16, 16, wifi);
    
  if (SD.begin(chipSelect, SPI_HALF_SPEED)) {
        u8g2.drawXBMP(0, 0, 16, 11, SDcard);
        }
    if (gpsValid) {
        u8g2.drawXBMP(20, 0, 16, 16, gpslogo);       
    }
    int networks = WiFi.scanNetworks();
        u8g2.setFont(u8g2_font_ncenB10_tr);
        u8g2.drawStr(10, 32, "SignalSeeker");
        u8g2.sendBuffer();
}

const char S_WEP[] = "WEP";
const char S_TKIP[] = "WPA";
const char S_CCMP[] = "WPA2";
const char S_NONE[] = "None";
const char S_AUTO[] = "Auto";
const char S_UNKNOWN[] = "Unkn.";

const char* getEncryptionType(int authType) {
  switch (authType) {
    case ENC_TYPE_WEP:
      return S_WEP;
    case ENC_TYPE_TKIP:
      return S_TKIP;
    case ENC_TYPE_CCMP:
      return S_CCMP;
    case ENC_TYPE_NONE:
      return S_NONE;
    case ENC_TYPE_AUTO:
      return S_AUTO;
    default:
      return S_UNKNOWN;
  }
}

void loop() {
  
icons();   
int n = WiFi.scanNetworks(false, true);

  for (int i = 0; i < n; ++i) {
        while (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {           
          if (gps.location.isValid()) {
            float latitude = gps.location.lat();
            float longitude = gps.location.lng();
            Serial.print(latitude);
            Serial.print(longitude);
            gpsValid = true;
            u8g2.drawXBMP(40, 0, 16, 16, save);
            saveNetworkDetails(WiFi.SSID(i), latitude, longitude, WiFi.RSSI(i), WiFi.channel(i), WiFi.BSSIDstr(i), getEncryptionType(WiFi.encryptionType(i)));
          } else {
            gpsValid = false;
          }
        }
      }
}
}
