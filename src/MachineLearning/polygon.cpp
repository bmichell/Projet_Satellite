#include "polygon.h"
using namespace Eigen;
using namespace std;

Polygon::Polygon() : _size(0), _bandCount(0), _data(_size), _class()
{
}

Polygon::Polygon(string filename) : _size(0), _bandCount(0), _data(_size), _class()
{
    OpenImage(filename);
}

Polygon::Polygon(const Class& cl) : _size(0), _bandCount(0), _data(_size), _class(cl)
{
}

Polygon::Polygon(const Polygon& other) : _size(other.size()), _bandCount(other.getBandCount()), _data(other.size()*other.getBandCount()), _class(other.getClass())
{
    for(unsigned i = 0; i  < _size ; i++)
    {
        this->_data[i] = other.getVector(i);
    }
}

Polygon Polygon::operator=(const Polygon& other)
{
    this->_bandCount = other.getBandCount();
    this->_size = other.size();
    this->_data.resize(_bandCount*_size);
    _class=other.getClass();
    for(unsigned i = 0; i  < _size ; i++)
    {
        this->_data[i] = other.getVector(i);
    }
    return *this;
}

bool Polygon::OpenImage(std::string filename)
{
    fstream image;
    image.open(filename.c_str(), ios::in);
    if(image.is_open())
    {
        double token;
        image >> _size;
        image >> _bandCount;
        VectorXd zero(VectorXd::Zero(_bandCount));
        _data.resize(_size);
        for(unsigned int i = 0; i < _size; i++)
        {
            _data[i] = zero;
        }
        for(unsigned int b = 0; b < _bandCount; b++)
        {
            for(unsigned int i = 0; i < _size; i++)
            {
                    image >> _data[i][b];
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
    return _data[i];
}

float Polygon::getValue(unsigned int index, unsigned int band) const
{
    return _data[index][band];
}

std::vector<VectorXd> Polygon::getData() const
{
    return _data;
}

Eigen::Vector3i Polygon::getColor() const
{
    return _class.getColor();
}

Class Polygon::getClass() const
{
    return _class;
}

unsigned int Polygon::size() const
{
    return _size;
}

unsigned int Polygon::getBandCount() const
{
    return _bandCount;
}
