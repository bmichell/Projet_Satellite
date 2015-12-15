#include "ldatraining.h"
#include <iostream>

using namespace Eigen;
using namespace std;

LDATraining::LDATraining() : _normal(), _moy(), _isTrain(false)
{
}

LDATraining LDATraining::operator=(const LDATraining& other)
{
    this->_normal = other.getNormal();
    this->_moy = other.getMoy();
    this->_polygons = other.getPolygons();
    this->_isTrain = bool(other.getNormal().size());
    return *this;
}

bool LDATraining::doTraining()
{
    VectorXd zero(VectorXd::Zero(_polygons[0].getBandCount()));
    VectorXd inv_ETypeMoy = zero;
    VectorXd EType = zero;
    _moy.resize(_polygons.size());
    _normal.resize(_polygons.size());
    for(unsigned int i = 0; i < _polygons.size(); i++)
        {
            VectorXd tmp(_polygons[i].getBandCount());
            for(unsigned int j = 0; j < _polygons[i].size(); j++)
            {
                tmp += _polygons[i].getVector(j);
            }
            _moy[i] = tmp/_polygons[i].size();
        }

        for(unsigned int i = 0; i < _polygons.size(); i++)
        {
            VectorXd tmp(_polygons[i].getBandCount());
            tmp=zero;
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
                _normal[iter] = inv_ETypeMoy.cwiseProduct(_moy[i]-_moy[j]);
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

    vector<bool> isInotJ(getNumberOfClass()*getNumberOfClass());
    int iter = 0;
    for(unsigned int i = 0; i < _polygons.size()-1; i++)
    {
        for(unsigned int j = i+1; j < _polygons.size(); j++)
        {
            VectorXd n = getNormal(iter);
            double dist=vec.cwiseProduct(n).sum();
            double c=(_moy[i].cwiseProduct(n).sum()+_moy[j].cwiseProduct(n).sum())*0.299;
            isInotJ[iter] = (dist > c);
            iter++;
        }
    }
    vector<float> choice(getNumberOfClass());
    iter = 0;
    for(unsigned int i = 0; i < _polygons.size()-1; i++)
    {
        for(unsigned int j = i+1; j < _polygons.size(); j++)
        {
            if(isInotJ[iter])
            {
                choice[i]++;
            }
            else
            {
                choice[j]++;
            }
            iter++;
        }
    }
    int tmp = max_element(choice.begin(), choice.end()) - choice.begin();
    return _polygons[tmp].getColor();
}

