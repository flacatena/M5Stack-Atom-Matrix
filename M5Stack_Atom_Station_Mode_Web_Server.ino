#include <WiFi.h>

const char* ssid = "SSID";
const char* password = "PWD";

WiFiServer server(80);

String html = "<!DOCTYPE html> \
<html> \
<body> \
<center><h1>M5STACK ATOM MATRIX - STATION MODE - WEB SERVER</h1></center> \
</body> \
</html>";

void setup() {
Serial.begin(115200);
WiFi.begin(ssid,password);
server.begin();
}

void loop() {
WiFiClient client = server.available();
client.println(html);
}