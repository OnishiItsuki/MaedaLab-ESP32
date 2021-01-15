const int InputP = 25;
const int InputN = 33;
const int VOLT = 3.3;
const int ANALOG_MAX = 4096;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int read_P = analogRead(InputP);
  int read_N = analogRead(InputN);

  float voltage_P = (long)read_P * VOLT / ANALOG_MAX;
  float voltage_N = (long)read_N * VOLT / ANALOG_MAX;

  Serial.print("Positive:");
  Serial.print(voltage_P);
  Serial.print(" V, ");
  Serial.print("Negative:");
  Serial.print(voltage_N);
  Serial.print("V");
  
  delay(1000);
}
