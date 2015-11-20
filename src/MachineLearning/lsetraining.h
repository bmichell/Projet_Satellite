#ifndef LSETRAINING_H
#define LSETRAINING_H
#include "training.h"

class LSETraining : public Training
{
public:
    LSETraining();
    LSETraining operator=(const LSETraining& other);
    virtual bool doTraining();
    virtual std::vector<Polygon> getTrain() const {return _polygons;}
    virtual std::vector<Eigen::VectorXd> getNormal() const {return _normal;}
    virtual void addImage(Polygon& image){_polygons.push_back(image);}
    virtual Eigen::VectorXd getNormal(unsigned int ID) const {return _normal[ID];}
    virtual Eigen::Vector3i getClassif(Eigen::VectorXd vec) const;
    virtual Eigen::Matrix4f confusionMatrix() const;

private:
    std::vector<Eigen::VectorXd> _normal;
    bool _isTrain;
};

#endif // LSETRAINING_H
