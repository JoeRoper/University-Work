#include "Farm.h"

// FIXME - You may need to add #includes here (e.g. <thread>)

void Farm::add_task(Task* task)
{
	push(task);
}

void Farm::run()
{
	//Allows the user to input how many CPU cores they want to use
	int coreAmount = std::thread::hardware_concurrency();
	cout << "CPU cores available: " << coreAmount << endl;
	cout << "How cores would you like to use? Please enter a number between 0 - " << coreAmount + 1 << endl;
	cin >> numcores;
	while (true)
	{
		if ((numcores <= 0) || (numcores > coreAmount))
		{
			cout << "Please enter a valid amount." << endl;
			cin >> numcores;

		}
		else { break; }
	}

	for (int i = 0; i < numcores; ++i)//uses the farming pattern to parralise the mandelbrot task
	{
		std::thread* worker = new std::thread([this]
		{
			while (!empty())
			{
				Task* task = front();
				task->run();
				delete task;
			}
		});
		ThreadCounter++;
		cout << "Thread No: " << ThreadCounter << " is done" << endl;
		Mandel_Conditon.notify_one();
		my_threads.push_back(worker);
		
	}
	
	for (auto it : my_threads)
	{
		it->join();
	}

}

bool Farm::empty()
{
	task_queue_mtx.lock();
	bool empty = task_queue.empty();
	task_queue_mtx.unlock();
	return empty;
}

Task* Farm::front()
{
	task_queue_mtx.lock();
	Task* task = task_queue.front();
	task_queue.pop();
	task_queue_mtx.unlock();
	return task;
}

void Farm::push(Task* task)
{
	task_queue_mtx.lock();
	task_queue.push(task);
	task_queue_mtx.unlock();
}

int Farm::GetThreadCounter()
{
	return ThreadCounter;
}

int Farm::GetNumCores()
{
	return numcores;
}



