#include <ESP32Servo.h>
#include <Arduino.h>
#define GH_INCLUDE_PORTAL
#include <GyverHub.h>

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
#define HELLO_MODE_TIME 5000
// билдер
void build(gh::Builder& b) {
  if (b.beginRow()) {
    b.Joystick(&pos, 0, 1).noLabel(1).color(gh::Colors::Red);
    b.endRow();
  }
  if (b.beginRow()) {
    b.Button().label("hello").attach(&hello_mode);
    b.Button().label("dance").attach(&dance_mode);
    b.endRow();
  }
  if (b.beginRow()) {
    b.Button().label("come to me").attach(&come_to_me_mode);
    b.Button().label("arm up").attach(&arm_up_mode);
    b.endRow();
  }
  if (b.beginRow()) {
    b.Button().label("happy").attach(&happy_mode);
    b.Button().label("idk").attach(&idk_mode);
    b.endRow();
  }
}

int i = 0;

void home() {  //TODO
  if (front_left_high.read() > FRONT_LEFT_HIGH_ZERO - MAX_DEVIATION && front_left_high.read() < FRONT_LEFT_HIGH_ZERO + MAX_DEVIATION) {
    front_left_low.write(FRONT_LEFT_LOW_ZERO - LEG_UP_DEGREE);
    front_left_high.write(FRONT_LEFT_HIGH_ZERO);
    front_left_low.write(FRONT_LEFT_LOW_ZERO);
  } else {
    if (front_left_low.read() > FRONT_LEFT_LOW_ZERO - MAX_DEVIATION && front_left_low.read() < FRONT_LEFT_LOW_ZERO + MAX_DEVIATION) front_left_low.write(FRONT_LEFT_LOW_ZERO);
  }

  if (front_right_high.read() > FRONT_RIGHT_HIGH_ZERO - MAX_DEVIATION && front_right_high.read() < FRONT_RIGHT_HIGH_ZERO + MAX_DEVIATION) {
    front_right_low.write(FRONT_RIGHT_LOW_ZERO - LEG_UP_DEGREE);
    front_right_high.write(FRONT_RIGHT_HIGH_ZERO);
    front_right_low.write(FRONT_RIGHT_LOW_ZERO);
  } else {
    if (front_right_low.read() > FRONT_RIGHT_LOW_ZERO - MAX_DEVIATION && front_right_low.read() < FRONT_RIGHT_LOW_ZERO + MAX_DEVIATION) front_right_low.write(FRONT_RIGHT_LOW_ZERO);
  }

  if (rear_left_high.read() > REAR_LEFT_HIGH_ZERO - MAX_DEVIATION && rear_left_high.read() < REAR_LEFT_HIGH_ZERO + MAX_DEVIATION) {
    rear_left_low.write(REAR_LEFT_LOW_ZERO + LEG_UP_DEGREE);
    rear_left_high.write(REAR_LEFT_HIGH_ZERO);
    rear_left_low.write(REAR_LEFT_LOW_ZERO);
  } else {
    if (rear_left_low.read() > REAR_LEFT_LOW_ZERO - MAX_DEVIATION && rear_left_low.read() < REAR_LEFT_LOW_ZERO + MAX_DEVIATION) rear_left_low.write(REAR_LEFT_LOW_ZERO);
  }

  if (rear_right_high.read() > REAR_RIGHT_HIGH_ZERO - MAX_DEVIATION && rear_right_high.read() < REAR_RIGHT_HIGH_ZERO + MAX_DEVIATION) {
    rear_right_low.write(REAR_RIGHT_LOW_ZERO + LEG_UP_DEGREE);
    rear_right_high.write(REAR_RIGHT_HIGH_ZERO);
    rear_right_low.write(REAR_RIGHT_LOW_ZERO);
  } else {
    if (rear_right_low.read() > REAR_RIGHT_LOW_ZERO - MAX_DEVIATION && rear_right_low.read() < REAR_RIGHT_LOW_ZERO + MAX_DEVIATION) rear_right_low.write(REAR_RIGHT_LOW_ZERO);
  }
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
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - LEG_UP_DEGREE);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      break;
    case 1:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - LEG_UP_DEGREE);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 70);
      break;
    case 2:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - LEG_UP_DEGREE);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 160);
      break;
    case 3:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO - LEG_UP_DEGREE);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO + 45);
      front_left_low.write(FRONT_LEFT_LOW_ZERO - 70);
      break;
  }
}

void set_all_modes_false() {
  hello_mode = false;
  dance_mode = false;
  come_to_me_mode = false;
  arm_up_mode = false;
  happy_mode = false;
  idk_mode = false;
}

bool is_in_mode() {
  return hello_mode && dance_mode && come_to_me_mode && arm_up_mode && happy_mode && idk_mode;
}

void setup() {
  Serial.begin(115200);

  front_left_high.attach(12);
  front_left_low.attach(13);
  front_right_high.attach(27);
  front_right_low.attach(14);
  rear_left_high.attach(25);
  rear_left_low.attach(26);
  rear_right_high.attach(32);
  rear_right_low.attach(33);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("Bulkarezik");
  hub.config(F("MyDevices"), F("ESP"));
  hub.onBuild(build);
  hub.begin();

  home();
  delay(1000);
}

void loop() {
  hub.tick();

  if (pos.y > pos.x && pos.y > -pos.x) {
    if (is_in_mode) set_all_modes_false();
    static uint32_t tmr;
    if (millis() - tmr >= map(pos.y, 30, 255, 400, 150)) {
      tmr = millis();
      i++;
      if (i > 3) i = 0;
    }
    walk_forward(i);
  }
  if (pos.y < pos.x && pos.y < -pos.x) {
    if (is_in_mode) set_all_modes_false();
    static uint32_t tmr;
    if (millis() - tmr >= map(pos.y, -30, -255, 400, 150)) {
      tmr = millis();
      i++;
      if (i > 3) i = 0;
    }
    walk_backward(i);
  }
  if (pos.y < pos.x && pos.y > -pos.x) {
    if (is_in_mode) set_all_modes_false();
    static uint32_t tmr;
    if (millis() - tmr >= map(pos.x, 30, 255, 400, 150)) {
      tmr = millis();
      i++;
      if (i > 3) i = 0;
    }
    rotate_clockwise(i);
  }
  if (pos.y > pos.x && pos.y < -pos.x) {
    if (is_in_mode) set_all_modes_false();
    static uint32_t tmr;
    if (millis() - tmr >= map(-pos.x, 30, 255, 400, 150)) {
      tmr = millis();
      i++;
      if (i > 3) i = 0;
    }
    rotate_anticlockwise(i);
  }


  if (hello_mode) {
    static uint32_t tmr, out;
    if (millis() - tmr >= 400) {
      tmr = millis();
      i++;
      if (i > 3) i = 0;
    }
    if (millis() - out >= HELLO_MODE_TIME) {
      out = millis();
      hello_mode = false;
    }
    hello(i);
  }

  static uint32_t tmr;
  if (pos.x == 0 && pos.y == 0 && millis() - tmr > 250 && !is_in_mode()) {
    tmr = millis();
    home();
  }
}