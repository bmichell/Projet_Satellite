#!/usr/bin/python

import numpy as np
import gdal, ogr
import argparse
from os import path

parser = argparse.ArgumentParser(description="ce que fait le programme",formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument("--files", nargs='+',help="va contenir tous les arguments libres")
parser.add_argument("--inputfile",help="raster")
parser.add_argument("--output",help="fichier d'enregistrement")
args = parser.parse_args()


def new_raster_from_base(base, outputURI, format, nodata, filldata, nbands, datatype):
    cols = base.RasterXSize
    rows = base.RasterYSize
    projection = base.GetProjection()
    geotransform = base.GetGeoTransform()
    bands = base.RasterCount
    driver = gdal.GetDriverByName(format)
    new_raster = driver.Create(str(outputURI), cols, rows, nbands, datatype)
    new_raster.SetProjection(projection)
    new_raster.SetGeoTransform(geotransform)
    for b in xrange(1,nbands+1):
        new_raster.GetRasterBand(b).SetNoDataValue(nodata)
        new_raster.GetRasterBand(b).Fill(filldata)
    return new_raster


base_raster = gdal.Open(args.inputfile)
labels_raster = new_raster_from_base(base_raster, "labels.tif", "GTiff", -1, 0, 1, gdal.GDT_Float64)
for a in xrange(len(args.files)):
    print args.files[a]
    shape_datasource = ogr.Open(args.files[a])
    shape_layer = shape_datasource.GetLayer()
    gdal.RasterizeLayer(labels_raster, [1], shape_layer, burn_values=[a+1])

    labels = labels_raster.GetRasterBand(1).ReadAsArray()

    nbands = base_raster.RasterCount;
    ny = labels.shape[0]
    nx = labels.shape[1]

    out = open(args.output + "-" + path.splitext(path.basename(args.files[a]))[0] + ".txt" ,'w')
    out.write('                                                                                                                                                                                                                               \n')
    i = []
    for b in range(0,nbands):
        i += [0]
        # on recupere les valeurs de chaque bande comme tableau numpy
        band_data = base_raster.GetRasterBand(b+1).ReadAsArray()
        # Il est ici possible de lire les pixels un par un
        for y in range(ny):
            isValue = False
            for x in range(nx):
                # pour les pixels avec une classe definie
                if labels[y,x]!=0:
                   # valeur de la bande pour ce pixel
                   out.write(str(band_data[y,x]) + " ")
                   i[b]+=1
                   isValue = True
            if isValue :
                out.write('\n ')
    out.seek(0,0)
    out.write("b1 : " + str(i[0]) + "\tb2 :" + str(i[1])  + "\tb3 :" +str(i[2]) + "\tb4 :"+str(i[3]) + "\tb5 :"+str(i[4]) + "\tb6 :"+str(i[5]) + "\tb7 :"+str(i[6]) + "\tb8 :"+str(i[7]) + "\tb9 :"+str(i[8]) + "\tb10 :"+str(i[9]) + "\tb11 :"+str(i[10]) + "\tb12 :"+str(i[11]) + "\tb13 :"+str(i[12]) + "\tb14 :"+str(i[13]) + "\tb15 :"+str(i[14]) + "\tb16 :" + str(i[15]) +  "\tb17 :" + str(i[16]) )
    out.seek(-1,2)
