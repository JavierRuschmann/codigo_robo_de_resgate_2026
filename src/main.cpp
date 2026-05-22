#include <Arduino.h>

void set_pwm(int motor, int pwm);

void set_direction(int motor, int sign);

const int pin_pwm_a = 14;
const int switch_a_1 = 26;
const int switch_a_2 = 27;

const int pin_pwm_b = 25;
const int switch_b_1 = 32;
const int switch_b_2 = 33;

const int standby = 13;

const int ir_sensor_vin = 13;
const int ir_sensor_out = 4;

const int pwm_a = 0;
const int pwm_b = 1;

const int PWM_FREQUENCY = 1000;
const int PWM_RESOLUTION = 10;
const int PWM_MAX = (int) ((pow(2, PWM_RESOLUTION) - 1));

const int BAUD_RATE = 115200;

void setup() {
  Serial.begin(BAUD_RATE);

  ledcSetup(pwm_a, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(pwm_b, PWM_FREQUENCY, PWM_RESOLUTION);

  ledcAttachPin(pin_pwm_a, pwm_a);
  ledcAttachPin(pin_pwm_b, pwm_b);

  pinMode(ir_sensor_vin, OUTPUT);
  pinMode(ir_sensor_out, INPUT);
  digitalWrite(ir_sensor_vin, HIGH);

  pinMode(switch_a_1, OUTPUT);
  pinMode(switch_a_2, OUTPUT);

  pinMode(switch_b_1, OUTPUT);
  pinMode(switch_b_2, OUTPUT);

  pinMode(standby, OUTPUT);
  digitalWrite(standby, HIGH);

  set_direction(0, 1);
  set_direction(1, 1);

  set_pwm(0, 500);
  set_pwm(1, 500);
}

void loop() {
  Serial.println(analogRead(ir_sensor_out));
  delay(500);
}

void set_pwm(int motor, int pwm)
{
  if (motor != 0) motor = 1;

  if (pwm > PWM_MAX) ledcWrite(motor, PWM_MAX);
  else if (pwm < 0) ledcWrite(motor, 0);
  else ledcWrite(motor, pwm);
}

void set_direction(int motor, int sign)
{
  int motor_pin_1;
  int motor_pin_2;
  if (motor == 0)
  {
    motor_pin_1 = switch_a_1;
    motor_pin_2 = switch_a_2;
  }
  else
  {
    motor_pin_1 = switch_b_1;
    motor_pin_2 = switch_b_2;
  }

  if (sign > 0)
  {
    digitalWrite(motor_pin_1, HIGH);
    digitalWrite(motor_pin_2, LOW);
  }
  else if (sign < 0)
  {
    digitalWrite(motor_pin_1, LOW);
    digitalWrite(motor_pin_2, HIGH);
  }
  else
  {
    digitalWrite(motor_pin_1, LOW);
    digitalWrite(motor_pin_2, LOW);
  }
}