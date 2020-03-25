#ifndef THRESHOLDTABLE_H
#define THRESHOLDTABLE_H

#include <iostream>
#include <set>
#include <Eigen/Core>

/**
 * @brief The ColorThreshold struct, permit to make different threshold with a data on each step.
 * On a scale[-1, 1] by convention but no warning if use an other.
 */
template <typename T>
struct Threshold
{
    Threshold(double max, T data)
        : _max(max), _data(data)
    {}

    double _max;
    T _data;

    bool operator<( const Threshold& other ) const
    { return _max < other._max; }
};

/**
 * @brief The ColorThresholdTable class
 * Construction like [-LIMIT_DOUBLE, 1st value[ for first data, [1st value, 2nd value[ for 2nd data,
 * ..., [n-1, n [ for n data layer, and  [n, LIMIT_DOUBLE] for default value.
 * The default data is for higher value than max of the table.
 */
template <class T>
class ThresholdTable
{
public:

    /**
     * @brief ThresholdTable
     * @param defaultData the default value to set.
     */
    ThresholdTable(T defaultData = T()){
        Threshold<T> defaulLayer(std::numeric_limits<double>::max(), defaultData);
        addLayer(defaulLayer);
    }

    /**
     * @brief addLayer add a layer with upperbound=value and will be sorted in the table.
     * @param value the max value of the layer. layer = [previous max layer, value)
     * @param data the data associated.
     */
    void addLayer(double value, T data){
        if(value < -1. || value > 1.)
        {
            std::cerr << "Warning : Adding value to treshold table in scale outside convention [-1, 1].\n"
                      << "Value : "<< value << ".\n";
        }
        this->addLayer(Threshold<T>(value, data));
    }

    /**
     * @brief getColorLayerByValue
     * @param value that is in layer = [lowerbound,upperbound=maxvalue].
     * @return The color of the layer that is belong or the default one if is higher than max of the table.
     * Print a warning if convention [-1,1] is noit respected.
     */
    T getColorLayerByValue(double value) const{
        if(value <= -1. || value >= 1.)
        {
            std::cerr << "Warning : Get value to treshold table in scale outside convention ]-1, 1[.\n"
                      << "Can be a result not desired.\n"
                      << "Value : "<< value << ".\n";
        }
        Threshold<T> val(value, T());
        auto it = _layers.upper_bound(val);
        return it->_data;
    }

    /**
     * @brief getDefaultColor
     * @return the default data.
     */
    T getDefaultColor() const{
        return _layers.end()->_data;
    }

    /**
     * @brief getLayers
     * @return the differents layers added. At least the default, that is last one.
     */
    const std::set<Threshold<T>>& getLayers() const{
        return _layers;
    }

private:

    /**
     * @brief addLayer add a layer in the structure.
     * @param data the treshold to add.
     */
    void addLayer(Threshold<T> data){
        _layers.insert(data);
    }

private:

    std::set<Threshold<T>> _layers;

};

/**
 * @brief ColorThresholdTable use for a threshold scale foàr colors. Exemple : the treshold can be height factor displacement associated to a color.
 */
typedef ThresholdTable<Eigen::Vector3f> ColorThresholdTable;

ColorThresholdTable *DefaultColorThresholdTable();

#endif // THRESHOLDTABLE_H

