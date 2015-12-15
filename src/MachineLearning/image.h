/**
 * @file image.h
 * @brief Ce fichier contient la définition de l'interface Image. Cette interface est un canevas pour pourvoir intégrer de nouveaux formats
 * d'image dans le projet. Cette interface a pour but notamment de permettre d'afficher les images au format RGB, même si elles sont redimensionnées.
 * D'autre part, elle permet de récupérer toutes les informations intrinsèques de l'image.
 *
 * @author Benjamin MICHELLAND
 * @version 0.1
 * @date 24/11/2015
 */
#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <Eigen/Eigen>
#include <vector>

/**
  @interface Image
  @brief Interface définissant les fonctions de base nécessaire à la gestion des images, quel que soit leur format (TIF, PPM, ...)
  @date 24/11/2015
*/

class Image
{
public:

    /**
     * Permet de récupérer un vecteur contenant les composante RGB d'un pixel
     * @param[in]     x est la position horizontale du pixel.
     * @param[in]     y est la position verticale du pixel.
     * @return un vecteur contenant les trois composantes RGB du pixel considéré.
     */
    virtual Eigen::Vector3i getRGB(float x, float y) = 0;
    /**
     * Permet de récupérer la largeur de l'image
     * @return La largeur de l'image.
     */
    virtual unsigned int getWidth() const = 0;
    /**
     * Permet de récupérer la hauteur de l'image
     * @return La hauteur de l'image.
     */
    virtual unsigned int getHeight() const = 0;
};

#endif // IMAGE_H
