#ifndef TRAINING_H
#define TRAINING_H
#include <Eigen/Eigen>
#include "polygon.h"
#include "vector"

class Training
{
public:
    Training() : _polygons() {}
    virtual ~Training() {}
    virtual bool doTraining() = 0;
    virtual Eigen::Vector3i getClassif(Eigen::VectorXd vec) const = 0;
    virtual Eigen::MatrixXf confusionMatrix() const;
    Eigen::MatrixXf confusionMatrix(std::vector<Polygon> polygons) const;
    virtual std::vector<Polygon> getPolygons() const;
    virtual void addImage(Polygon& image);
    virtual unsigned int getNumberOfClass() const;

protected:
    std::vector<Polygon> _polygons;
};

#endif // TRAINING_H
