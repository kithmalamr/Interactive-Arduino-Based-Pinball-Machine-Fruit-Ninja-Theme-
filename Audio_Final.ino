#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(10, 11);  // RX (10), TX (11)
DFRobotDFPlayerMini myDFPlayer;
const int headphoneDetectPin = 2;  // Single pin for detecting headphones
bool isHeadphonesConnected = false;

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600);
    pinMode(headphoneDetectPin, INPUT_PULLUP);  // Enable pull-up resistor

    if (!myDFPlayer.begin(mySerial)) {
        Serial.println("DFPlayer Mini not detected!");
        while (true);
    }

    myDFPlayer.volume(30);  // Default speaker volume
    Serial.println("DFPlayer Mini ready.");
    checkHeadphoneStatus();  // Initial check for headphones
    Serial.println("Available commands: splatter, bomb, frenzy, freeze, gameOver, theme");
}

void loop() {
    checkHeadphoneStatus();  // Continuously monitor headphone connection status

    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');  
        input.trim();  

        if (input.length() == 0) {
            Serial.println("No input detected. Please enter a valid command.");
            return;
        }

        processCommand(input);
    }
}

// Function to process commands
void processCommand(String command) {
    if (command.equalsIgnoreCase("splatter")) {
        splatter();
    } else if (command.equalsIgnoreCase("bomb")) {
        bomb();
    } else if (command.equalsIgnoreCase("frenzy")) {
        frenzy();
    } else if (command.equalsIgnoreCase("freeze")) {
        freeze();
    } else if (command.equalsIgnoreCase("gameOver")) {
        gameOver();
    } else if (command.equalsIgnoreCase("theme")) {
        theme();
    } else {
        Serial.println("Invalid command. Available commands: splatter, bomb, frenzy, freeze, gameOver, theme");
    }
}

// Functions to play specific sounds
void splatter() {
    playFile(1, "Splatter sound playing...");
}

void bomb() {
    playFile(2, "Bomb sound playing...");
}

void frenzy() {
    playFile(3, "Frenzy mode sound playing...");
}

void freeze() {
    playFile(4, "❄ Freeze sound playing...");
}

void gameOver() {
    playFile(5, "Game Over sound playing...");
}

void theme() {
    playFile(6, "Theme music playing...");
}

// Function to play a file with a status message
void playFile(int fileNumber, String message) {
    Serial.println(message);
    myDFPlayer.play(fileNumber);
}

// Function to check headphone connection and switch audio output
void checkHeadphoneStatus() {
    int headphoneState = digitalRead(headphoneDetectPin);  // Read headphone switch status

    if (headphoneState == HIGH) {  // Headphones plugged in (Switch is open)
        if (!isHeadphonesConnected) {
            Serial.println("Headphones detected! Switching to AUX output...");
            myDFPlayer.stop();  // Stop current playback
            myDFPlayer.outputDevice(DFPLAYER_DEVICE_AUX);  // Use DAC output for headphones
            delay(500);  // Wait for device to switch
            myDFPlayer.volume(30);  // Set volume for headphones
            isHeadphonesConnected = true;
        }
    } else {  // Headphones NOT plugged in (Switch is closed)
        if (isHeadphonesConnected) {
            Serial.println("Headphones disconnected! Switching back to speaker...");
            myDFPlayer.stop();  // Stop current playback
            delay(500);  // Allow time for mode switch
            myDFPlayer.volume(30);  // Restore speaker volume
            isHeadphonesConnected = false;
        }
    }
}