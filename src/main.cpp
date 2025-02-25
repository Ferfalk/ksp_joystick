#include <Arduino.h>
#include <Joystick.h>

// Uncomment the line below to enable debug mode
// #define DEBUG

// Initialize joystick with 3 axes (X, Y, and Rz) and 1 button
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK, 1, 0,  // 1 button, no hat switch
                   true, true, false,                                         // X, Y (No Z)
                   false, false, true,                                        // No rudder, throttle, but Rz (rotation)
                   false, false, false, false);                               // No additional axes

// Pin configuration for analog inputs and button
const int xAxisPin = A0;   // X-axis (Analog Input)
const int yAxisPin = A1;   // Y-axis (Analog Input)
const int rzAxisPin = A2;  // Rotation (Rz) (Analog Input)
const int buttonPin = 2;   // Button (Digital Input)

// Configuration parameters
const int deadzoneThreshold = 16;  // Adjust deadzone threshold (0-1023)
const int normalDelay = 10;        // Normal delay between loop iterations
const int debugDelay = 500;        // Delay in debug mode (ms)
const int debounceDelay = 10;      // Debounce delay for button presses

int lastButtonState = HIGH;  // Initialize to HIGH as the input uses pull-up

// Debug function declaration (if DEBUG is enabled)
#ifdef DEBUG
void debugPrint(int x, int y, int rz, bool button);
#endif

// Declare variables outside the loop, improves performance slightly
int rawX, rawY, rawRz;
int xValue, yValue, rzValue;
bool currentButtonState;

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);  // Enable internal pull-up resistor for button
    Joystick.begin();                  // Initialize joystick

#ifdef DEBUG
    Serial.begin(115200);  // Start serial communication for debugging
    Serial.println("Debug Mode: ON");
#endif
}

// Function to apply the deadzone and rescale the value
int applyDeadzone(int rawValue) {
    int centeredValue = rawValue - 512;  // Center the value (-512 to 511)

    if (abs(centeredValue) < deadzoneThreshold) {
        return 512;  // Return center position if within deadzone
    }

    // Rescale the value to maintain full range (0-1023)
    return (centeredValue > 0) ? map(centeredValue, deadzoneThreshold, 511, 512, 1023)
                               : map(centeredValue, -511, -deadzoneThreshold, 0, 511);
}

void loop() {
    // Read analog values from the joystick axes (0-1023)
    rawX = analogRead(xAxisPin);
    rawY = analogRead(yAxisPin);
    rawRz = analogRead(rzAxisPin);

    // Apply deadzone to each axis
    xValue = applyDeadzone(rawX);
    yValue = applyDeadzone(rawY);
    rzValue = applyDeadzone(rawRz);

    // Update joystick values
    Joystick.setXAxis(xValue);
    Joystick.setYAxis(yValue);
    Joystick.setRzAxis(rzValue);

    // Read the button state (LOW when pressed)
    currentButtonState = !digitalRead(buttonPin);
    if (currentButtonState != lastButtonState) {
        Joystick.setButton(0, currentButtonState);
        lastButtonState = currentButtonState;
        delay(debounceDelay);  // Debounce delay to prevent multiple triggers
    }

#ifdef DEBUG
    // In debug mode, print joystick values to Serial monitor
    debugPrint(xValue, yValue, rzValue, currentButtonState);
    delay(debugDelay);
#else
    delay(normalDelay);
#endif
}

// Debug function to print joystick values to Serial
#ifdef DEBUG
void debugPrint(int x, int y, int rz, bool button) {
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" | Y: ");
    Serial.print(y);
    Serial.print(" | Rz: ");
    Serial.print(rz);
    Serial.print(" | Button: ");
    Serial.println(button ? "PRESSED" : "RELEASED");
}
#endif
