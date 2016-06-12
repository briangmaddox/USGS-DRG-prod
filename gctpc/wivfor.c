/*******************************************************************************
NAME                            WAGNER IV

PURPOSE:	Transforms input longitude and latitude to Easting and
		Northing for the Wagner IV projection.  The
		longitude and latitude must be in radians.  The Easting
		and Northing values will be returned in meters.

PROGRAMMER              DATE
----------              ----
D. Steinwand, EROS      May, 1991
J. Moyers, MCMC		July, 1995		Incorrect use of function
						'perror'. Changed to printf.

This function was implemented with formulas supplied by John P. Snyder.

ALGORITHM REFERENCES

1.  Snyder, John P. and Voxland, Philip M., "An Album of Map Projections",
    U.S. Geological Survey Professional Paper 1453 , United State Government
    Printing Office, Washington D.C., 1989.

2.  Snyder, John P., Personal correspondence, January 1991.
*******************************************************************************/
#include "cproj.h"

/* Variables common to all subroutines in this code file
  -----------------------------------------------------*/
static double lon_center;	/* Center longitude (projection center) */
static double R;		/* Radius of the earth (sphere) */
static double false_easting;	/* x offset				*/
static double false_northing;	/* y offset				*/

/* Initialize the Wagner IV projection
  ------------------------------------*/
wivforint(r, center_long,false_east,false_north) 
double r; 			/* (I) Radius of the earth (sphere) */
double center_long;		/* (I) Center longitude */
double false_east;		/* x offset				*/
double false_north;		/* y offset				*/
{
/* Place parameters in static storage for common use
  -------------------------------------------------*/
R = r;
lon_center = center_long;
false_easting = false_east;
false_northing = false_north;

/* Report parameters to the user
  -----------------------------*/
ptitle("WAGNER IV"); 
radius(r);
cenlon(center_long);
offsetp(false_east,false_north);
return(OK);
}

/* Wagner IV forward equations--mapping lat,long to x,y
  ----------------------------------------------------*/
wivfor(lon, lat, x, y)
double lon;			/* (I) Longitude */
double lat;			/* (I) Latitude */
double *x;			/* (O) X projection coordinate */
double *y;			/* (O) Y projection coordinate */
{
double adjust_lon();	/* Function to adjust longitude to -180 - 180 */
double delta_lon;	/* Delta longitude (Given longitude - center */
double theta;
double delta_theta;
double con;
long i;

/* Forward equations
  -----------------*/
delta_lon = adjust_lon(lon - lon_center);
theta = lat;
con = 2.9604205062 * sin(lat);

/* Iterate using the Newton-Raphson method to find theta
  -----------------------------------------------------*/
for (i=0;;i++)
   {
   delta_theta = -(theta + sin(theta) - con) / (1.0 + cos(theta));
   theta += delta_theta;
   if (fabs(delta_theta) < EPSLN) break;
   /* if (i >= 30) perror("Iteration failed to converge","wagneriv-forward"); */
   if (i >= 30) printf("Iteration failed to converge in wagneriv-forward");
   }
theta /= 2.0;
*x = 0.86310 * R * delta_lon * cos(theta) + false_easting;
*y = 1.56548 * R * sin(theta) + false_northing;
return(OK);
}
