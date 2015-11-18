#ifndef IMAGEOUT_H
#define IMAGEOUT_H

#include "train.h"
#include "imagetif.h"

class ImageOut
{
public:
    ImageOut();
    ~ImageOut(){}
    bool save(std::string filename);
    bool saveTIF(std::string filename);
    virtual void setTraining(Train* t)
    {
        _Classif = t;}
    virtual void setTIF(ImageTIF* img)
    {
        delete _imagIn;
        _imagIn = img;
    }
    int getClassif(unsigned int x, unsigned int y);

private:
    Train* _Classif;
    ImageTIF* _imagIn;
};

#endif // IMAGEOUT_H
