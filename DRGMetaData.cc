
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "drg/DRGMetaData.h"

DRGMetaData::DRGMetaData(void)
{
   _mapname = NULL;
   _stateabbrev = NULL;
   _mapdate = NULL;
   _revdate = NULL;
   _imprintdate = NULL;
   _datagendate = NULL;
   _mapscale = 0.0;
   _x = 0.0;
   _y = 0.0;
}

DRGMetaData::~DRGMetaData(void)
{
   if (_mapname)
      delete _mapname;

   if (_stateabbrev)
      delete _stateabbrev;

   if (_mapdate)
      delete _mapdate;

   if (_revdate)
      delete _revdate;

   if (_imprintdate)
      delete _imprintdate;

   if (_datagendate)
      delete _datagendate;
}

bool DRGMetaData::writeToFile(char* filename)
{
         // Writes the eight line ascii metadata file as described
         // in the DRG statement of work (SOW).

   FILE* outfile;

   outfile = fopen(filename,"w");
   if (outfile == NULL)
      return false;

   // if we have something to print, print it. Otherwise leave it blank.

   if (_mapname)
      fprintf(outfile,"%s\n",_mapname);
   else 
      fprintf(outfile,"\n");

   if (_stateabbrev)
      fprintf(outfile,"%s\n",_stateabbrev);
   else 
      fprintf(outfile,"\n");

   if (_mapdate)
      fprintf(outfile,"%s\n",_mapdate);
   else 
      fprintf(outfile,"\n");

   if (_revdate)
      fprintf(outfile,"%s\n",_revdate);
   else 
      fprintf(outfile,"\n");

   if (_imprintdate)
      fprintf(outfile,"%s\n",_imprintdate);
   else 
      fprintf(outfile,"\n");

   if (_datagendate)
      fprintf(outfile,"%s\n",_datagendate);
   else 
      fprintf(outfile,"\n");

   if (_mapscale)
      fprintf(outfile,"%.0lf\n",_mapscale);
   else 
      fprintf(outfile,"\n");

   fprintf(outfile,"%lf,%lf\n",_x,_y);

   fclose(outfile);
   return true;
}

bool DRGMetaData::readFromFile(char* filename)
{
   // Reads the eight line ascii metadata file as described
   // in the DRG statement of work (SOW).

   FILE* infile;
   char tmpbuf[1000];

   infile = fopen(filename,"r");
   if (infile == NULL)
      return false;

   fgets(tmpbuf,1000,infile);
   tmpbuf[strlen(tmpbuf)-1] = '\0';
   _mapname = new char[strlen(tmpbuf)+1];
   strcpy(_mapname,tmpbuf);

   fgets(tmpbuf,1000,infile);
   tmpbuf[strlen(tmpbuf)-1] = '\0';
   _stateabbrev = new char[strlen(tmpbuf)+1];
   strcpy(_stateabbrev,tmpbuf);

   fgets(tmpbuf,1000,infile);
   tmpbuf[strlen(tmpbuf)-1] = '\0';
   _mapdate = new char[strlen(tmpbuf)+1];
   strcpy(_mapdate,tmpbuf);

   fgets(tmpbuf,1000,infile);
   tmpbuf[strlen(tmpbuf)-1] = '\0';
   _revdate = new char[strlen(tmpbuf)+1];
   strcpy(_revdate,tmpbuf);

   fgets(tmpbuf,1000,infile);
   tmpbuf[strlen(tmpbuf)-1] = '\0';
   _imprintdate = new char[strlen(tmpbuf)+1];
   strcpy(_imprintdate,tmpbuf);

   fgets(tmpbuf,1000,infile);
   tmpbuf[strlen(tmpbuf)-1] = '\0';
   _datagendate = new char[strlen(tmpbuf)+1];
   strcpy(_datagendate,tmpbuf);

   fscanf(infile,"%lf",&_mapscale);
   fscanf(infile,"%lf,%lf",&_x,&_y);

   fclose(infile);

   return true;
}

bool DRGMetaData::setMapName(char* name)
{
   _mapname = new char[strlen(name)+1];
   strcpy(_mapname,name);
   return true;
}

char* DRGMetaData::getMapName(void)
{
   // Map name on the first line of the map name block of the source
   // material. Capitaliztion shall be exactly as it appears
   // on the source.
   
   return _mapname;
}

bool DRGMetaData::setStateAbbrevs(char* abbrevs)
{
   _stateabbrev = new char[strlen(abbrevs)+1];
   strcpy(_stateabbrev,abbrevs);
   return true;
}

char* DRGMetaData::getStateAbbrevs(void)
{
   // List of the one or more state abbreviations that follow the 
   // map name from line 1. Abbreviations shall be in the U.S. Post
   // Office standard two letter capitalized form with 
   // abbreviations seperated by the comma character. The contractor
   // shall derive the U.S. Post Office standard abbreviation from the
   // abbreviation found on the source when necessary.

   return _stateabbrev;
}

bool DRGMetaData::setMapDate(char* date)
{
   _mapdate = new char[strlen(date)+1];
   strcpy(_mapdate,date);
   return true;
}

char* DRGMetaData::getMapDate(void)
{
   // Map Date (lower right corner in black type as YYYY).

   return _mapdate;
}

bool DRGMetaData::setRevisionDate(char* revdate)
{
   _revdate = new char[strlen(revdate)+1];
   strcpy(_revdate,revdate);
   return true;
}

char* DRGMetaData::getRevisionDate(void)
{
   // Most recent revision date (lower right corner as YYYY).

   return _revdate;
}

bool DRGMetaData::setImprintDate(char* impdate)
{
   _imprintdate = new char[strlen(impdate)+1];
   strcpy(_imprintdate,impdate);
   return true;
}

char* DRGMetaData::getImprintDate(void)
{
   // Map imprint date (lower right hand corner as YYYY).

   return _imprintdate;
}

bool DRGMetaData::setDataGenerationDate(char* gendate)
{
   _datagendate = new char[strlen(gendate)+1];
   strcpy(_datagendate,gendate);
   return true;
}

char* DRGMetaData::getDataGenerationDate(void)
{
   // Data Generation date (as YYYY/MM/DD).

   return _datagendate;
}

bool DRGMetaData::setMapScale(double denom)
{
   _mapscale = denom;
   return true;
}

double DRGMetaData::getMapScale(void)
{
   // The denominator of the map scale fraction.
   return _mapscale;
}

bool DRGMetaData::setWorldCoords(double x, double y)
{
   _x = x;
   _y = y;
   return true;
}

void DRGMetaData::getWorldCoords(double& x, double& y)
{
   // World coordinates of the (1,1) pixel.

   x = _x;
   y = _y;
}
