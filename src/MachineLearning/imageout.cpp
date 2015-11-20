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
        desc << this->_Classif->getClassif(_imagIn->readPixel(x,y)).transpose()
             << std::endl;
    }
}
desc.close();
return true;
}
