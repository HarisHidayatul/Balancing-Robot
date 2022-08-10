#include <setMotor.h>
setMotor::setMotor(){}
setMotor::~setMotor(){}
void setMotor::initMotor1(unsigned char step, unsigned char direction,unsigned char ms1,unsigned char ms2){
    freqBegin1(step);
    direction1 = direction;
    ms11 = ms1;
    ms21 = ms2;
    pinMode(direction1,OUTPUT);
    pinMode(ms11,OUTPUT);
    pinMode(ms21,OUTPUT);
    digitalWrite(ms11,HIGH);
    digitalWrite(ms21,HIGH);
}
void setMotor::initMotor2(unsigned char step, unsigned char direction, unsigned char ms1,unsigned char ms2){
    freqBegin2(step);
    direction2 = direction;
    ms12 = ms1;
    ms22 = ms2;
    pinMode(direction2,OUTPUT);
    pinMode(ms12,OUTPUT);
    pinMode(ms22,OUTPUT);
    digitalWrite(ms12,HIGH);
    digitalWrite(ms22,HIGH);
}
void setMotor::setDirection1(bool direction){
    //if direction true, go to forward
    if(direction){
        digitalWrite(direction1,HIGH);
    }else{
        digitalWrite(direction1,LOW);
    }
}
void setMotor::setDirection2(bool direction){
    if(direction){
        digitalWrite(direction2,HIGH);
    }else{
        digitalWrite(direction2,LOW);
    }
}
void setMotor::loopSpeed(signed int motor1,signed int motor2){
    int speed1=0;
    int speed2=0;
    if(motor1==0){
        //setActiveFreq1(false);
    }else if (motor1>0)
    {
        //setActiveFreq1(true);
        setDirection1(true);
    }else{
        //setActiveFreq1(true);
        setDirection1(false);
        motor1=0-motor1;
    }
    if(motor2==0){
        //setActiveFreq2(false);
    }else if (motor2>0)
    {
        //setActiveFreq2(true);
        setDirection2(false);
    }else{
        //setActiveFreq2(true);
        setDirection2(true);
        motor2=0-motor2;
    }
    //speedLoop(motor1,motor2);
    speed1 = 150-motor1;
    speed2 = 150-motor2;
    if(speed1 < 3)speed1=3;
    if(speed2 < 3)speed2=3;
    setDelay1(speed1);
    setDelay2(speed2);
}