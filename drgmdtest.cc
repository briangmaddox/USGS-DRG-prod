#include <stdio.h>
#include "drg/DRGMetaData.h"

void main()
{
   DRGMetaData drgmd;
   double x,y;

   drgmd.readFromFile("m1.out");

   printf("Map Name: '%s'\n",drgmd.getMapName());
   printf("State Abbrevs: '%s'\n",drgmd.getStateAbbrevs());
   printf("Map Date: '%s'\n",drgmd.getMapDate());
   printf("Revision Date: '%s'\n",drgmd.getRevisionDate());
   printf("Imprint Date: '%s'\n",drgmd.getImprintDate());
   printf("Data Generation Date: '%s'\n",drgmd.getDataGenerationDate());
   printf("Map Scale: %lf\n",drgmd.getMapScale());
   drgmd.getWorldCoords(x,y);
   printf("UTM values of pixel (1,1): %lf,%lf\n",x,y);

   drgmd.setMapScale(24000.0);
   drgmd.setWorldCoords(123.0,456.0);

   drgmd.writeToFile("m2.out");

}
