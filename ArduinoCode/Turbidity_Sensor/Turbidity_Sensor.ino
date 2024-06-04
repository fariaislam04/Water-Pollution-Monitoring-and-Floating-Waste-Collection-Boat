int sensorPin = A0;

void setup()
{ 
  Serial.begin(9600);
}

void loop() 
{
  int sensorValue = analogRead(sensorPin);
  int turbidity = map(sensorValue, 0, 750, 100, 0);
  delay(100);

  if (turbidity < 20) 
  {
    Serial.print("Clear");
  }
  if ((turbidity > 20) && (turbidity < 50)) 
  {
    Serial.print("Cloudy");
  }
  if (turbidity > 50) 
  {
    Serial.print("Dirty");
  }
}