
void controlpointparams(int maptype, int& num_across, int& num_down, 
                        double& width, double& height);
   // For USGS maps at least, the control points are arranged in a 
   // rectangle. For example, the 1:24000 USGS topographic map has
   // 16 control points arranged in a square with 4 control points
   // "across" and 4 control points "down". The width and height of
   // the square are 0.125 degrees.
   // This function returns the width and height in decimal degrees
   // for each type of map, as well as the number of control points across
   // and down.

void calculate_groundcoords(int maptype, int utmzone, int datum, 
                            double selong, double selat,
                            double x[], double y[], int& numpoints);
   // Input:
   //
   //    maptype -- one of the defined constants USGS24000, USGS100000
   //    utmzone -- the utm zone.
   //    datum -- one of the defined constants DATUM_NAD27, DATUM_NAD83
   //    selong, selat -- longitude and latitude of southeast corner of map.
   //
   // Output:
   //    x[],y[] -- coordinates for generated control points. Each array is
   //               assumed to be large enough to hold all generated 
   //               control points.
   //    numpoints -- number of control points generated. 
