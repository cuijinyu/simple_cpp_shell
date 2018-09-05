#include <iostream>
#include <windows.h>
#include <string.h>
#include <io.h>
using namespace std;

void welcome () {
    printf("----Welcome to C_shell----\n");
    printf("----a simple shell writen in C++ worked on Windows----\n");
    printf("----for study----\n");
}

void getUserName () {
    char userNameBuffer[256];
    DWORD dwUserNameSize = 256;
    GetUserName(userNameBuffer, &dwUserNameSize);
    printf("[$%s", userNameBuffer);
}

void getDir () {
    char dirBuffer[256];
    DWORD dirBufferSize = 256;
    GetCurrentDirectory(dirBufferSize, dirBuffer);
    printf(" %s]:", dirBuffer);
}

void setDir (char* path) {
    SetCurrentDirectory(TEXT(path));
}

void parseCommender(char* commender) {
    cout << commender << endl;
    char * splitedArray;
    splitedArray = strtok(commender, " ");
    while (splitedArray != NULL) {
        cout << splitedArray << " " << endl;
    }
}

int main() {

    welcome();
    //main loop
    while (true) {
        getUserName();
        getDir();
        char buffer[256];
        fgets(buffer, 256, stdin);
        parseCommender(buffer);
    }

    return 0;
}