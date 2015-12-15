/**
 * @file polygon.h
 * @brief Ce fichier contient la definition de la classe Polygon qui contient les données d'entrainement des classification.
 *
 * @author Benjamin MICHELLAND
 * @version 0.1
 * @date 12/11/2015
 */

#ifndef Polygon_H
#define Polygon_H
#include <fstream>
#include <vector>
#include <Eigen/Eigen>
#include "class.h"

class Polygon
{
public:
    Polygon();
    Polygon(std::string filename);
    Polygon(const Polygon& other);
    Polygon(const Class& cl);
    Polygon operator=(const Polygon& other);
    virtual ~Polygon() {}
    /**
     * Permet d'ouvrir une image, écrase toute image précédement ouverte.
     * @param[in]     filename : chemin vers l'image à ouvrir.
     * @return true si l'image à bien été ouverte, false sinon.
     */
    virtual bool OpenImage(std::string filename);
    virtual Eigen::VectorXd getVector(unsigned int index) const;
    virtual float getValue(unsigned int index, unsigned int band) const;
    virtual std::vector<Eigen::VectorXd> getData() const;
    virtual Eigen::Vector3i getColor() const;
    virtual Class getClass() const;
    virtual unsigned int size() const;
    virtual unsigned int getBandCount() const;

private:
    unsigned int _size;
    unsigned int _bandCount;
    std::vector<Eigen::VectorXd> _data;
    Class _class;
};

#endif // Polygon_H
