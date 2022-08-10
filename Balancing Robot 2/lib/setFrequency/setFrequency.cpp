#include <setFrequency.h>
bool setFrequency::toggle1 = false;
bool setFrequency::toggle2 = false;
setFrequency::setFrequency(){
    toggle1=false;
    toggle2=false;
    activeFreq1=false;
    activeFreq2=false;
};
//~setFrequency();
void setFrequency::freqBegin1(unsigned char pinFreq){
    this->pinFreq1 = pinFreq;
    pinMode(pinFreq1,OUTPUT);
    activeFreq1 = true;
}
void setFrequency::freqBegin2(unsigned char pinFreq){
    this->pinFreq2 = pinFreq;
    pinMode(pinFreq2,OUTPUT);
    activeFreq2 = true;
}
void setFrequency::speedLoop(unsigned int speed1,unsigned int speed2){
    int currentMicros = millis();
    if(activeFreq1){
        static int previousMicros1=0;
        static bool previousState1 =false;
        if(currentMicros - previousMicros1 > (100-speed1)){
            previousMicros1 = currentMicros;
            digitalWrite(pinFreq1,toggle1);
            if(toggle1){
                if(previousState1){
                    totalRising1++;
                    previousState1=false;
                }
            }else{
                previousState1 = true;
            }
            toggle1 = !toggle1;
        }
    }
    if(activeFreq2){
        static int previousMicros2=0;
        static bool previousState2 =false;
        if(currentMicros - previousMicros2 > (100-speed2)){
            previousMicros2 = currentMicros;
            digitalWrite(pinFreq2,toggle2);
            if(toggle2){
                if(previousState2){
                    totalRising2++;
                    previousState2=false;
                }
            }else{
                previousState2 = true;
            }
            toggle2 = !toggle2;
        }
    }
}
unsigned int setFrequency::gettotalRising1(){
    return totalRising1;
}
void setFrequency::resetRising1(){
    totalRising1=0;
}

void setFrequency::setActiveFreq1(bool freq){
    activeFreq1 = freq;
}
void setFrequency::setActiveFreq2(bool freq){
    activeFreq2 = freq;
}
unsigned int setFrequency::gettotalRising2(){
    return totalRising2;
}
void setFrequency::resetRising2(){
    totalRising2=0;
}