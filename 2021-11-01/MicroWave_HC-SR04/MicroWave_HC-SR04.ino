#include <Ultrasonic.h>

Ultrasonic ultrasonic(8, 9);
void setup()
{
  Serial.begin(9600);  
}

void loop()
{  
  Serial.print("感測距離:");
  Serial.println(ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM));  
  delay(1000);
}
