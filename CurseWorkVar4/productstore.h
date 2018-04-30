#ifndef PRODUCTSTORE_H
#define PRODUCTSTORE_H
#include <qlist.h>
#include "employee.h"
#include "customer.h"
#include <QtGui>

class ProductStore : public QObject
{
    Q_OBJECT
private:
    Employee *_cashier;
    QList<Customer*> _deque;
private slots:
    void AfterProcessCustomer();
public:
    int order;
    ProductStore(Employee *cashier, int order);
    bool AddCustomer(Customer *customer);
    int Count();
    void Process();
};

#endif // PRODUCTSTORE_H
