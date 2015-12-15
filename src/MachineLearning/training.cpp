#include "training.h"

using namespace Eigen;
using namespace std;

Eigen::MatrixXf Training::confusionMatrix() const
{
    MatrixXf confusion(_polygons.size()+1,_polygons.size()+1);
    VectorXd row(_polygons.size());
    row = VectorXd::Zero(_polygons.size());
    confusion = MatrixXf::Zero(_polygons.size()+1,_polygons.size()+1);
    int size = 0;
    for(unsigned int i = 0; i < _polygons.size();i++)
    {
        for(unsigned j =0; j < _polygons[i].size() ; j++)
        {
            for(unsigned int k = 0; k < _polygons.size();k++)
            {
                if(getClassif(_polygons[i].getVector(j)) == _polygons[k].getColor())
                {
                    confusion(i,k)++;
                }
            }
        }
        size += _polygons[i].size();
        confusion(i,_polygons.size()) = confusion(i,i)/_polygons[i].size();
    }
    int size2 = 0;
    for(unsigned int k = 0; k < _polygons.size();k++)
    {
        size2=0;
        for(unsigned int j = 0; j < _polygons.size(); j++)
        {
            size2+=confusion(j,k);
        }
        confusion(_polygons.size(),k) = confusion(k,k)/size2;
        confusion(_polygons.size(),_polygons.size()) += confusion(k,k);
    }
    confusion(_polygons.size(),_polygons.size()) /= size;
    return confusion;
}

Eigen::MatrixXf Training::confusionMatrix(vector<Polygon> polygons) const
{
    MatrixXf confusion(polygons.size()+1,polygons.size()+1);
    VectorXd row(polygons.size());
    row = VectorXd::Zero(polygons.size());
    confusion = MatrixXf::Zero(polygons.size()+1,polygons.size()+1);
    int size = 0;
    for(unsigned int i = 0; i < polygons.size();i++)
    {
        for(unsigned j =0; j < max(polygons[i].size(),(unsigned)10000) ; j++)
        {
            for(unsigned int k = 0; k < polygons.size();k++)
            {
                if(getClassif(polygons[i].getVector(j)) == polygons[k].getColor())
                {
                    confusion(i,k)++;
                }
            }
        }
        size += max(polygons[i].size(),(unsigned)10000);
        confusion(i,polygons.size()) = confusion(i,i)/max(polygons[i].size(),(unsigned)10000);
    }
    int size2 = 0;
    for(unsigned int k = 0; k < polygons.size();k++)
    {
        size2=0;
        for(unsigned int j = 0; j < polygons.size(); j++)
        {
            size2+=confusion(j,k);
        }
        confusion(polygons.size(),k) = confusion(k,k)/size2;
        confusion(polygons.size(),polygons.size()) += confusion(k,k);
    }
    confusion(polygons.size(),polygons.size()) /= size;
    return confusion;
}

void Training::addImage(Polygon& image)
{
    _polygons.push_back(image);
}

unsigned int Training::getNumberOfClass() const
{
    return _polygons.size();
}

vector<Polygon> Training::getPolygons() const
{
    return _polygons;
}
