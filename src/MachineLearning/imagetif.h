#ifndef IMAGETIF_H
#define IMAGETIF_H
#include "image.h"
#include "gdal/gdal_priv.h"
#include "gdal/cpl_conv.h"


class ImageTIF : public Image
{
public:
    ImageTIF(){}
    ImageTIF(const ImageTIF& other);
    ImageTIF operator=(const ImageTIF& other);
    virtual ~ImageTIF() {}
    virtual bool OpenImage(std::string filename);
    virtual Eigen::VectorXd readPixel(unsigned int x, unsigned int y) const;
    virtual float readPixelParBand(unsigned int x, unsigned int y, unsigned int b) const;
    virtual std::vector<float> getData() const;

};

#endif // IMAGETIF_H
