#include <Arduino.h>

class freqAsyn
{
private:
    /* data */
    static bool toggle1,toggle2;
    static bool activeFreq1,activeFreq2;
    static unsigned char pinFreq1,pinFreq2;
    static unsigned int delay1, delay2;
public:
    freqAsyn();
    bool getToogle1();
    static void setToogle1(bool state);
    static void setToogle2(bool state);
    bool getToogle2();
    bool getActiceFreq1();
    bool getActiveFreq2();
    void setPinFreq1(bool state);
    void setPinFreq2(bool state);
    void setDelay1(unsigned int delay);
    void setDelay2(unsigned int delay);
    unsigned int getDelay1();
    unsigned int getDelay2();
    //~freqAsyn();
    void freqBegin1(unsigned char pinFreq1);
    void freqBegin2(unsigned char pinFreq2);
};
