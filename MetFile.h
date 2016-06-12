#ifndef METFILE_H
#define METFILE_H


class MetFile
{
private:
  
  int    cYear;
  double northLat;
  double southLat;
  double westLong;
  double eastLong;
  int    UTMZone;
  double mapScale;
  int    productClass;
  char*  cellName; 
  double ulx;
  double uly;
  double xPixRes;
  double yPixRes;
  int    productID;
  int    datYear;

public:
  
  MetFile(void);
  ~MetFile(void);
  
  bool writeToFile(char*);

  bool readFromFile(char*);

  bool setNorthLat(double);
  double getNorthLat(void);
  bool setSouthLat(double);
  double getSouthLat(void);
  bool setWestLong(double);
  double getWestLong(void);
  bool setEastLong(double);
  double getEastLong(void);
  
  bool setUTMZone(int);
  int  getUTMZone(void);

  bool setMapScale(double);
  double getMapScale(void);

  bool setProductClass(int);
  int  getProductClass(void);
     
  bool setProductID(int);
  int  getProductID(void);
 
  bool setCellName(const char*);
  char* getCellName(void);           // user must free memory

  bool setULX(double);
  double getULX(void);
  bool setULY(double);
  double getULY(void);
  // World coordinates of the (0,0) pixel.
  
  bool setXPixRes(double);
  double getXPixRes(void);

  bool setYPixRes(double);
  double getYPixRes(void);

  bool setc_year(int);
  int  getc_year(void);

  /// added to output the datum year returned from the database
  //@{
  bool setdat_year(int);
  int getdat_year(void);
  //@}
};

#endif // DRGMETADATA_H

