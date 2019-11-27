#include "LedControl.h"
#include "data.h"

//del[] = {20,50,80};

int Laser_pin = 3;
int t = 0;
int toBlink[] = {0, 2, 4, 7, 10, 29, 31, 32, 57, 58, 59, 60};
static int current_emotion = 0;
boolean state = false;
int intense = 0;
LedControl LeftEye = LedControl(12, 10 , 11, 1); //(DATA, CLK, CS, no of daisychain)
LedControl RightEye = LedControl(9, 7, 8 , 1);
LedControl Lips  = LedControl(6, 4, 5, 4);

void chooser(int i);
void Bbye(int del);
void wakeup(int del);
void Blink(int del);
boolean isBlinkable(int data);
void cleardisp(boolean lt = true, boolean rt = true, boolean lp = true);

void startface() {
  LeftEye.shutdown(0, false);
  RightEye.shutdown(0, false);
  
  LeftEye.setIntensity(0, intense);
  RightEye.setIntensity(0, intense);


  leftEye.clearDisplay(0);
  RightEye.clearDisplay(0);
  for (int i = 0; i < 4; i++) {
    Lips.shutdown(i, false);
    Lips.setIntensity(i, intense);
    Lips.clearDisplay(i);
  }
    
  chooser(61);
  wakeup(300);
  Blink(65);
  for (int j = 1; j < 3; j++) {
    for (int i = 0; i < 8; i++) {
      Lips.setRow(j, i, lp_D_1[2 - j][i]);
    }
  }
}

void setup() {
  startface();
  pinMode(Laser_pin, OUTPUT);
  digitalWrite(Laser_pin, HIGH);
  Serial.begin(9600);
  Serial.println("Ready...");
}

void loop() {
  while (!Serial.available()) {
    delay(10);
    t++;
    if (t > 250 && isBlinkable(current_emotion)) {
      Blink(30);
      if (current_emotion != 61)
        chooser(current_emotion);
      t = 0;
    }
  }
  int i = Serial.parseInt();
  switch (i) {
    case -1:
      if (state)
        digitalWrite(Laser_pin, HIGH);
      else
        digitalWrite(Laser_pin, LOW);
      state = !state;
      Serial.println(state);
      break;
    case -2:
      while (!Serial.available());
      intense = Serial.parseInt();
      intense = intense < 15 ? intense : 0;
      startface();
      break;
    default:
      chooser(i);
  }
}

void chooser(int i) {
  switch (i) {
    case 61://normal
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
        RightEye.setRow(0, i, eye_normal[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_D_1[2 - j][i]);
        }
      }
      //      Serial.println("case 0 innitiated");
      current_emotion = 0;
      break;
    case 1://:|
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
        RightEye.setRow(0, i, eye_normal[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_pipe[2 - j][i]);
        }
      }
      Serial.println("case 1 innitiated");
      Blink(25);
      delay(30);
      Blink(25);
      current_emotion = 1;
      delay(5000);
      chooser(61);
      break;
    case 2://D:
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
        RightEye.setRow(0, i, eye_normal[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_sad1[2 - j][i]);
        }
      }
      Serial.println("case 2 innitiated");
      current_emotion = 2;

      break;
    case 3://:O
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
        RightEye.setRow(0, i, eye_normal[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_O[2 - j][i]);
        }
      }
      Serial.println("case 3 innitiated");
      current_emotion = 3;

      delay(400);
      Blink(25);
      delay(500);
      Blink(25);
      delay(500);
      chooser(61);
      break;
    case 4://:V
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
        RightEye.setRow(0, i, eye_normal[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_V[2 - j][i]);
        }
      }
      Serial.println("case 4 innitiated");
      current_emotion = 4;

      break;
    case 5://^^<3
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_happy[i]);
        RightEye.setRow(0, i, eye_happy[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_kiss[2 - j][i]);
        }
      }
      Serial.println("case 5 innitiated");
      current_emotion = 5;
      delay(5000);
      chooser(61);
      break;
    case 6://^^P
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_happy[i]);
        RightEye.setRow(0, i, eye_happy[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_P[2 - j][i]);
        }
      }
      Serial.println("case 6 innitiated");
      current_emotion = 6;
      delay(5000);
      chooser(61);
      break;
    case 7://^^D
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_happy[i]);
        RightEye.setRow(0, i, eye_happy[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_D_1[2 - j][i]);
        }
      }
      Serial.println("case 7 innitiated");
      current_emotion = 7;

      break;
    case 8://^^W
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_happy[i]);
        RightEye.setRow(0, i, eye_happy[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_Pout[2 - j][i]);
        }
      }
      Serial.println("case 8 innitiated");
      current_emotion = 8;
      delay(5000);
      chooser(61);
      break;
    case 9://^^V
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_happy[i]);
        RightEye.setRow(0, i, eye_happy[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_V[2 - j][i]);
        }
      }
      Serial.println("case 9 innitiated");
      current_emotion = 9;
      delay(5000);
      chooser(61);
      break;
    case 10://^^)
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_happy[i]);
        RightEye.setRow(0, i, eye_happy[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_smile1[2 - j][i]);
        }
      }
      Serial.println("case 10 innitiated");
      current_emotion = 10;

      break;
    case 11://:)
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
        RightEye.setRow(0, i, eye_normal[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_smile1[2 - j][i]);
        }
      }
      Serial.println("case 11 innitiated");
      current_emotion = 11;
      delay(5000);
      chooser(61);
      break;

    case 17://:W
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
        RightEye.setRow(0, i, eye_normal[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_Pout[2 - j][i]);
        }
      }
      Serial.println("case 17 innitiated");
      current_emotion = 17;

      Blink(60);
      delay(200);
      Blink(50);
      delay(5000);
      chooser(61);
      break;
    case 18://:<3
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
        RightEye.setRow(0, i, eye_normal[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_kiss[2 - j][i]);
        }
      }
      Serial.println("case 18 innitiated");
      current_emotion = 18;
      Blink(50);
      delay(200);
      Blink(50);
      delay(7000);
      chooser(61);
      break;
    case 19://VVV
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_V[i]);
        RightEye.setRow(0, i, eye_V[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_V[2 - j][i]);
        }
      }
      Serial.println("case 19 innitiated");
      current_emotion = 19;
      delay(5000);
      chooser(61);
      break;
    case 20://XD
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_XD[1][i]);
        RightEye.setRow(0, i, eye_XD[0][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_D_1[2 - j][i]);
        }
      }
      Serial.println("case 20 innitiated");
      current_emotion = 20;
      delay(5000);
      chooser(61);
      break;
    case 21://DX
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_XD[1][i]);
        RightEye.setRow(0, i, eye_XD[0][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_sad1[2 - j][i]);
        }
      }
      Serial.println("case 21 innitiated");
      current_emotion = 21;
      delay(5000);
      chooser(61);
      break;
    case 22://X|
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_XD[1][i]);
        RightEye.setRow(0, i, eye_XD[0][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_pipe[2 - j][i]);
        }
      }
      Serial.println("case 22 innitiated");
      current_emotion = 22;
      delay(5000);
      chooser(61);
      break;
    case 23://eyeroll D
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_roll[i]);
        RightEye.setRow(0, i, eye_roll[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_D_1[2 - j][i]);
        }
      }
      Serial.println("case 23 innitiated");
      current_emotion = 23;
      delay(5000);
      chooser(61);
      break;
    case 24://eyeroll smirk
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_roll[i]);
        RightEye.setRow(0, i, eye_roll[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_smirk[2 - j][i]);
        }
      }
      Serial.println("case 24 innitiated");
      current_emotion = 24;
      delay(5000);
      chooser(61);
      break;
    case 25://D eyeroll
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_roll[i]);
        RightEye.setRow(0, i, eye_roll[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_sad1[2 - j][i]);
        }
      }
      Serial.println("case 25 innitiated");
      current_emotion = 25;
      delay(5000);
      chooser(61);
      break;
    case 26://eyeroll v
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_roll[i]);
        RightEye.setRow(0, i, eye_roll[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_V[2 - j][i]);
        }
      }
      Serial.println("case 26 innitiated");
      current_emotion = 26;
      delay(5000);
      chooser(61);
      break;
    case 27://eyeroll W
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_roll[i]);
        RightEye.setRow(0, i, eye_roll[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_Pout[2 - j][i]);
        }
      }
      Serial.println("case 27 innitiated");
      current_emotion = 27;
      delay(5000);
      chooser(61);
      break;
    case 28://:{
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
        RightEye.setRow(0, i, eye_normal[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_chinup[2 - j][i]);
        }
      }
      Serial.println("case 28 innitiated");
      current_emotion = 28;
      delay(5000);
      chooser(61);
      break;
    case 29://<:D
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_slantbrow[0][i]);
        RightEye.setRow(0, i, eye_slantbrow[1][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_D_1[2 - j][i]);
        }
      }
      Serial.println("case 29 innitiated");
      current_emotion = 29;

    case 30://>:D
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_slantbrow[1][i]);
        RightEye.setRow(0, i, eye_slantbrow[0][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_D_1[2 - j][i]);
        }
      }
      Serial.println("case 30 innitiated");
      current_emotion = 30;
      delay(5000);
      chooser(61);
      break;
    case 31://D:>
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_slantbrow[0][i]);
        RightEye.setRow(0, i, eye_slantbrow[1][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_sad1[2 - j][i]);
        }
      }
      Serial.println("case 31 innitiated");
      current_emotion = 31;

      break;
    case 32://D:<
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_slantbrow[1][i]);
        RightEye.setRow(0, i, eye_slantbrow[0][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_sad1[2 - j][i]);
        }
      }
      Serial.println("case 32 innitiated");
      current_emotion = 32;

      break;
    case 33://>:W
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_slantbrow[1][i]);
        RightEye.setRow(0, i, eye_slantbrow[0][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_Pout[2 - j][i]);
        }
      }
      Serial.println("case 33 innitiated");
      current_emotion = 33;
      delay(5000);
      chooser(61);
      break;
    case 34://<:W
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_slantbrow[0][i]);
        RightEye.setRow(0, i, eye_slantbrow[1][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_Pout[2 - j][i]);
        }
      }
      Serial.println("case 34 innitiated");
      current_emotion = 34;
      delay(5000);
      chooser(61);
      break;
    case 35://):|
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_suspecious[1][i]);
        RightEye.setRow(0, i, eye_suspecious[0][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_pipe[2 - j][i]);
        }
      }
      Serial.println("case 35 innitiated");
      current_emotion = 35;
      delay(5000);
      chooser(61);
      break;
    case 36://-_-
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_doubt[i]);
        RightEye.setRow(0, i, eye_doubt[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_pipe[2 - j][i]);
        }
      }
      Serial.println("case 36 innitiated");
      current_emotion = 36;
      delay(5000);
      chooser(61);
      break;
    case 37://|D
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_doubt[i]);
        RightEye.setRow(0, i, eye_doubt[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_D_1[2 - j][i]);
        }
      }
      Serial.println("case 37 innitiated");
      current_emotion = 37;
      delay(5000);
      chooser(61);
      break;
    case 38://D|
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_doubt[i]);
        RightEye.setRow(0, i, eye_doubt[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_sad1[2 - j][i]);
        }
      }
      Serial.println("case 38 innitiated");
      current_emotion = 38;
      //no Blink
      break;
    case 39://<3<3D
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_love[i]);
        RightEye.setRow(0, i, eye_love[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_D_1[2 - j][i]);
        }
      }
      Serial.println("case 39 innitiated");
      current_emotion = 39;
      //      delay(5000);
      //      chooser(61);
      break;
    case 40://<3<3P
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_love[i]);
        RightEye.setRow(0, i, eye_love[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_P[2 - j][i]);
        }
      }
      Serial.println("case 40 innitiated");
      current_emotion = 40;
      delay(7000);
      chooser(61);
      break;
    case 41://<3<3W
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_love[i]);
        RightEye.setRow(0, i, eye_love[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_Pout[2 - j][i]);
        }
      }
      Serial.println("case 41 innitiated");
      current_emotion = 41;
      delay(5000);
      chooser(61);
      break;
    case 42://<3<3V
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_love[i]);
        RightEye.setRow(0, i, eye_love[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_V[2 - j][i]);
        }
      }
      Serial.println("case 42 innitiated");
      current_emotion = 42;
      delay(5000);
      chooser(61);
      break;
    case 43://<3<3|
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_love[i]);
        RightEye.setRow(0, i, eye_love[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_pipe[2 - j][i]);
        }
      }
      Serial.println("case 43 innitiated");
      current_emotion = 43;
      delay(5000);
      chooser(61);
      break;
    case 44://<3<3O
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_love[i]);
        RightEye.setRow(0, i, eye_love[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_O[2 - j][i]);
        }
      }
      Serial.println("case 44 innitiated");
      current_emotion = 44;
      delay(5000);
      chooser(61);
      break;
    case 45://<3<3KISS
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_love[i]);
        RightEye.setRow(0, i, eye_love[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_kiss[2 - j][i]);
        }
      }
      Serial.println("case 45 innitiated");
      current_emotion = 45;
      delay(5000);
      chooser(61);
      break;
    case 47://<3<3{
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_love[i]);
        RightEye.setRow(0, i, eye_love[i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_chinup[2 - j][i]);
        }
      }
      Serial.println("case 47 innitiated");
      current_emotion = 47;
      delay(5000);
      chooser(61);
      break;
    case 48://FUNNY
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_funny[2][i]);
        RightEye.setRow(0, i, eye_funny[3][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_chinup[2 - j][i]);
        }
      }
      Serial.println("case 48 innitiated");
      current_emotion = 48;
      delay(5000);
      chooser(61);
      break;
    case 49://FUNNY
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_funny[4][i]);
        RightEye.setRow(0, i, eye_funny[5][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_chinup[2 - j][i]);
        }
      }
      Serial.println("case 49 innitiated");
      current_emotion = 49;
      delay(5000);
      chooser(61);
      break;
    case 50://FUNNY
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_funny[3][i]);
        RightEye.setRow(0, i, eye_funny[2][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_chinup[2 - j][i]);
        }
      }
      Serial.println("case 50 innitiated");
      current_emotion = 50;
      delay(5000);
      chooser(61);
      break;
    case 51://FUNNY
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_funny[0][i]);
        RightEye.setRow(0, i, eye_funny[1][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_chinup[2 - j][i]);
        }
      }
      Serial.println("case 51 innitiated");
      current_emotion = 51;
      delay(5000);
      chooser(61);
      break;
    case 52://FUNNY
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_funny[2][i]);
        RightEye.setRow(0, i, eye_funny[3][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_pipe[2 - j][i]);
        }
      }
      Serial.println("case 52 innitiated");
      current_emotion = 52;
      delay(5000);
      chooser(61);
      break;
    case 53://FUNNY
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_left_right_up_down[0][i]);
        RightEye.setRow(0, i, eye_left_right_up_down[1][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_chinup[2 - j][i]);
        }
      }
      Serial.println("case 53 innitiated");
      current_emotion = 53;
      delay(5000);
      chooser(61);
      break;
    case 54://FUNNY
      cleardisp();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_funny[4][i]);
        RightEye.setRow(0, i, eye_funny[5][i]);
      }
      for (int j = 1; j < 3; j++) {
        for (int i = 0; i < 8; i++) {
          Lips.setRow(j , i, lp_pipe[2 - j][i]);
        }
      }
      Serial.println("case 54 innitiated");
      current_emotion = 54;
      delay(5000);
      chooser(61);
      break;
    case 57:
      cleardisp(true, true, false);
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_left_right_up_down[0][i]);
        RightEye.setRow(0, i, eye_left_right_up_down[0][i]);
      }
      Serial.println("case 57 innitiated");
      current_emotion = 57;
      break;
    case 58:
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_left_right_up_down[1][i]);
        RightEye.setRow(0, i, eye_left_right_up_down[1][i]);
      }
      Serial.println("case 58 innitiated");
      current_emotion = 58;
      break;
    case 59:
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_left_right_up_down[2][i]);
        RightEye.setRow(0, i, eye_left_right_up_down[2][i]);
      }
      Serial.println("case 59 innitiated");
      current_emotion = 59;
      break;
    case 60:
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_left_right_up_down[3][i]);
        RightEye.setRow(0, i, eye_left_right_up_down[3][i]);
      }
      Serial.println("case 60 innitiated");
      current_emotion = 60;
      break;
    case 195:
      wakeup(350);
      delay(80);
      chooser(61);
      delay(40);
      Blink(30);
      delay(20);
      chooser(61);
      delay(20);
      Blink(20);
      delay(40);
      chooser(61);
      break;
    case 196:
      Blink(20);
      chooser(current_emotion);
      break;
    //    case 197:
    //      updating();
    //      chooser(61);
    //      break;
    case 198:
      //      batAnEye();
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
        RightEye.setRow(0, i, eye_normal[i]);
      }
      delay(200);
      for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 8; i++) {
          LeftEye.setRow(0, i, eye_wakeup[j][i]); // FOR LETTER
        }
        delay(34);
      }
      delay(34);
      LeftEye.clearDisplay(0);
      delay(34);
      for (int j = 4; j >= 0; j-- ) {
        for (int i = 0; i < 8; i++)
          LeftEye.setRow(0, i, eye_wakeup[j][i]); // FOR LETTER
        delay(34);
      }
      delay(34);
      for (int i = 0; i < 8; i++) {
        LeftEye.setRow(0, i, eye_normal[i]);
      }
      delay(34);
      chooser(current_emotion);
      Serial.println("case 198 innitiated");
      break;
    default:
      Serial.println("Error:wrong emotion code");
//      Bbye(50);
//      cleardisp();
//      while (!Serial.available());
//      t = 0;
  }
  delay(20);
}
void Bbye(int del) {
  for (int i = 0; i < 8; i++) {
    LeftEye.setRow(0, i, eye_normal[i]);
    RightEye.setRow(0, i, eye_normal[i]);
  }
  delay(del);
  for (int j = 0; j < 5; j++) {
    //    cleardisp(true, true, false);
    for (int i = 0; i < 8; i++) {
      LeftEye.setRow(0, i, eye_wakeup[j][i]); // FOR LETTER
      RightEye.setRow(0, i, eye_wakeup[j][i]); // FOR LETTER
    }
    delay(del);
  }
  LeftEye.clearDisplay(0);
  RightEye.clearDisplay(0);
}
void wakeup(int del) {
  for (int j = 4; j >= 0; j-- ) {
    //    cleardisp(true, true, false);
    for (int i = 0; i < 8; i++) {
      LeftEye.setRow(0, i, eye_wakeup[j][i]); // FOR LETTER
      RightEye.setRow(0, i, eye_wakeup[j][i]); // FOR LETTER
    }
    delay(del);
  }
  delay(del);
  for (int i = 0; i < 8; i++) {
    LeftEye.setRow(0, i, eye_normal[i]);
    RightEye.setRow(0, i, eye_normal[i]);
  }
}
void Blink(int del) {
  Bbye(del);
  delay(del);
  wakeup(del);
}
boolean isBlinkable(int data) {
  for (int i = 0; i < sizeof(toBlink); i++) {
    if (toBlink[i] == data)
      return true;
  }
  return false;
}
void cleardisp(boolean lt = true, boolean rt = true, boolean lp = true) {
  if (lt)
    LeftEye.clearDisplay(0);
  if (rt)
    RightEye.clearDisplay(0);
  if (lp) {
    for (int i = 0; i < 4; i++) {
      Lips.clearDisplay(i);
    }
  }
}
