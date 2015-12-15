#include "svmtraining.h"
#include <Eigen/Eigen>
#include "omp.h"

using namespace Eigen;
using namespace dlib;
using namespace std;

SVMTraining::SVMTraining() : _samples(), _decFunc(), _isTrain(false), labels()
{

}

bool SVMTraining::doTraining()
{
    unsigned int size = 0;
    _samples.resize(_polygons.size());
    labels.resize(_polygons.size());
    for(unsigned int i = 0; i < _polygons.size(); i++)
    {
        size += _polygons[i].size();
    }
    _decFunc.resize(_polygons.size());
    for(unsigned int j = 0; j < _polygons.size(); j++)
    {
        unsigned int iter = 0;
        labels[j].resize(size);
        for(unsigned int i = 0; i < _polygons.size(); i++)
        {
            for(unsigned int m = 0; m < _polygons[i].size(); m++)
            {
                if(i==j)
                {
                    labels[j][iter] = 1.0;
                    sample_type matrice = mat(_polygons[i].getVector(m));
                    _samples[j].push_back(matrice);
                }
                else
                {
                    labels[j][iter] = -1.0;
                    sample_type matrice = mat(_polygons[i].getVector(m));
                    _samples[j].push_back(matrice);
                }
                iter++;
            }
        }
        svm_c_trainer<kernel_type> trainer;
        vector_normalizer< sample_type > normalizer;
        normalizer.train(_samples[j]);
        for (unsigned long i = 0; i < _samples[j].size(); ++i)
            _samples[j][i] = normalizer(_samples[j][i]);
        randomize_samples(_samples[j], labels[j]);
        if(j==0)
        {
            trainer.set_kernel(kernel_type(0.1));
            trainer.set_c(10);
        }
        else if(j==1)
        {
            trainer.set_kernel(kernel_type(1));
            trainer.set_c(100);
        }
        else if(j==2)
        {
            trainer.set_kernel(kernel_type(1));
            trainer.set_c(1000);
        }
        else
        {
            cout << "doing cross validation" << endl;
            for (double gamma = 0.01; gamma <= 100; gamma *= 10)
            {
                for (double C = .1; C <= 1000; C *= 10)
                {
                    // tell the trainer the parameters we want to use
                    trainer.set_kernel(kernel_type(gamma));
                    trainer.set_c(C);

                    cout << "gamma: " << gamma << "    C: " << C << endl;
                    cout << "     cross validation accuracy: "
                         << cross_validate_trainer(trainer, _samples[j], labels[j], 10) << endl;
                }
            }
            trainer.set_kernel(kernel_type(0.01));
            trainer.set_c(0.1);
        }
        funct_type learned_function;
        learned_function.normalizer = normalizer;
        learned_function.function = trainer.train(_samples[j], labels[j]);
        _decFunc[j].normalizer = normalizer;
        _decFunc[j].function = trainer.train(_samples[j], labels[j]);
        cout << "ok" << " " << j << endl;
    }
    return true;
}

Vector3i SVMTraining::getClassif(VectorXd vec) const
{
    sample_type v = mat(vec);
    std::vector<int> func(getNumberOfClass());
    for(unsigned int i=0; i  < getNumberOfClass(); i++)
    {
        if(_decFunc[i](v)>0)
        {
            func[i]++;
        }
        else
        {
            for(unsigned int j=0; j  < getNumberOfClass(); j++)
            {
                if(j!=i)
                {
                    func[j]++;
                }
            }
        }
    }
    int tmp = max_element(func.begin(), func.end()) - func.begin();
    return _polygons[tmp].getColor();
}
