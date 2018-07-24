#define RANGE 255

int sine[RANGE];
int cosi[RANGE];
void setup(){
  Serial.begin(9600);
  DDRD=B11111111;
  DDRB=B00111111;
  for(int i=0;i<RANGE;i++)
  {
    float x=float(i);
    float y=sin((x/RANGE)*2*PI);
    float z=cos((x/RANGE)*2*PI);
    sine[i]=int(y*128)+128;
    cosi[i]=int(z*128)+128;
  }
}

void loop()
{
  for (int i=0;i<RANGE;i++)
  {
    PORTD=sine[i];
    PORTB=cosi[i];
    delayMicroseconds(1);
    //Serial.println(cosi[i]);
  }
}

