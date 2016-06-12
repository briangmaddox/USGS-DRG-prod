#include <stdio.h>
#include <math.h>
#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include "drg/ARCWorldFile.h"

ARCWorldFile::ARCWorldFile(void)
{
  A = 0.0;
  B = 0.0;
  C = 0.0;
  D = 0.0;
  E = 0.0;
  F = 0.0;
}

bool ARCWorldFile::read(char* filename)
{
  FILE* infile;

  infile = fopen(filename,"r");
  if (infile == NULL)
    return false;
  
  fscanf(infile,"%lf",&A);
  fscanf(infile,"%lf",&D);
  fscanf(infile,"%lf",&B);
  fscanf(infile,"%lf",&E);
  fscanf(infile,"%lf",&C);
  fscanf(infile,"%lf",&F);

  fclose(infile);

  return true;
}

double ARCWorldFile::getPixelResolutionX(void)
{
  return A;
}

double ARCWorldFile::getPixelResolutionY(void)
{
  return fabs(E);
}

double ARCWorldFile::getWorldCoordX(int x, int y)
{
  return (A * x) + (B * y) + C;
}

double ARCWorldFile::getWorldCoordY(int x, int y)
{
  return (D * x) + (E * y) + F;
}

double ARCWorldFile::getTransX(void)
{
  return C;
}

double ARCWorldFile::getTransY(void)
{
  return F;
}

void ARCWorldFile::setTransX(double invalue)
{
  C = invalue;
  return;
}

void ARCWorldFile::setTransY(double invalue)
{
  F = invalue;
  return;
}

bool ARCWorldFile::write(char* filename)
{
  // Borrowed this from MetFile.cc and modified
  FILE* outfile;
  
  outfile = fopen(filename,"w");
  if (outfile == NULL)
    return false;
  
  fprintf(outfile, "%lf\n", A);
  fprintf(outfile, "%lf\n", D);
  fprintf(outfile, "%lf\n", B);
  fprintf(outfile, "%lf\n", E);
  fprintf(outfile, "%lf\n", C);
  fprintf(outfile, "%lf\n", F);
  fclose(outfile);
  return(true);
}
