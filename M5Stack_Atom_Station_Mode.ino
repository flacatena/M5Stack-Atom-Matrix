#include <WiFi.h>

const char* ssid = "SSID";
const char* password = "PWD";

void setup() {
Serial.begin(115200);
WiFi.begin(ssid, password);
}

void loop() {
}