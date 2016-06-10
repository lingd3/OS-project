#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

void execute(char*);
void getPathInputLineByLine() {
	cout << "Please enter the path: " << endl;
	char a[100];
	gets(a);
	while (a[0] != 'q') {
		execute(a);
	    for (int i = 0; i < 100; i++) a[i] = '\0';
	    cout << endl << "If you want to quit, please enter 'q', otherwise, enter the path: " << endl;
	    gets(a);
	}
}

void getPathFromFiles() {
	string s;
	ifstream in;
	in.open("script.txt");
	if (in.is_open()) {
        while (getline(in, s)) {
        	char a[100] = {'\0'};
        	sprintf(a, "%s", s.c_str());	
        	execute(a);
        }
	}
	in.close();
}

void execute(char a[]) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, a, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		fprintf(stderr, "Creat Process Failed");
		return;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	
	CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
	int enter;
	cout << "Please enter '1' for reading input line by line OR enter '2' for reading input from a file: ";
	cin >> enter;
	scanf("%*c");
	cout << endl;
	if (enter == 1) getPathInputLineByLine();
	else getPathFromFiles();
	return 0;
}
