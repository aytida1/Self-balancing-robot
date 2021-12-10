#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;








#define LED_PIN 13
bool blinkState = false;

// pins for controlling motor's speed and direciton
int p1 = 11;
int p2 = 10;
int p3 = 9;
int p4 = 6;



void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(115200);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
 
    // configure Arduino LED pin for output
    pinMode(LED_PIN, OUTPUT);

    pinMode(p1, OUTPUT);
    pinMode(p2, OUTPUT);
    pinMode(p3, OUTPUT);
    pinMode(p4, OUTPUT);
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    // calculated angle            
    int angle = map(ay, 16200, -16700, 90, -90) + 5;     // +5 for making value 0
        
        
    Serial.print("ay: "); Serial.println(angle);    // printing tilt angle
      

    //for moving forward
    if(angle > 4){
      
          
        float rot_angle = angle*(3.14/180);   // tilt angle in radian
        float rot_speed = (4.7)*cos(rot_angle)*sqrt(1-cos(rot_angle)) + 1;  //rotation speed of tyre in rad/s
        int analog_vlaue = map(rot_speed, 1, 2.67, 150, 255);   //  converting rot speed in analog value for analogWrite fxn
        
        analogWrite(p1, analog_vlaue);
        analogWrite(p2, 0);
        analogWrite(p3, 0);
        analogWrite(p4, analog_vlaue);

        
        
      }

    // for moving backward
    if(angle < -4){
      
         
        float rot_angle = angle*(3.14/180);   // tilt angle in radian
        float rot_speed = (4.7)*cos(rot_angle)*sqrt(1-cos(rot_angle)) + 1;  //rotation speed of tyre in rad/s
        int analog_vlaue = map(rot_speed, 1, 2.67, 100, 255);   //  converting rot speed in analog value for analogWrite fxn

        analogWrite(p1, 0);
        analogWrite(p2, analog_vlaue);
        analogWrite(p3, analog_vlaue);
        analogWrite(p4, 0);

        
      }

    else{
      delay(200);
      }
    
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
delay(100);
}
