#include <accSensor.h>

accSensor::accSensor(/* args */)
{
}

accSensor::~accSensor()
{
}
float accSensor::latitude =0;
float accSensor::longtitude = 0;
int accSensor::getPPM_co(){
    co.update();
    float z = co.readSensor();
    //z = z*10;
    return z;
    //return analogRead(A2);
    /*
    //return gasSensor.getPPM();
    int sensorValue = analogRead(A2);
    sensorValue = 1024 - sensorValue;
    int persen = (sensorValue * 0.004887)/4.84*100;
    int PPM = (((sensorValue*0.004887)*100)*2);
    return PPM;*/
}
int accSensor::getBatt(){
    int a = analogRead(A0);
    return a*0.247;
    //return a*1.9;
    //return a;
}
int accSensor::getCompss(){
  int angle16;
  unsigned char high_byte, low_byte, angle8;
  Wire.beginTransmission(CMPS12_ADDRESS);  //starts communication with CMPS12
  Wire.write(ANGLE_8);                     //Sends the register we wish to start reading from
  Wire.endTransmission();
 
  // Request 5 bytes from the CMPS12
  // this will give us the 8 bit bearing, 
  // both bytes of the 16 bit bearing, pitch and roll
  Wire.requestFrom(CMPS12_ADDRESS, 5);       
  
  while(Wire.available() < 5);        // Wait for all bytes to come back
  
  angle8 = Wire.read();               // Read back the 5 bytes
  high_byte = Wire.read();
  low_byte = Wire.read();
  
  angle16 = high_byte;                 // Calculate 16 bit angle
  angle16 <<= 8;
  angle16 += low_byte;
    
  return (int)angle16;
}
void accSensor::initCompss(){
    //Program Untuk Inisialisasi Kompas
}
int accSensor::getPPM_co2(){
    
    co2.update();
    float z = co2.readSensor();
    z = z*10;
    return z;
    /*
    int sensorValue = analogRead(A2);
    sensorValue = 1024 - sensorValue;
    int persen = (sensorValue * 0.004887)/4.84*100;
    int PPM = (((sensorValue*0.004887)*100)*2);
    return PPM;*/
}
int accSensor::getPPM_nh4(){
    
    nh4.update();
    float z = nh4.readSensor();
    z = z*10;
    return z;
    /*
    int sensorValue = analogRead(A2);
    sensorValue = 1024 - sensorValue;
    int persen = (sensorValue * 0.004887)/4.84*100;
    int PPM = (((sensorValue*0.004887)*100)*2);
    return PPM;*/
}
int accSensor::getPPM_h2s(){
    h2s.update();
    float z = h2s.readSensor();
    //z = z*100;
    return z;
    //return analogRead(A2);
}
void accSensor::initco(){
    
    co.setRegressionMethod(1); //_PPM =  a*ratio^b
  co.setA(605.18); co.setB(-3.937); // Configurate the ecuation values to get NH4 concentration
  co.init();
  //callibration mq135
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    co.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += co.calibrate(RatioMQ136CleanAir2);
    //Serial.print(".");
  }
  co.setR0(calcR0/10);
  //if(isinf(calcR0)) {Serial.println("Open Loop MQ135"); while(1);}
  //if(calcR0 == 0){Serial.println("Close Loop MQ135"); while(1);}
  co.serialDebug(true);
}
void accSensor::initco2(){
    co2.setRegressionMethod(1); //_PPM =  a*ratio^b
  co2.setA(110.47); co2.setB(-2.862); // Configurate the ecuation values to get NH4 concentration
  co2.init();
  //callibration mq135
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    co2.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += co2.calibrate(RatioMQ136CleanAir2);
    //Serial.print(".");
  }
  co2.setR0(calcR0/10);
  //if(isinf(calcR0)) {Serial.println("Open Loop MQ135"); while(1);}
  //if(calcR0 == 0){Serial.println("Close Loop MQ135"); while(1);}
  co2.serialDebug(true);
}
void accSensor::initnh4(){
    nh4.setRegressionMethod(1); //_PPM =  a*ratio^b
  nh4.setA(102.2); nh4.setB(-2.473); // Configurate the ecuation values to get NH4 concentration
  nh4.init();
  //callibration mq135
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    nh4.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += nh4.calibrate(RatioMQ136CleanAir2);
    //Serial.print(".");
  }
  nh4.setR0(calcR0/10);
  //if(isinf(calcR0)) {Serial.println("Open Loop MQ135"); while(1);}
  //if(calcR0 == 0){Serial.println("Close Loop MQ135"); while(1);}
  nh4.serialDebug(true);
}
void accSensor::inith2s(){
    h2s.setRegressionMethod(1); //_PPM =  a*ratio^b
  h2s.setA(102.2); h2s.setB(-2.473); // Configurate the ecuation values to get NH4 concentration
  h2s.init();
  //callibration mq136
  float calcR1 = 0;
  for(int i = 1; i<=10; i ++)
  {
    h2s.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR1 += h2s.calibrate(RatioMQ136CleanAir1);
    //Serial.print(".");
  }
  h2s.setR0(calcR1/10);
  //if(isinf(calcR1)) {Serial.println("Open Loop MQ136"); while(1);}
  //if(calcR1 == 0){Serial.println("Close Loop MQ136"); while(1);}
  h2s.serialDebug(true);
}

int accSensor::getRoll(){
    //return 0;
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    int z = euler.x();
    /*
    z = z*10;
    if(z<0){
        z = z*(-1);
        z++;
    }*/
    return z;
}
int accSensor::getPitch(){
    //return 0;
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    int z = euler.y();
    /*
    z = z*10;
    if(z<0){
        z = z*(-1);
        z++;
    }*/
    return z;
}
int accSensor::getYaw(){
    //return 0;
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    int z = euler.z();
    /*
    z = z*10;
    if(z<0){
        z = z*(-1);
        z++;
    }*/
    return z;
}
void accSensor::initBNO055(){
    status = bno.begin();
    //delay(1000);
    bno.setExtCrystalUse(true);
}
int accSensor::getHumadityBME280(){
    return (int)bme.readHumidity();
}
int accSensor::getTempBME280(){
    float z = bme.readTemperature();
    z = z*10;
    return (int)z;
}
int accSensor::getAltitudeBME280(){
    return (int)bme.readAltitude(SEALEVELPRESSURE_HPA) + 5;
}
void accSensor::init(){
    initBME280();
    initBNO055();
    initco();
    initco2();
    initnh4();
    inith2s();
    initCompss();
    initGPS();
}
void accSensor::initGPS(){
// 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

}
void accSensor::loopGPS(){
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if ((c) && (GPSECHO))
    //Serial.write(c);

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
  if (GPS.fix) {
       accSensor::latitude = GPS.latitudeDegrees;
       accSensor::longtitude = GPS.longitudeDegrees;
       //Serial.print(latitude);
       //Serial.print(longtitude);
       //Serial.print(GPS.latitudeDegrees);
  }
}
void accSensor::initBME280(){
    status = bme.begin(0x76);
}