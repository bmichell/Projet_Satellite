#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <vector>
#include "omp.h"

class Image
{
public:
    Image() : _data(), _bandCount(0), _xSize(0), _ySize(0){}
    virtual bool OpenImage(std::string filename)=0;
    virtual Eigen::VectorXd readPixel(unsigned int x, unsigned int y) const=0;
    virtual std::vector<float> getData() const {return _data;}
    virtual unsigned int getWidth() const {return _xSize;}
    virtual unsigned int getHeight() const {return _ySize;}
    virtual unsigned getBand() const {return _bandCount;}

protected:
    std::vector<float> _data;
    unsigned int _bandCount, _xSize, _ySize;
};

#endif // IMAGE_H
