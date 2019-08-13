#include <IRremote.h>
#include "num_definitions.h"

#define PWM_PIN 5
#define RECV_PIN 6

byte counterOld, counterNew;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(PWM_PIN, OUTPUT);
  digitalWrite(PWM_PIN, LOW);
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    long int irvalue = results.value;
    match_code_with_buttons();
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

void receive_cmd(int times, int delayHIGH, int delayLOW)
{
  for (int i=0; i<times; i++)
  {
    digitalWrite(PWM_PIN, HIGH);
    delay(delayHIGH);
    digitalWrite(PWM_PIN, LOW);
    delay(delayLOW);
  }

}
void match_code_with_buttons()
{

  switch(results.value)
  {

    case VolDOWN:
    {
      counterNew -= 22;
      if (counterNew < 21)
        counterNew = 0;

      for (int i=counterOld; i>=counterNew; i--){
        analogWrite(PWM_PIN, i); 
        delay(20);
      }
      counterOld = counterNew;
      break;
    } 
    
    case VolUP:
    {
     counterNew += 22;
     if (counterNew > 242)
        counterNew = 255;

      for (int i=counterOld; i<=counterNew; i++){
        analogWrite(PWM_PIN, i); 
        delay(20);
      }
      counterOld = counterNew;
      break;
    } 

    case Play:
    {
      for (int i=0; i<200; i++){
        receive_cmd(2, i*10, i*10);
      }

      break;
    }

    default: 
      Serial.println("BLEAH");
  }

}

/* codes:
Vol-: FD00FF
Vol+: FD40BF
Play: FD807F
Back: FD708F
1: FD08F7
2: FD8877
3: FD48B7
4: FD28D7
5: LFDA857
6: FD6897
7: FD18E7
8: FD9867
9: FD58A7
*/