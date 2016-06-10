#include <windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int counter = 0;
int p_in = 0;
int c_in = 0;
CRITICAL_SECTION criticalSection;

class Producer {
  private:
  	DWORD producerID; //������id 
	DWORD ThreadID;  //�߳�id 
	HANDLE ThreadHandle; //�߳̾�� 
  	
  public:
  	Producer(int id) {
  		producerID = id;
  		ThreadHandle = CreateThread(NULL, 0, producer, &producerID, 0, &ThreadID); //�����߳� 
	}
	
	static DWORD WINAPI producer(LPVOID Param) {
		DWORD id = *(DWORD*) Param;
		while (true) {

			while(!TryEnterCriticalSection(&criticalSection)); //ѭ��֪���߳��ܹ���ö���Դ�ķ���Ȩ�������ٽ��� 
			
			p_in++;
            counter++;  //counterֵ��1������ӡ���� 
            cout << "producer " << id << " is running" << "	" << "Number of counter : " <<  counter << endl;
            
            LeaveCriticalSection(&criticalSection); //�뿪�ٽ��������� 
		}
		return 0;
	}
		
};

class Consumer {
  private:
  	DWORD consumerID; //������id 
	DWORD ThreadID;  //�߳�id 
	HANDLE ThreadHandle;  //�߳̾�� 
  	
  public:
  	Consumer(int id) {
  		consumerID = id;
  		ThreadHandle = CreateThread(NULL, 0, consumer, &consumerID, 0, &ThreadID); //�����߳� 
	}
	
	static DWORD WINAPI consumer(LPVOID Param) {
		DWORD id = *(DWORD*) Param;
		while (true) {
			
			while(!TryEnterCriticalSection(&criticalSection));  //ѭ��֪���߳��ܹ���ö���Դ�ķ���Ȩ�������ٽ��� 
			
			c_in++;
			if (counter > 0) { //counterֵ��1������ӡ���� 
                counter--; 
                cout << "consumer " << id << " is running" << "	" << "Number of counter : " <<  counter << endl;
            } 
			else cout << "consumer " << id << " is waiting!" << endl;
			
            LeaveCriticalSection(&criticalSection); //�뿪�ٽ��������� 
		}
		return 0;
	}
};

int main(int argc, char *argv[]) {
	InitializeCriticalSection(&criticalSection); //��ʼ���ٽ��� 
	
    int producerCount, consumerCount; //���������ߺ����������� 
	cout <<  "Please enter the number of producer: ";
	cin >> producerCount;
	cout <<  "Please enter the number of consumer: ";
	cin >> consumerCount;
    
    for (int i = 0; i < producerCount; i++) { //���������� 
    	Producer p(i+1);
	}
	
	for (int i = 0; i < consumerCount; i++) { //���������� 
    	Consumer c(i+1);
	}
	
    Sleep(3000);  //��main���� 
    DeleteCriticalSection(&criticalSection); //�ͷ��ٽ��� 
    cout << endl << "������Դ������������Ϊ�� " << p_in << ", ����������Ϊ�� " << c_in << endl; 
	return 0;
}
