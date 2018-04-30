#ifndef LIVE_H
#define LIVE_H
#include <qlist.h>
#include "productstore.h"
#include <QtGui>
#include <QLabel>
#include "random.h"
#include "statistic.h"
class Live: public QObject
{
    Q_OBJECT
public:
    Statistic statistic;
    QList<ProductStore*> stores;
private:
    int _rest;
    int _restMin;
    int _min;
    int _averageWishingToPurchase;
    QTimer* ptimer;
    void AddStore(int averageServiceTime, int order);
    bool AddCustomer();
    int Next();
public:
    Live();
    virtual ~Live() {}
    void Start();
    void Stop();
    void SetParams(int averageServiceTime1, int averageServiceTime2, int averageWishingToPurchase, int secPerMinute);
signals:
     void StateChange();
public slots:
    void GeneratePopulation();
};

#endif // LIVE_H
