int mq135 = A0;
int data = 0;
void setup()
{
  Serial.begin(115200);
}
void loop()
{
 data = analogRead(mq135);
 Serial.print(data);
    if(data>600)
    {
      Serial.print("Bad Quality Air"); 
    }
}
