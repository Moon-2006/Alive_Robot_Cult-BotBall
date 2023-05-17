#include <kipr/wombat.h>

int rM = 0;
int lM = 0;
int towerCount = 0;

void rail2tower(int towerNum);
void railDist(int dist);

int main()
{
    create_connect();
    
    rail2tower(2);
    msleep(1000);
    return 0;
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
            create_drive_direct(170, 140);
            msleep(10);
        }
        if(get_create_rbump()==1){
            create_drive_direct(140, 170);
            msleep(10);
        }
        
        if(get_create_rbump()==0 && get_create_lbump()==0){
        create_drive_direct(140 , 170);
        msleep(10);
        }
    }
    create_stop();
    towerCount = towerCount + 1;
    printf("aligning at tower, added one to count\n");
    railDist(2);
    
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
    while(get_create_distance()<(dist * 10))
    {
        if(get_create_lbump()==1){
            create_drive_direct(180, 100);
            msleep(50);
        }
        if(get_create_rbump()==1){
            create_drive_direct(100, 180);
            msleep(50);
        }
        
        if(get_create_rbump()==0 && get_create_lbump()==0){
        create_drive_direct(100 , 180);
        msleep(50);
        }
    }
    create_stop();
}
