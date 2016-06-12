#include "drg/MetFile.h"
#include "drg/ARCWorldFile.h"
extern "C"
{
#include "drgoracle/DRGSourceInfo.h"
}
#include <iostream.h>
#include <string.h>
#include <unistd.h>
#include <string>

int main(int argc, char **argv)
{
  MetFile mf;
  DRGSourceInfo srcInfo;
  char GetAwayFromMe[10000];
  ARCWorldFile awf;
  bool rtn1;
  int rtn2;
  int zoneEast, zoneNumber;
  char* name;
  char* awfname;
  char* metname;
  int i;
  bool found;
  int files;
  int tries;
  string* argument;

  // added to account for multiple datums comming out of the database 
  // BGM 24 Feb 1997
  int my_datum_year;

  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " <filename> ... " << endl;
    exit(-1);
  }

  if (argc == 2) // check for version switch
  {
    argument = new string(argv[1]);
    if (*argument == "-V")
    {
      cout << argv[0] << ": $Revision: 1.1.1.1 $" << endl;
      delete argument;
      exit(0);
    }
    delete argument;
  }

  tries = 1;
  rtn2 = OracleConnect();
  while ( (rtn2 != DRGSI_SUCCESS) && (tries < 4) )
  {
    rtn2 = OracleConnect();
    tries++;
  }
  if (rtn2 != DRGSI_SUCCESS)
  {
    cerr << "Can't connect to Oracle server.  Giving up." << endl;
    exit(69);
  }
  
  for (files=1; files < argc; files++)
  {
    name = new char[strlen(argv[files]) + 1];
    strcpy(name,argv[files]);
    i = 0;
    found = false;
    while ( (!found) && (i < strlen(argv[files])) )
    {
      if (name[i] == '.')
	found = true;
      else
	i++;
    }
    if (found)
      name[i] = (char) 0; 
      metname = new char[strlen(name) + 5];
      strcpy(metname,name);
      strcat(metname,".met");
      awfname = new char[strlen(name) + 5];
      strcpy(awfname,name);
      strcat(awfname,".tfw");
      rtn1 = awf.read(awfname);
      if (!rtn1)
      {
	cout << "Can't open file " << awfname << endl;
	exit(69);
      } 

      rtn2 = GetDRGSourceInfo(name, &srcInfo, CONTRACT);

      if (rtn2 == DRGSI_SUCCESS)
      {
	// This nice big statement maps the datum year into the value returned
	// from the Oracle stuff that Jeff set up.  Any further add ons should
        // be done here.  Note that for additional supported datums, you
	// should follow what I've done by just returning the number you get
	// from the database if it's not mapped into a 1927 or 1983 value.
	// In fact, this is what the software that uses the metfiles expects.
	// BGM 24 Feb 1997
	switch(srcInfo.datum_year)
	{
	case 1020:  // NULLDatum
	{
	  my_datum_year = 1927;
	  break;
	}
	case 1010:  // NoDatum
	{
	  my_datum_year = 1927;
	  break;
	}
	case 1018:  // NAD27Predicted83Datum
	{
	  my_datum_year = 1927;
	  break;
	}
	case 1019:  // NAD27Adjusted83Datum
	{
	  my_datum_year = 1927;
	  break;
	}
	case 1011:  // Old Hawaiian Datum
	{
	  my_datum_year = 1927;
	  break;
	}
	case 1001:  // Undetermined Datum
	{
	  my_datum_year = 1927;
	  break;
	}
	case 1007:  // North American Datum
	{
	  my_datum_year = 1927;
	  break;
	}
	case 1008:  // North American 1927 Datum
	{
	  my_datum_year = 1927;
	  break;
	}
	case 1016:  // North American 1983 Datum
	{
	  my_datum_year = 1983;
	  break;
	}
	default:
	{
	  cout << "Error:  Unsupported datum #" << srcInfo.datum_year;
	  cout << " returned for " << argv[files] << endl;
	  delete [] name;
	  delete [] awfname;
	  delete [] metname;
	  continue;
	}
	}
	
	mf.setNorthLat(srcInfo.north_latitude);
	mf.setSouthLat(srcInfo.south_latitude);
	mf.setWestLong(srcInfo.west_longitude);
	mf.setEastLong(srcInfo.east_longitude);
	zoneEast = ((int)((srcInfo.east_longitude-180)/6)) * 6 + 180;
	zoneNumber = (zoneEast+180)/6;
	mf.setUTMZone(zoneNumber);
	mf.setMapScale(srcInfo.scale);
	mf.setProductClass(srcInfo.product_class);
	if (srcInfo.product_id == 0)
	{
	  // If no product ID found for CONTRACT, retry as IN_HOUSE
	  rtn2 = GetDRGSourceInfo(name,&srcInfo,IN_HOUSE);
	  if (srcInfo.product_id == 0)  
	    cerr << name << ": Error...no product ID." << endl;
	}    
	mf.setProductID(srcInfo.product_id);     
	mf.setCellName(srcInfo.cell_name);
	mf.setULX(awf.getWorldCoordX(0,0));
	mf.setULY(awf.getWorldCoordY(0,0));
	mf.setXPixRes(awf.getPixelResolutionX());
	mf.setYPixRes(awf.getPixelResolutionY());
	mf.setdat_year(my_datum_year);
  //       cout << "X,Y pixres: " << awf.getPixelResolutionX() << " " << awf.getPixelResolutionY() << endl;
	mf.writeToFile(metname);
      }
      else if (rtn2 == DRGSI_APP_ERROR)
      {
	cerr << "Can't find " << name << " in the database." << endl;
      }
      else if (rtn2 == DRGSI_ORA_EXCEPTION)
      {
	cerr << "Got an Oracle exception on " << name << endl;
      }
      else if (rtn2 == DRGSI_ORA_ERROR)
      {
	cerr << "Got an Oracle error on " << name << endl;
      }
      else
      {
	cerr << "Got an unknown error on " << name << endl;
      } 
      
      delete[] name;
      delete[] awfname;
      delete[] metname;
  }
  OracleDisconnect();
}


