#include "M5Atom.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "ATOM";
const char* password = "987654321";

AsyncWebServer server(80);
AsyncEventSource events("/events");

unsigned long last_time = 0;
unsigned long timerDelay = 1000;

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float accelerometer_X;
float accelerometer_Y;
float accelerometer_Z;

void startAccessPoint() {
WiFi.softAP(ssid , password);
}

void Read_Accelerometer() {
  M5.IMU.getAccelData(&accX,&accY,&accZ);
  accelerometer_X = accX;
  accelerometer_Y = accY;
  accelerometer_Z = accZ;
}

String processor(const String& var)
{
  Read_Accelerometer();
  if(var == "ACCELEROMETERX"){
  return String(accelerometer_X);
  }
  else if(var == "ACCELEROMETERY"){
    return String(accelerometer_Y);
  }
  else if(var == "ACCELEROMETERZ"){
    return String(accelerometer_Z);
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ATOM - ACCESS POINT MODE - X Y Z ACCELEROMTER VALUES</title>
</head>
<body>
  <div class="topnav">
    <h1>ATOM - ACCESS POINT MODE - MPU6886 - X Y Z ACCELEROMETER VALUES </h1>
  </div>
  <div class="content">
    <div class="boxes">
      <div class="box">
        <p> X AXIS </p><p><span id="X">%ACCELEROMETERX%</span> g </span></p>
      </div> 
      <br>
      <div class="box">
         <p> Y AXIS</p><p><span id="Y">%ACCELEROMETERY%</span> g </span></p>
      </div>  
      <br>
      <div class="box">
        <p> Z AXIS</p><p><span id="Z">%ACCELEROMETERZ%</span> g </span></p>
      </div> 
    </div>
  </div>

<script>
if (!!window.EventSource) {
 var source = new EventSource('/events');
 
 source.addEventListener('open', function(e) {
  console.log("Events got Connected!");
 }, false);

 source.addEventListener('error', function(e) {
  if (e.target.readyState != EventSource.OPEN) {
    console.log("Events got Disconnected!");
  }
 }, false);
 
 source.addEventListener('message', function(e) {
  console.log("message", e.data);
 }, false);
 
 source.addEventListener('ACCELEROMETERX', function(e) {
  console.log("X", e.data);
  document.getElementById("X").innerHTML = e.data;
 }, false);
  
 source.addEventListener('ACCELEROMETERY', function(e) {
  console.log("Y", e.data);
  document.getElementById("Y").innerHTML = e.data;
 }, false);

  source.addEventListener('ACCELEROMETERZ', function(e) {
  console.log("Z", e.data);
  document.getElementById("Z").innerHTML = e.data;
 }, false);
}
</script>
</body>
</html>)rawliteral";

void setup() {
  Serial.begin(115200);
  M5.begin(true, false, true);
  M5.IMU.Init();
  startAccessPoint();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", index_html, processor);
    }
  );

  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }

    client->send("hi!", NULL, millis(), 10000);
  });

  server.addHandler(&events);
  server.begin();
}

void loop() {

  if ((millis() - last_time) > timerDelay) {

    Read_Accelerometer();

    Serial.printf("X  = %.2f  \n", accelerometer_X);
    Serial.printf("Y = %.2f  \n",accelerometer_Y);
    Serial.printf("Z = %.2f  \n", accelerometer_Z);
    Serial.println();

    events.send("ping",NULL,millis());
    events.send(String(accelerometer_X).c_str(),"ACCELEROMETERX",millis());
    events.send(String(accelerometer_Y).c_str(),"ACCELEROMETERY",millis());
    events.send(String(accelerometer_Z).c_str(),"ACCELEROMETERZ",millis());
    last_time = millis();
  }
}
