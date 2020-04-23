#define RED  2 //replace with the pin you are connecting diode anode to


void setup() {
    pinMode(RED, OUTPUT);
    turnOn(RED);

}

void loop() {
}

void turnOn(byte output) {
  digitalWrite(output, HIGH);
}
