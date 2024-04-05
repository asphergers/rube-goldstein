#include <Servo.h>

#define MOTOR_PIN 2
#define MOTOR_INFO_OUT_PIN 50
#define MOTOR_INFO_IN_PIN 51
#define POT_INFO_IN_PIN A15
#define ZERO_IN_PIN 49
#define TURN_IN_PIN 48

Servo servo;
int pos = 120;
int delay_ms = 1000;
bool motor_enabled = true;

int delay_max = 2000;
int delay_min = 150;

void setup() {
    servo.attach(5);
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(MOTOR_INFO_OUT_PIN, OUTPUT);
    pinMode(MOTOR_INFO_IN_PIN, INPUT);

    pinMode(POT_INFO_IN_PIN, INPUT);

    pinMode(ZERO_IN_PIN, INPUT);
    pinMode(TURN_IN_PIN, INPUT);
}

int normalize(int value) {
    return (value - delay_min) / (delay_min / delay_max);
}

int prev_motor;
int current_motor;
int delay_input;
int current_zero_input;
int prev_zero_input;
int current_turn_input;
int prev_turn_input;
void handle_input() {
    current_motor = digitalRead(MOTOR_INFO_IN_PIN);
    if (current_motor == HIGH && prev_motor != HIGH) motor_enabled = !motor_enabled;

    if (motor_enabled) { digitalWrite(MOTOR_INFO_OUT_PIN, HIGH); } else { digitalWrite(MOTOR_INFO_OUT_PIN, LOW); }

    //delay_input = normalize(analogRead(POT_INFO_IN_PIN));
    //delay_ms = delay_input;


    current_zero_input = digitalRead(ZERO_IN_PIN);
    if (current_zero_input == HIGH && prev_zero_input != HIGH) servo.write(0);
    prev_zero_input = current_zero_input;

    current_turn_input = digitalRead(TURN_IN_PIN);
    if (current_turn_input == HIGH && prev_zero_input != HIGH) servo.write(pos); 
    prev_turn_input = current_turn_input;

    prev_motor = current_motor;
}

unsigned long current_time;
unsigned long next_time;

void loop() {
    current_time = millis();
    next_time = current_time + delay_ms;
    while (millis() < next_time) handle_input();
    if (motor_enabled) servo.write(0);

    current_time = millis();
    next_time = current_time + delay_ms;
    while (millis() < next_time) handle_input();
    if (motor_enabled) servo.write(pos);
}

