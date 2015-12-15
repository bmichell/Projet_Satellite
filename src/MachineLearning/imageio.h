/**
 * @file imageio.h
 * @brief Ce fichier contient la définition de la classe ImageOut qui permet la sauvegarde d'une Image, quelque soit son
 * format (TIF, PPM ou Classification).
 *
 * @author Benjamin MICHELLAND
 * @version 0.1
 * @date 12/11/2015
 */

#ifndef IMAGEOUT_H
#define IMAGEOUT_H
#include "training.h"
#include "imagetif.h"
#include "image.h"

/**
  @class ImageIO
  @brief Classe qui contient toutes les methodes necessaire a enregistrer des images,
  pour le moment uniquement au format ppm.
  @date 12/11/2015
*/

class ImageIO
{
public:
    ImageIO();
    virtual ~ImageIO(){}
    /**
     * Permet d'enregistrer l'image
     * @param[in]     filename est le chemin d'enregistrement de l'image.
     * @param[in]     img est une réference sur l'image à enregistrer.
     * @return true si le fichier est bien enregistré, false sinon.
     */
    virtual bool save(std::string filename, Image& img);
    virtual bool save1Band(std::string filename, ImageTIF &img, int b);
    /**
      @example savetif_ex.cpp
      Ceci est un exemple de l'enregistrement d'une image tif au format ppm (RGB)
      */
};

#endif // IMAGEOUT_H
