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
    auto step = Next();
    auto i = step;
    auto processed = 0;
    while(i-- > 0){
        if(this->AddCustomer()){
            processed++;
        }
    }

    qDebug()<< "_rest = " << _rest
            << "step = " << step
            << "processed = " << processed
            << " _restMin = " <<  _restMin;
    statistic.Add(_restMin, step, processed);
}

bool Live::AddCustomer()
{
    qSort(this->stores.begin(),  this->stores.end(),
      []( ProductStore* f, ProductStore* s) { return f->Count() < s->Count(); }
    );
    for(auto store : this->stores){
        if(store->AddCustomer(new Customer())){
            return true;
        }
    }
    return false;
}

int Live::Next()
{
    auto step = (new Random())->Next(0,_averageWishingToPurchase/60 +2);
    if(_rest >= step){
        _rest -= step;
    } else {
        step = _rest;
        _rest = 0;
    }
    _restMin += 1;
    if(_restMin == 60){
        _restMin = 0;
        _rest = _averageWishingToPurchase;
    }
    return step;
}

void Live::SetParams(int averageServiceTime1, int averageServiceTime2, int averageWishingToPurchase, int secPerMinute = 1)
{
    _restMin = 0;
    const int second = 1000;
    _min = secPerMinute * second;
    _averageWishingToPurchase = averageWishingToPurchase * 10;
    _rest = _averageWishingToPurchase;
    this->stores.clear();
    this->AddStore(averageServiceTime1 * _min, 1);
    this->AddStore(averageServiceTime2 * _min, 2);
    ptimer->setInterval(_min);
}

void Live::AddStore(int averageServiceTime, int order)
{
    this->stores.push_back(new ProductStore(new Employee(averageServiceTime), order));
}
