// Pin Definitions
const int hallDigitalPin = 4;  // Hall sensor output pin
const int led1 = 2;            // LED pin

void setup() { 
  pinMode(hallDigitalPin, INPUT_PULLUP);  // Internal pull-up for stable input
  pinMode(led1, OUTPUT);
  Serial.begin(9600);  // Faster Serial communication
}

void loop() { 
  static unsigned long lastPrintTime = 0; // Track last print time
  int hallDigital = digitalRead(hallDigitalPin);  // Read sensor state

  // LED Control - Turn ON when magnet is detected
  digitalWrite(led1, (hallDigital == LOW) ? HIGH : LOW);

  // Limit Serial Output to every 10ms to prevent flooding
  if (millis() - lastPrintTime > 10) {  
    Serial.print("Hall Sensor: ");
    Serial.println(hallDigital);
    lastPrintTime = millis();
  }
}
