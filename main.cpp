#include <iostream>
#include <iomanip>
#include <fstream>
#include <dos.h>
#include <time.h>
#include <string>
#include "dynamics.h"
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
    // set the font for the program
    setfont();
    // set the font color for the program
    Color(3);
    // set cursor off
    ShowConsoleCursor(false);
    // initialize menu selection
    // menu item to select menu
    // x coordinate in y direction to display the menu
    int menu_item = 0, x = 4;

    while(1){

        // the input is only valid for arrow-up, arrow-down, enter and escape button
        // if the up / down is at its limit it will pass
        gotoxy(2,x); Color(4); cout << "\x1a"; Color(3);
        gotoxy(5,2); cout << "MECHANICS [Dynamics]" << endl;
        gotoxy(5,4); cout << "Projectile Motion" << endl;
        gotoxy(5,5); cout << "Free Fall" << endl;
        gotoxy(5,6); cout << "Horizontal Projectile Motion" << endl;
        gotoxy(5,7); cout << "Info" << endl;
        gotoxy(5,8); cout << "Exit" << endl;
        // instructions
        gotoxy(5,15); cout << "\x18  - Up" << endl;
        gotoxy(5,16); cout << "\x19  - Down" << endl;
        gotoxy(5,17); cout << "[ENTER] - Select" << endl;
        gotoxy(5,18); cout << "[ESC] - Back" << endl;

        // pause the system without displaying the message
        system("pause>nul");

        // Put the cursor down by 1
        if(GetAsyncKeyState(VK_DOWN) < 0 && x != 8) //down button pressed
        {
            gotoxy(2,x); cout << "  ";
            x++;
            menu_item++;
            continue;
        }
		// Put the cursor up by 1
		else if(GetAsyncKeyState(VK_UP) < 0 && x != 4) //up button pressed
        {
            gotoxy(2,x); cout << "  ";
            x--;
            menu_item--;
            continue;
        }
        // if the user pressed entered for the menu
        else if(GetAsyncKeyState(VK_RETURN) < 0){ // Enter key pressed

            switch(menu_item){
                case 0: projectileMotion(); break;
                case 1: freeFall(); break;
                case 2: HorizontalPMotion(); break;
                case 3: Info(); break;
                case 4: Exit(); break;
            }
            
		}
        else if(GetAsyncKeyState(VK_ESCAPE) < 0){
            Exit();
        }
    }
}

// output file
// return a char which is Y-yes or N-no to the function
char Output(std::fstream &oFile, std::string &path)
{
    char output;

    // loop to get the input from the user
    do{
        std::cout << std::endl;
        std::cout << "Do you want to put the results into an output file? (Y/N)" << std::endl;
        std::cout << "Enter: ";
        output = getche();
    } while(output != 'y' && output != 'Y' && output != 'n' && output != 'N');

    // Open the output file if the user already have the saved file
    if(output == 'Y' || output == 'y'){

        // The program will loop if the output file is undefined
        do{
            cout << endl;
            std::cout << "Enter the name of file including file extension (.txt): ";
            cin.ignore();
            getline(cin,path);
            oFile.open(path, std::fstream::app);
            if(!oFile.is_open())
                std::cout << "Error opening the existing output file" << std::endl;
            
        } while(!oFile.is_open());
    }
    // return y/n
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
    system("cls");
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
    system("cls");
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
    system("cls");
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
    gotoxy(5,7); cout << "# twitter.com/fikieee11" << endl;
    gotoxy(5,9); system("pause");
    system("cls");

}

// exit
void Exit()
{
    system("cls");
    
    gotoxy(5,3); cout << "Exit the program?" << endl;
    gotoxy(5,5); cout << "[ENTER] - Yes" << endl;
    gotoxy(5,6); cout << "Any Key - No" << endl;

    system("pause>nul");

    if(GetAsyncKeyState(VK_RETURN)){
        system("cls");
        exit(0);
    }
    system("cls");
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

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("pmotionTime.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("pmotionRange.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("pmotionHeight.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("pmotionfinalVelocity.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("timeVelocity.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("timeHeight.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("heightVelocity.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("heightVelocity.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("velocityHeight.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "FREE FALL" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("velocityTime.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "HORIZONTAL PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("hpmotionTime.txt");

            if(nFile){
                output = Output(oFile,path);
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

            system("cls");
            cout << "HORIZONTAL PROJECTILE MOTION" << endl;
            cout << "Obtaining the file.." << endl;
            nFile.open("hpmotionRange.txt");

            if(nFile){
                output = Output(oFile,path);
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
