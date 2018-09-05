#include <iostream>
#include <windows.h>
#include <string.h>
#include <io.h>
#include <stack>
#include <vector>
#include <tchar.h>

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

bool createNewProcess (char * process) {
    cout << process << endl;
    PROCESS_INFORMATION pi;	//进程信息
    STARTUPINFO si;			//进程启动信息
    memset(&si, 0, sizeof(si));
    si.cb = SW_SHOW;
    si.wShowWindow = SW_SHOW;
    si.dwFlags = STARTF_USESHOWWINDOW;
    int res = CreateProcess(_T(process), NULL, NULL, NULL, NULL, NULL, NULL, NULL, &si, &pi);
    if (!res) {
        cout << GetLastError();
    }
    return true;
}

void parseCommender(char* commender) {
    vector<char *> commenderToken;
    char * splitedArray;
    splitedArray = strtok(commender, " ");
    while (splitedArray != NULL) {
        commenderToken.push_back(splitedArray);
        splitedArray = strtok(NULL, " ");
    }
    if (strcmp(commenderToken[0], "cd") == 0) {
        int tokenLength = strlen(commenderToken[1]);
        commenderToken[1][tokenLength - 1] = 0;
        setDir(commenderToken[1]);
    } else {
        commenderToken[0][strlen(commenderToken[0]) - 1] = 0;
        createNewProcess(commenderToken[0]);
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