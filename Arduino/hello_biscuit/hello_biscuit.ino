#include <Adafruit_BNO055.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

Adafruit_BNO055 bno055 = Adafruit_BNO055();
WiFiUDP Udp;
unsigned int localUdpPort = 4210;
char message[256];

void setup()
{
  // configure builtin led as output pin
  pinMode(LED_BUILTIN, OUTPUT); 
  //open serial port of speed 115200
  
  Serial.begin(115200);
  Udp.begin(localUdpPort);
  
  //start the sensor
  bno055.begin();
  Serial.println();

  WiFi.begin("SAROLTA", "Kelemen238");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Biscuit LED turns on when connected to WiFi
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

    // Obtain euler angle vector from Orientation Sensor
    imu::Vector<3> euler = bno055.getVector(Adafruit_BNO055::VECTOR_EULER);
    
    // Print euler angles as serial output
    //Serial.println("[EULER ANGLES]");
    //Serial.println(euler.x());
    //Serial.println(euler.y());
    //Serial.println(euler.z());

    // Send packet to port 4210
    Udp.beginPacket(Udp.remoteIP(),4210);

    sprintf(message,"[BISCUIT Euler Angles]\nx: %f\ny: %f\nz: %f\n",euler.x(),euler.y(),euler.z());
    Udp.write(message);
    Udp.endPacket();
    
    delay(100);
}
