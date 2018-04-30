#include "productstore.h"



ProductStore::ProductStore(QList<Employee *> employes): _dequeEmployes(employes)
{
    for(auto e : this->_dequeEmployes){
        connect(e->ptimer, SIGNAL(timeout()), SLOT(AfterProcessCustomer()));
    }
}

bool ProductStore::AddCustomer(Customer *customer)
{
    const int maxCount = 4;
    auto count = this->Count();
    if(count < maxCount){
        this->_deque.push_back(customer);
        this->Process();
        return true;
    } else {
        return false;
    }
}

int ProductStore::Count()
{
    return this->_deque.count();
}

bool ProductStore::Process()
{
    for(auto e : this->_dequeEmployes){
        if(!e->isInProcess()){
            e->Process();
            return true;
        }
    }
    return false;
}

void ProductStore::AfterProcessCustomer()
{
    if(this->Count()>0)
        this->_deque.pop_front();
    if(this->Count()>0)
        this->Process();
}
