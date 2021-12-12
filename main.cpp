/*  Authored by Fiekzz
    fikrichuck@gmail.com
    github.com/fiekzz
    github.com/Astranot */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <dos.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

using std::cout;
using std::cin;
using std::endl;

// class of formulas
class formula {

private:
    // variables to be returned
    double Time, Range, MaxHeight, Velocity, Height;
    double Vix, Viy, Vfx, Vfy;
    // gravity constant
    const double Gravity = 9.8;
    const double PI = 3.142;

public:
    // projectile motion when given angle, height, velocity
    void P_timeOfFlight(double angle, double height, double velocity);
    void P_range(double angle, double height, double velocity);
    void P_maxHeight(double angle, double height, double velocity);
    void P_finalVelocity(double angle, double height, double velocity);

    // free fall
    void F_Time_Velocity(double iVelocity, double fVelocity);
    void F_Velocity_Time(double iVelocity, double time);
    void F_Height_Velocity(double iVelocity, double fVelocity);
    void F_Time_Height(double iVelocity, double height);
    void F_Velocity_Height(double iVelocity, double height);
    void F_Height_Time(double iVelocity, double time);

    // horizontal projectile motion
    void H_TimeOfFlight(double iHeight, double velocity);
    void H_Range(double iHeight, double velocity);

    // display the data
    double showTime(){
        return Time;
    }
    double showRange(){
        return Range;
    }
    double showMaxHeight(){
        return MaxHeight;
    }
    double showVelocity(){
        return Velocity;
    }
    double showHeight(){
        return Height;
    }
    double showVfx(){
        return Vfx;
    }
    double showVfy(){
        return Vfy;
    }

};

/* ------------- PROJECTILE MOTION ------------- */
// find time
void formula::P_timeOfFlight(double angle, double height, double velocity)
{    
    // t = (Vy + pow(pow(Vy,2) + 2 * G * height),0.5) / G
    angle = (angle * PI) / 180;
    Time = (velocity * sin(angle) + pow(pow(velocity * sin(angle),2) + 2 * Gravity * height,0.5)) / Gravity;
}
// find range
void formula::P_range(double angle, double height, double velocity)
{
    // Rx = Vx * t
    angle = (angle * PI) / 180;
    double velocity_x = velocity * cos(angle);
    double time = (velocity * sin(angle) + pow(pow(velocity * sin(angle),2) + 2 * Gravity * height,0.5)) / Gravity;
    Range = velocity_x * time;
}
// find maximum height
void formula::P_maxHeight(double angle, double height, double velocity)
{
    // Vy = velocity * sin(angle)
    // MaxHeight = initital_height + pow(velocity_y) / (2 * G)
    angle = (angle * PI) / 180;
    double velocity_y = velocity * sin(angle);
    MaxHeight = height + pow(velocity_y,2) / (2 * Gravity);
}

// find final velocity when the object hits the ground
void formula::P_finalVelocity(double angle, double height, double velocity)
{
    double Angle = (angle * PI) / 180;
    Viy = velocity * sin(Angle);

    P_timeOfFlight(angle, height, velocity);

    Vfy = Viy + (-Gravity) * Time;
    Vfx = velocity * cos(Angle);

    Velocity = pow(pow(Vfx,2) + pow(Vfy,2),0.5);
}

/* ------------- FREE FALL ------------- */
// find time given velocity
void formula::F_Time_Velocity(double iVelocity, double fVelocity)
{
    // fVelocity = iVelocity + G * t
    // t = (fVelocity - iVelocity) / G
    Time = (fVelocity - iVelocity) / Gravity;
}
// find velocity given time
void formula::F_Velocity_Time(double iVelocity, double time)
{
    // V = Vo + G * t
    Velocity = iVelocity + Gravity * time;
}
// find height given velocity
void formula::F_Height_Velocity(double iVelocity, double fVelocity)
{
    // fVelocity = iVelocity + G * t
    // t = (fVelocity - iVelocity) / G
    double time = (fVelocity - iVelocity) / Gravity;
    Height = iVelocity * time + 0.5 * 9.8 * time;
}
// find time given height
void formula::F_Time_Height(double iVelocity, double height)
{
    // height = iVelocity * time + 0.5 * 9.8 * pow(time,2)
    // 0.5 * 9.8 * pow(time,2) + iVelocity * time - height = 0
    // root1 = (-b + pow(pow(b,2) - 4 * a * c,0.5)) / (2 * a);
    // root2 = (-b - pow(pow(b,2) - 4 * a * c,0.5)) / (2 * a);
    double time1 = (-iVelocity + pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);
    double time2 = (-iVelocity - pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);

    if(time1 > 0)
        Time = time1;
    else if(time2 > 0)
        Time = time2;
}
// find velocity given height
void formula::F_Velocity_Height(double iVelocity, double height)
{    
    double time1 = (-iVelocity + pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);
    double time2 = (-iVelocity - pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);

    if(time1 > 0)
        Time = time1;
    else if(time2 > 0)
        Time = time2;
    
    // V = Vo + G * t
    Velocity = iVelocity + Gravity * Time;
}
// find height given time
void formula::F_Height_Time(double iVelocity, double time)
{
    Height = iVelocity * time + 0.5 * Gravity * pow(time,2);
}

/* ------------- HORIZONTAL PROJECTILE MOTION ------------- */
// time of flight given initial height and velocity
void formula::H_TimeOfFlight(double iHeight, double velocity)
{
    Time = pow(2 * iHeight / Gravity,0.5);
}
// range of flight given initial height and velocity
void formula::H_Range(double iHeight, double velocity)
{
    double time = pow(2 * iHeight / Gravity,0.5);
    Range = velocity * time;
}

// menu displayer
void gotoxy(int x, int y){
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

// main menu
void projectileMotion();
void freeFall();
void HorizontalPMotion();
void Info();
void Exit();

// projectile motion menu
void P_TimeOfFlight();
void P_Range();
void P_MaxHeight();
void P_finalVelocity();

// free fall menu
void F_Time_Velocity();
void F_Time_Height();
void F_Height_Velocity();
void F_Height_Time();
void F_Velocity_Height();
void F_Velocity_Time();

// horizontal motion menu
void H_TimeOfFlight();
void H_Range();

// output file
char Output(std::fstream&,std::string&);

// main function
int main()
{
    do{

        system("cls");
        gotoxy(5,3); cout << "Mechanics (Dynamic)" << endl;
        gotoxy(5,4); cout << "1 - Projectile Motion" << endl;
        gotoxy(5,5); cout << "2 - Free Fall" << endl;
        gotoxy(5,6); cout << "3 - Horizontal Projectile Motion" << endl;
        gotoxy(5,7); cout << "4 - Info" << endl;
        gotoxy(5,8); cout << "5 - Exit" << endl;
        gotoxy(5,10); cout << "Select option: ";
        char op = getch();

        switch(op){
            case '1': projectileMotion(); break;
            case '2': freeFall(); break;
            case '3': HorizontalPMotion(); break;
            case '4': Info(); break;
            case '5': Exit(); break;
        }

    } while(1);
}

// output file
char Output(std::fstream &oFile, std::string &path)
{
    char output;
    do{
        cout << endl;
        cout << "Do you want to put the results into an output file? (Y/N)" << endl;
        cout << "Enter: ";
        output = getche();
        
    } while(output != 'y' && output != 'Y' && output != 'n' && output != 'N');
    
    if(output == 'Y' || output == 'y'){
        do{
            cout << "Enter the name of file: ";
            cin >> path;
            oFile.open(path, std::fstream::app);
            if(!oFile.is_open())
                cout << "Error opening the output file" << endl;
        } while(!oFile.is_open());
    }
    return output;
}

// projectile motion menu
void projectileMotion()
{
    char op;
    do{
        system("cls");
        cout << "PROJECTILE MOTION" << endl;
        cout << "1 - Time of flight" << endl;
        cout << "2 - Range" << endl;
        cout << "3 - Maximum Height" << endl;
        cout << "4 - Final velocity" << endl;
        cout << "5 - Back" << endl;
        cout << "Menu: ";
        op = getch();
        
        switch(op){
            case '1': P_TimeOfFlight(); break;
            case '2': P_Range(); break;
            case '3': P_MaxHeight(); break;
            case '4': P_finalVelocity(); break;
        }
    } while(op != '5');
}

// free fall menu
void freeFall()
{
    char op;
    do{
        system("cls");
        cout << "FREE FALL" << endl;  
        cout << "1 - Time of Fall given Velocity" << endl;
        cout << "2 - Time of Fall given Height" << endl;
        cout << "3 - Height of Fall given Velocity" << endl;
        cout << "4 - Height of Fall given Time" << endl;
        cout << "5 - Final velocity given Height" << endl;
        cout << "6 - Final Velocity given Time" << endl;
        cout << "7 - Back" << endl;
        cout << "Menu: " << endl;
        op = getch();

        switch(op){
            case '1': F_Time_Velocity(); break;
            case '2': F_Time_Height(); break;
            case '3': F_Height_Velocity(); break;
            case '4': F_Height_Time(); break;
            case '5': F_Velocity_Height(); break;
            case '6': F_Velocity_Time(); break;
        }
    } while(op != '7');
}

// horizontal projectile motion menu
void HorizontalPMotion()
{
    char op;
    do{
        system("cls");
        cout << "HORIZONTAL PROJECTILE MOTION" << endl;
        cout << "1 - Time of flight" << endl;
        cout << "2 - Range" << endl;
        cout << "3 - Back" << endl;
        cout << "Menu: ";
        op = getch();

        switch(op){
            case '1': H_TimeOfFlight(); break;
            case '2': H_Range(); break;
        }
    } while(op != '3');
}

// info
void Info()
{
    system("cls");
    gotoxy(5,3); cout << "# Started since 10 Dec 2021 12.00am" << endl;
    gotoxy(5,4); cout << "# Authored by Fikri Hisham-muddin 2112011" << endl;
    gotoxy(5,5); cout << "# fikrichuck@gmail.com" << endl;
    gotoxy(5,6); cout << "# github.com/Astranot" << endl;
    gotoxy(5,7); cout << "# github.com/Fiekzz" << endl;
    gotoxy(5,8); cout << "Press any key continue" << endl;
    gotoxy(5,9); getch();
}

// exit
void Exit()
{
    char op;
    system("cls");
    gotoxy(5,3); cout << "Exit the program? (Y/N)" << endl;
    gotoxy(5,4); op = getch();
    if(op == 'Y' || op == 'y'){
        system("cls");
        exit(0);
    }
    else
        return;
    
}

// projectile motion
void P_TimeOfFlight()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double angle, height, velocity, result;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "PROJECTILE MOTION" << endl;
        cout << "Time of flight" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'pmotionTime.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Find time of flight when given" << endl;
            cout << "Angle (deg).........: ";
            cin >> angle;
            cout << "Initial Height (m)..: ";
            cin >> height;
            cout << "Velocity (m/s)......: ";
            cin >> velocity;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.P_timeOfFlight(angle,height,velocity);
            cout << "Time (s)............: " << Formula.showTime() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showTime() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("pmotionTime.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> angle >> height >> velocity;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Angle (deg).........: " << angle << endl;
                    cout << "Initial Height (m)..: " << height << endl;
                    cout << "Velocity (m/s)......: " << velocity << endl;
                    Formula.P_timeOfFlight(angle,height,velocity);
                    cout << "Time (s)............: " << Formula.showTime() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showTime() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        

        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        op = getch();

    } while(op != 'e');

}
void P_Range()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double angle, height, velocity, result;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "PROJECTILE MOTION" << endl;
        cout << "Range of flight" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'pmotionRange.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Find range of flight when given" << endl;
            cout << "Angle (deg).........: ";
            cin >> angle;
            cout << "Initial height (m)..: ";
            cin >> height;
            cout << "Velocity (m/s)......: ";
            cin >> velocity;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.P_range(angle,height,velocity);
            cout << "Range (m)...........: " << Formula.showRange() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showRange() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("pmotionRange.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> angle >> height >> velocity;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Angle (deg).........: " << angle << endl;
                    cout << "Initial Height (m)..: " << height << endl;
                    cout << "Velocity (m/s)......: " << velocity << endl;
                    Formula.P_range(angle,height,velocity);
                    cout << "Range (m)...........: " << Formula.showRange() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showRange() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        
        op = getch();

    } while(op != 'e');
}
void P_MaxHeight()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double angle, height, velocity, result;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "PROJECTILE MOTION" << endl;
        cout << "Maximum height of flight" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'pmotionHeight.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Find maximum height of flight when given" << endl;
            cout << "Angle (rad)..............: ";
            cin >> angle;
            cout << "Initial height (m).......: ";
            cin >> height;
            cout << "Velocity (m/s)...........: ";
            cin >> velocity;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.P_maxHeight(angle,height,velocity);
            cout << "Max Height (m)...........: " << Formula.showMaxHeight() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showMaxHeight() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("pmotionHeight.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> angle >> height >> velocity;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Angle (rad).............: " << angle << endl;
                    cout << "Initial Height (m)......: " << height << endl;
                    cout << "Velocity (m/s)..........: " << velocity << endl;
                    Formula.P_maxHeight(angle,height,velocity);
                    cout << "Max Height(m)...........: " << Formula.showMaxHeight() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showMaxHeight() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        
        op = getch();

    } while(op != 'e');
}

void P_finalVelocity()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double angle, height, velocity, result;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "PROJECTILE MOTION" << endl;
        cout << "Final velocity when the object hits the ground" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'pmotionfinalVelocity.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Find maximum height of flight when given" << endl;
            cout << "Angle (deg).......................: ";
            cin >> angle;
            cout << "Initial height (m)................: ";
            cin >> height;
            cout << "Velocity (m/s)....................: ";
            cin >> velocity;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.P_finalVelocity(angle,height,velocity);
            cout << "Final velocity x-direction (m/s)..: " << Formula.showVfx() << endl;
            cout << "Final velocity y-direction (m/s)..: " << Formula.showVfy() << endl;
            cout << "Final velocity (m/s)..............: " << Formula.showVelocity() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showVelocity() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("pmotionfinalVelocity.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> angle >> height >> velocity;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Angle (rad).............: " << angle << endl;
                    cout << "Initial Height (m)......: " << height << endl;
                    cout << "Velocity (m/s)..........: " << velocity << endl;
                    Formula.P_finalVelocity(angle,height,velocity);
                    cout << "Final velocity x-direction (m/s)..: " << Formula.showVfx() << endl;
                    cout << "Final velocity y-direction (m/s)..: " << Formula.showVfy() << endl;
                    cout << "Final velocity (m/s)..............: " << Formula.showVelocity() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showVfx() << " " << Formula.showVfy() << " " << Formula.showVelocity() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        
        op = getch();

    } while(op != 'e');
}

// free fall menu
void F_Time_Velocity()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double iVelocity, fVelocity;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "FREE FALL" << endl;
        cout << "Time of fall given velocity" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'timeVelocity.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Find time of fall given" << endl;
            cout << "Initital velocity (m/s)..: ";
            cin >> iVelocity;
            cout << "Final velocity (m/s).....: ";
            cin >> fVelocity;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.F_Time_Velocity(iVelocity,fVelocity);
            cout << "Time (s).................: " << Formula.showTime() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showTime() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("timeVelocity.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> iVelocity >> fVelocity;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Initital velocity (m/s)..: " << iVelocity << endl;
                    cout << "Final velocity (m/s).....: " << fVelocity << endl;
                    Formula.F_Time_Velocity(iVelocity,fVelocity);
                    cout << "Time (s).................: " << Formula.showTime() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showTime() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        op = getch();

    } while(op != 'e');
}
void F_Time_Height()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double iVelocity, height;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "FREE FALL" << endl;
        cout << "Time of fall given Height" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'timeHeight.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Find time of fall given" << endl;
            cout << "Initital velocity (m/s)..: ";
            cin >> iVelocity;
            cout << "Height of fall (m).......: ";
            cin >> height;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.F_Time_Height(iVelocity,height);
            cout << "Time (s).................: " << Formula.showTime() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showTime() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("timeHeight.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> iVelocity >> height;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Initital velocity (m/s)..: " << iVelocity << endl;
                    cout << "Height of fall...........: " << height << endl;
                    Formula.F_Time_Height(iVelocity,height);
                    cout << "Time (s).................: " << Formula.showTime() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showTime() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        
        op = getch();

    } while(op != 'e');
}
void F_Height_Velocity()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double iVelocity, fVelocity;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "FREE FALL" << endl;
        cout << "Height of fall given velocity" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'heightVelocity.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Find height of fall given" << endl;
            cout << "Initital velocity (m/s)..: ";
            cin >> iVelocity;
            cout << "Final velocity (m/s).....: ";
            cin >> fVelocity;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.F_Height_Velocity(iVelocity,fVelocity);
            cout << "Height (m)...............: " << Formula.showHeight() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showHeight() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("heightVelocity.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> iVelocity >> fVelocity;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Initital velocity (m/s)..: " << iVelocity << endl;
                    cout << "Final velocity (m/s).....: " << fVelocity << endl;
                    Formula.F_Height_Velocity(iVelocity,fVelocity);
                    cout << "Height (m)...............: " << Formula.showHeight() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showHeight() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        
        op = getch();

    } while(op != 'e');
}
void F_Height_Time()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double iVelocity, time;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "FREE FALL" << endl;
        cout << "Height of fall given time" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'heightTime.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Find height of fall given" << endl;
            cout << "Initital velocity (m/s)..: ";
            cin >> iVelocity;
            cout << "Time of fall (s).........: ";
            cin >> time;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.F_Height_Time(iVelocity,time);
            cout << "Height (m)...............: " << Formula.showHeight() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showHeight() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("heightVelocity.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> iVelocity >> time;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Initital velocity (m/s)..: " << iVelocity << endl;
                    cout << "Final velocity (m/s).....: " << time << endl;
                    Formula.F_Height_Time(iVelocity,time);
                    cout << "Height (m)...............: " << Formula.showHeight() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showHeight() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        
        op = getch();

    } while(op != 'e');
}
void F_Velocity_Height()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double iVelocity, height;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "FREE FALL" << endl;
        cout << "Velocity of fall given height" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'velocityHeight.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Find velocity of fall given" << endl;
            cout << "Initital velocity (m/s)..: ";
            cin >> iVelocity;
            cout << "Height of fall (m).......: ";
            cin >> height;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.F_Velocity_Height(iVelocity,height);
            cout << "Velocity (m/s)...........: " << Formula.showVelocity() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showVelocity() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("velocityHeight.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> iVelocity >> height;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Initital velocity (m/s)..: " << iVelocity << endl;
                    cout << "Height of fall (m).......: " << height << endl;
                    Formula.F_Velocity_Height(iVelocity,height);
                    cout << "Velocity (m/s)...........: " << Formula.showVelocity() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showVelocity() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        
        op = getch();

    } while(op != 'e');
}
void F_Velocity_Time()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double iVelocity, time;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "FREE FALL" << endl;
        cout << "Velocity of fall given height" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'velocityTime.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Find velocity of fall given" << endl;
            cout << "Initital velocity (m/s)..: ";
            cin >> iVelocity;
            cout << "Time of fall (m).........: ";
            cin >> time;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.F_Velocity_Time(iVelocity,time);
            cout << "Height (m)...............: " << Formula.showVelocity() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showVelocity() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("velocityTime.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> iVelocity >> time;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Initital velocity (m/s)..: " << iVelocity << endl;
                    cout << "Time of fall (s).........: " << time << endl;
                    Formula.F_Velocity_Time(iVelocity,time);
                    cout << "Velocity (m/s)...............: " << Formula.showVelocity() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showVelocity() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        
        op = getch();

    } while(op != 'e');
}

// horizontal motion menu
void H_TimeOfFlight()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double height, velocity;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "HORIZONTAL PROJECTILE MOTION" << endl;
        cout << "Time of flight" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'hpmotionTime.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "HORIZONTAL PROJECTILE MOTION" << endl;
            cout << "Time of flight given" << endl;
            cout << "Initital height (m)..: ";
            cin >> height;
            cout << "Velocity (m/s).......: ";
            cin >> velocity;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.H_TimeOfFlight(height,velocity);
            cout << "Time (s).............: " << Formula.showTime() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showTime() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "HORIZONTAL PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("hpmotionTime.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> height >> velocity;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Initital Height (m)..: " << height << endl;
                    cout << "Velocity (m/s).......: " << velocity << endl;
                    Formula.H_TimeOfFlight(height,velocity);
                    cout << "Time (s).............: " << Formula.showTime() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showTime() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        
        op = getch();

    } while(op != 'e');
}
void H_Range()
{
    formula Formula;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    double height, velocity;
    char op, output;
    char menu;

    do{

        system("cls");
        cout << "HORIZONTAL PROJECTILE MOTION" << endl;
        cout << "Range" << endl;
        cout << "1 - Enter data by typing" << endl;
        cout << "2 - Enter data by input file 'hpmotionRange.txt'" << endl;
        cout << "3 - back" << endl;
        cout << "Enter: ";
        menu = getche();
        
        if(menu == '1'){

            output = Output(oFile, path);

            system("cls");
            cout << "HORIZONTAL PROJECTILE MOTION" << endl;
            cout << "Range" << endl;
            cout << "Initital height (m)..: ";
            cin >> height;
            cout << "Velocity (m/s).......: ";
            cin >> velocity;

            cout << std::setprecision(2) << std::fixed << endl;
            Formula.H_Range(height,velocity);
            cout << "Range (m)............: " << Formula.showRange() << endl;
            cout << endl;

            if(output == 'Y' || output == 'y'){
                oFile << Formula.showRange() << endl;
            }
            oFile.close();

        } else if(menu == '2'){

            output = Output(oFile,path);

            system("cls");
            cout << "HORIZONTAL PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("hpmotionRange.txt");

            if(nFile){
                while(!nFile.eof()){
                    nFile >> height >> velocity;
                    cout << std::setprecision(2) << std::fixed << endl;
                    cout << "Initital Height (m)..: " << height << endl;
                    cout << "Velocity (m/s).......: " << velocity << endl;
                    Formula.H_Range(height,velocity);
                    cout << "Range (s)............: " << Formula.showRange() << endl;
                    cout << endl;

                    if(output == 'Y' || output == 'y'){
                        oFile << Formula.showRange() << endl;
                    }
                }
                nFile.close();
                oFile.close();
            } else {
                cout << "Error opening the file!" << endl;
            }
        
        } else if(menu == '3')
            break;
        
        if(menu == '1' || menu == '2')
            cout << "Press any key to repeat the calculation or press 'e' to back" << endl;
        
        op = getch();

    } while(op != 'e');
}
