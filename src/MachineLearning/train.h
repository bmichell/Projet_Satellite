 #ifndef TRAIN_H
#define TRAIN_H
#include "Eigen/Eigen"
#include "polygon.h"
#include "vector"

class Train
{
public:
    Train();
    Train operator=(const Train& other);
    virtual bool doTraining();
    virtual std::vector<Polygon> getTrain() const {return _polygons;}
    virtual std::vector<Eigen::VectorXd> getNormal() const {return _normal;}
    virtual std::vector<Eigen::VectorXd> getDir() const {return _dir;}
    virtual void addImage(Polygon& image){_polygons.push_back(image);}
    virtual unsigned int getNumberOfClass() const {return _polygons.size();}
    virtual Eigen::VectorXd getNormal(unsigned int ID) const {return _normal[ID];}

private:
    std::vector<Polygon> _polygons;
    std::vector<Eigen::VectorXd> _normal;
    std::vector<Eigen::VectorXd> _dir;
};

#endif // TRAIN_H
