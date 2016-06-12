#ifndef DRGMETADATA_H
#define DRGMETADATA_H


class DRGMetaData
{
   // Encapsulates DRG Metadata. The data can be written to a file, or
   // (To Be Implemented) inserted into an Oracle database.

   private:

   protected:

      char* _mapname;
      char* _stateabbrev;
      char* _mapdate;
      char* _revdate;
      char* _imprintdate;
      char* _datagendate;
      double _mapscale;
      double _x,_y;

   public:

      DRGMetaData(void);
      ~DRGMetaData(void);

      bool writeToFile(char* filename);
         // Writes the eight line ascii metadata file as described
         // in the DRG statement of work (SOW).
      bool readFromFile(char* filename);
         // Reads the eight line ascii metadata file as described
         // in the DRG statement of work (SOW).


      bool setMapName(char* name);
      char* getMapName(void);
         // Map name on the first line of the map name block of the source
         // material. Capitaliztion shall be exactly as it appears
         // on the source.

      bool setStateAbbrevs(char* abbrevs);
      char* getStateAbbrevs(void);
         // List of the one or more state abbreviations that follow the 
         // map name from line 1. Abbreviations shall be in the U.S. Post
         // Office standard two letter capitalized form with 
         // abbreviations seperated by the comma character. The contractor
         // shall derive the U.S. Post Office standard abbreviation from the
         // abbreviation found on the source when necessary.

      bool setMapDate(char* date);
      char* getMapDate(void);
         // Map Date (lower right corner in black type as YYYY).

      bool setRevisionDate(char* revdate);
      char* getRevisionDate(void);
         // Most recent revision date (lower right corner as YYYY).

      bool setImprintDate(char* impdate);
      char* getImprintDate(void);
         // Map imprint date (lower right hand corner as YYYY).

      bool setDataGenerationDate(char* gendate);
      char* getDataGenerationDate(void);
         // Data Generation date (as YYYY/MM/DD).

      bool setMapScale(double denom);
      double getMapScale(void);
         // The denominator of the map scale fraction.

      bool setWorldCoords(double x, double y);
      void getWorldCoords(double& x, double& y);
         // World coordinates of the (1,1) pixel.

};

#endif // DRGMETADATA_H

