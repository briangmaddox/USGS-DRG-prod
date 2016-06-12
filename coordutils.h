
#ifndef COORDUTILS_H
#define COORDUTILS_H

void dec2dms(double decdeg, double& degrees, double& minutes, double& seconds);

void utm2longlat(double utm_x, double utm_y, long utmzone,
                 char* datum, double* longitude, double* latitude);


#endif // COORDUTILS_H
