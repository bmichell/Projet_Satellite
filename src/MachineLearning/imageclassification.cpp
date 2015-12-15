#include "imageclassification.h"

using namespace std;
using namespace Eigen;

ImageClassification::ImageClassification()
{
    _imagIn = NULL;
}

void ImageClassification::evaluateClassif()
{
    /// On redimensionne le tableau des données (_data) à la taille de l'image
    _data.resize(_imagIn->getHeight()*_imagIn->getWidth());
    /// On parcourt chaque pixel de l'image et on récupére la couleur de la classification grâce au trainer.
    for (unsigned y=0; y < _imagIn->getHeight(); y++)
    {
        for (unsigned x=0; x < _imagIn->getWidth(); x++)
        {
            _data[x+y*_imagIn->getWidth()] = this->_Classif->getClassif(_imagIn->readPixel(x,y));
        }
    }
}

void ImageClassification::setTraining(Training* t)
{
    _Classif = t;
}

void ImageClassification::setTIF(ImageTIF* img)
{
    if(_imagIn != NULL)
    {
    delete _imagIn;
    }
    _imagIn = img;
}

unsigned int ImageClassification::getWidth() const
{
    return _imagIn->getWidth();
}

unsigned int ImageClassification::getHeight() const
{
    return _imagIn->getHeight();
}

Vector3i ImageClassification::getRGB(float x, float y)
{
    Vector3i pixel(0,0,0);
    int x1=round(x);
    int y1=round(y);
    pixel = _data[x1+y1*_imagIn->getWidth()];
    return pixel;
}
