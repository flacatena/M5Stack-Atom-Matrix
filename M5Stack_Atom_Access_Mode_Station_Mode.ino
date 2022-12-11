#include <WiFi.h>

const char* atom_ssid = "M5Stack Atom Access and Station Mode";
const char* atom_pwd = "987654321";

const char* network_ssid = "SSID";
const char* network_password = "PWD";

void setup() {
Serial.begin(115200);
WiFi.begin(network_ssid, network_password);
WiFi.softAP(atom_ssid, atom_pwd);
}

void loop() {
}