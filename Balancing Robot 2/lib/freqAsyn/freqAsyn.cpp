#include <freqAsyn.h>
bool freqAsyn::toggle1=0;
bool freqAsyn::toggle2=0;
bool freqAsyn::activeFreq1=0;
bool freqAsyn::activeFreq2=0;
unsigned char freqAsyn::pinFreq1=255;
unsigned char freqAsyn::pinFreq2=255;
unsigned int freqAsyn::delay1 =0;
unsigned int freqAsyn::delay2=0;
freqAsyn::freqAsyn(){
};
bool freqAsyn::getToogle1(){
    return toggle1;
}
void freqAsyn::setDelay1(unsigned int delay){
    this->delay1 = delay;
    activeFreq1 = true;
}
void freqAsyn::setDelay2(unsigned int delay){
    this->delay2 = delay;
    activeFreq2 = true;
}
unsigned int freqAsyn::getDelay1(){
    return delay1;
}
unsigned int freqAsyn::getDelay2(){
    return delay2;
}
void freqAsyn::setToogle1(bool state){
    toggle1 = state;
}
void freqAsyn::setToogle2(bool state){
    toggle2 = state;
}
bool freqAsyn::getToogle2(){
    return toggle2;
}
bool freqAsyn::getActiceFreq1(){
    return activeFreq1;
}
bool freqAsyn::getActiveFreq2(){
    return activeFreq2;
}
void freqAsyn::setPinFreq1(bool state){
    digitalWrite(pinFreq1,state);
}
void freqAsyn::setPinFreq2(bool state){
    digitalWrite(pinFreq2,state);
}
//~freqAsyn();
void freqAsyn::freqBegin2(unsigned char pinFreq2){
    this->pinFreq2 = pinFreq2;
    pinMode(pinFreq2,OUTPUT);
}
void freqAsyn::freqBegin1(unsigned char pinFreq1){
    this->pinFreq1 = pinFreq1;
    
    pinMode(pinFreq1,OUTPUT);

    //activeFreq1 = true;
    //activeFreq2 = true;
    cli();//stop interrupts
    //set timer0 interrupt at 10kHz
    TCCR0A = 0;// set entire TCCR2A register to 0
    TCCR0B = 0;// same for TCCR2B
    TCNT0  = 0;//initialize counter value to 0
    // set compare match register for 10khz increments
    OCR0A = 24;// = (16*10^6) / (10000*64) - 1 (must be <256)
    // turn on CTC mode
    TCCR0A |= (1 << WGM01);
    // Set CS01 and CS00 bits for 64 prescaler
    TCCR0B |= (1 << CS01) | (1 << CS00);   
    // enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);
    sei();//allow interrupts
}
ISR(TIMER0_COMPA_vect){//timer0 interrupt 5kHz
//generates pulse wave of frequency 10kHz/2 = 5kHz (takes two cycles for full wave- toggle high then toggle low)
    freqAsyn a = freqAsyn();
    static unsigned int b=0;
    if(a.getActiceFreq1()==true){
        if(b % a.getDelay1()==0){
            a.setPinFreq1(a.getToogle1());
            a.setToogle1(!a.getToogle1());
        }
    }
    if(a.getActiveFreq2()==true){
        if(b % a.getDelay2()==0){
            a.setPinFreq2(a.getToogle2());
            a.setToogle2(!a.getToogle2());
        }
    }
    b++;
}