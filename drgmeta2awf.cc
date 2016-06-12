
#include <stdio.h>
#include "drg/DRGMetaData.h"
#include "drg/usgsmaptypes.h"

void main(int argc, char** argv)
{
   // Converts a DRG metadata file to an Arc World File.

   DRGMetaData drgmd;
   double scale;
   double pixres;
   FILE* outfile;
   double x,y;

   if (argc != 3)
      {
         printf("%s <drgmetadatafile> <arcworldfile>\n",argv[0]);
         exit(1);
      }

   if (!drgmd.readFromFile(argv[1]))
      {
         printf("%s: Error reading file '%s'.\n",argv[0],argv[1]);
         exit(1);
      }

   scale = drgmd.getMapScale();
   if (scale == 24000)
      pixres = USGS24000RES;
   else if (scale == 63360)
      pixres = USGS63360RES;
   else if (scale == 100000)
      pixres = USGS100000RES;
   else if (scale == 250000)
      pixres = USGS250000RES;
   else if (scale == 1000000)
      pixres = 63.50;
   else
      {
         printf("Map scale %lf unsupported.\n",scale);
         exit(1);
      }

   outfile = fopen(argv[2],"w");
   if (outfile == NULL)
      {
         printf("%s: Unable to open '%s'\n",argv[2]);
         exit(1);
      }

   fprintf(outfile,"%lf\n",pixres);
   fprintf(outfile,"0\n0\n");
   fprintf(outfile,"%lf\n",-1.0 * pixres);
   drgmd.getWorldCoords(x,y);
   fprintf(outfile,"%lf\n%lf\n",x,y);

   fclose(outfile);

}