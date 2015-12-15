#ifndef SVMTRAINING_H
#define SVMTRAINING_H
#include "training.h"
#include <dlib/svm_threaded.h>

typedef dlib::matrix<double, 13, 1> sample_type ;
typedef dlib::radial_basis_kernel< sample_type > kernel_type;
typedef dlib::decision_function<kernel_type> dec_funct_type;
typedef dlib::normalized_function<dec_funct_type> funct_type;

class SVMTraining : public Training
{
public:
    SVMTraining();
    SVMTraining operator=(const SVMTraining& other);
    virtual bool doTraining();
    virtual Eigen::Vector3i getClassif(Eigen::VectorXd vec) const;

private:
    std::vector<std::vector<sample_type> > _samples;
    std::vector<funct_type> _decFunc;
    bool _isTrain;
    std::vector< std::vector<double> > labels;

    /**
      @example svm_ex.cpp
      Ceci est un exemple de l'utilisation de l'entrainement à l'aide des SVM
      sur les données du satelitte sentinel2.
      */
};

#endif // SVMTRAINING_H
