#include <WiFi.h>

const char* ssid = "M5STACK ATOM - ACCESS POINT - WEB SERVER";
const char* password = "987654321";

WiFiServer server(80);

String html = "<!DOCTYPE html> \
<html> \
<body> \
<center><h1>M5STACK ATOM MATRIX - ACCESS POINT - WEB SERVER</h1></center> \
</body> \
</html>" ;

void setup() {
Serial.begin(115200);
WiFi.softAP(ssid,password);
IPAddress IP = WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.print(IP);
server.begin();
}

void loop() {
WiFiClient client = server.available();
client.println(html);
} 
