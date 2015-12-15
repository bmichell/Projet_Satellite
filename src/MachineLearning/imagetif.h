/**
 * @file imagetif.h
 * @brief Ce fichier contient la definition de la classe ImageTIF qui permet de gerer les images au format Geotif à l'aide
 * Gdal.
 *
 * @author Benjamin MICHELLAND
 * @version 0.1
 * @date 12/11/2015
 */

#ifndef IMAGETIF_H
#define IMAGETIF_H
#include "../external/gdal/include/gdal_priv.h"
#include "../external/gdal/include/cpl_conv.h"
#include "image.h"

/**
  @class ImageTIF
  @brief Classe qui contient toutes les methodes necessaire a enregistrer des images,
  pour le moment uniquement au format ppm.
  @date 12/11/2015
*/
class ImageTIF : public Image
{
public:
    ImageTIF() : _data(), _bandCount(0), _xSize(0), _ySize(0){}
    ImageTIF(const std::string filename);
    ImageTIF(const ImageTIF& other);
    ImageTIF operator=(const ImageTIF& other);
    virtual ~ImageTIF() {}
    /**
     * Permet d'ouvrir une image multispectrale GeoTIF à l'aide de la librairie GDAL
     * @param[in]     filename est le chemin de l'image.
     * @return true si le fichier est bien ouvert, false sinon.
     */
    virtual bool OpenImage(std::string filename);
    /**
     * Permet d'obtenir un vecteur contenant toutes les bandes d'un pixel
     * @param[in]     x est la coordonnée horizontale du pixel.
     * @param[in]     y est la coordonnée verticale du pixel.
     * @return le vecteur contenant toutes les bandes.
     */
    virtual Eigen::VectorXd readPixel(unsigned int x, unsigned int y) const;
    /**
     * Permet d'obtenir la valeur d'une bande d'un pixel extrapolé dans l'image, cette valeur peut notament servir
     * pour redimentionner l'image.
     * @param[in]     x est la coordonnée horizontale du pixel.
     * @param[in]     y est la coordonnée verticale du pixel.
     * @param[in]     b est le numéro de la bande.
     * @return la valeur de la bande du pixel.
     */
    virtual float readPixelParBand(float x, float y, unsigned int b) const;
    /**
     * Permet d'obtenir la valeur d'une bande d'un pixel déjà existant dans l'image.
     * @param[in]     x est la coordonnée horizontale du pixel.
     * @param[in]     y est la coordonnée verticale du pixel.
     * @param[in]     b est le numéro de la bande.
     * @return la valeur de la bande du pixel.
     */
    virtual float readPixelParBand(unsigned int x, unsigned int y, unsigned int b) const;
    /**
     * Permet d'obtenir le tableau complet des données.
     * @return le tableau des valeurs flottantes de l'image.
     */
    virtual std::vector<float> getData() const;
    /**
     * Permet de recuperer un vecteur contenant les composante RGB d'un pixel
     * @param[in]     x est la position horizontale du pixel.
     * @param[in]     y est la position verticale du pixel.
     * @return un vecteur contenant les trois composantes RGB du pixel considéré.
     */
    virtual Eigen::Vector3i getRGB(float x, float y);
    /**
     * Permet de récuperer la largeur de l'image
     * @return La largeur de l'image.
     */
    virtual unsigned int getWidth() const {return _xSize;}
    /**
     * Permet de récuperer la hauteur de l'image
     * @return La hauteur de l'image.
     */
    virtual unsigned int getHeight() const {return _ySize;}
    /**
     * Permet de récuperer le nombre de bandes de l'image
     * @return Le nombre de bandes de l'image.
     */
    virtual unsigned getBand() const {return _bandCount;}
    virtual void corPPM(std::string filename);

protected:
    //! @brief Vecteur contenant toute les valeurs des pixels de l'image original
    std::vector<float> _data;
    //! @brief Donnees intrinsec de l'image (hauteur, largeur et nombre de bandes)
    unsigned int _bandCount, _xSize, _ySize;
};

#endif // IMAGETIF_H
