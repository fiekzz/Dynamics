#include <iostream>
#include "displayer.h"

/****************************************
 *  
 *  # Authored by Group 4 Section 6
 *  # Since 10 Dec 2021 12.00am
 *  # github.com/fiekzz/Dynamics
 *  # MIT License
 *  
 *  - Fikri Bin Hisham-muddin 2112011
 *  - 
 *  - 
 *  - 
 * 
 ****************************************/

// The comments are not fully covered as there are too many lines to cover
// Updates can be requested anytime

using std::cout;
using std::cin;
using std::endl;

// main menu
void projectileMotion();
void freeFall();
void HorizontalPMotion();
void Info();
void Exit();

// projectile motion menu
void P_TimeOfFlight(); // 0
void P_Range(); // 1
void P_MaxHeight(); // 2
void P_finalVelocity(); // 3

// free fall menu
void F_Time_Velocity(); // 4
void F_Time_Height(); // 5
void F_Height_Velocity(); // 6
void F_Height_Time(); // 7
void F_Velocity_Height(); // 8
void F_Velocity_Time(); // 9

// horizontal motion menu
void H_TimeOfFlight(); //10
void H_Range(); // 11

// enter data by typing
void inputType();
// enter data by input file
void inputFile();
// alipan
// main function
int main()
{
    // set the font for the program
    setfont();
    // set the font color for the program
    Color(3);
    // set cursor off
    ShowConsoleCursor(false);

    const int menuSize = 4;

    MenuItems mainMenu[menuSize] = {{"Projectile Motion", projectileMotion},
                                    {"Free Fall", freeFall},
                                    {"Horizontal Projectile Motion", HorizontalPMotion},
                                    {"Info", Info}};
        
    showMenu(menuSize, mainMenu, "MECHANICS [Dynamics]", false);

}

// projectile motion menu
void projectileMotion()
{
    system("cls");
    const int menuSize = 4;

    MenuItems pmotionMenu[menuSize] = {{"Time of flight", P_TimeOfFlight},
                                       {"Range", P_Range},
                                       {"Maximum Height", P_MaxHeight},
                                       {"Final velocity", P_finalVelocity}};
        
    showMenu(menuSize, pmotionMenu, "PROJECTILE MOTION", true);
}

// free fall menu
void freeFall()
{
    system("cls");
    const int menuSize = 6;
    MenuItems freeFallMenu[menuSize] = {{"Time of Fall given Velocity", F_Time_Velocity},
                                        {"Time of Fall given Height", F_Time_Height},
                                        {"Height of Fall given Velocity", F_Height_Velocity},
                                        {"Height of Fall given Time", F_Height_Time},
                                        {"Final velocity given Height", F_Velocity_Height},
                                        {"Final velocity given Time", F_Velocity_Time}};

    showMenu(menuSize,freeFallMenu,"FREE FALL", true);
}

// horizontal projectile motion menu
void HorizontalPMotion()
{
    system("cls");
    const int menuSize = 2;
    MenuItems hpmMenu[menuSize] = {{"Time of flight", H_TimeOfFlight},
                                   {"Range", H_Range}};
    
    showMenu(menuSize,hpmMenu,"HORIZONTAL PROJECTILE MOTION", true);
}

// info about the program
// connect to the developer with the given link
void Info()
{
    system("cls");
    gotoxy(5,3); cout << "# Started since 10 Dec 2021 12.00am" << endl;
    gotoxy(5,4); cout << "# Authored by Group 4 Section 6" << endl;
    gotoxy(5,5); cout << "# Original Source File at" << endl;
    gotoxy(5,6); cout << "# github.com/fiekzz/Dynamics" << endl;
    gotoxy(5,9); system("pause");
    system("cls");
}

// projectile motion
void P_TimeOfFlight() // 0
{
    questionItems item;
    item.question[0] = "Angle (deg).........: ";
    item.question[1] = "Initial Height (m)..: ";
    item.question[2] = "Velocity (m/s)......: ";
    item.answer[0] = "Time (s)............: ";
    item.size = 3;
    item.type = 0;
    ShowMenu("PROJECTILE MOTION", "Time of flight","pmotionTime.txt",item);
    system("cls");
}
void P_Range() // 1
{
    questionItems item;
    item.question[0] = "Angle (deg).........: ";
    item.question[1] = "Initial Height (m)..: ";
    item.question[2] = "Velocity (m/s)......: ";
    item.answer[0] = "Range (m)...........: ";
    item.size = 3;
    item.type = 1;
    ShowMenu("PROJECTILE MOTION", "Range of flight","pmotionRange.txt",item);
    system("cls");
}
void P_MaxHeight() // 2
{
    questionItems item;
    item.question[0] = "Angle (deg).........: ";
    item.question[1] = "Initial Height (m)..: ";
    item.question[2] = "Velocity (m/s)......: ";
    item.answer[0] = "Max Height(m)...........: ";
    item.size = 3;
    item.type = 2;
    ShowMenu("PROJECTILE MOTION", "Maximum height of flight","pmotionHeight.txt",item);
    system("cls");
}

void P_finalVelocity() // 3
{
    questionItems item;
    item.question[0] = "Angle (deg).........: ";
    item.question[1] = "Initial Height (m)..: ";
    item.question[2] = "Velocity (m/s)......: ";
    item.answer[0] = "Final velocity x-direction (m/s)..: ";
    item.answer[1] = "Final velocity y-direction (m/s)..: ";
    item.answer[2] = "Final velocity (m/s)..............: ";
    item.size = 3;
    item.type = 3;
    ShowMenu("PROJECTILE MOTION", "Final velocity when the object hits the ground","pmotionfinalVelocity.txt",item);
    system("cls");
}

// free fall menu
void F_Time_Velocity() // 4
{
    questionItems item;
    item.question[0] = "Initital velocity (m/s)..: ";
    item.question[1] = "Final velocity (m/s).....: ";
    item.answer[0] = "Time (s).................: ";
    item.size = 2;
    item.type = 4;
    ShowMenu("FREE FALL", "Time of fall given velocity","timeVelocity.txt",item);
    system("cls");
}
void F_Time_Height() // 5
{
    questionItems item;
    item.question[0] = "Initital velocity (m/s)..: ";
    item.question[1] = "Height of fall...........: ";
    item.answer[0] = "Time (s).................: ";
    item.size = 2;
    item.type = 5;
    ShowMenu("FREE FALL", "Time of fall given height","timeHeight.txt",item);
    system("cls");
}
void F_Height_Velocity() // 6
{
    questionItems item;
    item.question[0] = "Initital velocity (m/s)..: ";
    item.question[1] = "Final velocity (m/s).....: ";
    item.answer[0] = "Height (m)...............: ";
    item.size = 2;
    item.type = 6;
    ShowMenu("FREE FALL", "Height given velocity","heightVelocity.txt",item);
    system("cls");
}
void F_Height_Time() // 7
{
    questionItems item;
    item.question[0] = "Initital velocity (m/s)..: ";
    item.question[1] = "Time of fall (s).........: ";
    item.answer[0] = "Height (m)...............: ";
    item.size = 2;
    item.type = 7;
    ShowMenu("FREE FALL", "Height of fall given time","heightTime.txt",item);
    system("cls");
}
void F_Velocity_Height() // 8
{
    questionItems item;
    item.question[0] = "Initital velocity (m/s)..: ";
    item.question[1] = "Height of fall (m).......: ";
    item.answer[0] = "Velocity (m/s)...........: ";
    item.size = 2;
    item.type = 8;
    ShowMenu("FREE FALL", "Velocity of fall given height","velocityHeight.txt",item);
    system("cls");
}
void F_Velocity_Time() // 9
{
    questionItems item;
    item.question[0] = "Initital velocity (m/s)..: ";
    item.question[1] = "Time of fall (m).........: ";
    item.answer[0] = "Velocity (m/s)...........: ";
    item.size = 2;
    item.type = 9;
    ShowMenu("FREE FALL", "Velocity of fall given time","velocityTime.txt",item);
    system("cls");
}

// horizontal motion menu
void H_TimeOfFlight() // 10
{
    questionItems item;
    item.question[0] = "Initital height (m)..: ";
    item.question[1] = "Velocity (m/s).......: ";
    item.answer[0] = "Time (s).............: ";
    item.size = 2;
    item.type = 10;
    ShowMenu("HORIZONTAL PROJECTILE MOTION", "Time of flight","hpmotionTime.txt",item);
    system("cls");
}
void H_Range() // 11
{
    questionItems item;
    item.question[0] = "Initital height (m)..: ";
    item.question[1] = "Velocity (m/s).......: ";
    item.answer[0] = "Range (m)............: ";
    item.size = 2;
    item.type = 11;
    ShowMenu("HORIZONTAL PROJECTILE MOTION", "Range","hpmotionRange.txt",item);
    system("cls");
}
