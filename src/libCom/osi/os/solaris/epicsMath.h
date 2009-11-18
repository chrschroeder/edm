/*************************************************************************\
* Copyright (c) 2008 UChicago Argonne, LLC as Operator of Argonne
*     National Laboratory.
* EPICS BASE is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
\*************************************************************************/
#ifndef INC_epicsMath_H
#define INC_epicsMath_H

#include <math.h>

#include <ieeefp.h>

#ifndef isinf
#  define isinf(x) (((x)==(x)) && !finite((x)))
/* same as (!isnan(x) && !finite(x)) */
#endif

#endif /* INC_epicsMath_H */