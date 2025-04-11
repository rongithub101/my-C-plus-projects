const int sensorPin =0 ;
int ledPin = 13;
int lightLevel;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);
  delay(2000);
  lightLevel = analogRead(sensorPin);
  Serial.print("The Photoresistor is reading: ");
  Serial.println(lightLevel);
  digitalWrite(ledPin, LOW);
  delay(2000);
  lightLevel = analogRead(sensorPin);
  Serial.print("The Photoresistor is reading: ");
  Serial.println(lightLevel);
}
