#include <led.h>
LED::LED(const byte pin){
    pinMode(pin, OUTPUT); 
}
 
LED13::~LED13(){}
void LED::on(){
        digitalWrite(pin,HIGH); 
}
void LED::off(){
        digitalWrite(pin,LOW); 
}

void LED::blink(int time){
        on();                   
        delay(time/2);  
        off();          
        delay(time/2); 
}
