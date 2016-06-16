#include<windows.h>
#include<stdio.h>
#include<iostream>
using namespace std;

int main() {
	HANDLE hFile, hMapFile;
	LPVOID lpMapAddress;
	
	//���ļ�����ȡ��� 
	hFile = CreateFile("data.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE) { //����ʧ�� 
		cout<< "error number " << GetLastError() << " occured on file open."  <<  endl;
        return 0;
	}
	
	hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, TEXT("SharedObject")); //�����ļ�ӳ����� 
		 
	lpMapAddress = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0); //�����ļ���ͼ 
		
	Sleep(3000000);  //���������� 
	UnmapViewOfFile(lpMapAddress); //ɾ���ļ���ͼ 
	CloseHandle(hFile); //�ر�ӳ���ļ� 
	CloseHandle(hMapFile);
	
}
