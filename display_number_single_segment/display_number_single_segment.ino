#define LATCH_PIN 4
#define CLK_PIN 7
#define DATA_PIN 8

const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};

byte cntr = 0;

void setup() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  writeNumberToSegment(cntr % 4, cntr % 10);
  cntr++;
  delay(1000);
}

void writeNumberToSegment(byte segment, byte value)
{
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, SEGMENT_MAP[value]);
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, SEGMENT_SELECT[segment] );
  digitalWrite(LATCH_PIN, HIGH);
}
