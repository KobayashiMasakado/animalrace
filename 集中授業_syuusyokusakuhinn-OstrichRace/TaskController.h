#include "Task.h"
#include <list>
class Task;

class TaskController:public Task
{
private:
	std::list<Task*> m_taskList;
public:
	TaskController();
	~TaskController();
	void AddTask(Task* task);
	void EraseTask(Task* task);
	void Update();
	void Render();

};

