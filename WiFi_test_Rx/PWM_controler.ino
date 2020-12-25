// Construction machine controler for ESP32-WROVER-B
// Itsuki Onishi
// December 2020

#include <Ticker.h>

#define START_BYTE 0x0f
#define SAMPLING_PERIOD 5.0f  // scale is ms
#define BYTE_A 2*(i-1)
#define BYTE_B 2*(i-1)+1

// set output pins
// right side
#define boomOutA 15
#define boomOutB 2
#define armOutA 0
#define armOutB 4
// left side
#define bucketOutA 13
#define bucketOutB 12
#define slewingOutA 14
#define slewingOutB 27
#define rightWheelOutA 26
#define rightWheelOutB 25
#define leftWheelOutA 33
#define leftWheelOutB 32

uint8_t PWM_buffer[8];  // This list stock input signal

int outputBuffer[12];  // This list hold Duty ratio on each pins
int pwmProcessFlag = 0;  // This is the index of waiting sinal


Ticker ticker;


// set duty ratio on each pins
void set_output(void)
{
  Serial.println("run set_output func");
  for (int i = 0; i < 12; i++) {
    ledcWrite(i, outputBuffer[i]);
    Serial.print(i);
    Serial.print(": ");
    Serial.println(outputBuffer[i]);
  }
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
  if (pwmProcessFlag == 0) {
    return;
  } else {
    for (int i = 1; i < 7; i++) {
      // buffer[0] is start byte, so input signals start from 1
      // Both pins is LOW when buffer is 0 or 128.
      if ((int)(buffer[i]) >= 128) {
        outputBuffer[BYTE_A] = 0;
        outputBuffer[BYTE_B] = (int)(buffer[i] - 128);
      } else {
        outputBuffer[BYTE_A] = (int)(buffer[i]);
        outputBuffer[BYTE_B] = 0;
      }
      buffer[i] = 0;
    }
    set_output();
    pwmProcessFlag = 0;
    Serial.println("set outputs");
  }
}


void PWM_init()
{
  pin_init();

  // set tickers
  ticker.attach_ms(SAMPLING_PERIOD, PWM_processor);

  delay(5);
}


int check_values()
{
  if (buffer[0] != START_BYTE) {
    Serial.println("start byte ERROR");
    return 0;
  }

  //  check parity
  uint8_t serialXOR = buffer[1];
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

  Serial.println("print Buffer array");
  for (int i = 0; i < 8; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(buffer[i]);
  }
  pwmProcessFlag = 1;
  return 1;
}
