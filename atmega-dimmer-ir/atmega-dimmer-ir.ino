#include <IRremote.h>
#include "num_definitions.h"

#define PWM_PIN 5
#define RECV_PIN 6

byte counterOld = 0;
byte counterNew = 0;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(PWM_PIN, OUTPUT);
  for (int i=0; i<=254; i++)
  {
    analogWrite(PWM_PIN, i); 
    delay(5);
  }
  counterOld = 254;
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    long int irvalue = results.value;
    match_code_with_buttons();
    irrecv.resume(); // Receive the next value
  }
  delay(50);
}

void receive_cmd(int times, int delayHIGH, int delayLOW)
{
  for (int i=0; i<times; i++)
  {
    for (int j=0; j<=254; j++){
      analogWrite(PWM_PIN, j);
      delay(1);
    }
    delay(delayHIGH);
    for (int j=254; j>=0; j--){
    analogWrite(PWM_PIN, j);
    delay(1);
    } digitalWrite(PWM_PIN, LOW);
    delay(delayLOW);
  }

}

void linear_decrease()
{
    for (int i=counterOld; i>=counterNew; i--)
    {
      analogWrite(PWM_PIN, i); 
      delay(5);
    }
    counterOld = counterNew;

}

void linear_increase()
{
    for (int i=counterOld; i<=counterNew; i++)
    {
      analogWrite(PWM_PIN, i); 
      delay(5);
    }
    counterOld = counterNew;
}

void linear_dim()
{
  if (counterNew > counterOld) linear_increase();
  if (counterNew < counterOld) linear_decrease();
}

void match_code_with_buttons()
{

  switch(results.value)
  {

    case VolDOWN:{
      counterNew -= 22;
      if (counterNew < 21) counterNew = 0;
      linear_dim();
      break;
    } 

    case VolUP:{
      counterNew += 22;
      if (counterNew > 242) counterNew = 255;
      linear_dim();
      break;
    } 

    case Play:{
      for (int i=0; i<10000; i+=10) {
        receive_cmd(2, i*10, i*10);
      }
      break;
    }
    
    case Back:{
      counterNew = 0;
      linear_dim();
      break;
    }

    case NUM1:{
      counterNew = 25;
      linear_dim();
      break;
    }
    case NUM2:{
      counterNew = 50;
      linear_dim();
      break;
    }
    case NUM3:{
      counterNew = 75;
      linear_dim();
      break;
    }
    case NUM4:{
      counterNew = 100;
      linear_dim();
      break;
    }
    case NUM5:{
      counterNew = 125;
      linear_dim();
      break;
    }
    case NUM6:{
      counterNew = 150;
      linear_dim();
      break;
    }
    case NUM7:{
      counterNew = 175;
      linear_dim();
      break;
    }
    case NUM8:{
      counterNew = 200;
      linear_dim();
      break;
    }
    case NUM9:{
      counterNew = 255;
      linear_dim();
      break;
    }

    default: 
      Serial.println("BLEAH");

  }

}
