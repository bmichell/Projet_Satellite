#include "polygon.h"

using namespace Eigen;
using namespace std;

Polygon::Polygon(const Polygon& other) : _size(other.size()), _bandCount(other.getBandCount()), _data(other.size()*other.getBandCount())
{
    for(unsigned i = 0; i  < _size ; i++)
    {
        for(unsigned b = 0; b < _bandCount; b++)
        {
            this->_data[b+i*_bandCount] = other.getValue(i,b);
        }
    }
}

Polygon Polygon::operator=(const Polygon& other)
{
    this->_bandCount = other.getBandCount();
    this->_size = other.size();
    this->_data.resize(_bandCount*_size);
    for(unsigned i = 0; i  < _size ; i++)
    {
        for(unsigned b = 0; b < _bandCount; b++)
        {
            this->_data[b+i*_bandCount] = other.getValue(i,b);
        }
    }
    return *this;
}

bool Polygon::OpenImage(std::string filename)
{
    fstream image;
    image.open(filename.c_str(), ios::in);
    if(image.is_open())
    {
        image >> _size;
        image >> _bandCount;
        _data.resize(_size*_bandCount);
        for(unsigned int b = 0; b < _bandCount; b++)
        {
            for(unsigned int i = 0; i < _size; i++)
            {
                image >> _data[b+i*_bandCount];
            }
        }
        image.close();
        return true;
    }
    return false;
}

Eigen::VectorXd Polygon::getVector(unsigned int i) const
{
    if(i>=_data.size())
    {
        throw string("Pixel en dehors de l'image.");
    }
    VectorXd pixel(_bandCount);
    for(unsigned int b = 0; b< _bandCount; b++)
    {
        pixel[b] = _data[b+_bandCount*i];
    }
    return pixel;
}

float Polygon::getValue(unsigned int index, unsigned int band) const
{
    return _data[band +_bandCount*index];
}

std::vector<float> Polygon::getData() const
{
    return _data;
}
