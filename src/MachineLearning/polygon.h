#ifndef Polygon_H
#define Polygon_H
#include "image.h"
#include <fstream>

class Polygon
{
public:
    Polygon() : _size(0), _bandCount(0), _data(_size*_bandCount){}
    Polygon(std::string filename);
    Polygon(const Polygon& other);
    Polygon operator=(const Polygon& other);
    virtual ~Polygon() {}
    virtual bool OpenImage(std::string filename);
    virtual Eigen::VectorXd getVector(unsigned int index) const;
    virtual float getValue(unsigned int index, unsigned int band) const;
    virtual std::vector<float> getData() const;
    virtual unsigned int size() const {return _size;}
    virtual unsigned int getBandCount() const {return _bandCount;}

private:
    unsigned int _size;
    unsigned int _bandCount;
    std::vector<float> _data;
};

#endif // Polygon_H
