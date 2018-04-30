#ifndef STATISTIC_H
#define STATISTIC_H
#include <qlist.h>
#include <QtGui>

struct StatisticData{
    int timeMin;
    int step;
    int processed;
};
class Statistic
{
public:
    QList<StatisticData> _data;
    Statistic();
    int Mean(){
        int processed = 0;
        for (auto d : _data) {
            processed += d.processed;
        }
        return processed/_data.count();
    }
    bool Sd(){
        auto mean = Mean();
        auto sd = 0;
        for (auto d : _data) {
            sd += std::pow(d.processed - mean,2);
        }
        return std::sqrt(sd/_data.count());
    }
    void Add( int timeMin, int step, int processed){
        StatisticData data;
        data.step = step;
        data.timeMin = timeMin;
        data.processed = processed;
        _data.push_back( data );
    }
};
#endif // STATISTIC_H
