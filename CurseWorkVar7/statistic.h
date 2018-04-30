#ifndef STATISTIC_H
#define STATISTIC_H
#include <qlist.h>
#include <QtGui>

struct StatisticData{
    double processed;
    int isProcessed;
    int count;
};
class Statistic
{
public:
    QList<StatisticData> _data;
    Statistic();
    double Mean(){
        double processed = 0;
        for (auto d : _data) {
            processed += d.processed;
        }
        return processed/(double)_data.count();
    }
    double Sd(){
        double mean = Mean();
        double sd = 0;
        for (auto d : _data) {
            sd += std::pow(d.processed - mean,2);
        }
        return std::sqrt(sd/(double)_data.count());
    }
    void Add( bool isProcessed, int count){
        StatisticData data;
        data.isProcessed = isProcessed;
        data.count = count;
        data.processed = data.count;
        _data.push_back( data );

         qDebug()<< "isProcessed = " << isProcessed
                 << "count = " << count;
    }
};
#endif // STATISTIC_H
