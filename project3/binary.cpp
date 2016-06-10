#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

int bnumber_count = 100;  //设置生成100个随机二进制数 

int main() {
	
	cout << "要生成新的二进制随机数吗? 若是，输入1: ";
	int new_binary = 0;
	cin >> new_binary;
	if (new_binary != 1) return 0; //如果不生成新的二进制文件，那么就使用之前生成的文件 
	
	FILE *fp;
	fp = fopen("data.txt", "wb"); //打开文件 
	srand((unsigned)time(NULL));

	while (bnumber_count--) {
		char a[8];
		int bnumber = rand()%255; //生成随机二进制数 
		
		if (bnumber < 128) { //将小于8位的二进制数前面补0，格式化数据 
			itoa(bnumber, a, 2);
			int bnumber_length = 0;
			while (a[bnumber_length] == '0' || a[bnumber_length] == '1') bnumber_length++; //计算随机数的位数 
			
			int k; //补0操作，将二进制数都统一设为8位 
			for (int j = bnumber_length-1, k = 7; j >= 0; j--) {
				a[k] = a[j];
				k--;
			}
			for (int j = 0; j < 8-bnumber_length; j++) a[j] = '0';
			
		}
		
		else itoa(bnumber, a, 2); //位数达到8位的数直接转化 
		
		fwrite(a, sizeof(char), 8, fp); //写入文件 
		char b[1] = {'\n'}; //换行 
		fwrite(b, 1, 1, fp);
	}
	cout << "随机二进制文件已经生成" << endl; 
	fclose(fp); 
	return 0;
}
