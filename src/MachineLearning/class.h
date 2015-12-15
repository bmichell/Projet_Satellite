#ifndef CLASS_H
#define CLASS_H
#include <eigen3/Eigen/Eigen>
#include <vector>

class Class
{
public:
    Class();
    Class(const Class& other);
    virtual Eigen::Vector3i getColor() const;

private:
    Eigen::Vector3i _color;


public:
    static unsigned int _iter;
};

#endif // CLASS_H
