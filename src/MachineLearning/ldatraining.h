#ifndef LDATRAINING_H
#define LDATRAINING_H
#include "training.h"

class LDATraining : public Training
{
public:
    LDATraining();
    virtual bool doTraining();
    virtual Eigen::Vector3i getClassif(Eigen::VectorXd vec) const;
    virtual Eigen::Matrix4f confusionMatrix() const;
    virtual Eigen::VectorXd getNormal(unsigned int ID) const {return _normal[ID];}

    std::vector<Eigen::VectorXd> _normal;
    std::vector<Eigen::VectorXd> _moy;
    bool _isTrain;
};

#endif // LDATRAINING_H
