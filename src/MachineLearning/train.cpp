#include "train.h"

using namespace std;
using namespace Eigen;

Train::Train() : _train(), _normal(), _dir()
{
}

Train Train::operator=(const Train& other)
{
    this->_dir = other.getDir();
    this->_normal = other.getNormal();
    this->_train = other.getTrain();
    return *this;
}

bool Train::doTraining()
{
    for(unsigned int i = 0; i < _train.size(); i++)
    {
        unsigned int size = 0;
        for(unsigned int l = 0; l < _train.size(); l++)
        {
            size += _train[l].getWidth() + _train[l].getHeight();
        }
        VectorXd I(size);
        MatrixXd X(size, _train[i].getBand() + 1);
        int iter =0;
        for(unsigned int k = 0; k < _train.size(); k++)
        {
            for(unsigned int m = 0; m < _train[k].getWidth() + _train[k].getHeight()-2; m++)
            {
            if(k == i )
            {
                I[k]=1;
                VectorXd pixel = _train[k].readPixel(m,0);
                for(unsigned int j=0; j < pixel.size(); j++)
                {
                    X(iter,j)=pixel[j];
                }
                X(iter,_train[i].getBand())=1;
            }
            else
            {
                I[k]=-1;
                VectorXd pixel = _train[k].readPixel(m,0);
                for(unsigned int j=0; j < pixel.size(); j++)
                {
                     X(iter,j)=pixel[j];
                }
                X(iter,_train[i].getBand())=1;
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
