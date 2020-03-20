#ifndef THRESHOLDTABLE_H
#define THRESHOLDTABLE_H

#include <set>
#include <Eigen/Core>

/**
 * @brief The ColorThreshold struct, permit to make different threshold
 */
template <typename T>
struct Threshold
{
    Threshold(double max, T data)
        : _max(max), _data(data){}

    double _max;
    T _data;

    bool operator<( const Threshold& other ) const
    { return _max < other._max; }
};

/**
 * @brief The ColorThresholdTable class
 */
template <class T>
class ThresholdTable
{
public:
    ThresholdTable(){
        Threshold<T> defaulLayer(
                    std::numeric_limits<double>::max(),
                    T());
        addLayer(defaulLayer);
    }

    ThresholdTable(T defaultData){
        Threshold<T> defaulLayer(
                    std::numeric_limits<double>::max(),
                    defaultData);
        addLayer(defaulLayer);
    }

    void addLayer(Threshold<T> data){
        _layers.insert(data);
    }

    void addLayer(double value, T data){
        this->addLayer(Threshold<T>(value, data));
    }

    T getColorLayerByValue(double value) const{
        Threshold<T> val(value, T());
        auto it = _layers.upper_bound(val);
        return it->_data;
    }

    T getDefaultColor() const{
        return _layers.end()->_data;
    }

    const std::set<Threshold<T>>& getLayers() const{
        return _layers;
    }

private:

    std::set<Threshold<T>> _layers;

};

typedef ThresholdTable<Eigen::Vector3f> ColorThresholdTable;

#endif // THRESHOLDTABLE_H
