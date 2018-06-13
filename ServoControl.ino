#include <Servo.h>               
Servo SS;        //initialize a servo object for the connected servo  
                
int angle = 0;    
 
void setup() 
{ 
  SS.attach(9);      // attach the signal pin of servo to pin9 of arduino
} 
  
void loop() 
{ 
  for(angle = 0; angle < 180; angle += 1)  
  {                                  
    SS.write(angle);                 //command to rotate the servo to the specified angle
    delay(15);                       
  } 
 
  delay(1000);
  
  for(angle = 180; angle>=1; angle-=5)      
  {                                
    SS.write(angle);              //command to rotate the servo to the specified angle
    delay(5);                       
  } 

    delay(1000);
}
