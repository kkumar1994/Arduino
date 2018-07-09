#ifndef LED
#define LED
 
#include <Arduino.h>
 
class LED {
private:
        const byte pin;
public:
        LED(const byte pin);
        ~LED();
        void on();
        void off();
        void blink(int time);

};
 
#endif
