#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

int bnumber_count = 100;  //��������100������������� 

int main() {
	
	cout << "Ҫ�����µĶ������������? ���ǣ�����1: ";
	int new_binary = 0;
	cin >> new_binary;
	if (new_binary != 1) return 0; //����������µĶ������ļ�����ô��ʹ��֮ǰ���ɵ��ļ� 
	
	FILE *fp;
	fp = fopen("data.txt", "wb"); //���ļ� 
	srand((unsigned)time(NULL));

	while (bnumber_count--) {
		char a[8];
		int bnumber = rand()%255; //��������������� 
		
		if (bnumber < 128) { //��С��8λ�Ķ�������ǰ�油0����ʽ������ 
			itoa(bnumber, a, 2);
			int bnumber_length = 0;
			while (a[bnumber_length] == '0' || a[bnumber_length] == '1') bnumber_length++; //�����������λ�� 
			
			int k; //��0������������������ͳһ��Ϊ8λ 
			for (int j = bnumber_length-1, k = 7; j >= 0; j--) {
				a[k] = a[j];
				k--;
			}
			for (int j = 0; j < 8-bnumber_length; j++) a[j] = '0';
			
		}
		
		else itoa(bnumber, a, 2); //λ���ﵽ8λ����ֱ��ת�� 
		
		fwrite(a, sizeof(char), 8, fp); //д���ļ� 
		char b[1] = {'\n'}; //���� 
		fwrite(b, 1, 1, fp);
	}
	cout << "����������ļ��Ѿ�����" << endl; 
	fclose(fp); 
	return 0;
}
