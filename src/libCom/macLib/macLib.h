/*************************************************************************\
* Copyright (c) 2007 UChicago Argonne LLC, as Operator of Argonne
*     National Laboratory.
* Copyright (c) 2002 The Regents of the University of California, as
*     Operator of Los Alamos National Laboratory.
* EPICS BASE is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
\*************************************************************************/
/* macLib.h,v 1.10.2.5 2008/03/31 19:30:17 anj Exp
 *
 * Definitions for macro substitution library (macLib)
 *
 * William Lupton, W. M. Keck Observatory
 */

#ifndef INCmacLibH
#define INCmacLibH

/*
 * EPICS include files needed by this file
 */
#include "ellLib.h"
#include "shareLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Maximum size of macro name or value string (simpler to make fixed)
 */
#define MAC_SIZE 256

/*
 * Macro substitution context. One of these contexts is allocated each time
 * macCreateHandle() is called
 */
typedef struct {
    long        magic;          /* magic number (used for authentication) */
    int         dirty;          /* values need expanding from raw values? */
    int         level;          /* scoping level */
    int         debug;          /* debugging level */
    ELLLIST     list;           /* macro name / value list */
    int         flags;          /* operating mode flags */
} MAC_HANDLE;

/*
 * Function prototypes (core library)
 */
epicsShareFunc long             /* 0 = OK; <0 = ERROR */
epicsShareAPI macCreateHandle(
    MAC_HANDLE  **handle,       /* address of variable to receive pointer */
                                /* to new macro substitution context */

    char        *pairs[]        /* pointer to NULL-terminated array of */
                                /* {name,value} pair strings; a NULL */
                                /* value implies undefined; a NULL */
                                /* argument implies no macros */
);

epicsShareFunc void
epicsShareAPI macSuppressWarning(
    MAC_HANDLE  *handle,        /* opaque handle */

    int         falseTrue       /*0 means issue, 1 means suppress*/
);

epicsShareFunc long             /* #chars copied, <0 if any macros are */
                                /* undefined */
epicsShareAPI macExpandString(
    MAC_HANDLE  *handle,        /* opaque handle */

    const char  *src,           /* source string */

    char        *dest,          /* destination string */

    long        maxlen          /* maximum number of characters to copy */
                                /* to destination string */
);


epicsShareFunc long             /* length of value */
epicsShareAPI macPutValue(
    MAC_HANDLE  *handle,        /* opaque handle */

    const char  *name,          /* macro name */

    const char  *value          /* macro value */
);

epicsShareFunc long             /* #chars copied (<0 if undefined) */
epicsShareAPI macGetValue(
    MAC_HANDLE  *handle,        /* opaque handle */

    const char  *name,          /* macro name or reference */

    char        *value,         /* string to receive macro value or name */
                                /* argument if macro is undefined */

    long        maxlen          /* maximum number of characters to copy */
                                /* to value */
);

epicsShareFunc long             /* 0 = OK; <0 = ERROR */
epicsShareAPI macDeleteHandle(
    MAC_HANDLE  *handle         /* opaque handle */
);

epicsShareFunc long             /* 0 = OK; <0 = ERROR */
epicsShareAPI macPushScope(
    MAC_HANDLE  *handle         /* opaque handle */
);

epicsShareFunc long             /* 0 = OK; <0 = ERROR */
epicsShareAPI macPopScope(
    MAC_HANDLE  *handle         /* opaque handle */
);

epicsShareFunc long             /* 0 = OK; <0 = ERROR */
epicsShareAPI macReportMacros(
    MAC_HANDLE  *handle         /* opaque handle */
);

/*
 * Function prototypes (utility library)
 */
epicsShareFunc long             /* #defns encountered; <0 = ERROR */
epicsShareAPI macParseDefns(
    MAC_HANDLE  *handle,        /* opaque handle; can be NULL if default */
                                /* special characters are to be used */

    const char  *defns,         /* macro definitions in "a=xxx,b=yyy" */
                                /* format */

    char        **pairs[]       /* address of variable to receive pointer */
                                /* to NULL-terminated array of {name, */
                                /* value} pair strings; all storage is */
                                /* allocated contiguously */
);

epicsShareFunc long             /* #macros defined; <0 = ERROR */
epicsShareAPI macInstallMacros(
    MAC_HANDLE  *handle,        /* opaque handle */

    char        *pairs[]        /* pointer to NULL-terminated array of */
                                /* {name,value} pair strings; a NULL */
                                /* value implies undefined; a NULL */
                                /* argument implies no macros */
);

epicsShareFunc char *           /* expanded string; NULL if any undefined macros */
epicsShareAPI macEnvExpand(
    const char *str             /* string to be expanded */
);

#ifdef __cplusplus
}
#endif

#endif /*INCmacLibH*/