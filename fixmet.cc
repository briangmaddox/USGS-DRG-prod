// $Id: fixmet.cc,v 1.1.1.1 2002-02-19 19:09:42 bmaddox Exp $
// $Revision: 1.1.1.1 $
// fixmet.cc
// Brian Maddox bmaddox@usgs.gov
// 29 November 1996
/*
  This program was created to fix a problem we had with some of the drg's.
  In some cases, the NAD year in the oracle database may be wrong (ie, it
  might say it's a NAD27 but really be done with NAD83 or what not).  If
  that's the case, then the validators will have to georef the image to the
  right projection method.  What this program does is to take in the datum
  year and the metadata file and will read in the data from the old met file,
  update it with the new data from the new ArcWorld file, and then append the
  new datum year to the end of the met file so that when tif2usgsdrg is run,
  the values in the drg will be correct. Note that some of this code is taken
  from makemet.cc itself.
  */

#include "drg/MetFile.h"
#include "drg/ARCWorldFile.h"
#include <iostream.h>
#include <string>
extern "C"
{
#include <stdlib.h>
}

int main(int argc, char* argv[])
{
  MetFile* inmeta;    // input metadata file
  ARCWorldFile* awf;  // ARCWorldFile handler
  string* metaname;   // Name of the metadata file
  string* arcname;    // Name of the arcworld file
  int datyear;        // Hold the inputted datum hear
  bool temp1, temp2;  // temporary boolean values for error checking
  string* argument;   // Hold command line argument (if any)

  if (argc == 2)
  {
    argument = new string(argv[1]);
    if (*argument == "-V")
    {
      cout << argv[0] << " $Revision: 1.1.1.1 $" << endl;
      delete argument;
      exit(0);
    }
    delete argument;
  }

  if (argc != 4) // User didn't input the correct number of inputs
  {
    cerr << "Incorrect usage:  Call with " << argv[0] << " datum-year metfile-name world-file-name" << endl;
    exit(-1);
  }

  datyear = atoi(argv[1]);
  metaname = new string(argv[2]);
  arcname = new string(argv[3]);

  inmeta = new MetFile;
  awf = new ARCWorldFile;
  temp1 = awf->read(const_cast<char*>(arcname->data()));
  if (!temp1)
  {
    cerr << "Error:  ArcWorld file " << arcname << " could not be opened." <<
      endl;
    cerr << "Exiting " << argv[0] << " ...." << endl;
    delete inmeta;
    delete metaname;
    delete awf;
    delete arcname;    
    exit(-1);
  }

  temp2 = inmeta->readFromFile(const_cast<char*>(metaname->data()));
  if (!temp2)
  {
    cerr << "Error:  Metafile " << metaname << " could not be opened." << endl;
    cerr << "Exiting " << argv[0] << " ..." << endl;
    delete inmeta;
    delete metaname;
    delete awf;
    delete arcname;
    exit(-1);
  }

  inmeta->setULX(awf->getWorldCoordX(0,0));
  inmeta->setULY(awf->getWorldCoordY(0,0));
  inmeta->setXPixRes(awf->getPixelResolutionX());
  inmeta->setYPixRes(awf->getPixelResolutionY());
  inmeta->setdat_year(datyear);
  inmeta->writeToFile(const_cast<char*>(metaname->data()));

  delete inmeta;
  delete metaname;
  delete awf;
  delete arcname;
  return(0);
}


