// Construction machine controller for ESP32-WROVER-B
// Itsuki Onishi
// December 2020

#include <Ticker.h>

#define DUTY_RATIO_BIT_SIZE 7 // the range of duty ratio is 0~128 (first bit represents the direction of motor rotation)
#define PWM_FREQ 115200       // uint is [kHz]
#define SET_SIGNAL_SPAN_MS 5.0f
#define BYTE_A 2 * i
#define BYTE_B 2 * i + 1

// set output pins
// right side
#define BOOM_OUT_A 15
#define BOOM_OUT_B 2
#define ARM_OUT_A 0
#define ARM_OUT_B 4
// left side
#define BUCKET_OUT_A 13
#define BUCKET_OUT_B 12
#define SLEWING_OUT_A 14
#define SLEWING_OUT_B 27
#define RIGHT_WHEEL_OUT_A 26
#define RIGHT_WHEEL_OUT_B 25
#define LEFT_WHEEL_OUT_A 33
#define LEFT_WHEEL_OUT_B 32

static const int control_signal_buffer_size = NUM_CH * 2;
int control_input_signal[control_signal_buffer_size]; // This list hold Duty ratio on each pins

Ticker ticker;

void _set_duty_ratio_for_each_pins(void)
{
  Serial.println("run _set_duty_ratio_for_each_pins func");
  for (int i = 0; i < control_signal_buffer_size; i++)
  {
    ledcWrite(i, control_input_signal[i]);

    // show the value of signal
    Serial.print(i);
    Serial.print(": ");
    Serial.println(control_input_signal[i]);
  }
}

void _pin_init()
{
  // initialize pins
  for (int i = 0; i < control_signal_buffer_size; i++)
  {
    ledcSetup(i, PWM_FREQ, DUTY_RATIO_BIT_SIZE);
  }

  // set pair of pin and indexies of control_signal_buffer
  ledcAttachPin(BOOM_OUT_A, 0);
  ledcAttachPin(BOOM_OUT_B, 1);
  ledcAttachPin(ARM_OUT_A, 2);
  ledcAttachPin(ARM_OUT_B, 3);
  ledcAttachPin(BUCKET_OUT_A, 4);
  ledcAttachPin(BUCKET_OUT_B, 5);
  ledcAttachPin(SLEWING_OUT_A, 6);
  ledcAttachPin(SLEWING_OUT_B, 7);
  ledcAttachPin(RIGHT_WHEEL_OUT_A, 8);
  ledcAttachPin(RIGHT_WHEEL_OUT_B, 9);
  ledcAttachPin(LEFT_WHEEL_OUT_A, 10);
  ledcAttachPin(LEFT_WHEEL_OUT_B, 11);

  // initial state is free run
  for (int i = 0; i < NUM_CH; i++)
  {
    control_input_signal[BYTE_A] = 0;
    control_input_signal[BYTE_B] = 0;
  }
  _set_duty_ratio_for_each_pins();
}

void PWM_init()
{
  _pin_init();
  ticker.attach_ms(SET_SIGNAL_SPAN_MS, _set_duty_ratio_for_each_pins); // setp4
  delay(500);
}

//  control witch pins (A or B) are LOW or HIGH on each DoF.
//  control_signal_buffer that is HIGH pin holds duty ratio.
void compute_motor_controll_signals(uint8_t input_signal[]) // PWM_signal[NUM_CH], step3
{
  for (int i = 0; i < NUM_CH; i++)
  {
    // Both pins is LOW when signal_buffer is 0 (free).
    // When input signal is 128, this process send motor stop signal.
    if ((int)(input_signal[i]) > 128)
    {
      control_input_signal[BYTE_A] = 0;
      control_input_signal[BYTE_B] = (int)(signal_buffer[i] - 128);
    }
    else if ((int)(input_signal[i]) == 128))
      {
        control_input_signal[BYTE_A] = 128;
        control_input_signal[BYTE_B] = 128;
      }
    else
    {
      control_input_signal[BYTE_A] = (int)(signal_buffer[i]);
      control_input_signal[BYTE_B] = 0;
    }
  }
}
