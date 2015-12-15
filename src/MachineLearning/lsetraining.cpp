#include "lsetraining.h"

using namespace std;
using namespace Eigen;

LSETraining::LSETraining() : _normal(), _isTrain(false)
{

}

LSETraining LSETraining::operator=(const LSETraining& other)
{
    this->_normal = other.getNormal();
    this->_polygons = other.getPolygons();
    this->_isTrain = bool(other.getNormal().size());
    return *this;
}

bool LSETraining::doTraining()
{
    unsigned int size = 0;
    unsigned int iter = 0;
    for(unsigned int l = 0; l < _polygons.size(); l++)
    {
        size += _polygons[l].size();
    }
    VectorXd I(size);
    I = VectorXd::Zero(size);
    MatrixXd X(size, _polygons[0].getBandCount() + 1);
    _normal.resize(_polygons.size());
    X = MatrixXd::Zero(size, _polygons[0].getBandCount() + 1);

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
        _normal[i] = nor;
        _normal[i].head(nor.size()-1)/=sqrt(_normal[i].head(nor.size()-1).cwiseProduct(_normal[i].head(nor.size()-1)).sum());
    }
    _isTrain = true;
    return true;
}

Vector3i LSETraining::getClassif(VectorXd vec) const
{
    if(vec.size() != _polygons[0].getBandCount())
    {
        throw string("Le vecteur n'as pas le bon nombre de bande %d / %d",vec.size(),_polygons[0].getBandCount());
    }
    if(!_isTrain)
    {
        throw string("Veuillez réaliser l'entrainement !!!");
    }

    vector<bool> is(getNumberOfClass());
    vector<float> dist(getNumberOfClass());
    for(unsigned int i = 0; i<getNumberOfClass(); i++)
    {
        VectorXd n = getNormal(i);
        dist[i] = vec.cwiseProduct(n.head(n.size()-1)).sum();
        float c=n[n.size()-1];
        is[i] = (dist[i] > c);
    }
    int tmp = -1;
    for(unsigned int i=0; i  < getNumberOfClass(); i++)
    {
        if(is[i])
        {
            if(tmp==-1)
            {
            tmp = i;
            }
            else if(dist[i] < dist[tmp])
            {
                tmp = i;
            }
        }
    }
    if(tmp == -1)
    {
        tmp = max_element(dist.begin(),dist.end()) - dist.begin();
    }
    return _polygons[tmp].getColor();
}
