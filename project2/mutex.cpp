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
  	DWORD producerID; //生产者id 
	DWORD ThreadID;  //线程id  
	HANDLE ThreadHandle;  //线程句柄 
  	
  public:
  	Producer(int id) {
  		producerID = id;
  		ThreadHandle = CreateThread(NULL, 0, producer, &producerID, 0, &ThreadID); //创建线程 
	}
	
	static DWORD WINAPI producer(LPVOID Param) {
		DWORD id = *(DWORD*) Param;
		while(true) {   
            WaitForSingleObject(mutex, INFINITE); //加锁 
            
            if (stop == 1) break; //当main函数被唤醒后，不再输出
			 
            p_in++;
            counter++;  //counter值加1，并打印出来 
            cout << "producer " << id << " is running" << "	" << "Number of counter : " <<  counter << endl;

            ReleaseMutex(mutex); //解锁 
		}
		return 0;
	}
		
};

class Consumer {
  private:
  	DWORD consumerID; //消费者id 
	DWORD ThreadID;  //线程id 
	HANDLE ThreadHandle; //线程句柄 
  	
  public:
  	Consumer(int id) {
  		consumerID = id;
  		ThreadHandle = CreateThread(NULL, 0, consumer, &consumerID, 0, &ThreadID); //创建线程 
	}
	
	static DWORD WINAPI consumer(LPVOID Param) {
		DWORD id = *(DWORD*) Param;
		while(true) {   
            WaitForSingleObject(mutex, INFINITE); //加锁 
            
            if (stop == 1) break;  //当main函数被唤醒后，不再输出
            
            c_in++; 
            if (counter > 0){ //counter值减1，并打印出来 
            	counter--; 
                cout << "consumer " << id << " is running" << "	" << "Number of counter : " <<  counter << endl;
            } 
			else cout << "consumer " << id << " is waiting!" << endl;
			
            ReleaseMutex(mutex); //解锁 
		}
		return 0;
	}
};

int main(int argc, char *argv[]) {
	mutex = CreateMutex(NULL, false, "");; //初始化互斥量 
	
	if (mutex == NULL) {
		cout << "CreateMutex error: " << GetLastError() << endl;
        return -1;
	}
	
	int producerCount, consumerCount; //设置生产者和消费者数量 
	cout <<  "Please enter the number of producer: ";
	cin >> producerCount;
	cout <<  "Please enter the number of consumer: ";
	cin >> consumerCount;
    
    for (int i = 0; i < producerCount; i++) { //创建生产者 
    	Producer p(i+1);
	}
	
	for (int i = 0; i < consumerCount; i++) { //创建消费者 
    	Consumer c(i+1);
	}

    Sleep(3000); //将main挂起 
    stop = 1;
    CloseHandle(mutex); //销毁互斥量 
    cout << endl << "访问资源的生产者数量为： " << p_in << ", 消费者数量为： " << c_in << endl; 
	return 0;
}
