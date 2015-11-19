#include "imagetif.h"

using namespace Eigen;
using namespace std;

ImageTIF::ImageTIF(const ImageTIF& other)
{
    *this = other;
}

ImageTIF ImageTIF::operator=(const ImageTIF& other)
{
    _xSize = other.getWidth();
    _ySize = other.getHeight();
    _bandCount = other.getBand();
    _data.resize(_xSize*_ySize*_bandCount);
    for(unsigned y = 0; y< _ySize;y++)
    {
        for(unsigned x = 0; x< _xSize;x++)
        {
        VectorXd pixel = other.readPixel(x,y);
        for(unsigned b = 0; b< _bandCount;b++)
        {
            _data[b+_bandCount*y+x*_bandCount*_ySize] = pixel[b];
        }
        }
    }
    return *this;
}

bool ImageTIF::OpenImage(std::string filename)
{
    GDALDataset  *poDataset;
    GDALAllRegister();
    poDataset     = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly );
    _ySize     = poDataset->GetRasterYSize();
    _xSize     = poDataset->GetRasterXSize();
    _bandCount = 13;
    _data.resize(_ySize*_xSize*_bandCount);
    GDALRasterBand *bands;
    if( poDataset != NULL )
    {
        // read one row from each band and store it in list
        for (unsigned int b = 1; b <= _bandCount; ++b )
        {
            bands = poDataset->GetRasterBand(b);
        // iterate over image row by row
        for (unsigned int row = 0; row < _ySize; ++row )
        {
                float *scanline;
                scanline = (float *) CPLMalloc( sizeof( float ) * _xSize );
                bands->RasterIO( GF_Read, 0, row, _xSize, 1, scanline, _xSize,
                                      1, GDT_Float32, 0, 0 );
                for (unsigned int col = 0; col < _xSize; ++col)
                {
                        // get value in (row, col) from band r
                        _data[b-1+_bandCount*row+col*_bandCount*_ySize] = scanline[col];
                }
            }
        }
        GDALClose(poDataset);
        return true;
    }
    return false;
}

Eigen::VectorXd ImageTIF::readPixel(unsigned int x, unsigned int y) const
{
    if(x >= _xSize || y >= _ySize)
    {
        throw string("Pixel en dehors de l'image.");
    }
    else
    {
        VectorXd pixel(_bandCount);
        for(unsigned int i = 0; i< _bandCount; i++)
        {
            pixel[i] = _data[i+_bandCount*y+x*_ySize*_bandCount];
        }
        return pixel;
    }
}

float ImageTIF::readPixelParBand(unsigned int x, unsigned int y, unsigned int b) const
{
    return _data[b+_bandCount*y+x*_ySize*_bandCount];
}

std::vector<float> ImageTIF::getData() const
{
    return _data;
}
