#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <algorithm>

int currentShot=0;
int gunAttachments[2][4];
int scopeType[2];
int attMod[2];
int cur_gun_id[3];
int cur_eqp_gun=1;
int elapsed=0;
int stance;
bool isOn=false;
bool isMapOpen=false;
bool isInventoryOpen=false;
bool isMenuOpen=false;


using namespace std;

struct Weapon{
    int id;
    int val_x[3][40];
    int val_y[3][40];
    int RPS;
    bool isSingle;
    string name;
} AK, Groza, M16, ScarL, M4, Aug, MG, UMP, Uzi, Vec, Thompson, Winchester, VSS, Mini14, SKS, Kar98, MK14, M24, AWM, Glock, P92, P1911, R45, Revolver;

Weapon Guns[3];

void initARs(){
    AK.id=1;
    //difference - 1.394117647058824
    int tempAKY0[40] = {19,19,19,19,19,19,19,19,19,19,19,22,22,22,22,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23};
    int tempAKY1[40] = {17,17,17,17,17,17,17,17,17,17,17,20,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21};
    int tempAKY2[40] = {14,14,14,14,14,14,14,14,14,14,14,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18};
    copy(tempAKY0,tempAKY0+40,AK.val_y[0]);
    copy(tempAKY1,tempAKY1+40,AK.val_y[1]);
    copy(tempAKY2,tempAKY2+40,AK.val_y[2]);
    AK.RPS=100;
    AK.name="AK47";

    Groza.id=2;
    int tempGrozaY0[40] = {19,19,19,19,19,19,19,19,19,19,19,22,22,22,22,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23};
    int tempGrozaY1[40] = {17,17,17,17,17,17,17,17,17,17,17,20,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21};
    int tempGrozaY2[40] = {14,14,14,14,14,14,14,14,14,14,14,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18};
    copy(tempGrozaY0,tempGrozaY0+40,Groza.val_y[0]);
    copy(tempGrozaY1,tempGrozaY1+40,Groza.val_y[1]);
    copy(tempGrozaY2,tempGrozaY2+40,Groza.val_y[2]);
    Groza.RPS=80;
    Groza.name="Groza";

    M16.id=3;
    //Difference - 1.923076923076923
    int tempM16Y0[40] = {15,15,15,17,19,19,19,19,19,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16};
    int tempM16Y1[40] = {13,13,13,15,17,17,17,17,17,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14};
    int tempM16Y2[40] = {10,10,10,12,14,14,14,14,14,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11};
    copy(tempM16Y0,tempM16Y0+40,M16.val_y[0]);
    copy(tempM16Y1,tempM16Y1+40,M16.val_y[1]);
    copy(tempM16Y2,tempM16Y2+40,M16.val_y[2]);
    //M16.val_y = {25,25,25,29,33,33,32,33,32,32,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30};
    M16.RPS=75;
    M16.name="M16";

    ScarL.id=4;
    //Difference - 1.25
    int tempScarY0[40] = {18,19,20,19,20,20,20,20,20,20,21,21,22,22,22,22,23,24,24,25,26,28,29,29,30,29,30,29,30,29,30,29,29,29,29,29,30,30,30,30};
    int tempScarY1[40] = {16,17,18,17,18,18,18,18,18,18,19,19,20,20,20,20,21,22,22,23,24,26,27,27,28,27,28,27,28,27,28,27,27,27,27,27,28,28,28,28};
    int tempScarY2[40] = {13,14,15,14,15,15,15,15,15,15,16,16,17,17,17,17,18,19,19,20,21,23,24,24,25,24,25,24,25,24,25,24,24,24,24,24,25,25,25,25};
    copy(tempScarY0,tempScarY0+40,ScarL.val_y[0]);
    copy(tempScarY1,tempScarY1+40,ScarL.val_y[1]);
    copy(tempScarY2,tempScarY2+40,ScarL.val_y[2]);
    //ScarL.val_y={20,21,22,21,22,22,23,22,23,23,24,24,25,25,25,25,26,27,28,29,30,32,34,34,35,34,35,34,35,34,35,34,34,34,34,34,35,35,35,35,35,35,35,35,35,35}
    ScarL.RPS=96;
    ScarL.name="Scar-L";

    M4.id=5;
    int tempM4Y0[40] = {21,21,21,21,21,21,21,21,21,23,23,24,23,24,25,25,26,27,27,32,31,31,31,31,31,31,31,32,32,32,35,35,35,35,35,35,35,35,35,35};
    int tempM4Y1[40] = {17,17,17,17,17,17,17,17,17,19,19,20,19,20,21,21,22,23,23,28,27,27,27,27,27,27,27,28,28,28,31,31,31,31,31,31,31,31,31,31};
    int tempM4Y2[40] = {13,13,13,13,13,13,13,13,13,15,15,16,15,16,17,17,18,19,19,24,23,23,23,23,23,23,23,24,24,24,27,27,27,27,27,27,27,27,27,27};
    copy(tempM4Y0,tempM4Y0+40,M4.val_y[0]);
    copy(tempM4Y1,tempM4Y1+40,M4.val_y[1]);
    copy(tempM4Y2,tempM4Y2+40,M4.val_y[2]);
    //M4.val_y = {21,21,21,21,21,21,21,21,21,23,23,24,23,24,25,25,26,27,27,32,31,31,31,31,31,31,31,32,32,32,35,35,35,35,35,35,35,35,35,35,35}
    M4.RPS=86;
    M4.name="M4";

    Aug.id=6;
    int tempAugY0[40] = {18,19,20,19,20,20,20,20,20,20,21,21,22,22,22,22,23,24,24,25,26,28,29,29,30,29,30,29,30,29,30,29,29,29,29,29,30,30,30,30};
    int tempAugY1[40] = {16,17,18,17,18,18,18,18,18,18,19,19,20,20,20,20,21,22,22,23,24,26,27,27,28,27,28,27,28,27,28,27,27,27,27,27,28,28,28,28};
    int tempAugY2[40] = {13,14,15,14,15,15,15,15,15,15,16,16,17,17,17,17,18,19,19,20,21,23,24,24,25,24,25,24,25,24,25,24,24,24,24,24,25,25,25,25};
    copy(tempAugY0,tempAugY0+40,Aug.val_y[0]);
    copy(tempAugY1,tempAugY1+40,Aug.val_y[1]);
    copy(tempAugY2,tempAugY2+40,Aug.val_y[2]);
    Aug.RPS=86;
    Aug.name="Aug";

    MG.id=7;
    int tempMGY0[40] = {18,19,20,19,20,20,20,20,20,20,21,21,22,22,22,22,23,24,24,25,26,28,29,29,30,29,30,29,30,29,30,29,29,29,29,29,30,30,30,30};
    int tempMGY1[40] = {16,17,18,17,18,18,18,18,18,18,19,19,20,20,20,20,21,22,22,23,24,26,27,27,28,27,28,27,28,27,28,27,27,27,27,27,28,28,28,28};
    int tempMGY2[40] = {13,14,15,14,15,15,15,15,15,15,16,16,17,17,17,17,18,19,19,20,21,23,24,24,25,24,25,24,25,24,25,24,24,24,24,24,25,25,25,25};
    copy(tempMGY0,tempMGY0+40,MG.val_y[0]);
    copy(tempMGY1,tempMGY1+40,MG.val_y[1]);
    copy(tempMGY2,tempMGY2+40,MG.val_y[2]);
    MG.RPS=75;
    MG.name="MG";
}
void initSMGs(){
    UMP.id=8;
    int tempUMPY0[40] = {18,19,18,19,18,19,19,21,23,24,23,24,23,24,23,24,23,24,23,24,23,24,24,25,24,25,24,25,24,25,24,25,25,26,25,26,25,26,25,26};
    int tempUMPY1[40] = {14,15,14,15,14,15,15,17,19,20,19,20,19,20,19,20,19,20,19,20,19,20,20,21,20,21,20,21,20,21,20,21,21,22,21,22,21,22,21,22};
    int tempUMPY2[40] = {10,11,10,11,10,11,11,13,15,16,15,16,15,16,15,16,15,16,15,16,15,16,16,17,16,17,16,17,16,17,16,17,17,18,17,18,17,18,17,18};
    copy(tempUMPY0,tempUMPY0+40,UMP.val_y[0]);
    copy(tempUMPY1,tempUMPY1+40,UMP.val_y[1]);
    copy(tempUMPY2,tempUMPY2+40,UMP.val_y[2]);
    UMP.RPS=92;
    UMP.name="UMP";

    Uzi.id=9;
    int tempUziY0[40] = {16,17,18,20,21,22,23,24,25,26,28,30,32,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34};
    int tempUziY1[40] = {14,15,14,15,14,15,15,17,19,20,19,20,19,20,19,20,19,20,19,20,19,20,20,21,20,21,20,21,20,21,20,21,21,22,21,22,21,22,21,22};
    int tempUziY2[40] = {10,11,10,11,10,11,11,13,15,16,15,16,15,16,15,16,15,16,15,16,15,16,16,17,16,17,16,17,16,17,16,17,17,18,17,18,17,18,17,18};
    copy(tempUziY0,tempUziY0+40,Uzi.val_y[0]);
    copy(tempUziY1,tempUziY1+40,Uzi.val_y[1]);
    copy(tempUziY2,tempUziY2+40,Uzi.val_y[2]);
    Uzi.RPS=48;
    Uzi.name="Uzi";

    Vec.id=10;
    int tempVecY0[40] = {16,17,18,20,21,22,23,24,25,26,28,30,32,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34};
    int tempVecY1[40] = {14,15,14,15,14,15,15,17,19,20,19,20,19,20,19,20,19,20,19,20,19,20,20,21,20,21,20,21,20,21,20,21,21,22,21,22,21,22,21,22};
    int tempVecY2[40] = {10,11,10,11,10,11,11,13,15,16,15,16,15,16,15,16,15,16,15,16,15,16,16,17,16,17,16,17,16,17,16,17,17,18,17,18,17,18,17,18};
    copy(tempVecY0,tempVecY0+40,Vec.val_y[0]);
    copy(tempVecY1,tempVecY1+40,Vec.val_y[1]);
    copy(tempVecY2,tempVecY2+40,Vec.val_y[2]);
    Vec.RPS=55;
    Vec.name="Vector";

    Thompson.id=11;
    int tempThompsonY0[40] = {16,17,18,20,21,22,23,24,25,26,28,30,32,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34};
    int tempThompsonY1[40] = {14,15,14,15,14,15,15,17,19,20,19,20,19,20,19,20,19,20,19,20,19,20,20,21,20,21,20,21,20,21,20,21,21,22,21,22,21,22,21,22};
    int tempThompsonY2[40] = {10,11,10,11,10,11,11,13,15,16,15,16,15,16,15,16,15,16,15,16,15,16,16,17,16,17,16,17,16,17,16,17,17,18,17,18,17,18,17,18};
    copy(tempThompsonY0,tempThompsonY0+40,Thompson.val_y[0]);
    copy(tempThompsonY1,tempThompsonY1+40,Thompson.val_y[1]);
    copy(tempThompsonY2,tempThompsonY2+40,Thompson.val_y[2]);
    Thompson.RPS=86;
    Thompson.name="Thompson";
}
void initSnipers(){
    int tempArr[40];
    for (int i=0;i<40;i++)
        tempArr[i]=15;

    Winchester.id=12;
    copy(tempArr,tempArr+40,Winchester.val_y[0]);
    copy(tempArr,tempArr+40,Winchester.val_y[1]);
    copy(tempArr,tempArr+40,Winchester.val_y[2]);
    Winchester.RPS=500; // No idea o_O
    Winchester.name="Winchester";

    VSS.id=13;
    copy(tempArr,tempArr+40,VSS.val_y[0]);
    copy(tempArr,tempArr+40,VSS.val_y[1]);
    copy(tempArr,tempArr+40,VSS.val_y[2]);
    VSS.RPS=86;
    VSS.name="VSS";

    Mini14.id=14;
    copy(tempArr,tempArr+40,Mini14.val_y[0]);
    copy(tempArr,tempArr+40,Mini14.val_y[1]);
    copy(tempArr,tempArr+40,Mini14.val_y[2]);
    Mini14.RPS=100;
    Mini14.name="Mini14";

    SKS.id=19;
    copy(tempArr,tempArr+40,SKS.val_y[0]);
    copy(tempArr,tempArr+40,SKS.val_y[1]);
    copy(tempArr,tempArr+40,SKS.val_y[2]);
    SKS.RPS=90;
    SKS.name="SKS";

    Kar98.id=16;
    copy(tempArr,tempArr+40,Kar98.val_y[0]);
    copy(tempArr,tempArr+40,Kar98.val_y[1]);
    copy(tempArr,tempArr+40,Kar98.val_y[2]);
    Kar98.RPS=1900;
    Kar98.name="Kar98";

    MK14.id=17;
    copy(tempArr,tempArr+40,MK14.val_y[0]);
    copy(tempArr,tempArr+40,MK14.val_y[1]);
    copy(tempArr,tempArr+40,MK14.val_y[2]);
    MK14.RPS=90;
    MK14.name="MK14";

    M24.id=18;
    copy(tempArr,tempArr+40,M24.val_y[0]);
    copy(tempArr,tempArr+40,M24.val_y[1]);
    copy(tempArr,tempArr+40,M24.val_y[2]);
    M24.RPS=1800;
    M24.name="M24";

    AWM.id=19;
    copy(tempArr,tempArr+40,AWM.val_y[0]);
    copy(tempArr,tempArr+40,AWM.val_y[1]);
    copy(tempArr,tempArr+40,AWM.val_y[2]);
    AWM.RPS=1850;
    AWM.name="AWM";
}
void initPistols(){
    int tempArr[40];
    for (int i=0;i<40;i++)
        tempArr[i]=15;

    Glock.id=20;
    copy(tempArr,tempArr+40,Glock.val_y[0]);
    copy(tempArr,tempArr+40,Glock.val_y[1]);
    copy(tempArr,tempArr+40,Glock.val_y[2]);
    Glock.RPS=60;
    Glock.name="Glock";

    P92.id=21;
    copy(tempArr,tempArr+40,P92.val_y[0]);
    copy(tempArr,tempArr+40,P92.val_y[1]);
    copy(tempArr,tempArr+40,P92.val_y[2]);
    P92.RPS=135;
    P92.name="P92";

    P1911.id=22;
    copy(tempArr,tempArr+40,P1911.val_y[0]);
    copy(tempArr,tempArr+40,P1911.val_y[1]);
    copy(tempArr,tempArr+40,P1911.val_y[2]);
    P1911.RPS=110;
    P1911.name="P1911";

    R45.id=23;
    copy(tempArr,tempArr+40,R45.val_y[0]);
    copy(tempArr,tempArr+40,R45.val_y[1]);
    copy(tempArr,tempArr+40,R45.val_y[2]);
    R45.RPS=400;    //Unknown
    R45.name="R45";

    Revolver.id=24;
    copy(tempArr,tempArr+40,Revolver.val_y[0]);
    copy(tempArr,tempArr+40,Revolver.val_y[1]);
    copy(tempArr,tempArr+40,Revolver.val_y[2]);
    Revolver.RPS=400;
    Revolver.name="Revolver";
}

void init(){
    initARs();
    initSMGs();
    initSnipers();
    initPistols();
}
bool keyDown (int vcode){
    return GetAsyncKeyState(vcode) & ~32767;
}
bool isRunning(){
    if (isMapOpen)
        return false;
    if (isMenuOpen)
        return false;
    if (isInventoryOpen)
        return false;
    return isOn;
}
void listKeys(){
    cout << "F1: Change AR" << endl <<
            "F2: Change SMG" << endl <<
            "F3: Change Sniper" << endl <<
            "F4: Change Pistol" << endl << endl <<
            "0: Remove Attachments" << endl <<
            "1: Add Vertical Grip" << endl <<
            "2: Add Angeled Grip" << endl <<
            "3: Add Stock" << endl <<
            "4: Add Compensator" << endl <<
            "5: Change Scope" << endl <<
            "6: Reset All Paramters";;
}
void status(){
    int i=cur_eqp_gun-1;
    system("CLS");
    cout << "Status: " << isRunning() << endl <<
            "   Map: " << isMapOpen << endl <<
            "   Menu: " << isMenuOpen << endl <<
            "   Inventory: " << isInventoryOpen << endl <<
            "Weapon: " << Guns[i].name << endl <<
            "Gun Slot: " << cur_eqp_gun << endl <<
            "Scope: " << scopeType[i] << endl <<
            "Stance: " << stance << endl <<
            "RPS: " << Guns[i].RPS << endl <<
            "Current Shot: " << currentShot << endl <<
            //"Single Fire: " << Guns[i].isSingle << endl <<
            "Base Y: " << Guns[i].val_y[stance][currentShot] << endl <<
            "Mod Y: " << attMod[i] << endl << endl;
    listKeys();
}
void moveMouse(){
    int i=cur_eqp_gun-1;
    Sleep(Guns[i].RPS-1);
    int valX=0;
    int valY=(Guns[i].val_y[stance][currentShot] - attMod[i]) * scopeType[i];
    if (valY<0)
        valY=0;
    mouse_event(MOUSEEVENTF_MOVE, Guns[i].val_x[stance][0], valY, 0, 0);
    currentShot++;
    if (currentShot>=40)
        currentShot=0;
}
//Attachments

void removeAttachments(){
    int i = cur_eqp_gun-1;
    for (int j = 0 ; j<4 ; j++)
        gunAttachments[i][j]=false;
    attMod[i]=0;
    scopeType[i]=1;
}
void resetToDefault(){
    Guns[0]=Winchester;//load a default AR to button 1;
    Guns[1]=AK;//load a default AR to button 1;
    Guns[2]=P1911;//load a default AR to button 1;
    cur_gun_id[0]=12;
    cur_gun_id[1]=1;
    cur_gun_id[2]=22;
    cur_eqp_gun=1;
    removeAttachments();
    cur_eqp_gun=2;
    removeAttachments();
}
void addStock(){
    int i = cur_eqp_gun-1;
    if (gunAttachments[i][0])
        return;
    gunAttachments[i][0]=true;
    attMod[i]+=2;
}
void addVerticalGrip(){
    int i = cur_eqp_gun-1;
    if (gunAttachments[i][1])
        return;
    if (gunAttachments[i][2])
    {
        gunAttachments[i][2]=false;
        attMod[i]-=3;
    }
    gunAttachments[i][1]=true;
    attMod[i]+=6;
}
void addErgoGrip(){
    int i = cur_eqp_gun-1;
    if (gunAttachments[i][2])
        return;
    if (gunAttachments[i][1])
    {
        gunAttachments[i][1]=false;
        attMod[i]-=6;
    }
    gunAttachments[i][2]=true;
    attMod[i]+=3;
}
void addComp(){
    int i = cur_eqp_gun-1;
    if (gunAttachments[i][3])
        return;
    gunAttachments[i][3]=true;
    attMod[i]+=6;
}
void changeScope(){
    int i = cur_eqp_gun-1;
    if (scopeType[i]==1)
        scopeType[i]=2;
    else if (scopeType[i]==2)
        scopeType[i]=4;
    else if (scopeType[i]==4)
        scopeType[i]=8;
    else if (scopeType[i]==8)
        scopeType[i]=15;
    else
        scopeType[i]=1;
}

//cycle through guns.

void switchAR(){
    int i = cur_eqp_gun-1;
    if (i>1)
        return;
    cur_gun_id[i]++;
    int j = cur_gun_id[i];
    if (j==1)
        Guns[i]=AK;
    else if (j==2)
        Guns[i]=Groza;
    else if (j==3)
        Guns[i]=M16;
    else if (j==4)
        Guns[i]=ScarL;
    else if (j==5)
        Guns[i]=M4;
    else if (j==6)
        Guns[i]=Aug;
    else if (j==7)
        Guns[i]=MG;
    else
    {
        cur_gun_id[i]=0;
        switchAR();
    }
}
void switchSMG(){
    int i = cur_eqp_gun-1;
    if (i>1)
        return;
    cur_gun_id[i]++;
    int j = cur_gun_id[i];
    if (j==8)
        Guns[i]=UMP;
    else if (j==9)
        Guns[i]=Uzi;
    else if (j==10)
        Guns[i]=Vec;
    else if (j==11)
        Guns[i]=Thompson;
    else
    {
        cur_gun_id[i]=7;
        switchSMG();
    }
}
void switchSniper(){
    int i = cur_eqp_gun-1;
    if (i>1)
        return;
    cur_gun_id[i]++;
    int j = cur_gun_id[i];
    if (j==12)
        Guns[i]=Winchester;
    else if (j==13)
        Guns[i]=VSS;
    else if (j==14)
        Guns[i]=Mini14;
    else if (j==15)
        Guns[i]=SKS;
    else if (j==16)
        Guns[i]=Kar98;
    else if (j==17)
        Guns[i]=MK14;
    else if (j==18)
        Guns[i]=M24;
    else if (j==19)
        Guns[i]=AWM;
    else
    {
        cur_gun_id[i]=11;
        switchSniper();
    }
}
void switchPistol(){
    cur_gun_id[2]++;
    int j = cur_gun_id[2];
    if (j==20)
        Guns[2]=Glock;
    else if (j==21)
        Guns[2]=P92;
    else if (j==22)
        Guns[2]=P1911;
    else if (j==23)
        Guns[2]=R45;
    else if (j==24)
        Guns[2]=Revolver;
    else
    {
        cur_gun_id[2]=19;
        switchPistol();
    }
}

//The first function to run.

int main (void){
    init();
    resetToDefault();
    while (true)
	{
	    elapsed++;
        if (keyDown(49)) //1 is pressed.
		{
            isOn = true;
            isMapOpen = false;
            isMenuOpen =  false;
            isInventoryOpen = false;
            cur_eqp_gun =1;
            Sleep(200);
        }
        else if (keyDown(50)) //2 is pressed.
		{
            isOn = true;
            isMapOpen = false;
            isMenuOpen =  false;
            isInventoryOpen = false;
            cur_eqp_gun=2;
            Sleep(200);
        }
        else if (keyDown(51)) //3 is pressed.
		{
            isOn = true;
            isMapOpen = false;
            isMenuOpen =  false;
            isInventoryOpen = false;
            cur_eqp_gun=3;
            Sleep(200);
        }
		else if (keyDown(53)) //5 is pressed.
		{
            isOn = false;
            Sleep(200);
        }
		else if (keyDown(54)) //6 is pressed.
		{
            resetToDefault();
            Sleep(200);
        }
        if (keyDown(107)) //+ is pressed
        {
            Guns[cur_eqp_gun-1].val_y[stance][0]++;
            Sleep(200);
        }
        else if (keyDown(109)) //- is pressed
        {
            Guns[cur_eqp_gun-1].val_y[stance][0]--;
            Sleep(200);
        }
        if (keyDown(112)) // F1 is pressed
        {
            switchAR();
            Sleep(200);
        }
        if (keyDown(113)) // F2 is pressed
        {
            switchSMG();
            Sleep(200);
        }
        if (keyDown(114)) // F3 is pressed
        {
            switchSniper();
            Sleep(200);
        }

        if (keyDown(115)) // F4 is pressed
        {
            switchPistol();
            Sleep(200);
        }
        if (keyDown(96)) // KP_0 is pressed
            removeAttachments();
        else if (keyDown(97)) // KP_1 is pressed
        {
            addVerticalGrip();
            Sleep(200);
        }
        else if (keyDown(98)) // KP_2 is pressed
        {
            addErgoGrip();
            Sleep(200);
        }
        else if (keyDown(99)) // KP_3 is pressed
        {
            addStock();
            Sleep(200);
        }
        else if (keyDown(100)) // KP_4 is pressed
        {
            addComp();
            Sleep(200);
        }
        else if (keyDown(101)) // KP_5 is pressed
        {
            changeScope();
            Sleep(200);
        }
        if (keyDown(77))  // M is pressed
        {
            isMapOpen=!isMapOpen;
            Sleep(200);
        }
        else if (keyDown(9)) //Tab is pressed
        {
            isInventoryOpen=!isInventoryOpen;
            Sleep(200);
        }
        else if (keyDown(27)) //ESC is pressed
        {
            if (isInventoryOpen)
                isInventoryOpen=false;
            if (isMapOpen)
                isMapOpen=false;
            else
                isMenuOpen=!isMenuOpen;
            Sleep(200);
        }
        if (keyDown(32)) //Space is presed
        {
            stance=0;
        }
        else if (keyDown(67)) //C is presed
        {
            if (stance==1)
                stance=0;
            else
                stance=1;
            Sleep(200);
        }
        else if (keyDown(90)) //Z is presed
            stance=2;
        if (keyDown(1) && isRunning()) // mouse1 is pressed5
        {
            moveMouse();
            elapsed=1000;
            status();
            continue;
        }
        else
            currentShot=0;
        Sleep(1);
        if (elapsed>1000)
        {
            status();
            elapsed=0;
        }
    }
    return 0;
}
