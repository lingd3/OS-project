#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;

int sort_num[100] = {0};

int char_to_int(char* c) { //将二进制数转化为十进制数 
	int sum = 0, i, k = 0;
	for (i = 7; i >= 0; i--) {
		if (c[i] == '1') sum += pow(2, k);
		k++;
	}
	return sum;
}

void sort(char base[]) { //排序 
	int i, j = 0;
	for (i = 0; i < 900; i++) { //先将每个二进制数转化为十进制数 
		if (i%9 == 0) {
			char c[8] = {base[i], base[i+1], base[i+2], base[i+3], base[i+4], base[i+5], base[i+6], base[i+7]};
			sort_num[j] = char_to_int(c); 
			j++;
		}
	}
	
	int m;
	for (int k = 0; k < 100; k++) { //将十进制数排序 
		for (int l = k+1; l < 100; l++) {
			if (sort_num[k] > sort_num[l]) {
				m = sort_num[k];
				sort_num[k] = sort_num[l];
				sort_num[l] = m;
			}
		}
	}
	
	for (int k = 0; k < 100; k++) { //输出排好序的数 
		cout << sort_num[k] << endl;
	}
} 

void write_to_disk(char base[]) { //将内存内容写回磁盘文件中 
	for (int k = 0; k < 100; k++) {
		char a[8] = {'\0'};
		if (sort_num[k] < 128) { //将小于8位的二进制数前面补0，格式化数据 
			itoa(sort_num[k], a, 2);
			int bnumber_length = 0;
			while (a[bnumber_length] == '0' || a[bnumber_length] == '1') bnumber_length++; //计算随机数的位数 
			
			int k; //补0操作，将二进制数都统一设为8位 
			for (int j = bnumber_length-1, k = 7; j >= 0; j--) {
				a[k] = a[j];
				k--;
			}
			for (int j = 0; j < 8-bnumber_length; j++) a[j] = '0';
		}		
		else itoa(sort_num[k], a, 2); //位数达到8位的数直接转化 
	
		int j;
		for (j = 0; j < 8; j++) {
			base[9*k+j] = a[j]; //写回文件中 
		}
		base[9*k+j] = '\n';
	}
}

int main() {
	HANDLE hMapFile;
	LPVOID lpMapAddress;
	
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, TEXT("SharedObject")); //打开共享的文件对象 
	
	lpMapAddress = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);//获取文件视图  
	
	char *base;
	base = (char*)lpMapAddress;
	
	sort(base); //排序 
	
	write_to_disk(base); //将内存中的内容写到磁盘上 
	FlushViewOfFile(lpMapAddress, 1000);
	
	UnmapViewOfFile(lpMapAddress); //删除文件视图 
	CloseHandle(hMapFile); //关闭内存映射文件 
}
