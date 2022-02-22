// 2021/02/22
// Itsuki Onishi
// onishi.itsuki@ist.osaka-u.ac.jp
//
// This program controll moters of Construction machine RC by the signal from "lever_angle_reader.ino".
//
// At first, include package for ESP32.
// See: https://github.com/espressif/arduino-esp32
//      https://dandydot.no-ip.biz/~dot/presen/advtech/seminars/iot_workshop/install-esp32-board-manager/README.md.html

#define NUM_CH 6

uint8_t PWM_signal[NUM_CH];

void setup()
{
    // Serial initialization must be located before device initialization process because
    // functions in the other files use Serial communication.
    Serial.begin(115200);
    Serial.println();

    // device initialization
    PWM_init();
    WiFi_init();
    UDP_init();
}

void _set_basic_signal()
{
    for (int i = 0; i < NUM_CH; i++)
    {
        // If moving of motor is not smooth, change following value to 0 (stop signal -> free spin signal)
        PWM_buffer[i] = 128; // stop signal
    }
}

void loop()
{
    bool check_result = receive_signal(PWM_signal); // step2

    // step3
    if (check_result)
    {
        compute_motor_control_signals(PWM_signal);
    }
    else
    {
        _set_basic_signal();
        compute_motor_control_signals(PWM_signal);
    }
}