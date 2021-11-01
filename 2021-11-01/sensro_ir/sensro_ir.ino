/*
 * IR sensor
 *
 *
 *
 * 
 */


boolean IR_left;

boolean IR_right;

void setup()
{
  Serial.begin(9600);


  pinMode(7, INPUT);
  pinMode(6, INPUT);
}


void loop()
{
  IR_left = digitalRead(7);
  IR_right = digitalRead(6);
  Serial.println(IR_left);
  Serial.println(IR_right);
  delay(100);
}
