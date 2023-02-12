# include <SD.h> // Loading SD library
#include <SPI.h> // Loading SPI Communication Library

int chipSelect = 4; //  Variable for Chip Select Pin
int SDOutputPin = 10; // Variable for SD output
File Data; // Variable for working with File object

#include <SPI.h> // Importing SPI Library
#include <Wire.h> // Importing Wire Library
#include <Adafruit_GFX.h> // Importing GFX Library
#include <Adafruit_SSD1306.h> // Importing SSD1306 Library

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Initializing Display

int potPin = A2; // Variable for Potentiometer Pin
float potVal = 11; // Variable for Potentiometer Value
float oldPotVal = 0; // Variable for last Potentiometer Value

int buttonPin = A3; // Variable for button
boolean buttonState = 0; // Variable for button state

String txt = ".txt"; // String for txt
String Letter = "A.txt"; // Declaring Which Letter is Recorded
String letterList[5] = {"A.txt", "E.txt", "I.txt", "O.txt", "U.txt"}; // List of letters
int index; // Variable for button index

float rawEMG = 0; // Variable for raw EMG output of Muscle Sensor
float modEMG = 0; // Variable for Modified EMG output of Muscle Sensor

int rawEMGPin = A0; // Variable for Analog pin connected to EMG sensor
int modEMGPin = A1; // Variable for Analog pin connected to EMG sensor

int recordingPin = 22; // Digital pin connected to LED to indicate EMG recording
int stablePin = 26; // Digital pin connected to LED to indicate EMG is NOT recording

void setup() {
  SD.begin(chipSelect); // Initialize SD card with Chip Select Pin
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Starting Display
  Serial.begin(115200); // Setting Baud Rate for Serial monitor

  display.clearDisplay(); // Clearing Display
  display.setTextSize(1); // Setting Text Size
  display.setTextColor(WHITE); // Setting Text Color
  display.setCursor(0, 10); // Setting Cursor position
  display.println("EMG Grapher..."); // Printing on Display
  display.display(); // Updating Display

  pinMode(SDOutputPin, OUTPUT); // Setting pin as OUTPUT

  pinMode(potPin, INPUT); // Setting pin as INPUT
  potVal = analogRead(potPin); // Measuring Potentiometer Value
  oldPotVal = potVal; // Setting Old Potentiometer Value

  pinMode(rawEMGPin, INPUT); // Setting pin as INPUT
  pinMode(modEMGPin, INPUT); // Setting pin as INPUT

  pinMode(recordingPin, OUTPUT); // Setting pin as OUTPUT
  pinMode(stablePin, OUTPUT); // Setting pin as OUTPUT

  digitalWrite(recordingPin, HIGH); //Turning On LED
  digitalWrite(stablePin, HIGH); //Turning On LED
  delay(1000); // Wait for 1 second
  digitalWrite(recordingPin, LOW); //Turning Off LED
  digitalWrite(stablePin, LOW); //Turning Off LED
  delay(1000); // Wait for 1 second

  display.clearDisplay(); // Clearing Display
  displayEMG();
}

void loop() {
  Button(); // Void Loop for Measuring Button State
  Potentiometer(); // Void Loop for Measuring Potentiometer
  if (buttonState == 1) { // If button is pressed
    while (buttonState == 1) {
      digitalWrite(stablePin, LOW); // Turning of stable LED
      digitalWrite(recordingPin, HIGH); // Turning on recording LED
      Data = SD.open(Letter, FILE_WRITE); //Open SD card for Writing
      while (!Data) { // Loop Breakout to ensure SD card is open
        digitalWrite(stablePin, HIGH); // Turning of stable LED
        digitalWrite(recordingPin, LOW); // Turning on recording LED
        SD.begin(chipSelect); // Initialize SD card with Chip Select Pin
        Data = SD.open(Letter, FILE_WRITE); //Open SD card for Writing
        Serial.println("Error Opening File");
      }
      recordEMG(); // Void Loop for Recording EMG Signal
    }
  }
  else {
    digitalWrite(stablePin, HIGH); // Turning of stable LED
    digitalWrite(recordingPin, LOW); // Turning on recording LED
  }
}

void recordEMG() {
  rawEMG = analogRead(rawEMGPin); // Reading Raw EMG data
  modEMG = analogRead(modEMGPin); // Reading Modified EMG data

  Serial.print(rawEMG); // print Raw EMG values
  Serial.print(","); // Print comma to seperate values
  Serial.println(modEMG); // print Modified EMG values

  Data.print(rawEMG); // print Raw EMG values
  Data.print(","); // Print comma to seperate values
  Data.println(modEMG); // print Modified EMG values

  Data.close(); // Closing Data file

  displayEMG();// Void Loop for displaying EMG values
}

void displayEMG() {
  if (random(0, 250) == 50) { // Once every 1000 times
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Starting Display
  }
  display.clearDisplay(); // Clearing Display
  display.setTextSize(1); // Setting Text Size
  display.setTextColor(WHITE); // Setting Text Color
  display.setCursor(0, 10); // Setting Cursor position
  display.print("Raw EMG Value: "); // Printing on Display

  display.println(rawEMG); // Printing on Display
  display.println(""); // Printing on Display
  display.print("Mod EMG Value: "); // Printing on Display
  display.println(modEMG); // Printing on Display

  display.println(""); // Printing on Display
  display.print("Letter: "); // Printing on Display
  display.println(Letter); // Printing on Display
  display.print("Pot: "); // Printing on Display
  display.print(potVal); // Printing on Display
  display.print("   B: "); // Printing on Display
  display.print(buttonState); // Printing on Display
  display.display(); // Updating Display
}

void Potentiometer() {
  potVal = analogRead(potPin); // Reads the "current" state of the Potentiometer
  if (abs(oldPotVal - potVal) >= 10) { // If Potentiometer Value has changed
    oldPotVal = potVal; // Updating Old Potentiometer Value
    index = map(potVal, 0, 1024, 0, 5); // Mapping Values to index value
    Letter = letterList[index]; // Updateing Letter Variable

    displayEMG();
  }
}
void Button() {
  if (buttonState != !(digitalRead(buttonPin))) { // Button has been pressed
    buttonState = !buttonState; // Inverts signal
    displayEMG(); //Update Display
  }
}
