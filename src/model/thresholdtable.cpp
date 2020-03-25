#include "thresholdtable.h"

ColorThresholdTable *DefaultColorThresholdTable()
{
    Eigen::Vector3f defaultCol{0.2f, 0.2f, 0.2f};
    ColorThresholdTable* layers = new ColorThresholdTable(defaultCol);

    Eigen::Vector3f sea{0.0f, 0.0f, 0.5f};
    layers->addLayer(0, sea);

    Eigen::Vector3f ground{0.0f, 0.33f, 0.0f};
    layers->addLayer(0.5, ground);

    Eigen::Vector3f montain{0.5f, 0.25f, 0.0f};
    layers->addLayer(0.9, montain);

    Eigen::Vector3f ice{0.8f, 0.8f, 0.8f};
    layers->addLayer(1.0, ice);
    return layers;
}
