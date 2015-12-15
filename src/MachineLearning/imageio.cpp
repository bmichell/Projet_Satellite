#include "imageio.h"
#include <omp.h>

using namespace std;
using namespace Eigen;

ImageIO::ImageIO()
{
}

bool ImageIO::save(std::string filename, Image &img)
{
    /// Ouverture du fichier de l'image PPM
    std::fstream desc(filename.c_str(), std::ios::out | std::ios::trunc);

    /// Vérification de l'ouverture du fichier
    if (desc.bad())
    {
        std::cout << "Ouverture en ecriture impossible." << std::endl;
        return false;
    }

    /// Ecriture de l'en-tête de l'image au format PPM (P3 = ASCII RGB\ Largeur Hauteur\ MaxVal\ Data)
    desc << "P3" << std::endl;
    desc << img.getWidth() << " " << img.getHeight() << std::endl;
    desc << 255 << std::endl;

    /// Double boucle for pour parcourrir tous les pixels de l'image
    for (unsigned y=0; y < img.getHeight(); y++)
    {
        for (unsigned x=0; x < img.getWidth(); x++)
        {
            /// Ecriture de la valeur de chaque pixel
            desc << img.getRGB(x,y).transpose()
                    << std::endl;
        }
    }
    /// Fermeture du fichier
    desc.close();
    return true;
}

bool ImageIO::save1Band(std::string filename, ImageTIF& img, int b)
{
    /// Ouverture du fichier de l'image PPM
    std::fstream desc(filename.c_str(), std::ios::out | std::ios::trunc);

    /// Vérification de l'ouverture du fichier
    if (desc.bad())
    {
        std::cout << "Ouverture en ecriture impossible." << std::endl;
        return false;
    }

    /// Ecriture de l'en-tête de l'image au format PPM (P3 = ASCII RGB\ Largeur Hauteur\ MaxVal\ Data)
    desc << "P2" << std::endl;
    desc << img.getWidth() << " " << img.getHeight() << std::endl;
    desc << 255 << std::endl;

    /// Double boucle for pour parcourrir tous les pixels de l'image
    for (unsigned y=0; y < img.getHeight(); y++)
    {
        for (unsigned x=0; x < img.getWidth(); x++)
        {
            /// Ecriture de la valeur de chaque pixel
            desc << img.readPixelParBand(x,y,b)*255
                 << std::endl;
        }
    }
    /// Fermeture du fichier
    desc.close();
    return true;
}
