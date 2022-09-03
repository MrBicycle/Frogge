/*
    Frogge -v0.0
    Jeff Dickson
    Aug 29 2022

    This is a terminal version of the acade game "Frogger" done as a programming exercise
*/

#include <iostream>
#include <vector>
#include <Windows.h>
#include <thread>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

int nTerminalWidth = 80;
int nTerminalHeight = 25;
bool bGameOver = false;
int nGameState = 0;
int nTicTock = 3;
int nFrogX = 16;
int nFrogY = 23;
int nStartLocationX = 16; //Where should we put the frog after dying or getting to the end
int nStartLocationY = 23;
const int nArenaWidthX = 29;
const int nArenaHeightY = 23;
bool bFrogHit = false;
int nLives = 3;
bool bMovedY = false;

int nSlowCarCoordX = 2;
int nSlowCarCoordY = 21;
int nMedCarCoordY = 19;
int nFastCarCoordY = 17;

int nLogsCoordX = 2;
int nLogs1CoordY = 11;
int nLogs2CoordY = 9;
int nLogs3CoordY = 7;

int nScore = 0;
bool bFrogWin = false;

//function to move frog arround, does not account for collisions
int MoveDirX(bool arrowIn[]) {
    if (arrowIn[0] == true) {
        return 1;
    }
    if (arrowIn[2] == true) {
        return -1;
    }
    return 0;
} 
int MoveDirY(bool arrowIn[]) {
    if (arrowIn[1] == true) {
        return 2;
    }
    if (arrowIn[3] == true) {
        return -2;
    }
    return 0;
}

//function to check if this item is overlapping the frog
bool HitFrog(string ) {
    return false;
}

int ShiftString(string inputString[]) {
    string tempChar = inputString[0];
    for (int i = 0; i < nArenaWidthX - 1; i++) {
        inputString[i] = inputString[i+1];
    }
    inputString[nArenaWidthX - 1] = tempChar;
    return 0;
}

int main()
{
    /*====================Turn on Setup====================*/
    //Using screen buffer
    wchar_t* screen = new wchar_t[nTerminalWidth * nTerminalHeight];
    for (int n = 0; n < nTerminalWidth * nTerminalHeight; n++) {
        screen[n] = L' ';
    }
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    //Create string array to hold visuals
    string sScreens[3];
    {
        sScreens[0].append("................................................................................");//1
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append(".....................................Frogge.....................................");
        sScreens[0].append("................................................................................");//5
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");//10
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("........................Press the arrow buttons to start........................");//15
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................Jeff Dickson 2022...............................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");//20
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");
        sScreens[0].append("................................................................................");//25



        sScreens[1].append("................................................................................");//1 (Our playable boundries are: x:2~29 y: )
        sScreens[1].append("................................................................................");
        sScreens[1].append(".===============================................................................");//X Win Zone
        sScreens[1].append(".|........|...........|........|................................................");
        sScreens[1].append(".|........|...........|........|................................................");//5
        sScreens[1].append(".|........|...........|........|................................................");//X Slow Logs
        sScreens[1].append(".|^.^.^.^.^.^.^.^.^.^.^.^.^.^.^|................................................");
        sScreens[1].append(".|.^.^.^.^.^.^.^.^.^.^.^.^.^.^.|................................................");//X Fast Logs 
        sScreens[1].append(".|^.^.^.^.^.^.^.^.^.^.^.^.^.^.^|................................................");
        sScreens[1].append(".|.^.^.^.^.^.^.^.^.^.^.^.^.^.^.|................................................");//10X Slow Logs Left
        sScreens[1].append(".|^.^.^.^.^.^.^.^.^.^.^.^.^.^.^|................................................");
        sScreens[1].append(".|.^.^.^.^.^.^.^.^.^.^.^.^.^.^.|................................................");//X Slow Logs
        sScreens[1].append(".|^.^.^.^.^.^.^.^.^.^.^.^.^.^.^|................................................");
        sScreens[1].append(".|.............................|................................................");//X Safe Zone
        sScreens[1].append(".|.............................|................................................");//15
        sScreens[1].append(".|.............................|................................................");//X Safe Zone
        sScreens[1].append(".|-----------------------------|................................................");
        sScreens[1].append(".|.............................|................................................");//X Fast Cars
        sScreens[1].append(".|-..-..-..-..-..-..-..-..-..-.|................................................");
        sScreens[1].append(".|.............................|................................................");//20X Medium Cars
        sScreens[1].append(".|.-..-..-..-..-..-..-..-..-..-|................................................");
        sScreens[1].append(".|.............................|................................................");//X Slow Cars
        sScreens[1].append(".|-..-..-..-..-..-..-..-..-..-.|................................................");
        sScreens[1].append(".|.............................|................................................");//X
        sScreens[1].append(".===============================................................................");//25

        sScreens[2].append("................................................................................");//1 (Our playable boundries are: x:2~29 y: )
        sScreens[2].append("................................................................................");
        sScreens[2].append(".===============================................................................");//X Win Zone
        sScreens[2].append(".|........|...........|........|................................................");
        sScreens[2].append(".|........|...........|........|................................................");//5
        sScreens[2].append(".|........|...........|........|................................................");//X Slow Logs
        sScreens[2].append(".|.^.^.^.^.^.^.^.^.^.^.^.^.^.^.|................................................");
        sScreens[2].append(".|^.^.^.^.^.^.^.^.^.^.^.^.^.^.^|................................................");//X Fast Logs 
        sScreens[2].append(".|.^.^.^.^.^.^.^.^.^.^.^.^.^.^.|................................................");
        sScreens[2].append(".|^.^.^.^.^.^.^.^.^.^.^.^.^.^.^|................................................");//10X Slow Logs Left
        sScreens[2].append(".|.^.^.^.^.^.^.^.^.^.^.^.^.^.^.|................................................");
        sScreens[2].append(".|^.^.^.^.^.^.^.^.^.^.^.^.^.^.^|................................................");//X Slow Logs
        sScreens[2].append(".|.^.^.^.^.^.^.^.^.^.^.^.^.^.^.|................................................");
        sScreens[2].append(".|.............................|................................................");//X Safe Zone
        sScreens[2].append(".|.............................|................................................");//15
        sScreens[2].append(".|.............................|................................................");//X Safe Zone
        sScreens[2].append(".|-----------------------------|................................................");
        sScreens[2].append(".|.............................|................................................");//X Fast Cars
        sScreens[2].append(".|-..-..-..-..-..-..-..-..-..-.|................................................");
        sScreens[2].append(".|.............................|................................................");//20X Medium Cars
        sScreens[2].append(".|.-..-..-..-..-..-..-..-..-..-|................................................");
        sScreens[2].append(".|.............................|................................................");//X Slow Cars
        sScreens[2].append(".|-..-..-..-..-..-..-..-..-..-.|................................................");
        sScreens[2].append(".|.............................|................................................");//X
        sScreens[2].append(".===============================................................................");//25

    }

    string sSlowCar = "||]..........[|||].........[|";
    string sMedCar =  "[||8]..........[||8].........";
    string sFastCar = "{++]<..........{++]<.........";
    string sLogs =  "===^....==========^...=======";
    string sLogs2 = "===.....^=========.....^=====";
    string sLogs3 = "===^......========^......====";

    bool bKey[4]; // create array to hold active keyboard inputs

    while (!bGameOver) {
        /*====================Timing====================*/
        this_thread::sleep_for(100ms);
        if (nTicTock >= 3) { //count 0 1 2 3 used to time some elements of the game
            nTicTock = 0;
        }
        else {
            nTicTock++;
        }

        /*====================Input====================*/
        for (int k = 0; k < 4; k++) { //loops through the bkey array and activates element related to the given hexidecimal values
            auto keyHexes = "\x25\x26\x27\x28"; //left up right down
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)(keyHexes[k]))) != 0;
        }
        switch (nGameState) {
        case 0: //Start Screen nScreens index 0 any arrow input starts the game
        {/*====================Game Logic====================*/
            for (int k = 0; k < 4; k++) {//if any input, start the game, loop needs to be same length as input array
                if (bKey[k] == true) {
                    nGameState = 1;
                }
            }


            /*====================Render to Screen====================*/
            for (int x = 0; x < nTerminalWidth; ++x) {
                for (int y = 0; y < nTerminalHeight; ++y) {

                    if (sScreens[0][(y * nTerminalWidth) + x] != '.') {
                        screen[(y)*nTerminalWidth + (x)] = sScreens[0][(y * nTerminalWidth) + x];
                    }
                    else {
                        screen[(y)*nTerminalWidth + (x)] = ' ';
                    }
                }
            }
            break; }
        
        case 1:
            /*====================Game Logic====================*/
            if (bFrogHit == true) { //if hit decrement lives
                nLives--;
                if (nLives > 0) {
                    nFrogX = nStartLocationX;
                    nFrogY = nStartLocationY;
                    this_thread::sleep_for(1000ms);
                    bFrogHit = false;
                }
                else {
                    bGameOver = true;
                }
            }

            //If Win Flag Set
            if (bFrogWin == true) {
                nScore += 1000;
                nFrogX = nStartLocationX;
                nFrogY = nStartLocationY;
                this_thread::sleep_for(500ms);
                bFrogWin = false;
            }

            //input from arrows move frog
            if ((nFrogX - MoveDirX(bKey)) < nArenaWidthX + 2 && (nFrogX - MoveDirX(bKey)) > 1) {
                nFrogX -= MoveDirX(bKey);
            }
            if ((nFrogY - MoveDirY(bKey)) < nTerminalHeight - 1 && (nFrogY - MoveDirY(bKey)) > 1 && bMovedY == false) {
                nFrogY -= MoveDirY(bKey);
                if (MoveDirY(bKey) != 0) {
                    bMovedY = true;
                }
            }
            if (MoveDirY(bKey) == 0) {
                bMovedY = false;
            }

            //move slow speed car Index
            char tempChar;
            if (nTicTock == 0) {
                tempChar = sSlowCar[0];
                for (int i = 0; i < nArenaWidthX - 1; i++) {
                    sSlowCar[i] = sSlowCar[i + 1];
                }
                sSlowCar[nArenaWidthX - 1] = tempChar;
            }

            //move medium speed car Index
            if (nTicTock == 0 || nTicTock == 2) {
                tempChar = sMedCar[nArenaWidthX - 1];
                for (int i = 0; i < nArenaWidthX - 1; i++) {
                    sMedCar[nArenaWidthX - i - 1] = sMedCar[nArenaWidthX - i - 2];
                }
                sMedCar[0] = tempChar;
            }

            //move fast speed car Index
            tempChar = sFastCar[0];
            for (int i = 0; i < nArenaWidthX - 1; i++) {
                sFastCar[i] = sFastCar[i + 1];
            }
            sFastCar[nArenaWidthX - 1] = tempChar;

            //move slow log index and frog if on
            if (nTicTock == 0) {
                tempChar = sLogs[0];
                for (int i = 0; i < nArenaWidthX - 1; i++) {
                    sLogs[i] = sLogs[i + 1];
                }
                sLogs[nArenaWidthX - 1] = tempChar;

                for (int i = 0; i < nArenaWidthX - 1; i++) {
                    if (sLogs[i] != '.' && (((nLogs1CoordY * nTerminalWidth) + nLogsCoordX) + i) == ((nFrogY * nTerminalWidth) + nFrogX)) { //checks if our frogge is on the log and modify the value if so
                        nFrogX--;
                    }
                }
            }

            //Move middle log index and frog if on
            if (nTicTock == 0 || nTicTock == 2) {
                tempChar = sLogs2[nArenaWidthX - 1];
                for (int i = 0; i < nArenaWidthX - 1; i++) {
                    sLogs2[nArenaWidthX - i - 1] = sLogs2[nArenaWidthX - i - 2];
                }
                sLogs2[0] = tempChar;
                
                for (int i = nArenaWidthX - 1; i > 0; i--) {
                    if (sLogs2[i] != '.' && (((nLogs2CoordY * nTerminalWidth) + nLogsCoordX) + i) == ((nFrogY * nTerminalWidth) + nFrogX)) { //checks if our frogge is on the log and modify the value if so
                        nFrogX++;
                    }
                }
                
            }

            //move fast log index and frog if on
            tempChar = sLogs3[0];
            for (int i = 0; i < nArenaWidthX - 1; i++) {
                    sLogs3[i] = sLogs3[i + 1];
                }
                sLogs3[nArenaWidthX - 1] = tempChar;

            for (int i = 0; i < nArenaWidthX - 1; i++) {
                    if (sLogs3[i] != '.' && (((nLogs3CoordY * nTerminalWidth) + nLogsCoordX) + i) == ((nFrogY * nTerminalWidth) + nFrogX)) { //checks if our frogge is on the log and modify the value if so
                        nFrogX--;
                    }
                }

            if (nFrogX == 1 || nFrogX == 31) { //check if frog is out of bounds and must be killed
                bFrogHit = true;
            }

            if (nFrogY < 6) {
                bFrogWin = true;
            }

            /*====================Render to Screen====================*/
            for (int x = 0; x < nTerminalWidth; ++x) { //draw frame
                for (int y = 0; y < nTerminalHeight; ++y) {
                    if (nTicTock == 0 || nTicTock == 2) {

                        if (sScreens[1][(y * nTerminalWidth) + x] != '.') {

                            screen[(y)*nTerminalWidth + (x)] = sScreens[1][(y * nTerminalWidth) + x];
                        }
                        else {
                            screen[(y)*nTerminalWidth + (x)] = ' ';
                        }
                    }
                    else {
                        if (sScreens[2][(y * nTerminalWidth) + x] != '.') {

                            screen[(y)*nTerminalWidth + (x)] = sScreens[2][(y * nTerminalWidth) + x];
                        }
                        else {
                            screen[(y)*nTerminalWidth + (x)] = ' ';
                        }
                    }
                }
            }

            //Draw Current Location of "Slow Car" with collision check

            for (int i = 0; i < nArenaWidthX - 1; i++) { //if you get an out of bounds error it may have come from this
                if (sSlowCar[i] != '.') {
                    screen[((nSlowCarCoordY * nTerminalWidth) + nSlowCarCoordX) + i] = sSlowCar[i];

                    if ((((nSlowCarCoordY * nTerminalWidth) + nSlowCarCoordX) + i) == ((nFrogY * nTerminalWidth) + nFrogX)) { //checks if our frogge got hit by this car if yes flag for next cycle
                        bFrogHit = true;
                    }
                }
            }

            //Draw Current Location of "Medium Car" with collision check
            for (int i = 0; i < nArenaWidthX - 1; i++) {
                if (sMedCar[i] != '.') {
                    screen[((nMedCarCoordY * nTerminalWidth) + nSlowCarCoordX) + i] = sMedCar[i];

                    if ((((nMedCarCoordY * nTerminalWidth) + nSlowCarCoordX) + i) == ((nFrogY * nTerminalWidth) + nFrogX)) { //checks if our frogge got hit by this car if yes flag for next cycle
                        bFrogHit = true;
                    }
                }
            }

            //Draw Current Location of "Fast Car" with collision check
            for (int i = 0; i < nArenaWidthX - 1; i++) {
                if (sFastCar[i] != '.') {
                    screen[((nFastCarCoordY * nTerminalWidth) + nSlowCarCoordX) + i] = sFastCar[i];

                    if ((((nFastCarCoordY * nTerminalWidth) + nSlowCarCoordX) + i) == ((nFrogY * nTerminalWidth) + nFrogX)) { //checks if our frogge got hit by this car if yes flag for next cycle
                        bFrogHit = true;
                    }
                }
            }

            //Draw Current Location of "Logs1" with collision check
            for (int i = 0; i < nArenaWidthX - 1; i++) {
                if (sLogs[i] != '.') {
                    screen[((nLogs1CoordY * nTerminalWidth) + nLogsCoordX) + i] = sLogs[i];
                }
                if (sLogs[i] == '.' && ((nLogs1CoordY * nTerminalWidth) + nLogsCoordX) + i == (nFrogY * nTerminalWidth) + nFrogX) {
                    bFrogHit = true;
                }
            }

            //Draw Current Location of "Logs2" with collision check
            for (int i = 0; i < nArenaWidthX - 1; i++) {
                if (sLogs2[i] != '.') {
                    screen[((nLogs2CoordY * nTerminalWidth) + nLogsCoordX) + i] = sLogs2[i];
                }
                if (sLogs2[i] == '.' && ((nLogs2CoordY * nTerminalWidth) + nLogsCoordX) + i == (nFrogY * nTerminalWidth) + nFrogX) {
                    bFrogHit = true;
                }
            }

            //Draw Current Location of "Logs3" with collision check
            for (int i = 0; i < nArenaWidthX - 1; i++) {
                if (sLogs3[i] != '.') {
                    screen[((nLogs3CoordY * nTerminalWidth) + nLogsCoordX) + i] = sLogs3[i];
                }
                if (sLogs3[i] == '.' && ((nLogs3CoordY * nTerminalWidth) + nLogsCoordX) + i == (nFrogY * nTerminalWidth) + nFrogX) {
                    bFrogHit = true;
                }
            }


            //Draw Current Location of Frog
            if (bFrogHit == true) {
                screen[(nFrogY)*nTerminalWidth + (nFrogX)] = 'X';
            }
            else {
                screen[(nFrogY)*nTerminalWidth + (nFrogX)] = 'F';
            }

            //Draw Score
            swprintf_s(&screen[3 * nTerminalWidth + 35], 16, L"SCORE: %8d", nScore);

            //Draw Lives
            swprintf_s(&screen[5 * nTerminalWidth + 35], 16, L"Lives: %8d", nLives);

            break;

        }


        WriteConsoleOutputCharacter(hConsole, screen, nTerminalWidth * nTerminalHeight, { 0,0 }, &dwBytesWritten);
        //finishing write statement
    }

    CloseHandle(hConsole);
    cout << "Game Over!! Score:" << nScore << endl;
    system("pause");
    return 0;
}
