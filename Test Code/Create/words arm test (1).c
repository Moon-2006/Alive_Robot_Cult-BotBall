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
int lPull = 1800;
int lTilt  = 1646;
int hPull = 1504;
int hTilt = 1928; 
int tuck = 1350;
//motors
int base = 0;
int baseSpeed = -250;
float armDeg = -5.4;
int tower = 90;
int stack = 15;
//touch sensor for calibration
int set = 2;
void reset();
void place();
void grabReady(int height);
void grabReadyUnlooped(int height);
void highGrab();
void lowGrab();
    
int main() {
  reset();
  msleep(2000);
  lowGrab(1);
  return 0;
}
void reset(){
  while(digital(set) == 0){
    mav(base, -baseSpeed);
    msleep(1);
  }
  ao();
  cmpc(base);
}
void place() {
  enable_servo(arm);
  enable_servo(claw);
  enable_servo(shoulder);
  while(basePosition != stack || armPosition != placeReady){
    if(basePosition < stack){
      basePosition += 2;
      mtp(base, baseSpeed, basePosition); 
    }else if(basePosition > stack){
      basePosition -= 2;
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
  enable_servo(shoulder);
  int armPosition = get_servo_position(arm);
  int basePosition = gmpc(base);
  int shoulderPosition = get_servo_position(shoulder);
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
  int speed = 1;
  int armPosition = get_servo_position(arm);
  int basePosition = gmpc(base);
  int shoulderPosition = get_servo_position(shoulder);
    if(height == 0){
        if(abs(basePosition) < tower*armDeg){
            mav(base, baseSpeed);
            msleep(1);
        }if(abs(basePosition) > tower*armDeg){
            mav(base, baseSpeed);
            msleep(1);
        }if(abs(basePosition) == tower*armDeg) {
            ao();
        }if(armPosition < low){
            armPosition += 1;
            set_servo_position(armPosition);
            msleep(speed);
        }if(armPosition > low){
            armPosition += 1;
            set_servo_position(armPosition);
            msleep(speed);
        }if(shoulderPosition < tuck){
            armPosition += 1;
            set_servo_position(shoulderPosition);
            msleep(speed);
        }if(shoulderPosition > tuck){
            armPosition += 1;
            set_servo_position(shoulderPosition);
            msleep(speed);
        }
    }
    
    else if(height == 1){
     if(abs(basePosition) < tower*armDeg){
            mav(base, baseSpeed);
            msleep(1);
        }if(abs(basePosition) > tower*armDeg){
            mav(base, baseSpeed);
            msleep(1);
        }if(abs(basePosition) == tower*armDeg) {
            ao();
        }if(armPosition < high){
            armPosition += 1;
            set_servo_position(armPosition);
            msleep(speed);
        }if(armPosition > high){
            armPosition += 1;
            set_servo_position(armPosition);
            msleep(speed);
        }if(shoulderPosition < tuck){
            armPosition += 1;
            set_servo_position(shoulderPosition);
            msleep(speed);
        }if(shoulderPosition > tuck){
            armPosition += 1;
            set_servo_position(shoulderPosition);
            msleep(speed);
        }
    }
    return;
}
