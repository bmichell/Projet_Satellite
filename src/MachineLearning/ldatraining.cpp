#include "ldatraining.h"
#include <iostream>

using namespace Eigen;
using namespace std;

LDATraining::LDATraining()
{
}

bool LDATraining::doTraining()
{
    VectorXd inv_ETypeMoy(_polygons[0].getBandCount());
    VectorXd EType(_polygons[0].getBandCount());

    for(unsigned int i = 0; i < _polygons.size(); i++)
    {
        VectorXd tmp(_polygons[i].getBandCount());
        for(unsigned int j = 0; j < _polygons[i].size(); j++)
        {
            tmp += _polygons[i].getVector(j);
        }
        _moy.push_back(tmp/_polygons[i].size());
    }

    for(unsigned int i = 0; i < _polygons.size(); i++)
    {
        VectorXd tmp(_polygons[i].getBandCount());
        for(unsigned int j = 0; j < _polygons[i].size(); j++)
        {
            VectorXd diff = _polygons[i].getVector(j) - _moy[i];
            tmp += diff.cwiseProduct(diff);
        }
        for(unsigned k = 0; k < tmp.size(); k++)
        {
            EType[k] += sqrt(tmp[k]/_polygons[i].size())/_polygons.size();
        }
    }

    for(unsigned k = 0; k < EType.size(); k++)
    {
        inv_ETypeMoy[k] = 1.0/EType[k];
    }
    int iter=0;
    for(unsigned int i = 0; i < _polygons.size()-1; i++)
    {
        for(unsigned int j = i+1; j < _polygons.size(); j++)
        {
            _normal.push_back(inv_ETypeMoy.cwiseProduct(_moy[i]-_moy[j]));
            _normal[iter]/=sqrt(_normal[iter].cwiseProduct(_normal[iter]).sum());
            iter++;
        }
    }
    _isTrain = true;
    return true;
}

Eigen::Vector3i LDATraining::getClassif(Eigen::VectorXd vec) const
{
    if(vec.size() != _polygons[0].getBandCount())
    {
        throw string("Le vecteur n'as pas le bon nombre de bande %d / %d",vec.size(),_polygons[0].getBandCount());
    }
    if(!_isTrain)
    {
        throw string("Veuillez réaliser l'entrainement !!!");
    }

    vector<double> dist(getNumberOfClass());
    vector<double> c(getNumberOfClass());
    int iter = 0;
    for(unsigned int i = 0; i < _polygons.size()-1; i++)
    {
        for(unsigned int j = i+1; j < _polygons.size(); j++)
        {
        VectorXd n = getNormal(iter);
        dist[iter]=vec.cwiseProduct(n).sum();
        c[iter]=(_moy[i].cwiseProduct(n).sum()+_moy[j].cwiseProduct(n).sum())*0.299;
        iter++;
        }
    }
    bool is1not2 = (dist[0] > c[0]);
    bool is1not3 = (dist[1] > c[1]);
    bool is2not3 = (dist[2] > c[2]);

    if(is1not2)
    {
        if(is1not3 || is2not3)
        {
            return Vector3i(255,0,0);
        }
        else if(!is2not3)
        {
            return Vector3i(0,0,255);
        }
        else
        {
            return Vector3i(0,0,0);
        }
    }
    else if(is2not3)
    {
        return Vector3i(0,255,0);
    }
    else
    {
        return Vector3i(0,0,0);
    }
}

Eigen::Matrix4f LDATraining::confusionMatrix() const
{
    Matrix4f confusion;
    confusion << 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0;
    int size = 0;
    for(unsigned int i = 0; i < _polygons.size();i++)
    {
        for(unsigned j =0; j < _polygons[i].size() ; j++)
        {
            if(getClassif(_polygons[i].getVector(i))[0] == 255)
            {
                confusion(i,0)++;
            }
            else if(getClassif(_polygons[i].getVector(i))[1] == 255)
            {
                confusion(i,1)++;
            }
            else if(getClassif(_polygons[i].getVector(i))[2] == 255)
            {
                confusion(i,2)++;
            }
        }
        size += _polygons[i].size();
        confusion(i,3) = confusion(i,i)/_polygons[i].size();
    }
    confusion(3,0) = confusion(0,0)/(confusion(0,0)+confusion(1,0)+confusion(2,0));
    confusion(3,1) = confusion(1,1)/(confusion(1,1)+confusion(1,0)+confusion(1,2));
    confusion(3,2) = confusion(2,2)/(confusion(2,2)+confusion(1,2)+confusion(0,2));
    confusion(3,3) = (confusion(0,0)+confusion(1,1)+confusion(2,2))/size;
    return confusion;
}
