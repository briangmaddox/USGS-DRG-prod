
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "drg/MetFile.h"

MetFile::MetFile(void)
{
  northLat     = 0.0; 
  southLat     = 0.0; 
  westLong     = 0.0; 
  eastLong     = 0.0; 
  UTMZone      = 0;
  mapScale     = 0.0;
  productClass = 0;
  productID    = 0;
  cellName     = NULL;
  ulx          = 0.0;
  uly          = 0.0;
  xPixRes      = 0.0;
  yPixRes      = 0.0;
  cYear        = 0;
  datYear      = 1927;
}

MetFile::~MetFile(void)
{
  if (cellName != NULL)
    delete[] cellName;
}

bool MetFile::writeToFile(char* filename)
{
  FILE* outfile;
  
  outfile = fopen(filename,"w");
  if (outfile == NULL)
    return false;

  fprintf(outfile,"%lf\n",northLat);
  fprintf(outfile,"%lf\n",southLat);
  fprintf(outfile,"%lf\n",westLong);
  fprintf(outfile,"%lf\n",eastLong);
  fprintf(outfile,"%d\n",UTMZone);
  fprintf(outfile,"%.0lf\n",mapScale);
  fprintf(outfile,"%d\n",productClass); 
  fprintf(outfile,"%d\n",productID); 
  if (cellName)
    fprintf(outfile,"%s\n",cellName);
  else 
    fprintf(outfile,"\n");
  fprintf(outfile,"%lf,%lf\n",ulx,uly);
  fprintf(outfile,"%lf\n",xPixRes);
  fprintf(outfile,"%lf\n",yPixRes);
  fprintf(outfile,"%d\n",cYear);
  fprintf(outfile,"%d\n",datYear);
  fclose(outfile);
  return true;
}

bool MetFile::readFromFile(char* filename)
{
  FILE* infile;
  char tmpbuf[1000];
  
  infile = fopen(filename,"r");
  if (infile == NULL)
    return false;
  
  fscanf(infile,"%lf",&northLat);
  fscanf(infile,"%lf",&southLat);
  fscanf(infile,"%lf",&westLong);
  fscanf(infile,"%lf",&eastLong);
  fscanf(infile,"%d",&UTMZone);
  fscanf(infile,"%lf",&mapScale);
  fscanf(infile,"%d",&productClass);
  fscanf(infile,"%d",&productID);

  fgets(tmpbuf,1000,infile);
  fgets(tmpbuf,1000,infile);
  tmpbuf[strlen(tmpbuf)-1] = '\0';
  cellName = new char[strlen(tmpbuf)+1];
  strcpy(cellName,tmpbuf);

  fscanf(infile,"%lf,%lf",&ulx,&uly);
  fscanf(infile,"%lf",&xPixRes);
  fscanf(infile,"%lf",&yPixRes);
  fscanf(infile,"%d",&cYear);
  if ( fscanf(infile,"%d",&datYear) == EOF )
    datYear = 1927;
  fclose(infile);
  
  return true;
}

bool MetFile::setNorthLat(double lat)
{
  northLat = lat;
  return true;
}

double MetFile::getNorthLat(void)
{
  return northLat;
}

bool MetFile::setSouthLat(double lat)
{
  southLat = lat;
  return true;
}
double MetFile::getSouthLat(void)
{
  return southLat;
}


bool MetFile::setWestLong(double lon)
{
  westLong = lon;
  return true;
}

double MetFile::getWestLong(void)
{
  return westLong;
}

bool MetFile::setEastLong(double lon)
{
  eastLong = lon;
  return true;
}

double MetFile::getEastLong(void)
{
  return eastLong;
}

bool MetFile::setUTMZone(int zone)
{
  UTMZone = zone;
  return true;
}

int MetFile::getUTMZone(void)
{
  return UTMZone;
}

bool MetFile::setMapScale(double scale)
{
  mapScale = scale;
  return true;
}

double MetFile::getMapScale(void)
{
  return mapScale;
}

bool MetFile::setProductClass(int pclass)
{
  productClass = pclass;
  return true;
}

int MetFile::getProductClass(void)
{
  return productClass;
}

bool MetFile::setProductID(int pid)
{
  productID = pid;
  return true;
}

int MetFile::getProductID(void)
{
  return productID;
}

bool MetFile::setCellName(const char* cname)
{
  if (cellName) delete[] cellName;
  cellName = new char[strlen(cname)+1];
  strcpy(cellName,cname);
  return true;
}

char* MetFile::getCellName(void)
{
  return cellName;
}

bool MetFile::setULX(double x)
{
  ulx = x;
  return true;
}

double MetFile::getULX(void)
{
  return ulx;
}

bool MetFile::setULY(double y)
{
  uly = y;
  return true;
}

double MetFile::getULY(void)
{
  return uly;
}

bool MetFile::setXPixRes(double res)
{
  xPixRes = res;
  return true;
}

double MetFile::getXPixRes(void)
{
  return xPixRes;
}

bool MetFile::setYPixRes(double res)
{
  yPixRes = res;
  return true;
}

double MetFile::getYPixRes(void)
{
  return yPixRes;
}

bool MetFile::setc_year(int year)
{
  cYear = year;
  return true;
}

int MetFile::getc_year(void)
{
  return cYear;
}


bool MetFile::setdat_year(int indat)
{
  datYear = indat;
  return true;
}

int MetFile::getdat_year()
{
  return datYear;
}
