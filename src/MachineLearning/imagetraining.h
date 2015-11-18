#ifndef IMAGETRAINING_H
#define IMAGETRAINING_H
#include "image.h"
#include <fstream>

class ImageTraining : public Image
{
public:
    ImageTraining(){}
    ImageTraining(std::string filename);
    ImageTraining(const ImageTraining& other);
    ImageTraining operator=(const ImageTraining& other);
    virtual ~ImageTraining() {}
    virtual bool OpenImage(std::string filename);
    virtual Eigen::VectorXd readPixel(unsigned int x, unsigned int y) const;
    virtual float readPixelParBand(unsigned int x, unsigned int y, unsigned int b) const;
    virtual float readPixelParBand(unsigned int i) const;
    virtual std::vector<float> getData() const;
    virtual unsigned int getWidth() const {return _xSize;}
    virtual unsigned int getHeight() const {return _ySize;}
};

#endif // IMAGETRAINING_H
