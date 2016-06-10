#include <windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int counter = 0;
int p_in = 0;
int c_in = 0;
int stop = 0;
HANDLE mutex;

class Producer {
  private:
  	DWORD producerID; //������id 
	DWORD ThreadID;  //�߳�id  
	HANDLE ThreadHandle;  //�߳̾�� 
  	
  public:
  	Producer(int id) {
  		producerID = id;
  		ThreadHandle = CreateThread(NULL, 0, producer, &producerID, 0, &ThreadID); //�����߳� 
	}
	
	static DWORD WINAPI producer(LPVOID Param) {
		DWORD id = *(DWORD*) Param;
		while(true) {   
            WaitForSingleObject(mutex, INFINITE); //���� 
            
            if (stop == 1) break; //��main���������Ѻ󣬲������
			 
            p_in++;
            counter++;  //counterֵ��1������ӡ���� 
            cout << "producer " << id << " is running" << "	" << "Number of counter : " <<  counter << endl;

            ReleaseMutex(mutex); //���� 
		}
		return 0;
	}
		
};

class Consumer {
  private:
  	DWORD consumerID; //������id 
	DWORD ThreadID;  //�߳�id 
	HANDLE ThreadHandle; //�߳̾�� 
  	
  public:
  	Consumer(int id) {
  		consumerID = id;
  		ThreadHandle = CreateThread(NULL, 0, consumer, &consumerID, 0, &ThreadID); //�����߳� 
	}
	
	static DWORD WINAPI consumer(LPVOID Param) {
		DWORD id = *(DWORD*) Param;
		while(true) {   
            WaitForSingleObject(mutex, INFINITE); //���� 
            
            if (stop == 1) break;  //��main���������Ѻ󣬲������
            
            c_in++; 
            if (counter > 0){ //counterֵ��1������ӡ���� 
            	counter--; 
                cout << "consumer " << id << " is running" << "	" << "Number of counter : " <<  counter << endl;
            } 
			else cout << "consumer " << id << " is waiting!" << endl;
			
            ReleaseMutex(mutex); //���� 
		}
		return 0;
	}
};

int main(int argc, char *argv[]) {
	mutex = CreateMutex(NULL, false, "");; //��ʼ�������� 
	
	if (mutex == NULL) {
		cout << "CreateMutex error: " << GetLastError() << endl;
        return -1;
	}
	
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

    Sleep(3000); //��main���� 
    stop = 1;
    CloseHandle(mutex); //���ٻ����� 
    cout << endl << "������Դ������������Ϊ�� " << p_in << ", ����������Ϊ�� " << c_in << endl; 
	return 0;
}
