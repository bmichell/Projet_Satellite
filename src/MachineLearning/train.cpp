#include "train.h"

using namespace std;
using namespace Eigen;

Train::Train() : _polygons(), _normal(), _dir()
{
}

Train Train::operator=(const Train& other)
{
    this->_dir = other.getDir();
    this->_normal = other.getNormal();
    this->_polygons = other.getTrain();
    return *this;
}

bool Train::doTraining()
{
    unsigned int size = 0;
    unsigned int iter = 0;
    for(unsigned int l = 0; l < _polygons.size(); l++)
    {
        size += _polygons[l].size();
    }
    VectorXd I(size);
    MatrixXd X(size, _polygons[0].getBandCount() + 1);

    for(unsigned int i = 0; i < _polygons.size(); i++)
    {
        for(unsigned int m = 0; m < _polygons[i].size(); m++)
        {
        VectorXd pixel = _polygons[i].getVector(m);
        for(unsigned int j=0; j < pixel.size(); j++)
        {
            X(iter,j)=pixel[j];
        }
        iter++;
        }
         X(iter-1,_polygons[i].getBandCount())=1;
    }

    for(unsigned int i = 0; i < _polygons.size(); i++)
    {
        iter = 0;
        for(unsigned int k = 0; k < _polygons.size(); k++)
        {
            for(unsigned int m = 0; m < _polygons[k].size(); m++)
            {
            if(k == i )
            {
                I[iter]=1;
            }
            else
            {
                I[iter]=-1;
            }
            iter++;
            }
        }
        VectorXd nor(X.colPivHouseholderQr().solve(I));
        VectorXd normal(nor.head(nor.size()-1));
        _normal.push_back(normal);
        _normal[i]/=sqrt(_normal[i].cwiseProduct(_normal[i]).sum());
    }
    return true;
}
