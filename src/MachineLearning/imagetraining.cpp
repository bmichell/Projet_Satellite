#include "imagetraining.h"

using namespace Eigen;
using namespace std;

ImageTraining::ImageTraining(const ImageTraining& other)
{
    this->_bandCount = other.getBand();
    this->_xSize = other.getWidth();
    this->_ySize = other.getHeight();
    this->_data.resize(_bandCount*(_xSize+_ySize));
#pragma omp parallel for
    for(unsigned y = 0; y < _bandCount*(_xSize+_ySize) ; y++)
    {
        this->_data[y] = other.readPixelParBand(y);
    }
}

ImageTraining ImageTraining::operator=(const ImageTraining& other)
{
    this->_bandCount = other.getBand();
    this->_xSize = other.getWidth();
    this->_ySize = other.getHeight();
    this->_data.resize(_bandCount*(_xSize+_ySize));
#pragma omp parallel for
    for(unsigned y = 0; y < _bandCount*(_xSize+_ySize) ; y++)
    {
        this->_data[y] = other.readPixelParBand(y);
    }
    return *this;
}

bool ImageTraining::OpenImage(std::string filename)
{
    fstream image;
    image.open(filename.c_str(), ios::in);
    if(image.is_open())
    {
        unsigned int size = 0;
        image >> size;
        _xSize = ceil(0.5*size);
        _ySize = floor(0.5*size);
        image >> _bandCount;
        _data.resize(size*_bandCount);
        for(unsigned int b = 0; b < _bandCount; b++)
        {
            for(unsigned int i = 0; i < size; i++)
            {
                image >> _data[b+i*_bandCount];
            }
        }
        image.close();
        return true;
    }
    return false;
}

Eigen::VectorXd ImageTraining::readPixel(unsigned int x, unsigned int y) const
{
    if(x+y>_data.size())
    {
        throw string("Pixel en dehors de l'image.");
    }
    VectorXd pixel(_bandCount);
    for(unsigned int i = 0; i< _bandCount; i++)
    {
        pixel[i] = _data[i+_bandCount*(y+x)];
    }
    return pixel;
}

float ImageTraining::readPixelParBand(unsigned int x, unsigned int y, unsigned int b) const
{
    return _data[b+_bandCount*(y+x)];
}

float ImageTraining::readPixelParBand(unsigned int i) const
{
    return _data[i];
}

std::vector<float> ImageTraining::getData() const
{
    return _data;
}
