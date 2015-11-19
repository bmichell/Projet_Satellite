#include <iostream>
#include "imageout.h"
#include "imagetif.h"
#include "polygon.h"
#include "train.h"

using namespace std;

int main()
{
    ImageTIF venise;
    venise.OpenImage(("../../data/venise.tif"));
    cout << "Open Venise" << endl;
    Polygon Field, Water, Urban;
    Field.OpenImage("../../data/extractValues/Image-Field.txt");
    Water.OpenImage("../../data/extractValues/Image-Water.txt");
    Urban.OpenImage("../../data/extractValues/Image-Urban.txt");
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
    img.saveTIF("../../data/out/Venise.ppm");
    img.save("../../data/out/FirstLSE.ppm");
    return 0;
}

