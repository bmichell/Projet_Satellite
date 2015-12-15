/**
 * @file imageclassification.h
 * @brief Ce fichier contient toutes les fonctions nécessaires à la gestion d'image de classification
 * elle gère la partie classification (entrainement et image originale) et la partie image RGB.
 *
 * @author Benjamin MICHELLAND
 * @version 0.1
 * @date 5/12/2015
 */

#ifndef IMAGECLASSIFICATION_H
#define IMAGECLASSIFICATION_H
#include "image.h"
#include "training.h"
#include "imagetif.h"

/**
 * @class ImageClassification
 * @brief Classe gère les images de classification.
 * @date 12/11/2015
 */

class ImageClassification : public Image
{
public:
    ImageClassification();
    /**
     * Permet d'évaluer la classification et de générer ainsi l'image correspondante
     */
    virtual void evaluateClassif();
    /**
     * Permet de récupérer un vecteur contenant les composantes RGB d'un pixel
     * @param[in]     x est la position horizontale du pixel.
     * @param[in]     y est la position verticale du pixel.
     * @return un vecteur contenant les trois composantes RGB du pixel considéré.
     */
    virtual Eigen::Vector3i getRGB(float x, float y);
    /**
     * Permet de d'assigner un entrainement à cette classification.
     * @param[in]     t est un pointeur sur l'entrainement correspondant à la classification
     */
    virtual void setTraining(Training* t);
    /**
     * Permet de récupérer un vecteur contenant les composante RGB d'un pixel
     * @param[in]     img est un pointeur sur l'image d'origine sur laquelle on veut appliquer la classification.
     */
    virtual void setTIF(ImageTIF* img);

    /**
     * Permet de récupérer la largeur de l'image
     * @return La largeur de l'image.
     */
    virtual unsigned int getWidth() const;
    /**
     * Permet de récupérer la hauteur de l'image
     * @return La hauteur de l'image.
     */
    virtual unsigned int getHeight() const;

private :
    //! @brief Données de l'image
    std::vector<Eigen::Vector3i> _data;
    //! @brief Pointeur sur la classification
    Training* _Classif;
    //! @brief Pointeur sur l'image (TIF) originale
    ImageTIF* _imagIn;
};

#endif // IMAGECLASSIFICATION_H
