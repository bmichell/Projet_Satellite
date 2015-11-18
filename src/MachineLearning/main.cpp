#include <iostream>
#include "imageout.h"
#include "imagetif.h"
#include "imagetraining.h"
#include "train.h"

using namespace std;

int main()
{
    ImageTIF venise;
    venise.OpenImage(("../../data/venise.tif"));
    cout << "Open Venise" << endl;
    ImageTraining Field, Water, Urban;
    Field.OpenImage("../../data/extractValues/polygones-Field.txt");
    Water.OpenImage("../../data/extractValues/polygones-Water.txt");
    Urban.OpenImage("../../data/extractValues/polygones-Urban.txt");
    cout << "Open Polygons" << endl;
    Train triClass;
    triClass.addImage(Urban);
    triClass.addImage(Field);
    triClass.addImage(Water);
    cout << "Add Polygons" << endl;
    triClass.doTraining();
    ImageOut img;
    img.setTIF(&venise);
    cout << "Set TIF" << endl;
    img.setTraining(&triClass);
    cout << "Set Training" << endl;
    img.save("../../data/out/FirstLSE.ppm");
    return 0;
}

