#include "Wire.h"
#include "Math.h"
#include "I2Cdev.h"	
#include "MPU6050_6Axis_MotionApps20.h"
MPU6050 mpu;
	
// Variables to store the values from the sensor readings on mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz)
int16_t ax, ay, az;
int16_t gx, gy, gz;
// This global variable tells us how to scale gyroscope & acclerometer data
float    GYRO_FACTOR; 
float    ACCEL_FACTOR;

void setup()
{
Serial.begin(115200); delay(500);
 while (Serial.available() && Serial.read()); delay(500); 
 Wire.begin();    while (!Serial);

 mpu.initialize();
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
       
// Set the full scale range of the gyro
        uint8_t FS_SEL = 0;
//mpu.setFullScaleGyroRange(FS_SEL);

// get default full scale value of gyro - may have changed from default; function call returns values between 0 and 3
        uint8_t READ_FS_SEL = mpu.getFullScaleGyroRange();
        Serial.print("FS_SEL = ");
        Serial.println(READ_FS_SEL);
        GYRO_FACTOR = 200.0/(FS_SEL + 1);

// get default full scale value of accelerometer - may not be default value.  
// Accelerometer scale factor doesn't reall matter as it divides out
//Set the full scale range of the accelerometer
        uint8_t AFS_SEL = 0;
        mpu.setFullScaleAccelRange(AFS_SEL);
        
        uint8_t READ_AFS_SEL = mpu.getFullScaleAccelRange();
        Serial.print("AFS_SEL = ");
        Serial.println(READ_AFS_SEL);
}

void loop() 
{const float RADIANS_TO_DEGREES = 57.2958; 
        
mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);	

//We are interested on acceleration value ax, ay, az from function mpu.getMotion6() right above
double aXvector = ax ;
double aYvector = ay ;
double aZvector = az ;

double R = sqrt(aXvector * aXvector + aYvector * aYvector + aZvector * aZvector);

float aXCOSangle=acos(aXvector/R) * RADIANS_TO_DEGREES;
float aYCOSangle=acos(aYvector/R) * RADIANS_TO_DEGREES;
float aZCOSangle=acos(aZvector/R) * RADIANS_TO_DEGREES;	

Serial.print(aXvector); Serial.print("\t");  Serial.print(aXCOSangle); Serial.print("\t");
Serial.print(aYvector); Serial.print("\t");  Serial.print(aYCOSangle); Serial.print("\t");
Serial.print(aZvector); Serial.print("\t");  Serial.print(aZCOSangle); Serial.print("\t");
Serial.print(R); Serial.println();  
}

/*
if accelerometer is in level, flat, upright position, we should get an angle reading of aXCOSangle =90.0, and aXCOSangle =90.0 aZCOSangle=0
*/
