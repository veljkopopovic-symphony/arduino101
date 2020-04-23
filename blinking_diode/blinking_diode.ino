#define RED 2 //replace this with pin number you are connecting diode anode to
#define BLINK_INTERVAL 1000

void setup() {
    pinMode(RED, OUTPUT);
}

void loop() {
    turnOn(RED);
    delay(BLINK_INTERVAL);
    turnOff(RED);
    delay(BLINK_INTERVAL);
}

void turnOn(byte output) {
  digitalWrite(output, HIGH);
}

void turnOff(byte output) {
  digitalWrite(output, LOW);
}
