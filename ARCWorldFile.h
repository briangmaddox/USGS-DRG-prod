#ifndef ARCWORLDFILE_H
#define ARCWORLDFILE_H


class ARCWorldFile
{
  // This class serves as a wrapper around an ARC/INFO style "world" file.  

/*

An ARC style world file has six lines.  The ARC manual
defines them as transformation parameters for a siz parameter affine
transformation and defines the fields as A-F.  

x1 = Ax + By + C
y1 = Dx + Ey + F

where:
   x1 = calculated x-coordinate of the pixel on the map
   y1 = calculated y-coordinate of the pixel on the map
   x  = column number of a pixel in the image
   y  = row number of a pixel in the image
   A  = x-scale; dimension of a pixel in map units in x direction 
   B,D = rotation terms
   E = negative if y-scale; dimension of a pixel in map units in y direction
      ( The y-scale is negative because the origins of an image and a 
        geographic coordinate system are different.  The origin is located
        in the upper left corner of an image, whereas the origin of the map
        coordinate system is located in the lower left corner.  Row values in
        the image increase from the origin downward, while y-coordinate values
        in the map increase from the origin upward)
   C,F = translation terms; x,y map coordinates of the center of the upper left
         pixel

*/

private:

protected:
  double A,B,C,D,E,F;

public:

  ARCWorldFile(void);
  bool read(char* filename);

  double getPixelResolutionX(void);
  double getPixelResolutionY(void);
      
  double getWorldCoordX(int x, int y);
  // Returns the x component of the World Coordinate pair 
  // corresponding to the center of image pixel (x,y);

  double getWorldCoordY(int x, int y);
  // Returns the y component of the World Coordinate pair
  // corresponding to the center of image pixel (x,y);
  
  // The following were added to allow replacing the UTM values in the tfws
  // BGM 

  double getTransX(void);
  // Returns the X translation value (which is in UTM coordinates)

  double getTransY(void);
  // Returns the Y translation value (UTM coordinates)
  
  void setTransX(double invalue);
  // Sets the Translation X value in the world file

  void setTransY(double invalue);
  // Sets the translation Y value in the world file

  bool write(char* filename);
  // Writes the world file out
};

#endif // ARCWORLDFILE_H
