#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <fstream>
using namespace std;

// A helper function to print MCI errors
void printMciError(DWORD error) {
    char errorText[256];
    mciGetErrorStringA(error, errorText, sizeof(errorText));
    cout << "MCI Error: " << errorText << endl;
}

int main() {
    string filename = "Akaza_music.mp3"; // Correct filename with extension

    // You can remove the ifstream check as MCI will find the file itself
    // and give us a better error if it can't.

    cout << "Attempting to open file: " << filename << endl;

    // Open the device
    string openCommand = "open \"" + filename + "\" type mpegvideo alias myMusic";
    DWORD openError = mciSendStringA(openCommand.c_str(), NULL, 0, NULL);

    if (openError != 0) {
        cout << "Failed to open the file." << endl;
        printMciError(openError);
        system("pause"); // Wait for user to press a key
        return 1;
    }

    cout << "File opened successfully. Attempting to play..." << endl;

    // Play the device
    DWORD playError = mciSendStringA("play myMusic repeat", NULL, 0, NULL);

    if (playError != 0) {
        cout << "Failed to play the music." << endl;
        printMciError(playError);
        mciSendStringA("close myMusic", NULL, 0, NULL); // Clean up
        system("pause"); // Wait for user to press a key
        return 1;
    }

    cout << "Playing " << filename << " in a loop... Press Ctrl + C to stop." << endl;

    while (true) {
        Sleep(1000); // Keep the program running
    }

    // This part is never reached in a loop, but it's good practice
    mciSendStringA("close myMusic", NULL, 0, NULL);
    return 0;
}