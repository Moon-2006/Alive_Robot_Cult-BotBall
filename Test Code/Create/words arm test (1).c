//servos
int claw = 2;
int arm = 1;
int shoulder = 0;

//tower grab values
int open = 1900;
int galClose = 950;
int cubeClose = 1144;

//arm values
int high = 213;
int low = 1826;
int placeReady;

//shoulder values
int lTilt  = 1646;
int pull = 1504;
int hTilt = 1928; 
int tuck = 1350;
//motors
int base = 0;
int baseSpeed = 200;
float armDeg = 5.4;
int tower = 90;
int stack = 15;

//touch sensor for calibration
int set = 0;

void reset();
void place();
void grabReady(int height);
void grabReadyUnlooped(int height);
void highGrab();
void lowGrab();
    
int main() {
  reset();
  msleep(1000);
  highGrab(0);
  msleep(2000);
  place();
  msleep(2000);
  reset();
  //move create to low tower
  msleep(20000);
  lowGrab();
  msleep(2000);
  place();
  msleep(2000);
  reset();
  return 0;
}
void reset(){
  while(digital(set) == 0){
    mav(base, baseSpeed);
    msleep(1);
  }freeze(base);
  cmpc(base);
}
void place() {
  enable_servo(arm);
  enable_servo(claw);
  int speed = 3;
  int armPosition = get_servo_position(arm);
  int basePosition = gmpc(base);
  while(basePosition != stack || armPosition != placeReady){
    if(basePosition < stack){
      basePosition += 1;
      mtp(base, baseSpeed, basePosition); 
    }else if(basePosition > stack){
      basePosition -= 1;
      mtp(base, baseSpeed, basePosition); 
    }else {
      freeze(base);
    }if(armPosition < placeReady){
      armPosition += 1;
      set_servo_position(armPosition);
      msleep(speed);
    }else if(armPosition > placeReady){
      armPosition += 1;
      set_servo_position(armPosition);
      msleep(speed);
    }
  }
  set_servo_position(claw, open);
  msleep(100);
  
}
void highGrab(int object) {
  enable_servo(arm);
  enable_servo(claw);
  enable_servo(shoulder);
  int speed = 3;
  int armPosition = get_servo_position(arm);
  int basePosition = gmpc(base);
  int shoulderPosition = get_servo_position(shoulder);
  while(basePosition != tower || armPosition != high || shoulderPosition != tuck){
    grabReadyUnlooped(1);
  }
  set_servo_position(claw, open);
  msleep(200);
  set_servo_position(arm, highGrab);
  msleep(200);
  if (object = 0){
    set_servo_position(claw, cubeClose);
  }else if(object = 1){
    set_servo_position(claw, galClose);   
  }msleep(200);
}
void lowGrab(int object) {
  enable_servo(arm);
  enable_servo(claw);
  while(basePosition != tower || armPosition != low || shoulderPosition != tuck){
    grabReadyUnlooped(0);
  }
  set_servo_position(claw, open);
  msleep(200);
  set_servo_position(shoulder, lTilt);
  msleep(200);
  set_servo_position(claw, cubeClose);
  msleep(200);
  set_servo_position(shoulder, lPull);
}

//maybe use for moving arm as create switches towers    
void grabReadyUnlooped(int height){
  enable_servo(arm);
  enable_servo(claw);
  int speed = 3;
  int shoulderPosition = get_servo_position(shoulder);
  int basePosition = gmpc(base);
    if(height == 0){
        if(basePosition < tower*armDeg){
            basePosition += 1;
            mtp(base, baseSpeed, basePosition); 
        }else if(basePosition > tower*armDeg){
            basePosition -= 1;
            mtp(base, baseSpeed, basePosition); 
        }else {
            freeze(base);
        }if(armPosition < low){
            armPosition += 1;
            set_servo_position(armPosition);
            msleep(speed);
        }else if(armPosition > low){
            armPosition += 1;
            set_servo_position(armPosition);
            msleep(speed);
        }}if(shoulderPosition < tuck){
            armPosition += 1;
            set_servo_position(shoulderPosition);
            msleep(speed);
        }else if(shoulderPosition > tuck){
            armPosition += 1;
            set_servo_position(shoulderPosition);
            msleep(speed);
        }
    }
    else if(height == 1){
        if(basePosition < tower*armDeg){
      basePosition += 1;
      mtp(base, baseSpeed, basePosition); 
    }else if(basePosition > tower*armDeg){
      basePosition -= 1;
      mtp(base, baseSpeed, basePosition); 
    }else {
      freeze(base);
    }if(armPosition < high){
            armPosition += 1;
            set_servo_position(armPosition);
            msleep(speed);
        }else if(armPosition > high){
            armPosition += 1;
            set_servo_position(armPosition);
            msleep(speed);
        }}if(shoulderPosition < tuck){
            armPosition += 1;
            set_servo_position(shoulderPosition);
            msleep(speed);
        }else if(shoulderPosition > tuck){
            armPosition += 1;
            set_servo_position(shoulderPosition);
            msleep(speed);
        }
    }
}
