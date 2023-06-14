#include <kipr/wombat.h>
//back switch port = digital 0

int operations = 5; //The number of tower operations for NavMaster to complete (default should be 5)

int slowSpeedF = 380;
int fastSpeedF = 450;
int slowSpeedR = 380;
int fastSpeedR = 450;
int clawAligned = 0;


int lastTower = 0;
int towerCount = 0;
float rM = 0;
float lM = 0;

void driveCM(int dist, int speed);
void rail2tower(int towerNum);
void REVrail2tower(int towerNum);
void railDist(int dist);
void REVrailDist(int dist);
void turnLDeg(int dist, int speed);
void turnRDeg(int dist, int speed);
void fwd2tape();
void startingTurn();
void squareWithRail();
void NavMaster(int towerOrder[5]);
void NavMasterTEST(int towerOrder[5]);
void setBase();
void setShortBase();
void ShortTower();
void HighTower();
void set_position(int speed, int pos[4]);
int sum(int array[]);
float c(int port);
void baseTower();
//void baseStart();
void dropCube();
void dropCubeL();
void clawAlign();



//Variables for arm movement

//Servo ports
int armServo = 0;
int pitchServo = 1;
int clawServo = 2;
int baseMotor = 0;

int baseANGL = 500;
//int baseStartANGL = 200;

//Arm angles
int aShortTowerApproach = 2000;
int aShortTowerAfter = 756;
int aHighTower = 300;

//Pitch angles
int pBackHigh = 1415;
int pHighTower = 1850;
int pShortTower = 1600;
int pShortTower2 = 1750;

//Claw angles
int clawOpen = 1200;
int clawClose = 470;

//Starting Angles
int armStart = 0;
int pitchStart = 0;
int clawStart = 0;

//Drop Angles
int pDrop = 1393;
int aDrop = 1375;
int storeANGL = 5;
int ShortStoreANGL = 30;

int main()
{
    create_connect();
    enable_servos();
    //create_full();    <------------------------------------------------D A N G E R - C O D E ------------------------------------
    

    int capsule01[] = {800, 1500, clawOpen};
    set_position(15, capsule01);
    setBase();   
    
    printf("1\n");
    int posCapsuleStart[] = {1900, 1400, clawOpen};
    set_position(15, posCapsuleStart); 
    posCapsuleStart[1] = 1800;
    set_position(15, posCapsuleStart);
    
    printf("2\n");
    msleep(2000);
    posCapsuleStart[1] = 1400;
    set_position(15, posCapsuleStart); 
    int capsule02[] = {1000, 1500, clawOpen};
    set_position(15, capsule02);
    capsule02[2] = clawClose;
    set_position(15, capsule02);
    
    printf("3\n");

    
    /*
    baseStart();
    int posCapsuleStart[] = {1200, 1900, clawClose};
    set_position(15, posCapsuleStart);
    */
    
    
    
    fwd2tape();
    msleep(500);
    while(get_create_lbump()==0 && get_create_rbump()==0)
    {
        create_drive_direct(230, 200);
    }
    create_drive_direct(-200,-200);
    msleep(70);
    create_stop();
    msleep(100);
    startingTurn();
    msleep(100);
    //End of alignment code

    int NavCache[5] = {1, 2, 2, 4, 5};
    NavMaster(NavCache);
    
    
    /*
    int NavCacheTEST[5] = {1, 3, 5, 2, 4};
    while(digital(1) == 0){
    NavMasterTEST(NavCacheTEST);
    }
    */
    
    
    set_servo_position(2, clawOpen);
    msleep(100);
    mav(1, -1000);
    msleep(500);
    ao();
    disable_servos();
    create_disconnect();
    return 0;
}

void baseTower()
{
    cmpc(0);
    while(gmpc(0) < baseANGL)
    {
        mav(0, 300);
    }
    ao();
}

/*
void baseStart()
{
    cmpc(0);
    while(gmpc(0) < baseStartANGL)
    {
        mav(0, 300);
    }
    ao();
}
*/

void setBase(){
    printf("Setting Base\n");
    while(digital(2) == 0){
        mav(0, -300);
    }
    cmpc(0);
    while(gmpc(0) < storeANGL)
    {
        mav(0, 300);
    }
    ao();
}

void setShortBase(){
    printf("Setting Base\n");
    while(digital(2) == 0){
        mav(0, -300);
    }
    cmpc(0);
    while(gmpc(0) < ShortStoreANGL)
    {
        mav(0, 300);
    }
    ao();
}


void ShortTower()
{
    baseTower();
    int posCapsule[] = {aShortTowerApproach, pShortTower, clawOpen};
    set_position(15, posCapsule);
    
    posCapsule[1] = pShortTower2;
    set_position(15, posCapsule);
    
    posCapsule[2] = clawClose;
    set_position(15, posCapsule);
    
    posCapsule[1] = pShortTower;
    set_position(15, posCapsule);
    
    posCapsule[0] = aShortTowerAfter;
    posCapsule[1] = pShortTower;
    set_position(15, posCapsule);
    
    dropCubeL();

}

void HighTower()
{
    int posCapsule[] = {aHighTower, pBackHigh, clawOpen};
    set_position(15, posCapsule);
    baseTower();
    
    msleep(500);
    posCapsule[1] = pHighTower;
    set_position(15, posCapsule);
    posCapsule[2] = clawClose;
    set_position(15, posCapsule);
    
    msleep(500);
    //Moves to avoid cube hitting tower
    posCapsule[0] = posCapsule[0] - 10;
    posCapsule[1] = posCapsule[1] - 100;
    set_position(15, posCapsule);
    
    dropCube();
}

void dropCube()
{
    int posCapsule[] = {c(0), 1300, c(2)};
    set_position(15, posCapsule);
    
    msleep(1000);

    setBase();
    msleep(1000);
    
    posCapsule[0] = aDrop;
    posCapsule[1] = pDrop;
    set_position(15, posCapsule);
    msleep(500);
    //posCapsule[1] = pDrop + 75;
    posCapsule[0] = aDrop + 100;
    set_position(15, posCapsule);
    msleep(500);
    if(lastTower == 0){
    posCapsule[2] = clawOpen;
    set_position(15, posCapsule);
    }
    if(lastTower == 1){
    	posCapsule[1] = posCapsule[1] + 50;
    	set_position(15, posCapsule);
    }
}

void dropCubeL()
{
    int posCapsule[] = {c(0), 1300, c(2)};
    set_position(15, posCapsule);
    
    msleep(1000);

    setBase();
    msleep(1000);
    
    posCapsule[0] = aDrop;
    posCapsule[1] = pDrop;
    set_position(15, posCapsule);
    msleep(500);
    if(lastTower == 0){
        posCapsule[2] = clawOpen;
        set_position(15, posCapsule);
    }
    if(lastTower == 1){
    	posCapsule[1] = posCapsule[1] + 50;
    	set_position(15, posCapsule);
    }
}

void rail2tower(int towerNum)
{
    int towerCount = 0;
    
    if(analog(0)>2000 && analog(1)>2000){
    railDist(20);
    printf("leaving tower\n");
    }
    
    while(towerCount < towerNum)
    {
    while(analog(0)<2000 || analog(1)<2000)
    {
        if(get_create_lbump()==1){
            create_drive_direct(400, 370);
            msleep(10);
        }
        if(get_create_rbump()==1){
            create_drive_direct(350, 400);
            msleep(10);
        }
        
        if(get_create_rbump()==0 && get_create_lbump()==0){
        create_drive_direct(350 , 400);
        msleep(10);
        }
    }
    towerCount = towerCount + 1;
    printf("aligning at tower, added one to count\n");
    //railDist(2);
    
    if(towerCount < towerNum){
    railDist(20);
    printf("passed tower\n");
    }
    }
    
    printf("done\n");
    create_stop();
}
void railDist(int dist){
    set_create_distance(0);
    while(abs(get_create_distance())<(dist * 10))
    {        
        if(get_create_lbump()==1){
            create_drive_direct(400, 370);
            msleep(10);
        }
        if(get_create_rbump()==1){
            create_drive_direct(350, 400);
            msleep(10);
        }
        
        if(get_create_rbump()==0 && get_create_lbump()==0){
        create_drive_direct(350 , 400);
        msleep(10);
        }
    }
}

void REVrail2tower(int towerNum)
{
    int towerCount = 0;
    
    if(analog(0)>2000 && analog(1)>2000){
    REVrailDist(20);
    printf("leaving current tower\n");
    }
    
    while(towerCount < towerNum)
    {
    while(analog(0)<2000 || analog(1)<2000)
    {
        if(digital(0) == 0){
            create_drive_direct(-300, -420);
            msleep(10);
        }
        if(digital(0) ==1){
            create_drive_direct(-470, -270);
            msleep(50);
        }
    }
        
    towerCount = towerCount + 1;
    printf("aligning at tower, added one to count\n");
    //REVrailDist(2);
    
    if(towerCount < towerNum){
    REVrailDist(20);
    printf("passed tower\n");
    }  
    }
    
    printf("done\n");
    create_stop();
}


void REVrailDist(int dist){
    set_create_distance(0);
    while(abs(get_create_distance())<(dist * 10))
    {        
        if(digital(0) == 0){
            create_drive_direct(-300, -420);
            msleep(10);
        }
        if(digital(0) ==1){
            create_drive_direct(-470, -270);
            msleep(50);
        }
    }
}


void turnLDeg(int dist, int speed){
    set_create_total_angle(0);
    while(get_create_total_angle() < dist)
    {
        create_drive_direct(-speed, speed);
        msleep(10);
        /*
        printf("driving\n");
        printf("dist: %d\n", dist);
        printf("dist: %d\n", (dist - get_create_distance()));
        */
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
        /*
        printf("driving\n");
        printf("dist: %d\n", dist);
        printf("dist: %d\n", (dist - get_create_distance()));
        */
    }
    create_stop();

}

void fwd2tape()
{
    while(get_create_lcliff_amt()>2000 && get_create_rcliff_amt()>2000)
    {
        create_drive_direct(350 , 350);
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
        create_drive_direct((100 * lM), (100 * rM));
        msleep(10);
    }
    driveCM(7, 100);
}

void driveCM(int dist, int speed){
    set_create_distance(0);
    dist = (dist * 1) * 10;
    while(abs(get_create_distance()) < dist)
    {
        create_drive_direct(speed, speed);
        msleep(10);
        /*
        printf("driving\n");
        printf("dist: %d\n", dist);
        printf("dist: %d\n", (dist - get_create_distance()));
        */
    }
    create_stop();
}

void startingTurn(){
        while(digital(0) == 0){
            create_drive_direct(150, -150);
            msleep(15);
        }
    turnLDeg(10, 100);
    create_stop();    
}

void squareWithRail(){
    while(digital(0) == 0){
        create_drive_direct(100, -100);
    }
    while(digital(0) == 1){
        create_drive_direct(-100, 100);
    }
    create_stop();
    msleep(50);
}

void wiggle(){
    squareWithRail();
    squareWithRail();
}

void NavMaster(int towerOrder[5]){
    printf("Starting NavMaster\n");
    int t_Op = 0; //Tower Operation (how many towers the program has visited so far)
    int N_towerDist = 0; //Next tower distance (distance to the next tower from the current tower, measured in towers)
    rail2tower(towerOrder[t_Op]);
    msleep(1000); //placeholder
    clawAlign();
    squareWithRail();
        if(towerOrder[t_Op] == 1 || towerOrder[t_Op] == 5){
            ShortTower();
        }
        else{
            HighTower();
        }
    msleep(500); // placeholder
    rail2tower(1);
    t_Op++;
    printf("Tower One\n");
    msleep(1000);
    
    while(t_Op <= (operations-1) ){
        if(t_Op == 4){
            lastTower = 1;
        }
        printf("Continuing - ");
        N_towerDist = towerOrder[t_Op] - towerOrder[(t_Op - 1)];
        printf("-----------\nN_towerDist:%d\nTower Operation:%d\n-----------\n", N_towerDist, t_Op);
            if(N_towerDist > 0){
                rail2tower(N_towerDist);
                msleep(1000);
                clawAlign();
                squareWithRail();
                if(towerOrder[t_Op] == 1 || towerOrder[t_Op] == 5){
                    ShortTower();
                }
                else{
                    HighTower();
                }
                msleep(500); // placeholder
    			rail2tower(1);
				t_Op++;
            }    
            if(N_towerDist < 0){
                REVrail2tower(abs(N_towerDist));
                msleep(1000);
                clawAlign();
                squareWithRail();
                if(towerOrder[t_Op] == 1 || towerOrder[t_Op] == 5){
                    ShortTower();
                }
                else{
                    HighTower();
                }
                msleep(500); // placeholder
    			rail2tower(1);
				t_Op++;
            }
			if(N_towerDist == 0){
                printf("Mannn wtf you doin?? Im already there bro.\n");
                t_Op++;
            }
		msleep(1000);
    }
}
void NavMasterTEST(int towerOrder[5]){
    printf("Starting NavMaster\n");
    int t_Op = 0; //Tower Operation (how many towers the program has visited so far)
    int N_towerDist = 0; //Next tower distance (distance to the next tower from the current tower, measured in towers)    
    t_Op++;
    squareWithRail();
    msleep(1000);
    while(t_Op <= (operations-1) ){
        printf("Continuing - ");
        N_towerDist = towerOrder[t_Op] - towerOrder[(t_Op - 1)];
        printf("-----------\nN_towerDist:%d\nTower Operation:%d\n-----------\n", N_towerDist, t_Op);
            if(N_towerDist > 0){
                rail2tower(N_towerDist);
                t_Op++;
                squareWithRail();
            }    
            if(N_towerDist < 0){
                REVrail2tower(abs(N_towerDist));
                t_Op++;
				squareWithRail();
            }
			if(N_towerDist == 0){
                printf("Mannn wtf you doin?? Im already there bro.\n");
                t_Op++;
            }
		msleep(1000);
    }
    REVrail2tower(3);
}





//Servos  ---___-9 -_ -072344(*()&*_+_)_))_+_()!_+~(!(_)@$?_)+$>? ___-------------------------SERVOS ---- !! _ _ -1 -) E-21=EE8-239-0

void set_position(int speed, int pos[3])
{
    int delta[3] = {(pos[0] - get_servo_position(0)),(pos[1] - get_servo_position(1)),(pos[2] - get_servo_position(2))};
    int posCompletion[3] = {0, 0, 0};
    while(sum(posCompletion) < 3)
    {
        int port = 0;
        while(port < 3)
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
                //printf("completed port - %d\n", port);
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
    while(i < 3)
    {
        result = result + (array[i]);
        i = i + 1;
    }
    return result;
}

void clawAlign(){
    set_create_distance(0);
    while(analog(0) > 2000){
        printf("uh-oh\n");
        REVrailDist(1);
    }
    clawAligned = get_create_distance();
    create_stop();
}