#include "live.h"

Live::Live() : ptimer(new QTimer())
{
    this->SetParams(1,1,1, 1);
    this->GeneratePopulation();
    connect(ptimer, SIGNAL(timeout()),this, SLOT(GeneratePopulation()));
}

void Live::Start()
{
    this->ptimer->start();
}

void Live::Stop()
{
    this->ptimer->stop();
}

void Live::GeneratePopulation()
{
    emit StateChange();
    bool isOk = false;
    if(this->AddCustomer()){
        isOk = true;
    }

    statistic.Add(isOk, this->stores.first()->Count());
}

bool Live::AddCustomer()
{
    for(auto store : this->stores){
        if(store->AddCustomer(new Customer())){
            return true;
        }
    }
    return false;
}

void Live::SetParams(int averageServiceTimeMaster, int K, int averageWishingToPurchase, int secPerMinute = 1)
{
    const int second = 1000;
    _min = secPerMinute * second / 60;
    this->stores.clear();
    this->AddStore(averageServiceTimeMaster * _min, K);
    ptimer->setInterval(averageWishingToPurchase * _min );
}

void Live::AddStore(int averageServiceTime, int K)
{
    QList<Employee*> list;
    list.push_back(new Employee(averageServiceTime));//master
    list.push_back(new Employee(averageServiceTime * K));//slave
    this->stores.push_back(new ProductStore(list));
}
