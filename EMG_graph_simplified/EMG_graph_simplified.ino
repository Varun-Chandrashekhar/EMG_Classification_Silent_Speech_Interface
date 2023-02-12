int y=1;
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
  // put your setup code here, to run once:
Serial.begin(115200); // Setting Baud Rate for Serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(stablePin, LOW); // Turning of stable LED
      digitalWrite(recordingPin, HIGH); // Turning on recording LED
      recordEMG(); // Void Loop for Recording EMG Signal
}

void recordEMG() {
  rawEMG = analogRead(rawEMGPin); // Reading Raw EMG data
  modEMG = analogRead(modEMGPin); // Reading Modified EMG data
  
  if(y<10){
     y++;
     Serial.print("rawEMG"); // print Raw EMG values
     Serial.print(","); // Print comma to seperate values
     Serial.print("modEMG"); // print Modified EMG values
     Serial.print(","); // Print comma to seperate values
     Serial.print("base"); // print Modified EMG values
     Serial.print(","); // Print comma to seperate values
     Serial.println("base"); // print Modified EMG values
     delay(1000);
    
    }
 
  
  Serial.print(rawEMG); // print Raw EMG values
  Serial.print(","); // Print comma to seperate values
  Serial.print(modEMG); // print Modified EMG values
  Serial.print(","); // Print comma to seperate values
  Serial.print(0); // print Modified EMG values
  Serial.print(","); // Print comma to seperate values
  Serial.println(500); // print Modified EMG values
  delay(10);
  //Data.print(rawEMG); // print Raw EMG 
}
