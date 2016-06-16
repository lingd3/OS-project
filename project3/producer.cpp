#include<windows.h>
#include<stdio.h>
#include<iostream>
using namespace std;

int main() {
	HANDLE hFile, hMapFile;
	LPVOID lpMapAddress;
	
	//打开文件，获取句柄 
	hFile = CreateFile("data.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if(hFile == INVALID_HANDLE_VALUE) { //处理失败 
		cout<< "error number " << GetLastError() << " occured on file open."  <<  endl;
        return 0;
	}
	
	hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, TEXT("SharedObject")); //创建文件映射对象 
		 
	lpMapAddress = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0); //创建文件视图 
		
	Sleep(3000000);  //挂起生产者 
	UnmapViewOfFile(lpMapAddress); //删除文件视图 
	CloseHandle(hFile); //关闭映射文件 
	CloseHandle(hMapFile);
	
}
