#ifndef FARM_H
#define FARM_H

#include "task.h"
#include <thread>
#include <vector>
#include<iostream>
#include <string>
#include <queue>
#include <mutex>  
#include <condition_variable>	
using namespace std;

class Farm {
public:
	condition_variable Mandel_Conditon;//Used to notify a thread function to run when the farm is complete
	void add_task(Task* task);//adds a task onto the queue
	void run();//runs the farm computation
	bool empty();//checks if the task_queue is empty
	Task* front();//returns the front of the task_queue then pops it off the queue
	void push(Task* task);//pushes a task onto the queue
	int GetThreadCounter();//used in the write file thread function in project
	int GetNumCores();//used in the write file thread function in project
	std::mutex MandelMutex;//used to lock the write file thread function in project while the farm is running
private:
	std::queue<Task*> task_queue;//holds the tasks while the farm is running
	std::mutex task_queue_mtx;//allows the task_queue to be accessed safely
	std::vector<std::thread*> my_threads;//used to join the threads together after the farm has computed
	int ThreadCounter = 0;//used in the write file thread function to keep the task locked until the farm is completed
	int numcores;//used to determine how many CPU cores the user wants to use to compute the mandlebrot image
};

#endif
