const int InputP = 35;
const int InputN = 33;
const int VOLT = 3.3;
const int ANALOG_MAX = 4096;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int read_P = analogRead(InputP);
  int read_N = analogRead(InputN);

  float voltage_P = (float)read_P * VOLT * 1000 / ANALOG_MAX;
  float voltage_N = (float)read_N * VOLT * 1000 / ANALOG_MAX;
  float voltage_sum = voltage_P + voltage_N;

  Serial.print("Positive:");
  Serial.print(voltage_P);
  Serial.print(" mV, ");
  
  Serial.print("Negative:");
  Serial.print(voltage_N);
  Serial.print(" mV, ");

  Serial.print("Sum:");
  Serial.print(voltage_sum);
  Serial.println("mV");

  Serial.print("P: ");
  Serial.print(read_P);
  Serial.print("  ,N: ");
  Serial.println(read_N);
  
  delay(500);
}
