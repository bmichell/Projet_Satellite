#include "imagetif.h"
#include "fstream"
#include "var.h"

using namespace Eigen;
using namespace std;

ImageTIF::ImageTIF(const ImageTIF& other)
{
    *this = other;
}

ImageTIF::ImageTIF(const string filename)
{
    /// On ouvre l'image dont le chemin est filename
    OpenImage(filename);
}

ImageTIF ImageTIF::operator=(const ImageTIF& other)
{
    /// On initialise toutes les caractèristiques à l'aide des accesseurs de other.
    _xSize = other.getWidth();
    _ySize = other.getHeight();
    _bandCount = other.getBand();
    /// On redimentionne _data à la taille de l'image
    _data.resize(_xSize*_ySize*_bandCount);
    /// On lit tous les pixels de other et on les stocke dans _data.
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
    ///On initialise toutes les caractèristiques à l'aide des données de l'image Geotif.
    _ySize     = poDataset->GetRasterYSize();
    _xSize     = poDataset->GetRasterXSize();
    _bandCount = 12;
    GDALRasterBand *bands;
     _data.resize(_ySize*_xSize*(_bandCount));
    if( poDataset != NULL )
    {
        /// Pour chaque bande on lit une ligne, puis on parcourt les colonnes
        for (unsigned int b = 1; b <= _bandCount+1; ++b )
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
                    if(b<11)
                    {
                        _data[b-1+_bandCount*row+col*_bandCount*_ySize] = scanline[col];
                    }
                    else if(b>11)
                    {
                        _data[b-2+_bandCount*row+col*_bandCount*_ySize] = scanline[col];
                    }
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
        ///On crée un vecteur qui contient toutes les données d'un pixel
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

float ImageTIF::readPixelParBand(float x, float y, unsigned int b) const
{
    float pixel=0;
    int x1=round(x);
    int y1=round(y);
    pixel = _data[b+_bandCount*y1+x1*_ySize*_bandCount];
    return pixel;
}

Vector3i ImageTIF::getRGB(float x, float y)
{
    Vector3i pixel;
    int x1=round(x);
    int y1=round(y);
    /// On renvoie les bandes 4, 3 et 2 qui correspondent aux couleurs RGB sur les images Sentinel2
    pixel[0] = min((int)round(_data[3+_bandCount*y1+x1*_ySize*_bandCount]),255);
    pixel[1] = min((int)round(_data[2+_bandCount*y1+x1*_ySize*_bandCount]),255);
    pixel[2] = min((int)round(_data[1+_bandCount*y1+x1*_ySize*_bandCount]),255);
    return pixel;
}

std::vector<float> ImageTIF::getData() const
{
    return _data;
}

void ImageTIF::corPPM(std::string filename)
{
    fstream image;
    image.open(filename.c_str(), ios::in);
    unsigned int height=0, width=0;
    std::string token;
    if(image.is_open())
    {
        image >> token;
        image >> width;
        image >> height;
        _data.resize(3*height*width);
        for(unsigned int y = 0; y < height; y++)
        {
            for(unsigned int x = 0; x < width; x++)
            {
                for(int i =0; i < 3; i++)
                {
                    image >> _data[i+3*x+3*width*y];
                    if(_data[i+3*x+3*width*y] != 255)
                    {
                        _data[i+3*x+3*width*y]=0;
                    }
                }
            }
        }
        image.close();
    }

    std::fstream desc("/home/benjamin.michelland/Projet_Satellite/src/Projet_Satelitte2/data/out/corSVM", std::ios::out | std::ios::trunc);

    /// Vérification de l'ouverture du fichier
    if (desc.bad())
    {
        std::cout << "Ouverture en ecriture impossible." << std::endl;
    }

    /// Ecriture de l'en-tête de l'image au format PPM (P3 = ASCII RGB\ Largeur Hauteur\ MaxVal\ Data)
    desc << "P3" << std::endl;
    desc << width << " " << height << std::endl;
    desc << 255 << std::endl;

    /// Double boucle for pour parcourrir tous les pixels de l'image
    for (unsigned y=0; y < height; y++)
    {
        for (unsigned x=0; x < width; x++)
        {
            /// Ecriture de la valeur de chaque pixel
            desc << _data[1+3*x+3*width*y] << " " << _data[2+3*x+3*width*y] << " " << _data[3*x+3*width*y]
                    << std::endl;
        }
    }
    /// Fermeture du fichier
    desc.close();
}
