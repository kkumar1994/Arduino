#define FIGURE_DELAY  100  
#define TOTAL_POINTS  26

byte X_COORDINATES[TOTAL_POINTS]={
  5,5,5,5,15,5,15,15,25,25,15,30,40,40,30,30,45,45,45,55,55,55,65,75,70,60};

byte Y_COORDINATES[TOTAL_POINTS]={
  40,25,10,25,40,25,10,25,25,18,18,10,10,18,18,25,25,10,25,10,25,10,25,10,15,15};

void setup()
{
  DDRD = B11111111; //initialize port D as write (LSB starts with pin 0)
  DDRB = B00111111; //initialize 6 bits of port B as write (LSB starts with pin 8)

  byte t;
  for(t = 0; t < TOTAL_POINTS; t++)
  {
    Y_COORDINATES[t] = map(Y_COORDINATES[t],0,255,0,63); // I am using only 6-bits hence I've remapped it 
  }
}

void loop()
{
  byte t;
    for(t = 0; t < TOTAL_POINTS; t++)   
    {
      PORTD = X_COORDINATES[t];
      PORTB = Y_COORDINATES[t];
      delayMicroseconds(FIGURE_DELAY);    // small delay function
    }
}


