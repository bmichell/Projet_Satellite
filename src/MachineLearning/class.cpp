#include "class.h"
unsigned int Class::_iter = 0;
Class::Class() : _color(Eigen::Vector3i::Zero())
{
    if(_iter>9)
    {
        int tmp = _iter%9;
        if(tmp < 3)
        {
            _color[tmp]=255;
        }
        else
        {
            _color[tmp/3]=125;
            _color[tmp%3]=125;
        }
    }
    else if(_iter < 3)
    {
        _color[_iter]=255;
    }
    else
    {
        _color[_iter/3]=125;
        _color[_iter%3]=125;
    }
    _iter++;
}

Class::Class(const Class &other)
{
    _color = other.getColor();
}

Eigen::Vector3i Class::getColor() const
{
 return _color;
}
