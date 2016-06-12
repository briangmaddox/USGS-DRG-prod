#ifndef GCTPC_H
#define GCTPC_H

#include "gctpc/proj.h"

/* This didn't come with the original gctpc distribution. 
   But it *should* have. -- jamie 2/14/95 */

#ifdef __cplusplus
extern "C" {
#endif

void gctp(double* incoor, 
          long*   insys, 
          long*   inzone,
          double* inparm,
          long*   inunit,
          long*   indatum,
          long*   ipr,
          char*   efile,
          long*   jpr,
          char*   pfile,
          double* outcoor,
          long*   outsys,
          long*   outzone,
          double* outparm,
          long*   outunit,
          long*   outdatum,
          char*   fn27,
          char*   fn83,
          long*   iflg);

#ifdef __cplusplus
};
#endif

#endif  /* GCTPC_H */
