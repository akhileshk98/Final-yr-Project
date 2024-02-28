int mq135 = A0;
int data = 0;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
 data = analogRead(mq135);
    if(data>600)
    {
      Serial.print("Bad Quality Air"); 
    }
}
