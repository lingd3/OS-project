#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;

int sort_num[100] = {0};

int char_to_int(char* c) { //����������ת��Ϊʮ������ 
	int sum = 0, i, k = 0;
	for (i = 7; i >= 0; i--) {
		if (c[i] == '1') sum += pow(2, k);
		k++;
	}
	return sum;
}

void sort(char base[]) { //���� 
	int i, j = 0;
	for (i = 0; i < 900; i++) { //�Ƚ�ÿ����������ת��Ϊʮ������ 
		if (i%9 == 0) {
			char c[8] = {base[i], base[i+1], base[i+2], base[i+3], base[i+4], base[i+5], base[i+6], base[i+7]};
			sort_num[j] = char_to_int(c); 
			j++;
		}
	}
	
	int m;
	for (int k = 0; k < 100; k++) { //��ʮ���������� 
		for (int l = k+1; l < 100; l++) {
			if (sort_num[k] > sort_num[l]) {
				m = sort_num[k];
				sort_num[k] = sort_num[l];
				sort_num[l] = m;
			}
		}
	}
	
	for (int k = 0; k < 100; k++) { //����ź������ 
		cout << sort_num[k] << endl;
	}
} 

void write_to_disk(char base[]) { //���ڴ�����д�ش����ļ��� 
	for (int k = 0; k < 100; k++) {
		char a[8] = {'\0'};
		if (sort_num[k] < 128) { //��С��8λ�Ķ�������ǰ�油0����ʽ������ 
			itoa(sort_num[k], a, 2);
			int bnumber_length = 0;
			while (a[bnumber_length] == '0' || a[bnumber_length] == '1') bnumber_length++; //�����������λ�� 
			
			int k; //��0������������������ͳһ��Ϊ8λ 
			for (int j = bnumber_length-1, k = 7; j >= 0; j--) {
				a[k] = a[j];
				k--;
			}
			for (int j = 0; j < 8-bnumber_length; j++) a[j] = '0';
		}		
		else itoa(sort_num[k], a, 2); //λ���ﵽ8λ����ֱ��ת�� 
	
		int j;
		for (j = 0; j < 8; j++) {
			base[9*k+j] = a[j]; //д���ļ��� 
		}
		base[9*k+j] = '\n';
	}
}

int main() {
	HANDLE hMapFile;
	LPVOID lpMapAddress;
	
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, TEXT("SharedObject")); //�򿪹�����ļ����� 
	
	lpMapAddress = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);//��ȡ�ļ���ͼ  
	
	char *base;
	base = (char*)lpMapAddress;
	
	sort(base); //���� 
	
	write_to_disk(base); //���ڴ��е�����д�������� 
	FlushViewOfFile(lpMapAddress, 1000);
	
	UnmapViewOfFile(lpMapAddress); //ɾ���ļ���ͼ 
	CloseHandle(hMapFile); //�ر��ڴ�ӳ���ļ� 
}
