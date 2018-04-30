#include "productstore.h"



ProductStore::ProductStore(Employee *cashier, int order): _cashier(cashier), order(order)
{
    connect(this->_cashier->ptimer, SIGNAL(timeout()), SLOT(AfterProcessCustomer()));
}

bool ProductStore::AddCustomer(Customer *customer)
{
    const int maxCount = 3;
    auto count = this->Count();
    if(count < maxCount){
        this->_deque.push_back(customer);
        if(count == 0 || !this->_cashier->isInProcess()){
            this->Process();
        }
        return true;
    } else {
        return false;
    }
}

int ProductStore::Count()
{
    return this->_deque.count();
}

void ProductStore::Process()
{
    this->_cashier->Process();
}

void ProductStore::AfterProcessCustomer()
{
    if(this->Count()>0)
        this->_deque.pop_front();
    if(this->Count()>0)
        this->Process();
}
