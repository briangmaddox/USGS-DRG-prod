
#include <stdlib.h>
#include <math.h>
#include "gctpc/gctpc.h"

void dec2dms(double decdeg, double& degrees, double& minutes, double& seconds)
{
   // Convert decimal degrees to degrees minutes and seconds.

   double t1,t2;
   double thesign;

   thesign = 1.0;
   if (decdeg < 0.0)
      thesign = -1.0;

   decdeg = fabs(decdeg);

   degrees = (int) decdeg;

   t1 = decdeg - degrees;
   t2 = t1 * 60;
   minutes = (int) t2;
   seconds = (t2 - minutes) * 60;

   degrees = degrees * thesign;

}

void utm2longlat(double utm_x, double utm_y, long utmzone, 
                 char* datum, double* longitude, double* latitude)
{

   double incoor[2];
   long insys;
   long inzone;
   double inparm[15];
   long inunit;
   long indatum;
   long ipr;
   char* efile;
   long jpr;
   char* pfile;
   double outcoor[2];
   long outsys;
   long outzone;
   double outparm[15];
   long outunit;
   long outdatum;
   char* fn27;
   char* fn83;
   long iflg;



   insys = UTM;
   inzone = utmzone;
   incoor[0] = utm_x;
   incoor[1] = utm_y;
   inunit = 2; // Meters
   if (strcmp(datum,"nad27") == 0)
      {
         indatum = 0;   // NAD27
         outdatum = 0;
      }
   else
      {
         indatum = 8;   // NAD83
         outdatum = 8;
      }
   ipr = 0;  // Error messages to terminal
   efile = NULL;
   jpr = -1; // Don't print projection parameters
   pfile = NULL;
   outsys = GEO;
   outzone = 0;
   outunit = 4; // Degrees of arc
   fn27 = NULL;
   fn83 = NULL;


   gctp(incoor,&insys,&inzone,inparm,&inunit,&indatum,&ipr,efile,
        &jpr,pfile,outcoor,&outsys,&outzone,outparm,&outunit,
        &outdatum,fn27,fn83,&iflg);

   *longitude = outcoor[0];
   *latitude  = outcoor[1];

}


