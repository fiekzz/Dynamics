#ifndef __DISPLAYER_H
#define __DISPLAYER_H
#pragma once

/* 
    DISPLAYER HEADER FILE
    Help the main source file to run smoothly for the program and the user
    Contains:
    - font color
    - font size
    - coordinate to display the menu and data
    - close cursor
*/

// mirin
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include "dynamics.h"

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

// # Initialize the console (terminal) location
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

using std::cout;
using std::cin;
using std::endl;

// # A function to change the color of the font
// font color
void Color(int color){
    // set the color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// menu displayer
void gotoxy(int x, int y){
    // set the cursor position in x direction
    CursorPosition.X = x;
    // set the cursor position in y direction
    CursorPosition.Y = y;
    // detemine the cursor position
    SetConsoleCursorPosition(console, CursorPosition);
}

// setfont for the program
void setfont(){
    // declare font
    CONSOLE_FONT_INFOEX font;
    font.cbSize = sizeof(font);
    font.nFont = 0;
    font.dwFontSize.X = 0;
    font.dwFontSize.Y = 24;
    // font family
    font.FontFamily = FF_DONTCARE;
    // font weight
    font.FontWeight = FW_NORMAL;
    // type of font in the font family
    wcscpy(font.FaceName, L"Consolas");
    // set the font according to the settings
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
}

// set cursor on/off
void ShowConsoleCursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

// menu items object
struct MenuItems {
    // menu string
    std::string choice;
    // menu function
    void (*callback)();
};
// question items object
struct questionItems {
    std::string question[3];
    std::string answer[3];
    int type;
    int size;
};

/**
 * @brief A function to render arrow menu
 * 
 * @param x Accepts coord-x start
 * @param y Accepts coord-y start
 * @param menuSize The max number of menu list
 * @param menus A struct that contains menu option and callback Function
 * @param menu A struct that contains menu option and callback
 * @param menuTitle Menu Title
 * @param isBack Boolean for determining is previous screen available
 */
// menu function to display menu and call function

void Exit();
bool Output(std::fstream &, std::string &);
void inputData(int,questionItems, std::string);
double calcQuestion(int,double[3],double[3]);
// void inputMenu();
// double calcQuestion();

void showMenu(int menuSize, MenuItems menus[], std::string menuTitle = "", bool isBack = false)
{
    // const location to display menu
    const int xStart = 5, yStart = 4;
    // menu item location in array object
    int menu_item = 0;
    // location of x in y direction
    int x = yStart;

    while(true) {

        // display cursor
        gotoxy(2, x); Color(4); std::cout << "\x1a"; Color(3);
        // display title for menu items
        gotoxy(xStart, yStart - 2); std::cout << menuTitle << std::endl;
        // loop to display menu items
        for (int i = 0; i < menuSize; i++)
        {
            gotoxy(xStart, yStart + i); 
            std::cout << menus[i].choice << std::endl;
        }
        // check if there is another page before the displaying page
        // if there is, loop will break to go to previous page
        // otherwise, loop will break and run exit function to exit the program
        gotoxy(xStart, yStart + menuSize);
        std::cout << (isBack ? "Back" : "Exit") << std::endl;
        // display instructions
        gotoxy(5, 15); std::cout << "\x18  - Up" << std::endl;
        gotoxy(5, 16); std::cout << "\x19  - Down" << std::endl;
        gotoxy(5, 17); std::cout << "[ENTER] - Select" << std::endl;
        gotoxy(5, 18); std::cout << "[ESC] - Back" << std::endl;
        // gettting input key
        system("pause>nul");

        // put the cursor down by 1 until the lowest choice of menu
        if(GetAsyncKeyState(VK_DOWN) < 0 && x != yStart + menuSize) //down button pressed
        {
            gotoxy(2, x); std::cout << "  ";
            x++;
            menu_item++;
            continue;
        }
        // put the cursor up by 1 until the highest choice of menu
        else if(GetAsyncKeyState(VK_UP) < 0 && x != yStart) //up button pressed
        {
            gotoxy(2, x); std::cout << "  ";
            x--;
            menu_item--;
            continue;
        }
        else if(GetAsyncKeyState(VK_RETURN) < 0) // Enter key pressed
        {
            // check if the selected menu is the last choice 'back'
            if (menu_item == menuSize) {
                if (isBack) {
                    system("cls"); break; // if yes, break the loop and go to prev page
                } else {
                    Exit(); // if there is no prev page, exit function will be called
                }
            } else {
                menus[menu_item].callback(); // call the function according to the choice
                system("cls");
            }

		}
        else if(GetAsyncKeyState(VK_ESCAPE) < 0)
        {
            if (isBack) { // if 'back' button has been chosen, break the loop and go to prev page
                system("cls");
                break;
            } else {
                Exit(); // if there is no prev page, exit function will be called
            }
        }
    }
}

void ShowMenu(std::string menuTitle, std::string menuQuestion, std::string inputFile, questionItems Item){
    
    system("cls");
    // const location to display menu
    const int xStart = 5, yStart = 4;
    // menu item location in array object
    int menu_item = 0;
    // location of x in y direction
    int x = yStart;

    int menuSize = 2;

    while(true) {

        gotoxy(2,x); Color(4); std::cout << "\x1a"; Color(3);
        // display title for menu items
        gotoxy(xStart, yStart - 2); std::cout << menuTitle << " - " << menuQuestion << std::endl;

        gotoxy(xStart, yStart); std::cout << "Enter data by typing" << endl;
        gotoxy(xStart, yStart + 1); std::cout << "Enter data by input file " << inputFile << endl;

        // check if there is another page before the displaying page
        // if there is, loop will break to go to previous page
        // otherwise, loop will break and run exit function to exit the program
        gotoxy(xStart, yStart + menuSize); std::cout << "Back" << endl;
        
        // display instructions
        gotoxy(5, 15); std::cout << "\x18  - Up" << std::endl;
        gotoxy(5, 16); std::cout << "\x19  - Down" << std::endl;
        gotoxy(5, 17); std::cout << "[ENTER] - Select" << std::endl;
        gotoxy(5, 18); std::cout << "[ESC] - Back" << std::endl;
        // gettting input key
        system("pause>nul");

        // put the cursor down by 1 until the lowest choice of menu
        if(GetAsyncKeyState(VK_DOWN) < 0 && x != yStart + menuSize) //down button pressed
        {
            gotoxy(2, x); std::cout << "  ";
            x++;
            menu_item++;
            continue;
        }
        // put the cursor up by 1 until the highest choice of menu
        else if(GetAsyncKeyState(VK_UP) < 0 && x != yStart) //up button pressed
        {
            gotoxy(2, x); std::cout << "  ";
            x--;
            menu_item--;
            continue;
        }
        else if(GetAsyncKeyState(VK_RETURN) < 0) // Enter key pressed
        {
            // check if the selected menu is the last choice 'back'
            if (menu_item == menuSize) {
                system("cls");
                break;
            } else {
                inputData(menu_item,Item,inputFile);
                system("cls");
            }

		}
        else if(GetAsyncKeyState(VK_ESCAPE) < 0)
        {
            system("cls");
            break;
        }

    }
}

void inputData(int menu_item, questionItems Item, std::string inputFile)
{
    bool output;
    std::ifstream nFile;
    std::fstream oFile;
    std::string path;
    formula Formula;
    double angle,height,velocity,result;
    double input[5];
    int i, space = 2;
    int type = Item.type;
    double answer3[3];
    double answer;
    // const location to display menu
    const int xStart = 5, yStart = 4;
    if(menu_item == 0)
    {
        output = Output(oFile,path);
        system("cls");
        
        for(i = 0; i < Item.size; i++){
            gotoxy(xStart,yStart + i); cout << Item.question[i]; ShowConsoleCursor(true); cin >> input[i]; ShowConsoleCursor(false);
        }
        cin.ignore();

        answer = calcQuestion(type,input,answer3);

        if(answer == -3){
            for(int j = 0; j < 3; j++){
                gotoxy(xStart,yStart + i + j + 1); cout << Item.answer[j] << answer3[j] << endl;
            }
        } else {
            gotoxy(xStart,yStart + i + 1); cout << Item.answer[0] << answer << endl;
        }
        
        if(output)
        {
            if(answer == -3){
                for(int j = 0; j < 3; j++){
                    oFile << answer3[j] << endl;
                }
            } else {
                oFile << answer << endl;
            }
            oFile.close();
        }
        space += Item.size;
        
    } else if(menu_item == 1){
        gotoxy(xStart, yStart - 2); cout << "Obtaining the file.." << endl;
        nFile.open(inputFile);
        output = Output(oFile,path);
        system("cls");
        if(nFile){
            
            while(!nFile.eof()){
                if(type <= 3){
                    nFile >> input[0] >> input[1] >> input[2];
                }   
                else {
                    nFile >> input[0] >> input[1];
                }
                    
                for(i = 0; i < Item.size; i++){
                    gotoxy(xStart,yStart + i); cout << Item.question[i] << input[i] << endl;
                }

                answer = calcQuestion(type,input,answer3);

                if(answer == -3){
                    for(int j = 0; j < 3; j++){
                        gotoxy(xStart,yStart + i + j + 1); cout << Item.answer[j] << answer3[j] << endl;
                    }
                } else {
                    gotoxy(xStart,yStart + i + 1); cout << Item.answer[0] << answer << endl;
                }

                if(output){
                    if(answer == -3){
                        for(int j = 0; j < 3; j++){
                            oFile << answer3[j] << endl;
                        }
                    } else {
                        oFile << answer << endl;
                    }
                }
                space += Item.size;
            }
            oFile.close();
            nFile.close();
        } else {
            gotoxy(xStart,yStart); cout << "Error opening the file!" << endl;
        }
    }
    
    gotoxy(xStart, yStart + i + space); system("pause");
    system("cls");
}

double calcQuestion(int type, double input[3], double answer3[3])
{
    formula Formula;
    switch(type)
    {
        case 0: Formula.P_timeOfFlight(input[0],input[1],input[2]); return Formula.showTime();
        case 1: Formula.P_range(input[0],input[1],input[2]); return Formula.showRange();
        case 2: Formula.P_maxHeight(input[0],input[1],input[2]); return Formula.showMaxHeight();
        case 3: Formula.P_finalVelocity(input[0],input[1],input[2]);
                answer3[0] = Formula.showVfx();
                answer3[1] = Formula.showVfy();
                answer3[2] = Formula.showVelocity(); return -3;
        case 4: Formula.F_Time_Velocity(input[0],input[1]); return Formula.showTime();
        case 5: Formula.F_Time_Height(input[0],input[1]); return Formula.showTime();
        case 6: Formula.F_Height_Velocity(input[0],input[1]); return Formula.showHeight();
        case 7: Formula.F_Height_Time(input[0],input[1]); return Formula.showHeight();
        case 8: Formula.F_Velocity_Height(input[0],input[1]); return Formula.showVelocity();
        case 9: Formula.F_Velocity_Time(input[0],input[1]); return Formula.showVelocity();
        case 10: Formula.H_TimeOfFlight(input[0],input[1]); return Formula.showTime();
        case 11: Formula.H_Range(input[0],input[1]); return Formula.showRange();
    }
    return 404;
}

// exit
void Exit()
{
    system("cls");
    // ask comfirmation
    gotoxy(5,3); std::cout << "Exit the program?" << std::endl;
    gotoxy(5,5); std::cout << "[ENTER] - Yes" << std::endl;
    gotoxy(5,6); std::cout << "Any Key - No" << std::endl;

    system("pause>nul");
    // exit program if the user comfirmed to exit
    if(GetAsyncKeyState(VK_RETURN)){
        system("cls");
        exit(0);
    }
    system("cls");
}

// output file
// return a char which is Y-yes or N-no to the function
#include <string>

bool Output(std::fstream &oFile, std::string &path)
{
    // char output;
    system("cls");
    // const location to display menu
    const int xStart = 5, yStart = 4;
    // menu item location in array object
    int menu_item = 0;
    // location of x in y direction
    int x = yStart;
    int menuSize = 2;

    while(true) {

        gotoxy(2,x); Color(4); std::cout << "\x1a"; Color(3);
        // display title for menu items
        gotoxy(xStart, yStart - 2); std::cout << "Do you want to put the results into an output file?" << std::endl;
        gotoxy(xStart, yStart); std::cout << "Yes" << endl;
        gotoxy(xStart, yStart + 1); std::cout << "No" << endl;

        
        // display instructions
        gotoxy(5, 15); std::cout << "\x18  - Up" << std::endl;
        gotoxy(5, 16); std::cout << "\x19  - Down" << std::endl;
        gotoxy(5, 17); std::cout << "[ENTER] - Select" << std::endl;
        // gettting input key
        system("pause>nul");

        // put the cursor down by 1 until the lowest choice of menu
        if(GetAsyncKeyState(VK_DOWN) < 0 && x != yStart + menuSize) //down button pressed
        {
            gotoxy(2, x); std::cout << "  ";
            x++;
            menu_item++;
            continue;
        }
        // put the cursor up by 1 until the highest choice of menu
        else if(GetAsyncKeyState(VK_UP) < 0 && x != yStart) //up button pressed
        {
            gotoxy(2, x); std::cout << "  ";
            x--;
            menu_item--;
            continue;
        }
        else if(GetAsyncKeyState(VK_RETURN) < 0) // Enter key pressed
        {
            if(menu_item == 0){
                system("cls");
                ShowConsoleCursor(true);
                gotoxy(xStart,yStart); cout << "Enter the name of file including file extension (.txt): "; getline(cin,path);
                ShowConsoleCursor(false);
                oFile.open(path, std::fstream::app);
                return true;
            } else if(menu_item == 1){
                return false;
            }

		}

    }
}

#endif
