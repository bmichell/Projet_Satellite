#!/usr/bin/python

import numpy as np
import gdal, ogr
import argparse
parser = argparse.ArgumentParser(description="ce que fait le programme",formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument("--files", nargs='+',help="va contenir tous les arguments libres")
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


base_raster = gdal.Open("/home/benjamin/venise.tif")
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

for b in range(0,nbands):
    # on recupere les valeurs de chaque bande comme tableau numpy
    band_data = base_raster.GetRasterBand(b+1).ReadAsArray()

    # Il est ici possible de lire les pixels un par un
    for y in range(ny):
        for x in range(nx):
            # pour les pixels avec une classe definie
            if labels[y,x]!=0:
                # valeur de la bande pour ce pixel
                print band_data[y,x]
