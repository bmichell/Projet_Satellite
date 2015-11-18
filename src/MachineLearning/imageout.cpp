#include "imageout.h"

using namespace std;
using namespace Eigen;

ImageOut::ImageOut()
{
    _imagIn = new ImageTIF();
}

bool ImageOut::saveTIF(std::string filename)
{
    std::fstream desc(filename.c_str(), std::ios::out | std::ios::trunc);

    /* Vérification de l'ouverture du fichier */
    if (desc.bad())
    {
        std::cout << "Ouverture en ecriture impossible." << std::endl;
        return false;
    }
    desc << "P3" << std::endl;
    desc << _imagIn->getWidth() << " " << _imagIn->getHeight() << std::endl;
    desc << 255 << std::endl;

    for (unsigned y=0; y < _imagIn->getHeight(); y++)
    {
        for (unsigned x=0; x < _imagIn->getWidth(); x++)
        {
            /* Ecriture de la valeur de chaque pixel */
            desc << _imagIn->readPixelParBand(x,y,3) << " ";
            desc << _imagIn->readPixelParBand(x,y,2) << " ";
            desc << _imagIn->readPixelParBand(x,y,1) << " ";
            desc << std::endl;
        }
    }
    desc.close();
    return true;
}

bool ImageOut::save(std::string filename)
{
std::fstream desc(filename.c_str(), std::ios::out | std::ios::trunc);

/* Vérification de l'ouverture du fichier */
if (desc.bad())
{
    std::cout << "Ouverture en ecriture impossible." << std::endl;
    return false;
}
desc << "P3" << std::endl;
desc << _imagIn->getWidth() << " " << _imagIn->getHeight() << std::endl;
desc << 255 << std::endl;

for (unsigned y=0; y < _imagIn->getHeight(); y++)
{
    for (unsigned x=0; x < _imagIn->getWidth(); x++)
    {
        /* Ecriture de la valeur de chaque pixel */
        if(getClassif(x,y) == 1)
        desc << 255 << " ";
        else
        desc << 0 << " ";
        if(getClassif(x,y) == 2)
        desc << 255 << " ";
        else
        desc << 0 << " ";
        if(getClassif(x,y) == 3)
        desc << 255 << " ";
        else
        desc << 0 << " ";
        desc << std::endl;
    }
}
desc.close();
return true;
}

int ImageOut::getClassif(unsigned int x, unsigned int y)
{
    VectorXd pixel(_imagIn->getBand());
    for(unsigned int b=0; b<_imagIn->getBand(); b++)
    {
        pixel[b] = _imagIn->readPixelParBand(x,y,b);
    }
    vector<double> dist(_Classif->getNumberOfClass());
    for(unsigned int i = 0; i<_Classif->getNumberOfClass(); i++)
    {
        VectorXd n = _Classif->getNormal(i);
        dist[i]=pixel.cwiseProduct(n).sum();
    }
    bool is1 = (dist[0] > 0);
    bool is2 = (dist[1] > 0);
    bool is3 = (dist[2] > 0);

    if(is1)
    {
        if(is2 && is3)
        {
            return min_element(dist.begin(), dist.end()) - dist.begin() + 1;
        }
        else if(is2 && dist[1] < dist[0])
        {
            return 2;
        }
        else if(is3 && dist[2] < dist[0])
        {
            return 3;
        }
        return 1;
    }
    else if(is2)
    {
        if(is3 && dist[2] < dist[1])
        {
            return 3;
        }
        return 2;
    }
    else
    {
        return 3;
    }

    throw string("Pas de classification.");
}
