const int InputP = 33;
const int InputN = 35;
const int VOLT = 3.3;
const int ANALOG_MAX = 4096;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int read_P = analogRead(InputP);
  int read_N = analogRead(InputN);

  float voltage_P = (long)read_P * VOLT * 1000 / ANALOG_MAX;
  float voltage_N = (long)read_N * VOLT * 1000 / ANALOG_MAX;
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
  
  delay(500);
}
