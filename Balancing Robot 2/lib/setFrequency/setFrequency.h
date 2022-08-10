#include <Arduino.h>

class setFrequency
{
private:
    /* data */
    static bool toggle1,toggle2;
    bool activeFreq1,activeFreq2;
    unsigned char pinFreq1,pinFreq2;
    unsigned int totalRising1,totalRising2;
public:
    setFrequency();
    //~setFrequency();
    void freqBegin1(unsigned char pinFreq);
    void freqBegin2(unsigned char pinFreq);
    void speedLoop(unsigned int delayFreq1,unsigned int delayFreq2);
    unsigned int gettotalRising1();
    void resetRising1();
    unsigned int gettotalRising2();
    void resetRising2();
    void setActiveFreq1(bool freq);
    void setActiveFreq2(bool freq);
};
