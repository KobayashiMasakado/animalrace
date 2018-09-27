#include "pch.h"
#include "TaskController.h"

using namespace std;

TaskController::TaskController()
{
}

TaskController::~TaskController()
{
	for (list<Task*>::iterator ite = m_taskList.begin(); ite != m_taskList.end(); ite++)
	{
		Task* task = *ite;
		delete task;
	}
}

void TaskController::AddTask(Task * task)
{
	m_taskList.push_back(task);
}

void TaskController::EraseTask(Task * task)
{
	//for (list<Task*>::iterator ite = m_taskList.begin(); ite != m_taskList.end(); ite++)
	//{
	//	if ()
	//}
}

void TaskController::Update()
{
}

void TaskController::Render()
{
}
