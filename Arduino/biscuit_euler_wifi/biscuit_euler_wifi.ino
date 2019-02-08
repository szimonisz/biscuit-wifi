#include <Adafruit_BNO055.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

Adafruit_BNO055 bno055 = Adafruit_BNO055();
WiFiUDP Udp;

char* wifiSSID = "INSERT SSID HERE";
char* wifiPassword = "INSERT WIFI PASSWORD HERE";

// IP address must be seperated via commas, rather than periods:
IPAddress packetDestinationIP(01,123,123,123);
// Change this variable to change the port the biscuit data is sent to.
unsigned int localUdpPort = 4210;

char message[1024];

void setup()
{
  // configure builtin led as output pin
  pinMode(LED_BUILTIN, OUTPUT); 
  //open serial port of speed 115200
  
  Serial.begin(115200);
  Udp.begin(localUdpPort);
  
  // start the sensor
  bno055.begin();
  Serial.println();

  WiFi.begin(wifiSSID, wifiPassword);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Biscuit LED turns on when connected to WiFi
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

    // Obtain Euler Angle vector from Orientation Sensor (values in degrees)
    imu::Vector<3> euler = bno055.getVector(Adafruit_BNO055::VECTOR_EULER);
    // Magnetometer xyz values in uT (micro Teslas)
    imu::Vector<3> magnetometer = bno055.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    // Gyroscope xyz values in rps (radians per second)
    imu::Vector<3> gyroscope = bno055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    // Accelerometer xyz values in m/s^2
    imu::Vector<3> accelerometer = bno055.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    // Linear Acceleration xyz values in m/s^2
    imu::Vector<3> linear_accel = bno055.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    // Gravity xyz values in m/s^2
    imu::Vector<3> gravity = bno055.getVector(Adafruit_BNO055::VECTOR_GRAVITY);

    // Quaternion values (qW,qX,qY,qZ)
    imu::Quaternion quat = bno055.getQuat();

    Udp.beginPacket(packetDestinationIP,localUdpPort);
    
    sprintf(message,"[Euler Angles]\nx: %f\ny: %f\nz: %f\n",euler.x(),euler.y(),euler.z());
    sprintf(message+strlen(message),"[Magnetometer]\nx: %f\ny: %f\nz: %f\n",euler.x(),magnetometer.y(),magnetometer.z());
    sprintf(message+strlen(message),"[Gyroscope]\nx: %f\ny: %f\nz: %f\n",gyroscope.x(),gyroscope.y(),gyroscope.z());
    sprintf(message+strlen(message),"[Accelerometer]\nx: %f\ny: %f\nz: %f\n",accelerometer.x(),accelerometer.y(),accelerometer.z());
    sprintf(message+strlen(message),"[Linear Acceleration]\nx: %f\ny: %f\nz: %f\n",linear_accel.x(),linear_accel.y(),linear_accel.z());
    sprintf(message+strlen(message),"[Gravity]\nx: %f\ny: %f\nz: %f\n",gravity.x(),gravity.y(),gravity.z());
    sprintf(message+strlen(message),"[Quaternion]\nqW: %f\nqX: %f\nqY: %f\nqZ: %f\n",quat.w(),quat.x(),quat.y(),quat.z());

    Udp.write(message);
    Udp.endPacket();
    
    delay(100);
}
