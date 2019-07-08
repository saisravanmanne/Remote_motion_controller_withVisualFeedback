/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "Connectify-controlsystems";
const char* password = "controller123";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(12, OUTPUT);
pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
  digitalWrite(14, 0);
  digitalWrite(15, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\n');
  //     ****Serial.println(req);
  client.flush();
  //Serial.println(req.substring(5,9));
 String req2 = req.substring(5,9);
  
  // Match the request
  int val1=req2.toInt();
  Serial.println(val1);
  int val;
  //Serial.println(2*val1);
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  /*else {
    Serial.println("command received");
    client.stop();
    return;
  }*/
int calib=56;
  // Set GPIO2 according to the request
  client.flush();
  if ((val1 > 2999)&&(val1 < 3999)) {
    int rot=val1-3000;
    rot=rot/10;
    Serial.println(rot);
    digitalWrite(12,1);
    digitalWrite(13, 0);
    digitalWrite(14, 1);
    digitalWrite(15, 0);  
    delay(rot*calib);
    digitalWrite(12,0);
    digitalWrite(13, 1);
    digitalWrite(14, 1);
    digitalWrite(15, 0);  
  }
  if ((val1 > 3999)&&(val1 < 4999)) {
    int rot=val1-4000;
    rot=rot/10;
    Serial.println(rot);
 digitalWrite(12,0);
    digitalWrite(13, 1);
    digitalWrite(14, 0);
    digitalWrite(15, 1);  
    delay(rot*calib);
    digitalWrite(12,0);
    digitalWrite(13, 1);
    digitalWrite(14, 1);
    digitalWrite(15, 0);  
  }
  if (val1==1) {
    digitalWrite(12,0);
    digitalWrite(13, 0);
    digitalWrite(14, 0);
    digitalWrite(15, 0);  
  }
  if (val1==10) {
    digitalWrite(12,1);
    digitalWrite(13, 0);
    digitalWrite(14, 0);
    digitalWrite(15, 1);  
  }
if (val1==2) {
    digitalWrite(12,0);
    digitalWrite(13, 1);
    digitalWrite(14, 1);
    digitalWrite(15, 0);  
  }
  if (val1==3) {       //anticlockwise
    digitalWrite(12,1);
    digitalWrite(13, 0);
    digitalWrite(14, 1);
    digitalWrite(15, 0);  
  }
  if (val1==4) {
    digitalWrite(12,0);
    digitalWrite(13, 1);
    digitalWrite(14, 0);
    digitalWrite(15, 1);  
  }
  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n Blink rate updated ";
  //s += (val)?"high":"low";
  s += "</html>\n";
  client.print(s);

  

  // Send the response to the client
  
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}



