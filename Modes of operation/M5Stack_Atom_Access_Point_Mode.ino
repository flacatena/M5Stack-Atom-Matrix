#include <WiFi.h>

const char* ssid = "M5STACK ATOM MATRIX";
const char* password = "987654321";

void setup() {
Serial.begin(115200);
WiFi.softAP(ssid,password);
}

void loop () {
}
