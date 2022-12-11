#include <WiFi.h>

const char* atom_ssid = "M5STACK ATOM MATRIX - AP-SM -WS";
const char* atom_password = "987654321";

const char* network_ssid = "SSID";
const char* network_password = "PWD";

WiFiServer server(80);

String html = "<!DOCTYPE html> \
<html> \
<body> \
<center><h1>M5STACK ATOM MATRIX - ACCESS POINT - STATION MODE - WEB SERVER</h1></center> \
</body> \
</html>" ;

void setup() {
Serial.begin(115200);
WiFi.begin(network_ssid, network_password);
WiFi.softAP(atom_ssid, atom_password);
server.begin();
}

void loop() {
WiFiClient client = server.available();
client.println(html);
}
