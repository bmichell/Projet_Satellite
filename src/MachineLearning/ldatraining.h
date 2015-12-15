/**
 * @file ldatraining.h
 * @brief Ce fichier contient la definition de la classe LDATraining qui permet de réaliser une classification grace à la Linear Discriminant Analysis (LDA) à partir d'un jeu de données
 * d'entrainements, puis d'obtenir la classification de n'importe quel pixel.
 *
 * @author Benjamin MICHELLAND
 * @version 0.1
 * @date 12/11/2015
 */

#ifndef LDATRAINING_H
#define LDATRAINING_H
#include "training.h"

/**
  @class LDATraining
  @brief Classe correspond à la réalisation et l'application d'une classification basée sur le Linear Discriminant Analysis (LDA).
  Cet entrainement est du type un contre un (One Vs. One). Les données sont stockées de cette façon : 1vs2, ..., 1vsN, ..., (N-1)vsN.
  @date 24/11/2015
*/

class LDATraining : public Training
{
public:
    LDATraining();
    LDATraining operator=(const LDATraining& other);
    /**
     * Effectue l'entrainement LDA sur _polygons
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
    /**
     * @return _moy : le tableau des moyennes calculées lors de l'entrainement
     */
    virtual std::vector<Eigen::VectorXd> getMoy() const {return _moy;}

private:

    //! @brief Tableau contenant les normales de la classification
    std::vector<Eigen::VectorXd> _normal;
    //! @brief Tableau contenant les moyennes de la classification
    std::vector<Eigen::VectorXd> _moy;
    //! @brief Variable qui justifie de l'entrainement de la classe
    bool _isTrain;

    /**
      @example lda_ex.cpp
      Ceci est un exemple de l'utilisation de l'entrainement à l'aide de LDA
      sur les données du satelitte sentinel2.
      */
};

#endif // LDATRAINING_H
