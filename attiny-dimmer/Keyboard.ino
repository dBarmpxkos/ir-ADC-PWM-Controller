byte counterOld = 0;
byte counterNew = 0;
int PWM_PIN = 0;

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

void setup() {
	pinMode(0, OUTPUT);
	digitalWrite(0, HIGH);
}

void loop() {
	int potIn = analogRead(1);
	if (potIn > 600)
		counterNew += 15;
	if (potIn < 300)
		counterNew -=15;
	linear_dim();
	delay(250);
}
