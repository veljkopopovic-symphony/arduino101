//use Multifunction Shield for this example
#define LATCH_PIN 4
#define CLK_PIN 7
#define DATA_PIN 8

#define STAGE_INTERVAL 1000

const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};

const unsigned int nmbr = 1234;
const byte delays[] = {200, 100, 50, 20};
const byte delaysSize = sizeof(delays);

unsigned long lastTimeStamp = millis();
byte index = 0;

void setup() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

void loop() {
  maybeReduceDelay();
  writeNumber(nmbr);
}

void maybeReduceDelay() {
  if (index >= delaysSize) {
    return;
  }

  unsigned long now = millis();
  if (now - lastTimeStamp > STAGE_INTERVAL) {
    lastTimeStamp = now;
    index++;
  }
}

byte getDelay() {
  if (index >= delaysSize) {
    return 0;
  }

  return delays[index];
}

void writeNumber(int number) {
  if (0  == number) {
    writeNumberToSegment(3, 0);
    return;
  }
  
  const byte splitted[] = { (byte)((number / 1000) % 10), (byte)((number / 100) % 10), (byte)((number / 10) % 10), (byte)(number % 10) };
  bool leadingZero = true;
  
  for (byte i = 0; i < sizeof(splitted); i++) {
    delay(getDelay());
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
