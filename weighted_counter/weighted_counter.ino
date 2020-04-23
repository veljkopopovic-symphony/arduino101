//use Multifunction Shield for this example
#define LATCH_PIN 4
#define CLK_PIN 7
#define DATA_PIN 8

const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};

const byte BUTTON_PINS[] = {A1, A2, A3};
byte buttonPressed[] = {false, false, false}; 

unsigned int cntr = 0;

void setup() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  for (byte i = 0; i < sizeof(BUTTON_PINS); i++) {
    pinMode(BUTTON_PINS[i], INPUT);
  }
}

void loop() {
  byte inc = readKeyInputs();
  cntr += inc;
  writeNumber(cntr);
}

byte readKeyInputs() {
  byte inc = 0;
  
  for (byte i = 0; i < sizeof(BUTTON_PINS); i++) {
    bool isPressed = digitalRead(BUTTON_PINS[i]) == LOW;
    if (isPressed) {
      buttonPressed[i] = isPressed;
      continue;
    }

    if (isUpDetected(i)) {
      inc += (i+1);
    }

    buttonPressed[i] = isPressed;
  }

  return inc;
}

boolean isUpDetected(byte index) {
  return buttonPressed[index] == true;
}

void writeNumber(int number) {
  if (0  == number) {
    writeNumberToSegment(3, 0);
    return;
  }
  
  const byte splitted[] = { (byte)((number / 1000) % 10), (byte)((number / 100) % 10), (byte)((number / 10) % 10), (byte)(number % 10) };
  bool leadingZero = true;
  
  for (byte i = 0; i < sizeof(splitted); i++) {
    if (splitted[i] != 0) {
      leadingZero = false;
    }
    if (leadingZero) {
      continue;
    }
    writeNumberToSegment(i, splitted[i]);
  }
}

void writeNumberToSegment(byte segment, byte value)
{
  digitalWrite(LATCH_PIN,LOW);
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, SEGMENT_MAP[value]);
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, SEGMENT_SELECT[segment] );
  digitalWrite(LATCH_PIN,HIGH);
}
