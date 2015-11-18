 #ifndef TRAIN_H
#define TRAIN_H
#include "eigen3/Eigen/Eigen"
#include "imagetraining.h"
#include "vector"

class Train
{
public:
    Train();
    Train operator=(const Train& other);
    virtual bool doTraining();
    virtual std::vector<ImageTraining> getTrain() const {return _train;}
    virtual std::vector<Eigen::VectorXd> getNormal() const {return _normal;}
    virtual std::vector<Eigen::VectorXd> getDir() const {return _dir;}
    virtual void addImage(ImageTraining& image){_train.push_back(image);}
    virtual unsigned int getNumberOfClass() const {return _train.size();}
    virtual Eigen::VectorXd getNormal(unsigned int ID) const {return _normal[ID];}

private:
    std::vector<ImageTraining> _train;
    std::vector<Eigen::VectorXd> _normal;
    std::vector<Eigen::VectorXd> _dir;
};

#endif // TRAIN_H
