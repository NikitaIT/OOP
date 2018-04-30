#ifndef PRODUCTSTORE_H
#define PRODUCTSTORE_H
#include <qlist.h>
#include "employee.h"
#include "customer.h"
#include <QtGui>

class ProductStore : public QObject
{
    Q_OBJECT
public:
    QList<Employee*> _dequeEmployes;
private:
    QList<Customer*> _deque;
private slots:
    void AfterProcessCustomer();
public:
    ProductStore(QList<Employee*> employes);
    bool AddCustomer(Customer *customer);
    int Count();
    bool Process();
};

#endif // PRODUCTSTORE_H
