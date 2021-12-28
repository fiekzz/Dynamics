#ifndef __DISPLAYER_H
#define __DISPLAYER_H
#pragma once

/* 
    DISPLAYER HEADER FILE
    Help the main source file to run smoothly for the program and the user
    Contain:
    - font color
    - font size
    - coordinate to display the menu and data
*/


#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

// # Initialize the console (terminal) location
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

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

#endif
