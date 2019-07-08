void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
  digitalWrite(14, 0);
  digitalWrite(15, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
while (Serial.available()>0)
{
  int val = Serial.parseInt();
    digitalWrite(12,1);
    digitalWrite(13, 0);
    digitalWrite(14, 1);
    digitalWrite(15, 0);  
delay(val);

    digitalWrite(12,0);
    digitalWrite(13, 0);
    digitalWrite(14, 0);
    digitalWrite(15, 0);  
    delay(1000);
  Serial.println("one rotation start");
    digitalWrite(12,1);
    digitalWrite(13, 0);
    digitalWrite(14, 1);
    digitalWrite(15, 0);  
    delay(36*val);
    digitalWrite(12,0);
    digitalWrite(13, 0);
    digitalWrite(14, 0);
    digitalWrite(15, 0); 
}



}
