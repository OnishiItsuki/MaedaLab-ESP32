unsigned long inner_time;

void setup() {
  Serial.begin(115200);
}

void loop() {
  inner_time = micros();
  Serial.println(inner_time);
  inner_time = micros();
  Serial.println(inner_time);
  delay(1000);
}
