#include "lsetraining.h"

using namespace std;
using namespace Eigen;

LSETraining::LSETraining() : _normal(), _isTrain(false)
{

}

LSETraining LSETraining::operator=(const LSETraining& other)
{
    this->_normal = other.getNormal();
    this->_polygons = other.getTrain();
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
        _normal.push_back(nor);
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

    vector<double> dist(getNumberOfClass());
    vector<float> c(3);
    for(unsigned int i = 0; i<getNumberOfClass(); i++)
    {
        VectorXd n = getNormal(i);
        dist[i]=vec.cwiseProduct(n.head(n.size()-1)).sum();
        c[i]=n[n.size()-1];
    }

    bool is1 = (dist[0] > - c[0]);
    bool is2 = (dist[1] > - c[1]);
    bool is3 = (dist[2] > - c[2]);

    Vector3i color = Vector3i(0,0,0);

    if(is1)
    {
        if(is2 && is3)
        {
            color[min_element(dist.begin(), dist.end()) - dist.begin()] = 255;
            return color;
        }
        else if(is2 && dist[1] < dist[0])
        {
            color[1] = 255;
            return color;
        }
        else if(is3 && dist[2] < dist[0])
        {
            color[2] = 255;
            return color;
        }
        color[0] = 255;
        return color;
    }
    else if(is2)
    {
        if(is3 && dist[2] < dist[1])
        {
            color[2] = 255;
            return color;
        }
        color[1] = 255;
        return color;
    }
    else if(is3)
    {
        color[2] = 255;
        return color;
    }
    else
    {
        return color;
    }
}

Matrix4f LSETraining::confusionMatrix() const
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
