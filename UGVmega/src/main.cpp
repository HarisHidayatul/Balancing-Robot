#include <Arduino.h>
#include <SoftwareSerial.h>
#include <stringSerial.h>
stringSerial a = stringSerial();
float save1;
float save2;

int incomingByte = 0;
bool statusSerial=false;
int valueSerial = 0;



void transmitSensor(int i){
  if(i==0){
    Serial3.print(a.getdata(humadity));
  }else if(i==1){
    Serial3.print(a.getdata(temperature));
  }else if(i==2){
    Serial3.print(a.getdata(altitude));
  }else if(i==3){
    Serial3.print(a.getdata(roll));
  }else if(i==4){
    Serial3.print(a.getdata(pitch));
  }else if(i==5){
    Serial3.print(a.getdata(yaw));
  }else if(i==6){
    Serial3.print(a.getdata(co));
  }else if(i==7){
    Serial3.print(a.getdata(co2));
  }else if(i==8){
    Serial3.print(a.getdata(nh4));
  }else if(i==9){
    Serial3.print(a.getdata(h2s));
  }else if(i==10){
    Serial3.print(a.getdata(battery));
  }else if(i==11){
    Serial3.print(a.getdata(compass));
  }else if(i==12){
    Serial3.print(a.getdata(save1,lattt));
  }else if(i==13){
    Serial3.println(a.getdata(save2,lnggg));
  }
  a.clearBuff();
}
void setup() {
  a.init();
  Serial3.begin(9600);
}
void loop() {
  a.loopGPS();
  if(save1 != accSensor::latitude){
    save1 = accSensor::latitude;
  }
  if(save2 != accSensor::longtitude){
    save2 = accSensor::longtitude;
  }
  
  if (Serial3.available() > 0) {
    incomingByte = Serial3.read(); // read the incoming byte:
    Serial3.write(incomingByte);
    if(incomingByte == '#'){
      statusSerial = true;
    }else{
      if(statusSerial == true){
        if(incomingByte == '%'){
          transmitSensor(valueSerial);
          statusSerial = false;
          valueSerial = 0;
        }else{
          valueSerial = valueSerial*10 + (incomingByte-48);
        }
      }
    }
  }
}
  /*
  static int i=0;
  transmitSensor(i);
  i++;
  if(i > 13){i=0;}
  a.loopGPS();
  a.clearBuff();*/

