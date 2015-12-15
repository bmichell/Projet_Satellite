/**
 * @file lsetraining.h
 * @brief Ce fichier contient la definition de la classe LSETraining qui permet de réaliser une classification aux moindres carrés à partir d'un jeu de données
 * d'entrainements, puis d'obtenir la classification de n'importe quel pixel.
 *
 * @author Benjamin MICHELLAND
 * @version 0.1
 * @date 12/11/2015
 */

#ifndef LSETRAINING_H
#define LSETRAINING_H
#include "training.h"

/**
  @class LSETraining
  @brief Classe correspond à la réalisation et l'application d'une classification basée sur la minimisation au moindre carrés (LDA).
  Cet entrainement est du type un contre un (One Vs. All).
  @date 19/11/2015
*/

class LSETraining : public Training
{
public:
    LSETraining();
    LSETraining operator=(const LSETraining& other);
    /**
     * Effectue l'entrainement LSE sur _polygons
     * @return true si l'entrainement à réussi, faux sinon.
     */
    virtual bool doTraining();
    /**
     * @return _normal : le tableau des normales calculées lors de l'entrainement
     */
    virtual std::vector<Eigen::VectorXd> getNormal() const {return _normal;}
    /**
     * Permet de récupérer une seul des normales calculées
     * @param[in]     ID : numéro de la normale que l'on veut récuérer
     * @return un vecteur contenant les trois composantes RGB du pixel considéré.
     */
    virtual Eigen::VectorXd getNormal(unsigned int ID) const {return _normal[ID];}
    /**
     * Renvoie la couleur (sous forme d'un vecteur Eigen) de la classification conrespondant à un pixel.
     * @param[in]     vec est le pixel dont on veut connaitre la classification.
     * @return la couleur de la classification.
     */
    virtual Eigen::Vector3i getClassif(Eigen::VectorXd vec) const;

private:
    //! @brief Tableau contenant les normales de la classification
    std::vector<Eigen::VectorXd> _normal;
    //! @brief Variable qui justifie de l'entrainement de la classe
    bool _isTrain;
};

/**
  @example lse_ex.cpp
  Ceci est un exemple de l'utilisation de l'entrainement à l'aide des moindres carrés
  sur les données du satelitte sentinel2.
  */

#endif // LSETRAINING_H
