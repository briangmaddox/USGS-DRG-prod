#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/********************************/

/* Filename is entered in the format GYYXXXZZ.CSS */

/********************************/

int main()
{
void file_to_secorner(char *filename, double *se_lat, 
                      double *se_lon, char *scale);

char *filename;
double *se_latit, *se_long;
char *scale;

filename = (char *) malloc(20*sizeof(char));
scale = (char *) malloc(10*sizeof(char));
se_latit = (double *) malloc(sizeof(double));
se_long = (double *) malloc(sizeof(double));

printf("Please enter File Name  \n");
gets(filename);


file_to_secorner(filename, se_latit, se_long, scale);

printf("Filename = %s, SE LAT = %f, SE LON = %f, Scale = %s\n",
        filename, *se_latit, *se_long, scale); 

}


void file_to_secorner(filename, se_lat, se_lon, scale) 
                char *filename; double *se_lat; double *se_lon; char *scale;

{
        /* Declarations of the pieces of the file name */

  char *ret_string(int start, int end, char *in_string);

  char *G;	/* Specifies DRG 'G' */
  int  YY;	/* Latitude */

  char *yy;
  int  XXX;	/* Longitude */
  char *xxx;
  char *ZZ; 	/* Code for primary cell 01->64, 2 chars, 01,02 */ 
  int  zz; 
  char *C;	/* Code for geographic cell 'S','O','U' */
  char *SS;	/* Code for the scale '20','24','25','62','63','CK','QK'*/
  int ss;

  double degree_part; /* part of the degree to add on */

  G = (char *) malloc(strlen(filename)*sizeof(char));
  yy = (char *) malloc(strlen(filename)*sizeof(char));
  xxx = (char *) malloc(strlen(filename)*sizeof(char));
  ZZ = (char *) malloc(strlen(filename)*sizeof(char));
  C = (char *) malloc(strlen(filename)*sizeof(char));
  SS = (char *) malloc(strlen(filename)*sizeof(char));

  G = ret_string(0,0,filename);

  yy = ret_string(1,2,filename);
  YY = atoi(yy);
 
  xxx = ret_string(3,5,filename);
  XXX = atoi(xxx);

  ZZ = ret_string(6,7,filename);

  C = ret_string(9,9,filename);

  SS = ret_string(10,11,filename);

/* Set up the Scale for the switch statement */

  ss = 0;
  strcpy(scale," ");

  if (!strcmp(SS,"24")) 
   {
    ss = 1;
    strcpy(scale,"24K");
   }
  if (!strcmp(SS,"CK")) 
   {
    ss = 2;
    strcpy(scale,"100K");
   }

/* Determine which Scale is to be used to find the SE LAT and SE LONG */

 switch (ss) {
   case 0:  /* Error */
     printf("The filename extension is incorrect.\n");
     break;
   case 1:    /* SS = 24, If ZZ = 01 to 64  The 1:24,000-scale */
     zz = atoi(ZZ);
     *se_lat = (YY + 1) - ((floor((zz-1)/8))+1) * 0.125;
     *se_lon = (XXX + 0.875) - ((zz-1) % 8) * 0.125;
     break;
   case 2:   /* SS = CK, If ZZ = 01, 02  The 1:100,000-scale */
     zz = atoi(ZZ);
     *se_lat = (YY + 1) - (zz * 0.5); 
     *se_lon = XXX; 
     break;
 }

} 

char *ret_string(start, end, in_string) int start, end; char *in_string;
{
  int i;
  char *holder;
  int count;

  holder = (char *) malloc(strlen(in_string)*sizeof(char));
  count = 0;
  for(i=start; i<=end; i++)
  {
    holder[count] = in_string[i];
    count = count + 1;
  }
  holder[count] = '\0';
  
  return holder; 
}
