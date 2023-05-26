#include <kipr/wombat.h>


void driveCM(int dist, int speed);
void turnLDeg(int dist, int speed);   
void turnRDeg(int dist, int speed);   
void fwd2tape();
void rail2tape();
void trnL2tape();
void trnR2tape();
void greenDrives();
void followTape(int dist, int speed);
void thing();

void set_position(int speed, int pos[4]);
int sum(int array[]);
float c(int port);
void grab_drive();
void freePoints();
void dontDQ();
void followTape2Bump(int speed);


int posH[4] = {1000, 1000, 1000, 1000};
int anglCount = 0;
int rM = 0;
int lM = 0;


int main()
{
    create_connect();  
    enable_servos();

    //Positioning arm inside box and waiting for light trigger
    
    posH[0] = 500; //Vertical Base
    posH[1] = 2047; //Wrist
    posH[2] = 500;  // Claw
    posH[3] = 1200; //Horizontal Base
    set_position(10, posH);
	msleep(500);
    wait_for_light(0);
    shut_down_in(120);
    dontDQ(); //Moves arm to active position 
    
    
    //Aligns with right edge tape of watch floor and waits for LegoBot to clear backup room
    fwd2tape();
    msleep(6000);
    
    rail2tape(); //Move to backup room
    
    driveCM(3, -50);
    
    msleep(45000); //Wait for LegoBot to clear all poms
    
    //Grab first drive
	posH[0] = 1600; //Vertical Base
    posH[1] = 1000; //Wrist
    posH[2] = 1700;  // Claw
    posH[3] = 400; //Horizontal Base
    set_position(15, posH);
    posH[3] = 100; //Horizontal Base
    set_position(15, posH);
    posH[1] = 1700; //Wrist
    posH[0] = 850; //Vertical Base
    set_position(15, posH);
    posH[2] = 450; //Claw
    set_position(15, posH);
    posH[0] = 1100; //Vertical Base
    posH[1] = 1100; //Wrist7
    set_position(15, posH);
    posH[0] = 1500; //Vertical Base
    set_position(15, posH);
    

    //Drop first drive
    driveCM(3, 50);
    trnL2tape();
    posH[3] = 1500; //Horizontal Base
    set_position(15, posH);
    posH[0] = 300; //Vertical Base   
    posH[1] = 100; //Wrist
    set_position(15, posH); 
    posH[2] = 1000; //Claw
    set_position(15, posH);
    msleep(500);
    posH[0] = 1200; //Vertical Base
    set_position(15, posH);
    
    posH[0] = 1000; //Vertical Base
    posH[1] = 1300; //Wrist
    set_position(15, posH);
    
    turnRDeg(90, 50);
    thing();  // Grab drive 2
    trnL2tape(); // Drop drive 2
    posH[3] = 1400; //Horizontal Base
    set_position(15, posH);
    posH[0] = 500; //Vertical Base
    posH[1] = 500; //Wrist
    set_position(15, posH); 
    posH[2] = 900; //Claw
    set_position(15, posH);
    posH[0] = 1200; //Vertical Base
    set_position(15, posH);
    
    //Reposition
    msleep(2000);
    turnRDeg(5, 20);
    fwd2tape();
    turnRDeg(125, 100);
    trnR2tape();
    followTape(10, 75);
    create_stop();
    
    //Grab final drive
    grab_drive();
    
    //drop final drive
    posH[3] = 20; //Horizontal Base
    set_position(15, posH);
    posH[0] = 700; //Vertical Base
    posH[1] = 700; //Wrist
    set_position(15, posH); 
    posH[2] = 900; //Claw
    set_position(15, posH);
    turnLDeg(25, 50);
    create_stop();
    
    msleep(500);
    disable_servos();    
    create_disconnect();
    return 0;
}

void thing(){
	posH[0] = 1600; //Vertical Base
    posH[1] = 1100; //Wrist
    posH[2] = 1700;  // Claw
    posH[3] = 400; //Horizontal Base
    set_position(15, posH);
    posH[3] = 80; //Horizontal Base
    set_position(15, posH);
    posH[1] = 1200; //Wrist
    posH[0] = 650; //Vertical Base
    set_position(15, posH);
    posH[3] = 80; //Horizontal Base
    set_position(15, posH);
    posH[2] = 400; //Claw
    set_position(15, posH);
    driveCM(1, 50);
    msleep(2000);
    posH[0] = 1200; //Vertical Base
    //posH[1] = 1200; //Wrist
    set_position(15, posH);    
    posH[0] = 1500; //Vertical Base
    set_position(15, posH);
    driveCM(1, -50);


}
void dontDQ(){
    posH[3] = 900; //Horizontal Base
    set_position(10, posH);
    posH[0] = 900; //Vertical Base
    posH[1] = 1700; //Wrist
    posH[2] = 700;  // Claw
    set_position(10, posH);
}
void freePoints(){
    posH[0] = 250;
    posH[1] = 250;
    posH[3] = 300;
    set_position(10, posH);
    trnL2tape();
    msleep(500);
    posH[0] = 350;
    set_position(10, posH);
    turnRDeg(80, 70);
    msleep(3000);
}
void grab_drive(){
    
    posH[0] = 1200; //Vertical Base
    posH[1] = 900; //Wrist
    posH[2] = 1200;  // Claw
    posH[3] = 400; //Horizontal Base
    set_position(15, posH);
    posH[0] = 600; //Vertical Base
    set_position(15, posH);
    
    msleep(1000);
    
    posH[2] = 400;
    posH[3] = 450;
    set_position(10, posH);
    
    create_drive_direct(20, 20);
    msleep(200);
    create_stop();
    posH[0] = 1600;
    set_position(10, posH);
}
void greenDrives(){
    
    camera_update();
    if(get_object_bbox_width(1, 1) > 50)
    {
        int posD[4] = {1500, 1500, 450, c(3)};
    	set_position(10, posD);
    }
}

void driveCM(int dist, int speed){
    set_create_distance(0);
    dist = (dist * 1) * 10;
    while(abs(get_create_distance()) < dist)
    {
        create_drive_direct(speed, speed);
        msleep(10);
        printf("driving\n");
        printf("dist: %d\n", dist);
        printf("dist: %d\n", (dist - get_create_distance()));
    }
    create_stop();
}

void followTape(int dist, int speed){
    set_create_distance(0);
    dist = dist * 10;
    while(get_create_distance() < dist)
    {
        if(get_create_rfcliff_amt()>2000 && get_create_lfcliff_amt()>2000)
        {
            rM = 1;
            lM = 1;
        }else{
        if(get_create_rfcliff_amt()>2000)
        {
            rM = 1;
            lM = 0.8;
        }
        if(get_create_lfcliff_amt()>2000)
        {
            lM = 1;
            rM = 0.8;
        }
        }
        create_drive_direct((speed * lM), (speed * rM));
        msleep(10);
    }
    create_stop();
}
void followTape2Bump(int speed){
    set_create_distance(0);
    while(get_create_lbump() == 0)
    {
        if(get_create_rfcliff_amt()>2000 && get_create_lfcliff_amt()>2000)
        {
            rM = 1;
            lM = 1;
        }else{
        if(get_create_rfcliff_amt()>2000)
        {
            rM = 1;
            lM = 0.8;
        }
        if(get_create_lfcliff_amt()>2000)
        {
            lM = 1;
            rM = 0.8;
        }
        }
        create_drive_direct((speed * lM), (speed * rM));
        msleep(10);
    }
    create_stop();
}

void turnLDeg(int dist, int speed){
    set_create_total_angle(0);
    while(get_create_total_angle() < dist)
    {
        create_drive_direct(-speed, speed);
        msleep(10);
        printf("driving\n");
        printf("dist: %d\n", dist);
        printf("dist: %d\n", (dist - get_create_distance()));
    }
    create_stop();
}

void turnRDeg(int dist, int speed)
{
    set_create_total_angle(0);
    while(abs(get_create_total_angle()) < abs(dist))
    {
        create_drive_direct(speed, -speed);
        msleep(10);
        printf("driving\n");
        printf("dist: %d\n", dist);
        printf("dist: %d\n", (dist - get_create_distance()));
    }
    create_stop();

}

void fwd2tape()
{
    while(get_create_lcliff_amt()>2000 && get_create_rcliff_amt()>2000)
    {
        create_drive_direct(180 , 150);
        if(get_create_lbump()==1){
            create_drive_direct(150, 90);
            msleep(20);
        }
        if(get_create_rbump()==1){
            create_drive_direct(90, 150);
            msleep(20);
        }
    }
    while(get_create_lcliff_amt()>2000 || get_create_rcliff_amt()>2000)
    {
        rM = -0.1;
        lM = -0.1;
        if(get_create_rcliff_amt()>2000)
        {
            rM = 1;
        }
        if(get_create_lcliff_amt()>2000)
        {
            lM = 1;
        }
        create_drive_direct((85 * lM), (75 * rM));
        msleep(10);
    }
    driveCM(7, 100);
}

void rail2tape()
{
    while(get_create_lcliff_amt()>2000 && get_create_rcliff_amt()>2000)
    {
        create_drive_direct(150 , 130);
        if(get_create_lbump()==1){
            create_drive_direct(150, 100);
            msleep(20);
        }
        if(get_create_rbump()==1){
            create_drive_direct(100, 150);
            msleep(20);
        }
    }
    while(get_create_lcliff_amt()>2000 || get_create_rcliff_amt()>2000)
    {
        rM = -0.1;
        lM = -0.1;
        if(get_create_rcliff_amt()>2000)
        {
            rM = 1;
        }
        if(get_create_lcliff_amt()>2000)
        {
            lM = 1;
        }
        create_drive_direct((75 * lM), (75 * rM));
        msleep(10);
    }
    driveCM(7, 100);
}


void trnL2tape()
{
    create_drive_direct(-100, 100);
    msleep(500);
    while(get_create_rfcliff_amt()>2000)
    {
        create_drive_direct(-100, 100);
        printf("sensor reads %d\n", get_create_lfcliff_amt());
        msleep(10);
    }
    set_create_total_angle(0);
    while(get_create_lfcliff_amt()>2000)
    {
        create_drive_direct(100, -100);
        printf("sensor reads %d\n", get_create_rfcliff_amt());
        msleep(10);
        anglCount ++;
    }
    turnLDeg((anglCount/2), 100);
    create_stop();
}
void trnR2tape()
{
    create_drive_direct(100, -100);
    msleep(500);
    while(get_create_lfcliff_amt()>2000)
    {
        create_drive_direct(100, -100);
        printf("sensor reads %d\n", get_create_lfcliff_amt());
        msleep(10);
    }
    set_create_total_angle(0);
    while(get_create_rfcliff_amt()>2000)
    {
        create_drive_direct(-100, 100);
        printf("sensor reads %d\n", get_create_lfcliff_amt());
        msleep(10);
        anglCount ++;
    }
    turnRDeg((anglCount/2), 100);
    create_stop();
}



////////////////////////////////////////////////////// SERVOS --------------------------------------



void set_position(int speed, int pos[4])
{
    int delta[4] = {(pos[0] - get_servo_position(0)),(pos[1] - get_servo_position(1)),(pos[2] - get_servo_position(2)),(pos[3] - get_servo_position(3))};
    int posCompletion[4] = {0, 0, 0, 0};

    while(sum(posCompletion) < 4)
    {
        int port = 0;
        while(port < 4)
        {
            if(delta[port] > speed){
                set_servo_position(port, get_servo_position(port)+speed);
            }
            if(delta[port] < -speed){
                set_servo_position(port, get_servo_position(port)-speed);
            }
            if(abs(delta[port]) <= speed){
                set_servo_position(port, pos[port]);
                posCompletion[port] = 1;
                printf("completed port - %d\n", port);
            }
            delta[port] = (pos[port] - get_servo_position(port));
            port++;
            msleep(5);
        }
    }
}

float c(int port)
{
    return get_servo_position(port);
}

int sum(int array[])
{
    int i = 0;
    int result = 0;
    while(i < sizeof(array))
    {
        result += array[i];
        i++;
    }
    return result;
}
