const int InputR = 25;
const int InputL = 33
const int VOLT = 3.3;
const int ANALOG_MAX = 4096;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int reading = analogRead(voutPin);

  float voltage = ((long)reading * VOLT * 1000) / ANALOG_MAX;

  Serial.print(voltage);
  Serial.print(" mV, ");


  float microamp = (voltage * 1000) / 1000;

  Serial.print(microamp);
  Serial.print(" uA, ");


  float lx = microamp / (290 / 100);

  Serial.print(lx);
  Serial.println(" lx");

  delay(1000);
}
