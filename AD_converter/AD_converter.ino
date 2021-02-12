#define InputP 35
#define InputN 33

#define DIG_RANGE 128

const int VOLT = 3.3;
const int ANALOG_MAX = 4096;
const long CALIB_TIME = 1000; // Scale is "milli second""


int AnaInputP = 0;
int AnaInputN = 0;
int AnaInputDiff = 0;

float DigInput = 0;

int MaxAnaInput = 0;
int MinAnaInput = 0;

void Read_pin()
{
  AnaInputP = analogRead(InputP);
  AnaInputN = analogRead(InputN);
  AnaInputDiff = AnaInputP - AnaInputN;
}

void Wait_key()
{
  while (true) {
    if (Serial.available() > 0) {
      while (Serial.available() > 0) {
        Serial.read();
      }
      break;
    }
  }
}

void Calibration()
{
  Serial.println("\nStart calibration.");
  Serial.println("Keep tilting the lever in the positive direction and press a key\n");
  //  Serial.println();

  //  Calibrate maximum value
  while (true) {
    Serial.println("-> Start calibration of positive direction");
    Wait_key();
    Read_pin();
    if (AnaInputDiff < 0) {
      Serial.println("This is the wrong direction. Tilt the lever in the opposit direction\n");
      continue;
    }

    int TmpMax = 0;
    long StartTime = millis();
    Serial.println("Keep lever...");
    while (true) {
      Read_pin();
      if (AnaInputDiff > TmpMax) {
        TmpMax = AnaInputDiff;
      }
      long TmpTime = millis();
      if (TmpTime - StartTime > CALIB_TIME) {
        MaxAnaInput = TmpMax;
        break;
      }
    }
    Serial.println("Finish calibration of positive direction\n");
    break;
  }

  //  Calibrate minimum value
  while (true) {
    Serial.println("-> Start calibration of negative direction");
    Wait_key();
    Read_pin();
    if (AnaInputDiff > 0) {
      Serial.println("This is the wrong direction. Tilt the lever in the opposit direction\n");
      continue;
    }
    int TmpMin = 0;
    long StartTime = millis();
    Serial.println("Keep lever...");
    while (true) {
      Read_pin();
      if (AnaInputDiff < TmpMin) {
        TmpMin = AnaInputDiff;
      }
      long TmpTime = millis();
      if (TmpTime - StartTime > CALIB_TIME) {
        MinAnaInput = TmpMin;
        break;
      }
    }
    Serial.println("Finish calibration of negative direction\n");
    break;
  }

  Serial.println("Finish calibration. Result is following");
  Serial.print("Max value: ");
  Serial.print(MaxAnaInput);
  Serial.print("  Min value: ");
  Serial.print(MinAnaInput);
  Serial.print("\n\n");
}

uint8_t AD_converter()
{
  if (AnaInputDiff > 0) {
    DigInput = (AnaInputDiff / MaxAnaInput * DIG_RANGE);
  } else {
    DigInput = (AnaInputDiff / MinAnaInput * DIG_RANGE);
  }
  Serial.print("  Digital input: ");
  Serial.println(DigInput);
}



void setup()
{
  Serial.begin(115200);
  Calibration();
}

void loop()
{
  Read_pin();
  Serial.print("Analog input: ");
  Serial.print(AnaInputDiff);
  AD_converter();
  //
  //  Read_pin();
  //
  //  float voltage_P = AnaInputP * VOLT * 1000 / ANALOG_MAX;
  //  float voltage_N = AnaInputN * VOLT * 1000 / ANALOG_MAX;
  //  float voltage_sum = voltage_P - voltage_N;
  //
  //  Serial.print("Positive:");
  //  Serial.print(voltage_P);
  //  Serial.print(" mV, ");
  //
  //  Serial.print("Negative:");
  //  Serial.print(voltage_N);
  //  Serial.print(" mV, ");
  //
  //  Serial.print("Sum:");
  //  Serial.print(voltage_sum);
  //  Serial.println("mV");
  //
  //  Serial.print("P: ");
  //  Serial.print(AnaInputP);
  //  Serial.print("  ,N: ");
  //  Serial.println(AnaInputN);

  delay(500);
}
