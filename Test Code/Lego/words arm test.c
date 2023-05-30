//servos
int claw = 0;
int arm = 1;

//tower grab values
int high;
int low;
int open = 1200;
int galClose = 20;
int cubeClose = 50;

int highReady;
int lowReady;
int placeReady;

//motors
int base = 0;
int baseSpeed = 200;
float armDeg = 3.89;

int tower = 5;
int stack = 90;

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
void highGrab() {
  enable_servo(arm);
  enable_servo(claw);
  int speed = 3;
  int armPosition = get_servo_position(arm);
  int basePosition = gmpc(base);
  while(basePosition != tower || armPosition != highReady){
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
void lowGrab() {
  enable_servo(arm);
  enable_servo(claw);
  while(basePosition != tower || armPosition != lowReady){
    grabReadyUnlooped(0);
  }
  set_servo_position(claw, open);
  msleep(200);
  set_servo_position(arm, lowGrab);
  msleep(200);
  set_servo_position(claw, cubeClose);
  msleep(200);
}
//0 is low tower, 1 is high tower
void grabReady(int height){
  enable_servo(arm);
  enable_servo(claw);
  int speed = 3;
  int armPosition = get_servo_position(arm);
  int basePosition = gmpc(base);
    if(height == 0){
        while(basePosition != tower || armPosition != lowReady){
            grabReadyUnlooped(0);
            msleep(1);
        }
  set_servo_position(claw, open);
  msleep(200);
    }
  if(height == 1){
      while(basePosition != tower || armPosition != highReady){
        grabReadyUnlooped(1);
        msleep(1);
  }
}
//maybe use for moving arm as create switches towers    
void grabReadyUnlooped(int height){
  enable_servo(arm);
  enable_servo(claw);
  int speed = 3;
  int armPosition = get_servo_position(arm);
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
        }if(armPosition < lowReady){
            armPosition += 1;
            set_servo_position(armPosition);
            msleep(speed);
        }else if(armPosition > lowReady){
            armPosition += 1;
            set_servo_position(armPosition);
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
    }if(armPosition < highReady){
      armPosition += 1;
      set_servo_position(armPosition);
      msleep(speed);
    }else if(armPosition > highReady){
      armPosition += 1;
      set_servo_position(armPosition);
      msleep(speed);
    }
    }
}