#ifndef TASK_H
#define TASK_H

//Virtual class, children of this class excute the run function when created
class Task
{
public:
	virtual ~Task()
	{
	}


	virtual void run() = 0;
};

#endif
