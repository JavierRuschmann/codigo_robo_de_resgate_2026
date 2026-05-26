#include <Arduino.h>

void set_pwm(int motor, int pwm);

void set_direction(int motor, int sign);

const int pin_pwm_a = 4;
const int switch_a_1 = 16;
const int switch_a_2 = 17;

const int pin_pwm_b = 21;
const int switch_b_1 = 18;
const int switch_b_2 = 19;

const int ir_sensor_vin = 13;
const int IR_SENSOR_PINS = 5;
const int ir_sensor_pin[] = {14, 27, 26, 25, 33, 32};

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
  digitalWrite(ir_sensor_vin, HIGH);
  for (int i = 0; i < IR_SENSOR_PINS; i++)
  {
    pinMode(ir_sensor_pin[i], INPUT);
  }

  pinMode(switch_a_1, OUTPUT);
  pinMode(switch_a_2, OUTPUT);

  pinMode(switch_b_1, OUTPUT);
  pinMode(switch_b_2, OUTPUT);

  set_direction(0, 1);
  set_direction(1, 1);

  set_pwm(0, 500);
  set_pwm(1, 500);
}

void loop() {
  for (int i = 0; i < IR_SENSOR_PINS; i++)
  {
    Serial.print(analogRead(ir_sensor_pin[i]));
    Serial.print(" ");
  }

  Serial.println();
  
  delay(5);
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