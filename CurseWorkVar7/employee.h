#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QtGui>
#include <atomic>
class Employee : public QObject
{
    Q_OBJECT
private:
    int _averageServiceTime = 0;
    std::atomic<bool> inProcess;
public:
    QTimer* ptimer = new QTimer();
    Employee(int averageServiceTime);
    ~Employee();
    void Process();
    bool isInProcess();
public slots:
    void AfterProcess();

};

#endif // EMPLOYEE_H
