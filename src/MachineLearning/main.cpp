#include <iostream>
#include "imageio.h"
#include "imageclassification.h"
#include "imagetif.h"
#include "polygon.h"
#include "lsetraining.h"
#include "ldatraining.h"
#include "svmtraining.h"

using namespace std;

int main()
{
    ImageTIF venise;
    cout << "Open Venise" << endl;
    venise.OpenImage(("../data/venise.tif"));
    Polygon Urban, Field, Water;
    cout << "Open Polygons" << endl;
    Field.OpenImage("../data/Entrainement/s5-Field.txt");
    Water.OpenImage("../data/Entrainement/s5-Water.txt");
    Urban.OpenImage("../data/Entrainement/s5-Urbain.txt");
    LDATraining triClass;
    cout << "Add Polygons" << endl;
    triClass.addImage(Urban);
    triClass.addImage(Field);
    triClass.addImage(Water);
    cout << "doing training" << endl;
    triClass.doTraining();
    vector<Polygon> poly(3);
    Urban.OpenImage("/home/benjamin.michelland/Projet_Satellite/src/Projet_Satelitte2/data/test/Image-Urban.txt");
    poly[0]=Urban;
    Field.OpenImage("/home/benjamin.michelland/Projet_Satellite/src/Projet_Satelitte2/data/test/Image-Field.txt");
    poly[1]=Field;
    Water.OpenImage("/home/benjamin.michelland/Projet_Satellite/src/Projet_Satelitte2/data/test/Image-Water.txt");
    poly[2]=Water;
    cout << triClass.confusionMatrix(poly) << endl << endl;
    return 0;
}
