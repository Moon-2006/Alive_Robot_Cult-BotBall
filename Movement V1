#include <kipr/wombat.h>

int rM = 0;
int lM = 0;
int towerCount = 0;

void rail2tower();

int main()
{
    create_connect();  
    rail2tower();
    return 0;
}

void rail2tower(int towerNum)
{
    int towerCount = 0;
    while(towerCount < towerNum)
    {
    while(analog(0)<2000 || analog(1)<2000)
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
    ao();
    towerCount = towerCount + 1;
    }
    
    printf("done\n");
}
