#include <ESP32Servo.h>
#include <Arduino.h>
#define GH_INCLUDE_PORTAL
#include <GyverHub.h>
#include <GyverOLED.h>
#include <bitmaps.h>

GyverOLED<SSD1306_128x64> oled(0x3c);

GyverHub hub;
gh::Pos pos;


Servo front_left_high;
Servo front_left_low;
Servo front_right_high;
Servo front_right_low;
Servo rear_left_high;
Servo rear_left_low;
Servo rear_right_high;
Servo rear_right_low;


int minUs = 500;
int maxUs = 2400;


bool hello_mode;
bool dance_mode;
bool come_to_me_mode;
bool arm_up_mode;
bool happy_mode;
bool idk_mode;


#define FRONT_LEFT_HIGH_ZERO 90
#define FRONT_LEFT_LOW_ZERO 160
#define FRONT_RIGHT_HIGH_ZERO 90
#define FRONT_RIGHT_LOW_ZERO 20
#define REAR_LEFT_HIGH_ZERO 90
#define REAR_LEFT_LOW_ZERO 20
#define REAR_RIGHT_HIGH_ZERO 90
#define REAR_RIGHT_LOW_ZERO 160


#define WALK_DEGREE 45
#define LEG_UP_DEGREE 60
#define ROTATE_DEGREE 35
#define MAX_DEVIATION 2
#define HELLO_MODE_TIME 3000
#define HAPPY_MODE_TIME 5000
#define DANCE_MODE_TIME 5000
#define COME_TO_ME_MODE_TIME 5000
#define ARM_UP_MODE_TIME 5000
#define IDK_MODE_TIME 5000
#define FORCED_HOME_DELAY_TIME 30

int i = 0;
static uint32_t out;


void soft_home() {
  if (front_left_high.read() < FRONT_LEFT_HIGH_ZERO - MAX_DEVIATION || front_left_high.read() > FRONT_LEFT_HIGH_ZERO + MAX_DEVIATION) {
    front_left_low.write(FRONT_LEFT_LOW_ZERO - LEG_UP_DEGREE);
    front_left_high.write(FRONT_LEFT_HIGH_ZERO);
    front_left_low.write(FRONT_LEFT_LOW_ZERO);
  } else {
    if (front_left_low.read() < FRONT_LEFT_LOW_ZERO - MAX_DEVIATION || front_left_low.read() > FRONT_LEFT_LOW_ZERO + MAX_DEVIATION) front_left_low.write(FRONT_LEFT_LOW_ZERO);
  }

  if (front_right_high.read() < FRONT_RIGHT_HIGH_ZERO - MAX_DEVIATION || front_right_high.read() > FRONT_RIGHT_HIGH_ZERO + MAX_DEVIATION) {
    front_right_low.write(FRONT_RIGHT_LOW_ZERO - LEG_UP_DEGREE);
    front_right_high.write(FRONT_RIGHT_HIGH_ZERO);
    front_right_low.write(FRONT_RIGHT_LOW_ZERO);
  } else {
    if (front_right_low.read() < FRONT_RIGHT_LOW_ZERO - MAX_DEVIATION || front_right_low.read() > FRONT_RIGHT_LOW_ZERO + MAX_DEVIATION) front_right_low.write(FRONT_RIGHT_LOW_ZERO);
  }

  if (rear_left_high.read() < REAR_LEFT_HIGH_ZERO - MAX_DEVIATION || rear_left_high.read() > REAR_LEFT_HIGH_ZERO + MAX_DEVIATION) {
    rear_left_low.write(REAR_LEFT_LOW_ZERO + LEG_UP_DEGREE);
    rear_left_high.write(REAR_LEFT_HIGH_ZERO);
    rear_left_low.write(REAR_LEFT_LOW_ZERO);
  } else {
    if (rear_left_low.read() < REAR_LEFT_LOW_ZERO - MAX_DEVIATION || rear_left_low.read() > REAR_LEFT_LOW_ZERO + MAX_DEVIATION) rear_left_low.write(REAR_LEFT_LOW_ZERO);
  }

  if (rear_right_high.read() < REAR_RIGHT_HIGH_ZERO - MAX_DEVIATION || rear_right_high.read() > REAR_RIGHT_HIGH_ZERO + MAX_DEVIATION) {
    rear_right_low.write(REAR_RIGHT_LOW_ZERO + LEG_UP_DEGREE);
    rear_right_high.write(REAR_RIGHT_HIGH_ZERO);
    rear_right_low.write(REAR_RIGHT_LOW_ZERO);
  } else {
    if (rear_right_low.read() < REAR_RIGHT_LOW_ZERO - MAX_DEVIATION || rear_right_low.read() > REAR_RIGHT_LOW_ZERO + MAX_DEVIATION) rear_right_low.write(REAR_RIGHT_LOW_ZERO);
  }
}

void forced_home() {
  delay(FORCED_HOME_DELAY_TIME);
  front_left_high.write(FRONT_LEFT_HIGH_ZERO);
  delay(FORCED_HOME_DELAY_TIME);
  front_left_low.write(FRONT_LEFT_LOW_ZERO);
  delay(FORCED_HOME_DELAY_TIME);
  front_right_high.write(FRONT_RIGHT_HIGH_ZERO);
  delay(FORCED_HOME_DELAY_TIME);
  front_right_low.write(FRONT_RIGHT_LOW_ZERO);
  delay(FORCED_HOME_DELAY_TIME);
  rear_left_high.write(REAR_LEFT_HIGH_ZERO);
  delay(FORCED_HOME_DELAY_TIME);
  rear_left_low.write(REAR_LEFT_LOW_ZERO);
  delay(FORCED_HOME_DELAY_TIME);
  rear_right_high.write(REAR_RIGHT_HIGH_ZERO);
  delay(FORCED_HOME_DELAY_TIME);
  rear_right_low.write(REAR_RIGHT_LOW_ZERO);
  delay(FORCED_HOME_DELAY_TIME);
}

void walk_forward(int i) {
  switch (i) {
    case 0:
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO);

      front_left_low.write(FRONT_LEFT_LOW_ZERO - LEG_UP_DEGREE);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - WALK_DEGREE);

      rear_right_low.write(REAR_RIGHT_LOW_ZERO - LEG_UP_DEGREE);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO + WALK_DEGREE);
      break;

    case 1:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO);
      front_left_low.write(FRONT_LEFT_LOW_ZERO);
      break;

    case 2:
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + LEG_UP_DEGREE);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO + WALK_DEGREE);

      rear_left_low.write(REAR_LEFT_LOW_ZERO + LEG_UP_DEGREE);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO - WALK_DEGREE);

      front_left_high.write(FRONT_LEFT_HIGH_ZERO);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO);
      break;

    case 3:
      rear_left_low.write(REAR_LEFT_LOW_ZERO);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO);
      break;
  }
}

void walk_backward(int i) {
  switch (i) {
    case 0:
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO);

      front_left_low.write(FRONT_LEFT_LOW_ZERO - LEG_UP_DEGREE);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + WALK_DEGREE);

      rear_right_low.write(REAR_RIGHT_LOW_ZERO - LEG_UP_DEGREE);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO - WALK_DEGREE);
      break;

    case 1:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO);
      front_left_low.write(FRONT_LEFT_LOW_ZERO);
      break;

    case 2:
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + LEG_UP_DEGREE);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO - WALK_DEGREE);

      rear_left_low.write(REAR_LEFT_LOW_ZERO + LEG_UP_DEGREE);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO + WALK_DEGREE);

      front_left_high.write(FRONT_LEFT_HIGH_ZERO);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO);
      break;

    case 3:
      rear_left_low.write(REAR_LEFT_LOW_ZERO);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO);
      break;
  }
}

void rotate_clockwise(int i) {
  switch (i) {
    case 0:
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO);

      front_left_low.write(FRONT_LEFT_LOW_ZERO - LEG_UP_DEGREE);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - ROTATE_DEGREE);

      rear_right_low.write(REAR_RIGHT_LOW_ZERO - LEG_UP_DEGREE);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO - ROTATE_DEGREE);
      break;

    case 1:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO);
      front_left_low.write(FRONT_LEFT_LOW_ZERO);
      break;

    case 2:
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + LEG_UP_DEGREE);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO - ROTATE_DEGREE);

      rear_left_low.write(REAR_LEFT_LOW_ZERO + LEG_UP_DEGREE);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO - ROTATE_DEGREE);

      front_left_high.write(FRONT_LEFT_HIGH_ZERO);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO);
      break;

    case 3:
      rear_left_low.write(REAR_LEFT_LOW_ZERO);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO);
      break;
  }
}

void rotate_anticlockwise(int i) {
  switch (i) {
    case 0:
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO);

      front_left_low.write(FRONT_LEFT_LOW_ZERO - LEG_UP_DEGREE);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + ROTATE_DEGREE);

      rear_right_low.write(REAR_RIGHT_LOW_ZERO - LEG_UP_DEGREE);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO + ROTATE_DEGREE);
      break;

    case 1:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO);
      front_left_low.write(FRONT_LEFT_LOW_ZERO);
      break;

    case 2:
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + LEG_UP_DEGREE);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO + ROTATE_DEGREE);

      rear_left_low.write(REAR_LEFT_LOW_ZERO + LEG_UP_DEGREE);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO + ROTATE_DEGREE);

      front_left_high.write(FRONT_LEFT_HIGH_ZERO);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO);
      break;

    case 3:
      rear_left_low.write(REAR_LEFT_LOW_ZERO);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO);
      break;
  }
}

void hello(int i) {
  switch (i) {
    case 0:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 70);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      break;
    case 1:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      break;
    case 2:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 70);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      break;
    case 3:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      break;
  }
}

void happy(int i) {
  switch (i) {
    case 0:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 90);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + 90);
      rear_left_low.write(REAR_LEFT_LOW_ZERO + 90);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO + 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO + 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO - 45);
      break;
    case 1:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 90);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + 90);
      rear_left_low.write(REAR_LEFT_LOW_ZERO + 90);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO - 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO - 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO + 45);
      break;
    case 2:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 90);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + 90);
      rear_left_low.write(REAR_LEFT_LOW_ZERO + 90);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO + 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO + 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO - 45);
      break;
    case 3:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 90);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + 90);
      rear_left_low.write(REAR_LEFT_LOW_ZERO + 90);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO - 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO - 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO + 45);
      break;
  }
}

void dance(int i) {
  switch (i) {
    case 0:
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO + 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO + 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO - 45);

      front_left_low.write(FRONT_LEFT_LOW_ZERO - 45);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO - 45);
      rear_left_low.write(REAR_LEFT_LOW_ZERO - 45);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 45);
      break;
    case 1:
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO + 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO + 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO - 45);

      front_left_low.write(FRONT_LEFT_LOW_ZERO + 45);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + 45);
      rear_left_low.write(REAR_LEFT_LOW_ZERO + 45);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO + 45);
      break;
    case 2:
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO + 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO + 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO - 45);

      front_left_low.write(FRONT_LEFT_LOW_ZERO - 45);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO - 45);
      rear_left_low.write(REAR_LEFT_LOW_ZERO - 45);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 45);
      break;
    case 3:
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO + 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO + 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO - 45);

      front_left_low.write(FRONT_LEFT_LOW_ZERO + 45);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + 45);
      rear_left_low.write(REAR_LEFT_LOW_ZERO + 45);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO + 45);
      break;
  }
}

void come_to_me(int i) {
  switch (i) {
    case 0:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      break;
    case 1:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 70);
      break;
    case 2:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      break;
    case 3:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 70);
      break;
  }
}

void arm_up(int i) {
  switch (i) {
    case 0:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      break;
    case 1:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      break;
    case 2:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      break;
    case 3:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 90);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      break;
  }
}

void idk(int i) {
  switch (i) {
    case 0:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + 160);
      rear_left_low.write(REAR_LEFT_LOW_ZERO + 160);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 160);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO - 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO - 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO + 45);
      break;
    case 1:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + 160);
      rear_left_low.write(REAR_LEFT_LOW_ZERO + 160);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 160);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO - 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO - 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO + 45);
      break;
    case 2:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + 160);
      rear_left_low.write(REAR_LEFT_LOW_ZERO + 160);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 160);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO - 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO - 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO + 45);
      break;
    case 3:
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + 160);
      rear_left_low.write(REAR_LEFT_LOW_ZERO + 160);
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - 160);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO - 45);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO - 45);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO + 45);
      break;
  }
}

void set_hello() {
  if (!hello_mode) {
    forced_home();
    set_all_modes_false();
    set_hello_face();
    hello_mode = true;
    i = 0;
    out = millis();
  }
}

void set_happy() {
  if (!happy_mode) {
    forced_home();
    set_all_modes_false();
    set_happy_face();
    happy_mode = true;
    i = 0;
    out = millis();
  }
}

void set_dance() {
  if (!dance_mode) {
    forced_home();
    set_all_modes_false();
    set_dance_face();
    dance_mode = true;
    i = 0;
    out = millis();
  }
}

void set_come_to_me() {
  if (!come_to_me_mode) {
    forced_home();
    set_all_modes_false();
    set_come_to_me_face();
    come_to_me_mode = true;
    i = 0;
    out = millis();
  }
}

void set_arm_up() {
  if (!arm_up_mode) {
    forced_home();
    set_all_modes_false();
    set_arm_up_face();
    arm_up_mode = true;
    i = 0;
    out = millis();
  }
}

void set_idk() {
  if (!idk_mode) {
    forced_home();
    set_all_modes_false();
    set_idk_face();
    idk_mode = true;
    i = 0;
    out = millis();
  }
}

void set_hello_face() {
  oled.clear();
  oled.drawBitmap(0, 0, hello_face, 128, 64);
  oled.update();
}

void set_happy_face() {
  oled.clear();
  oled.drawBitmap(0, 0, happy_face, 128, 64);
  oled.update();
}

void set_come_to_me_face() {
  oled.clear();
  oled.drawBitmap(0, 0, come_to_me_face, 128, 64);
  oled.update();
}

void set_arm_up_face() {
  oled.clear();
  oled.drawBitmap(0, 0, arm_up_face, 128, 64);
  oled.update();
}

void set_dance_face() {
  oled.clear();
  oled.drawBitmap(0, 0, dance_face, 128, 64);
  oled.update();
}

void set_idk_face() {
  oled.clear();
  oled.drawBitmap(0, 0, idk_face, 128, 64);
  oled.update();
}

void set_default_face() {
  oled.clear();
  oled.drawBitmap(0, 0, default_face, 128, 64);
  oled.update();
}

void set_all_modes_false() {
  hello_mode = false;
  dance_mode = false;
  come_to_me_mode = false;
  arm_up_mode = false;
  happy_mode = false;
  idk_mode = false;
  set_default_face();
}

bool is_in_mode() {
  return hello_mode || dance_mode || come_to_me_mode || arm_up_mode || happy_mode || idk_mode;
}

void build(gh::Builder& b) {
  if (b.beginRow()) {
    b.Joystick(&pos, 0, 1).noLabel(1).color(gh::Colors::Red);
    b.endRow();
  }
  if (b.beginRow()) {
    b.Button().label("hello").attach(set_hello);
    b.Button().label("dance").attach(set_dance);
    b.endRow();
  }
  if (b.beginRow()) {
    b.Button().label("come to me").attach(set_come_to_me);
    b.Button().label("arm up").attach(set_arm_up);
    b.endRow();
  }
  if (b.beginRow()) {
    b.Button().label("happy").attach(set_happy);
    b.Button().label("idk").attach(set_idk);
    b.endRow();
  }
}


void setup() {
  Serial.begin(115200);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  front_left_high.attach(16, minUs, maxUs);
  front_left_high.setPeriodHertz(50);
  front_left_low.attach(13, minUs, maxUs);
  front_left_low.setPeriodHertz(50);
  front_right_high.attach(27, minUs, maxUs);
  front_right_high.setPeriodHertz(50);
  front_right_low.attach(14, minUs, maxUs);
  front_right_low.setPeriodHertz(50);
  rear_left_high.attach(25, minUs, maxUs);
  rear_left_high.setPeriodHertz(50);
  rear_left_low.attach(26, minUs, maxUs);
  rear_left_low.setPeriodHertz(50);
  rear_right_high.attach(32, minUs, maxUs);
  rear_right_high.setPeriodHertz(50);
  rear_right_low.attach(33, minUs, maxUs);
  rear_right_low.setPeriodHertz(50);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("Bulkarezik");
  hub.config(F("MyDevices"), F("ESP"));
  hub.onBuild(build);
  hub.begin();

  oled.init();
  set_default_face();


  soft_home();
  delay(1000);
}

void loop() {
  hub.tick();

  if (pos.y > pos.x && pos.y > -pos.x) {
    if (is_in_mode()) set_all_modes_false();
    static uint32_t tmr;
    if (millis() - tmr >= map(pos.y, 30, 255, 400, 150)) {
      tmr = millis();
      i++;
      if (i > 3) i = 0;
    }
    walk_forward(i);
  }
  if (pos.y < pos.x && pos.y < -pos.x) {
    if (is_in_mode()) set_all_modes_false();
    static uint32_t tmr;
    if (millis() - tmr >= map(pos.y, -30, -255, 400, 150)) {
      Serial.print(pos.y);
      tmr = millis();
      i++;
      if (i > 3) i = 0;
    }
    walk_backward(i);
  }
  if (pos.y < pos.x && pos.y > -pos.x) {
    if (is_in_mode()) set_all_modes_false();
    static uint32_t tmr;
    if (millis() - tmr >= map(pos.x, 30, 255, 400, 150)) {
      tmr = millis();
      i++;
      if (i > 3) i = 0;
    }
    rotate_clockwise(i);
  }
  if (pos.y > pos.x && pos.y < -pos.x) {
    if (is_in_mode()) set_all_modes_false();
    static uint32_t tmr;
    if (millis() - tmr >= map(-pos.x, 30, 255, 400, 150)) {
      tmr = millis();
      i++;
      if (i > 3) i = 0;
    }
    rotate_anticlockwise(i);
  }


  if (hello_mode) {
    hello(i);
    static gh::Timer tmr(400);
    if (tmr) {
      i++;
      if (i > 3) i = 0;
    }
    if (millis() - out > HELLO_MODE_TIME) {
      i = 0;
      hello_mode = false;
      set_default_face();
      if (!is_in_mode()) forced_home();
    }
  }

  if (happy_mode) {
    happy(i);
    static gh::Timer tmr(400);
    if (tmr) {
      i++;
      if (i > 3) i = 0;
    }
    if (millis() - out > HAPPY_MODE_TIME) {
      i = 0;
      happy_mode = false;
      set_default_face();
      if (!is_in_mode()) forced_home();
    }
  }

  if (dance_mode) {
    dance(i);
    static gh::Timer tmr(400);
    if (tmr) {
      i++;
      if (i > 3) i = 0;
    }
    if (millis() - out > DANCE_MODE_TIME) {
      i = 0;
      dance_mode = false;
      set_default_face();
      if (!is_in_mode()) forced_home();
    }
  }

  if (come_to_me_mode) {
    come_to_me(i);
    static gh::Timer tmr(200);
    if (tmr) {
      i++;
      if (i > 3) i = 0;
    }
    if (millis() - out > COME_TO_ME_MODE_TIME) {
      i = 0;
      come_to_me_mode = false;
      set_default_face();
      if (!is_in_mode()) forced_home();
    }
  }

  if (arm_up_mode) {
    arm_up(i);
    static gh::Timer tmr(200);
    if (tmr) {
      i++;
      if (i > 3) i = 0;
    }
    if (millis() - out > ARM_UP_MODE_TIME) {
      i = 0;
      arm_up_mode = false;
      set_default_face();
      if (!is_in_mode()) forced_home();
    }
  }

  if (idk_mode) {
    idk(i);
    static gh::Timer tmr(400);
    if (tmr) {
      i++;
      if (i > 3) i = 0;
    }
    if (millis() - out > IDK_MODE_TIME) {
      i = 0;
      idk_mode = false;
      set_default_face();
      if (!is_in_mode()) forced_home();
    }
  }

  static uint32_t tmr;
  if (pos.x == 0 && pos.y == 0 && millis() - tmr > 100 && !is_in_mode()) {
    tmr = millis();
    forced_home();
  }
}