#include "employee.h"

Employee::Employee(int averageServiceTime) : _averageServiceTime(averageServiceTime)
{
    connect(this->ptimer, SIGNAL(timeout()), SLOT(AfterProcess()));
}

Employee::~Employee()
{

}

void Employee::Process()
{
    inProcess = true;
    ptimer->start(_averageServiceTime);
}

bool Employee::isInProcess()
{
    return inProcess;
}

void Employee::AfterProcess()
{
    inProcess = false;
}

