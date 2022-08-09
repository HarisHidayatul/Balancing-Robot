#include <MQUnifiedsensor.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_GPS.h>

//Data Untuk GPS
#define mySerial Serial2
// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  true

#define CMPS12_ADDRESS 0x60  // Address of CMPS12 shifted right one bit for arduino wire library
#define ANGLE_8  1           // Register to read 8bit angle from

#include <MQ135.h> //https://circuitdigest.com/microcontroller-projects/interfacing-mq135-gas-sensor-with-arduino-to-measure-co2-levels-in-ppm

// data untuk bme sensor
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)


#define pin1 A2

#define placa "Arduino MEGA"
#define pin2 A2 //Analog input 4 of your arduino
#define type2 "MQ-136" //MQ4
#define RatioMQ136CleanAir1 1.75//RS / R0 = 3.6 ppm  //1.5 untuk h2s
#define RatioMQ136CleanAir2 2.0//2.75 untuk CO
#define Voltage_Resolution 5
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO

class accSensor
{
private:
    /* data */
    MQUnifiedsensor co = MQUnifiedsensor(placa, Voltage_Resolution, ADC_Bit_Resolution, pin2, type2);
    MQUnifiedsensor co2 = MQUnifiedsensor(placa, Voltage_Resolution, ADC_Bit_Resolution, pin2, type2);
    MQUnifiedsensor nh4 = MQUnifiedsensor(placa, Voltage_Resolution, ADC_Bit_Resolution, pin2, type2);
    MQUnifiedsensor h2s = MQUnifiedsensor(placa,Voltage_Resolution,ADC_Bit_Resolution, pin2,type2);//mq136

    
    Adafruit_GPS GPS = Adafruit_GPS(&mySerial);
    //MQ135 gasSensor = MQ135(pin1);

    Adafruit_BME280 bme; // I2C
    Adafruit_BNO055 bno = Adafruit_BNO055(55);
    
    bool status;

public:
    accSensor(/* args */);
    ~accSensor();
    static float latitude;
    static float longtitude;
    int getTempBME280();
    int getAltitudeBME280();
    int getHumadityBME280();
    int getRoll();
    int getPitch();
    int getYaw();
    int getPPM_co();
    int getPPM_co2();
    int getPPM_nh4();
    int getPPM_h2s();
    int getBatt();
    int getCompss();
    void init();
    void initBME280();
    void initBNO055();
    void initco();
    void initco2();
    void initnh4();
    void initCompss();
    void inith2s();
    void initGPS();
    void loopGPS();
};
