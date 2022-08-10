#include <Arduino.h>
//#include <setFrequency.h>
#include <freqAsyn.h>
class setMotor : private freqAsyn
{
private:
    unsigned char direction1,ms11,ms21;
    unsigned char direction2,ms12,ms22;
public:
    setMotor();
    ~setMotor();
    void loopSpeed(signed int motor1,signed int motor2);
    void initMotor1(unsigned char step, unsigned char direction,unsigned char ms1,unsigned char ms2);
    void initMotor2(unsigned char step, unsigned char direction,unsigned char ms1,unsigned char ms2);
    void setPosStart(signed int pos1,signed int pos2);
    void setDirection1(bool dirct);
    void setDirection2(bool dirct);
};