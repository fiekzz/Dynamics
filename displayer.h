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


#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include "dynamics.h"

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

// # Initialize the console (terminal) location
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void Exit();
void Output();
void inputMenu();

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

struct questionItems {
    // menu string
    std::string choice;
    // menu function
    void (*callback)(std::string[]);
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


void ShowMenu(int menuSize, MenuItems menus[], std::string menuTitle = "", bool isBack = false)
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
            std::cout << std::endl;
            std::cout << "Enter the name of file including file extension (.txt): ";
            std::cin.ignore();
            getline(std::cin,path);
            oFile.open(path, std::fstream::app);
            if(!oFile.is_open())
                std::cout << "Error opening the existing output file" << std::endl;
            
        } while(!oFile.is_open());
    }
    // return y/n
    return output;
}


#endif
