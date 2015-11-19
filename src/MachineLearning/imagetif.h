#ifndef IMAGETIF_H
#define IMAGETIF_H
#include <iostream>
#include <Eigen/Eigen>
#include <vector>
#include "omp.h"
#include "gdal_priv.h"
#include "cpl_conv.h"


class ImageTIF
{
public:
    ImageTIF() : _data(), _bandCount(0), _xSize(0), _ySize(0){}
    ImageTIF(const ImageTIF& other);
    ImageTIF operator=(const ImageTIF& other);
    virtual ~ImageTIF() {}
    virtual bool OpenImage(std::string filename);
    virtual Eigen::VectorXd readPixel(unsigned int x, unsigned int y) const;
    virtual float readPixelParBand(unsigned int x, unsigned int y, unsigned int b) const;
    virtual std::vector<float> getData() const;
    virtual unsigned int getWidth() const {return _xSize;}
    virtual unsigned int getHeight() const {return _ySize;}
    virtual unsigned getBand() const {return _bandCount;}

    protected:
    std::vector<float> _data;
    unsigned int _bandCount, _xSize, _ySize;
};

#endif // IMAGETIF_H
