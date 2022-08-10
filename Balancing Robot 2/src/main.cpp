#include <Arduino.h>
#include <mpuDmp.h>
#include <setMotor.h>
#include <PID_v1.h>
/*Direction 13
Step 12
Ms1 11
Ms2 10

Motor kiri
Direction 9
Step 8
Ms1 7
Ms2 6*/
mpuDmp mpu = mpuDmp();
setMotor motor = setMotor();


/*********Tune these Values*********/
double setpoint; //set the value when the bot is perpendicular to ground using serial monitor. 
//Read the project documentation on circuitdigest.com to learn how to set these values
double Input,Output;
double Kp = 1; //Set this first
double Kd = 1 ; //Set this secound
double Ki = 1; //Finally set this 
/******End*********/
PID myPID(&Input, &Output, &setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  // put your setup code here, to run once:
  mpu.beginInit();//kalibrasi awal mpu
  //Serial.begin(57600);
  motor.initMotor1(12,13,11,10);//kalibrasi awal motor 1
  motor.initMotor2(8,9,7,6);//kalibrasi awal motor 2

  setpoint =30;
  //setup PID
  myPID.SetMode(AUTOMATIC);
  //myPID.SetOutputLimits(-147,147); 
}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.loopMpu();
  myPID.Compute();
  Serial.println(Output);
  Serial.print(mpu.getRoll());
  Serial.print("//");
  Serial.print(mpu.getPitch());
  Serial.print("//");
  Serial.print(mpu.getYaw());
  Serial.print("//");
  Input = mpu.getRoll();

  //motor.loopSpeed(outputt*(-1),outputt*(-1));
  //motor.loopSpeed(145,145);
}