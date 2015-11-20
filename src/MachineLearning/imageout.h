#ifndef IMAGEOUT_H
#define IMAGEOUT_H

#include "lsetraining.h"
#include "imagetif.h"

class ImageOut
{
public:
    ImageOut();
    ~ImageOut(){}
    bool save(std::string filename);
    bool saveTIF(std::string filename);
    virtual void setTraining(Training* t)
    {
        _Classif = t;}
    virtual void setTIF(ImageTIF* img)
    {
        delete _imagIn;
        _imagIn = img;
    }

private:
    Training* _Classif;
    ImageTIF* _imagIn;
};

#endif // IMAGEOUT_H
