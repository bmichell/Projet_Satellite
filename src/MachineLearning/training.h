#ifndef TRAINING_H
#define TRAINING_H
#include "Eigen/Eigen"
#include "polygon.h"
#include "vector"

class Training
{
public:
    Training() : _polygons() {}
    virtual bool doTraining() = 0;
    virtual Eigen::Vector3i getClassif(Eigen::VectorXd vec) const = 0;
    virtual Eigen::Matrix4f confusionMatrix() const = 0;
    virtual void addImage(Polygon& image){_polygons.push_back(image);}
    virtual unsigned int getNumberOfClass() const {return _polygons.size();}

protected:
    std::vector<Polygon> _polygons;
};

#endif // TRAINING_H
