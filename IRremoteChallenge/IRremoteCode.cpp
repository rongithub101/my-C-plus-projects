#include <IRremote.h>
#include <Servo.h>
#define ON_OFF_KEY 0xFF629D
#define TOGGLE_COLOR_KEY 0xFF22DD
#define BRIGHTNESS_UP_KEY 0xFF02FD
#define BRIGHTNESS_DOWN_KEY 0xFFC23D
#define CIRCLE_KEY 0xFF9867
#define CUSTOM_FUNCTION_KEY 0xFF30CF

const int RECV_PIN = 11;
const int redPin = 5;
const int greenPin = 4;
const int bluePin = 3;
int red = 0;  // Initial intensity
int green = 0;
int blue = 0;
int currentBrightness = 0;  // Initial active color intensity
String targetColor = "RED"; // Initial active color
bool isOn = false;
IRrecv irrecv(RECV_PIN);  // Initialize IR Library
decode_results results;   // Initialize IR Library
Servo myservo;
int pos = 0;
void setup() {
  Serial.begin(9600);   // Start Serial
  irrecv.enableIRIn();  // Start the receiver
  // Set the three LED Pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  myservo.attach(9);
}
void loop() {
  if (irrecv.decode(&results)) {
    // Serial.println(results.value, HEX);  // Prints HEX code IR receiver receives
    irrecv.resume(); // Receive the next value
    // Power switch
    if (results.value == ON_OFF_KEY) {
      if (isOn == true) {
        Serial.println("Turning Off"); powerOff();
      }
      else if (isOn == false) {
        Serial.println("Turning On"); powerOn(); showCurrentActiveColor();
      }
    }
    // Color operations
    if (isOn == true) {
      if (results.value == TOGGLE_COLOR_KEY)      // Toggle active colors
        toggleActiveColor();
      else if (results.value == BRIGHTNESS_UP_KEY) // Brightness up
        brightnessUp();
      else if (results.value == BRIGHTNESS_DOWN_KEY) // Brightness down
        brightnessDown();
      else if (results.value == CIRCLE_KEY) // Circle
        circle();
      else if (results.value == CUSTOM_FUNCTION_KEY) { // Be creative with your own code
        // FILL IN YOUR OWN CODE
        targetColor = "BLUE";
        brightnessUp();
        delay(200);
        brightnessUp();
        delay(200);
        rotate();
        delay(200);
        targetColor = "GREEN";
        delay(200);
        brightnessDown();
        delay(200);
        brightnessUp();
        delay(200);
        rotate();
        delay(200);
        targetColor = "RED";
        brightnessUp();
        delay(200);
        rotate();
      }
    }
  }
  delay(100);
}
// Print current color setting on serial monitor
void showCurrentActiveColor() {
  Serial.print("Now controlling color ");
  Serial.println(targetColor);
}
// Turn Off LED
void powerOff() {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  isOn = false;
}
// Turn on LED
void powerOn() {
  updateColor();
  isOn = true;
}
// Turn up brightness for active color
void brightnessUp() {
  currentBrightness = (currentBrightness + 25) % 256;
  updateColor();
}
// Turn down brightness for active color
void brightnessDown() {
  currentBrightness = max(0, (currentBrightness - 25) % 256);
  updateColor();
}
// Toggle active color that you are changing brightness on
void toggleActiveColor() {
  if (targetColor == "RED")
    targetColor = "GREEN";
  else if (targetColor == "GREEN")
    targetColor = "BLUE";
  else if (targetColor == "BLUE")
    targetColor = "RED";
  showCurrentActiveColor();
}
// Update LED color to current setting
void updateColor() {
  if (targetColor == "RED")
    red = currentBrightness;
  else if (targetColor == "GREEN")
    green = currentBrightness;
  else if (targetColor == "BLUE")
    blue = currentBrightness;
  setColor(red, green, blue);
  showColorOnSerialMonitor();
}
// Display current color in Serial Monitor
void showColorOnSerialMonitor() {
  Serial.print("Red ");
  Serial.print(red / 255.0);
  Serial.print("\tGreen ");
  Serial.print(green / 255.0);
  Serial.print("\tBlue ");
  Serial.println(blue / 255.0);
}
// Output desired voltages to LED
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
// Circle through different colors

void rotate(){
  pos = pos + 90;
  myservo.write(pos);
  delay(200);
}
void circle() {
  red = 255;
  green = 127;
  blue = 0;
  Serial.println("Start Circle");
  while (true) {
    red = (red + 25 + 256) % 256;
    green = (green + 25 + 256) % 256;
    blue = (blue + 25 + 256) % 256;
    setColor(red, green, blue);
    showColorOnSerialMonitor();
    delay(150);
    if (irrecv.decode(&results)) {
      Serial.println("Stop Circle");
      irrecv.resume();
      return;
    }
  }
}