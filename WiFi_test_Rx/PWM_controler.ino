// Construction machine controler for ESP32-WROVER-B
// Itsuki Onishi
// December 2020

#include <Ticker.h>

#define START_BYTE 0x0f
#define SAMPLING_PERIOD 5.0f  // scale is ms
#define BYTE_A 2*i
#define BYTE_B 2*i+1

// set output pins
// right side
#define boomOutA 15
#define boomOutB 2
#define armOutA 0
#define armOutB 4
#define bucketOutA 13
#define bucketOutB 12
// left side
#define slewingOutA 14
#define slewingOutB 27
#define rightWheelOutA 26
#define rightWheelOutB 25
#define leftWheelOutA 33
#define leftWheelOutB 32

uint8_t PWM_buffer[8];  // This list stock input signal

int outputBuffer[12];  // This list hold Duty ratio on each pins
int bufferIndex = 0;  // This is the index of waiting sinal


Ticker ticker;


// set duty ratio on each pins
void set_output(void)
{
  ledcWrite(0, outputBuffer[0]);
  ledcWrite(1, outputBuffer[1]);
  ledcWrite(2, outputBuffer[2]);
  ledcWrite(3, outputBuffer[3]);
  ledcWrite(4, outputBuffer[4]);
  ledcWrite(5, outputBuffer[5]);
  ledcWrite(6, outputBuffer[6]);
  ledcWrite(7, outputBuffer[7]);
  ledcWrite(8, outputBuffer[8]);
  ledcWrite(9, outputBuffer[9]);
  ledcWrite(10, outputBuffer[10]);
  ledcWrite(11, outputBuffer[11]);
}


void pin_init()
{
  // initialize pins
  for (int i = 0; i < 12; i++) {
    ledcSetup(i, 115200, 7);
  }
  ledcAttachPin(boomOutA, 0);
  ledcAttachPin(boomOutB, 1);
  ledcAttachPin(armOutA, 2);
  ledcAttachPin(armOutB, 3);
  ledcAttachPin(bucketOutA, 4);
  ledcAttachPin(bucketOutB, 5);
  ledcAttachPin(slewingOutA, 6);
  ledcAttachPin(slewingOutB, 7);
  ledcAttachPin(rightWheelOutA, 8);
  ledcAttachPin(rightWheelOutB, 9);
  ledcAttachPin(leftWheelOutA, 10);
  ledcAttachPin(leftWheelOutB, 11);

  // initial state is free run
  for (int i = 0; i < 8; i++) {
    PWM_buffer[i] = 0;
  }
  for (int i = 0; i < 6; i++) {
    outputBuffer[BYTE_A] = 0;
    outputBuffer[BYTE_B] = 0;
  }
  set_output();
}


//  control whitch pins (A or B) are LOW or HIGH on each DoF.
//  outputBuffer that is HIGH pin holds duty ratio.
void PWM_processor(void)
{
  for (int i = 1; i < 7; i++) {
    // buffer[0] is start byte, so input signals start from 1
    // Both pins is LOW when buffer is 0 or 128.
    if (buffer[i] >= 128) {
      outputBuffer[BYTE_A] = 0;
      outputBuffer[BYTE_B] = buffer[i] - 128;
    } else {
      outputBuffer[BYTE_A] = buffer[i];
      outputBuffer[BYTE_B] = 0;
    }
    buffer[i] = 0;
  }
  set_output();
}


void PWM_init()
{
  pin_init();

  // set tickers
  ticker.attach_ms(SAMPLING_PERIOD, PWM_processor);

  delay(5);
}


int check_values(uint8_t buffer[])
{
  if (buffer[0] != START_BYTE) {
    Serial.println("start byte ERROR");
    return 0;
  }

  //  check parity
  uint8_t serialXOR = buffer[1];
  Serial.print("buffer: [");
  for (int i = 2; i <= 6; i++) {
    serialXOR ^= buffer[i];
  }
  if (serialXOR != buffer[7]) {
    Serial.print("parity byte ERROR: XOR is ");
    Serial.print(serialXOR);
    Serial.print(", buffer byte is ");
    Serial.println(buffer[7]);
    return 0;
  }

  return 1;
}
