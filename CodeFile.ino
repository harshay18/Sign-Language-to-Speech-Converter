#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

// Define the pins for DFPlayer Mini
SoftwareSerial mySerial(10, 11); // RX, TX
DFPlayerMini_Fast myDFPlayer;

// Define the analog input pins for the flex sensors
const int flexSensorPins[5] = {A0, A1, A2, A3, A4};

// Define thresholds for the flex sensors to detect specific gestures
int flexSensorThresholds[5] = {300, 300, 300, 300, 300};

// Function to initialize the pins
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  myDFPlayer.begin(mySerial);

  // Initialize DFPlayer Mini
  myDFPlayer.volume(10); // Set volume (0 to 30)
  for (int i = 0; i < 5; i++) {
    pinMode(flexSensorPins[i], INPUT);
  }
}

// Function to read the flex sensor values and determine the gesture
void loop() {
  int flexSensorValues[5];
  
  for (int i = 0; i < 5; i++) {
    flexSensorValues[i] = analogRead(flexSensorPins[i]);
    Serial.print("Flex Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(flexSensorValues[i]);
  }

  // Determine the gesture based on the flex sensor values
  if (flexSensorValues[0] > flexSensorThresholds[0] &&
      flexSensorValues[1] <= flexSensorThresholds[1] &&
      flexSensorValues[2] <= flexSensorThresholds[2] &&
      flexSensorValues[3] <= flexSensorThresholds[3] &&
      flexSensorValues[4] <= flexSensorThresholds[4]) {
    Serial.println("Gesture: I Need Water");
    myDFPlayer.play(1); // Play the first audio file on the SD card
  } else if (flexSensorValues[0] <= flexSensorThresholds[0] &&
             flexSensorValues[1] > flexSensorThresholds[1] &&
             flexSensorValues[2] <= flexSensorThresholds[2] &&
             flexSensorValues[3] <= flexSensorThresholds[3] &&
             flexSensorValues[4] <= flexSensorThresholds[4]) {
    Serial.println("Gesture: I Need Food");
    myDFPlayer.play(2); // Play the second audio file on the SD card
  } else if (flexSensorValues[0] <= flexSensorThresholds[0] &&
             flexSensorValues[1] <= flexSensorThresholds[1] &&
             flexSensorValues[2] > flexSensorThresholds[2] &&
             flexSensorValues[3] <= flexSensorThresholds[3] &&
             flexSensorValues[4] <= flexSensorThresholds[4]) {
    Serial.println("Gesture: I Want Medicine");
    myDFPlayer.play(3); // Play the third audio file on the SD card
  } else if (flexSensorValues[0] <= flexSensorThresholds[0] &&
             flexSensorValues[1] <= flexSensorThresholds[1] &&
             flexSensorValues[2] <= flexSensorThresholds[2] &&
             flexSensorValues[3] > flexSensorThresholds[3] &&
             flexSensorValues[4] <= flexSensorThresholds[4]) {
    Serial.println("Gesture: I Want to Sleep");
    myDFPlayer.play(4); // Play the fourth audio file on the SD card
  } else if (flexSensorValues[0] <= flexSensorThresholds[0] &&
             flexSensorValues[1] <= flexSensorThresholds[1] &&
             flexSensorValues[2] <= flexSensorThresholds[2] &&
             flexSensorValues[3] <= flexSensorThresholds[3] &&
             flexSensorValues[4] > flexSensorThresholds[4]) {
    Serial.println("Gesture: Help");
    myDFPlayer.play(5); // Play the fifth audio file on the SD card
  }

  delay(1000); // Add a delay to prevent overwhelming the serial monitor
}
