#include "co_pdr.h"
/** 
 * Proview   $Id: co_dbs.pdr,v 1.26 2008-10-16 11:12:33 claes Exp $
 * Copyright (C) 2005 SSAB Oxel�sund AB.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 2 of 
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with the program, if not, write to the Free Software 
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 **/

#ifndef co_dbs_h
#define co_dbs_h

#ifdef __cplusplus
extern "C" {
#endif

/* co_dbs.h -- database snapshot files
   This file defines the data structures needed to create and read
   dbs data files.

   Note ! 
   The data sturctures has to be equally align on different platforms.
   To ensure this filler elements has to be inserted (the pdr compiler doesn't 
   accept __attribute__((aligned(())).
   For example 
   - 64 bit words has to be aligned on 8 byte boundary.
   - data structure containing a 64 bit word has to be aligned on 8 byte boundary. 
   - element after data structure containing 64 bit word has to be aligned on 8 byte boundary.
   Note that pwr_tTime is a data structure with 64 bit words.


    +====================================================+
    | File Information                                   |
    +----------------------------------------------------+
    |                                                    |
    | Information about the load file.                   |
    |                                                    |
    +====================================================+

    +====================================================+
    | Section Directory Section                          |
    +----------------------------------------------------+
    |                                                    |
    | This section contains the section headers of all   |
    | sections in the file, including its own. So using  |
    | the size of this section it is possible to deduce  |
    | the total number of sections in a specific load    |
    | file.                                              |
    |                                                    |
    +====================================================+
    | Volume Information Section                         |
    +----------------------------------------------------+
    |                                                    |
    | Information about the volume in this file.         |
    |                                                    |
    +====================================================+
    | Volume Reference Section                           |
    +----------------------------------------------------+
    |                                                    |
    | Information about class volumes containing classes |
    | and types used in this volume.                     |
    |                                                    |
    | Information about volumes mounted in this volume.  |
    |                                                    |
    +====================================================+
    | Oid (Object identity) Section                      |
    +----------------------------------------------------+
    |                                                    |
    |                                                    |
    +====================================================+
    | Object Section                                     |
    +----------------------------------------------------+
    |                                                    |
    |                                                    |
    +====================================================+
    | Runtime Body Section                               |
    +----------------------------------------------------+
    |                                                    |
    |                                                    |
    +====================================================+
    | Name Table Section                                 |
    +----------------------------------------------------+
    |                                                    |
    | Used to find an object by name.                    |
    |                                                    |
    +====================================================+
    | Class Reference Table                              |
    +----------------------------------------------------+
    |                                                    |
    |                                                    |
    +====================================================+
    | Development Body Section.                          |
    +----------------------------------------------------+
    |                                                    |
    |                                                    |
    +====================================================+
    | Fixup Section.                                     |
    +----------------------------------------------------+
    |                                                    |
    |                                                    |
    +====================================================+

*/

#if defined(OS_ELN)
# include stddef
#else
# include <stddef.h>
#endif

#include "co_pdr.h"


#define dbs_cMagicCookie 0x012a51fb
#define dbs_cVersionStr	"V3.4.0"



#if defined OS_VMS || defined OS_ELN

# define dbs_cNameBaseDirectory "pwr_load:"
# define dbs_cNameDirectory     "pwrp_load:"
# define dbs_cDirectory         "pwrp_load:"
# define dbs_cBaseDirectory     "pwr_load:"
# define dbs_cNamePlc           "%splc_%s_%04d_%05d.exe"

# define dbs_cNameBootList      "pwrp_root:[common.db]pwrp_cnf_bootlist.dat"
# define dbs_cNameVolumeList    "pwrp_root:[common.db]pwrp_cnf_volumelist.dat"
# define dbs_cNamePlcVersion    "pwrp_root:[common.db]pwrp_cnf_plcvers_%s.dat"
# define dbs_cNameDistribute    "pwrp_root:[common.db]pwrp_cnf_distribute.dat"
# define dbs_cNameSysObject     "pwrp_root:[common.db]pwrp_cnf_sysobject.dat"
# define dbs_cNameGblVolumeList "pwra_db:pwr_volumelist.dat"
# define dbs_cNameRttCrr        "rtt_crr_%03.3d_%03.3d_%03.3d_%03.3d.dat"
# define dbs_cNameRttCrrObj     "rtt_crro_%03.3d_%03.3d_%03.3d_%03.3d.dat"
# define dbs_cNameRttCrrCode    "rtt_crrc_%03.3d_%03.3d_%03.3d_%03.3d.dat"
# define dbs_cNameRttPlc        "rtt_plc_%03.3d_%03.3d_%03.3d_%03.3d.dat"

#elif defined OS_LYNX || defined OS_LINUX || defined OS_MACOS

# define dbs_cNameBaseDirectory "pwr_load"
# define dbs_cNameDirectory     "pwrp_load"
# define dbs_cDirectory         "$pwrp_load/"
# define dbs_cNamePlc           "%splc_%s_%04d_%05d"

# define dbs_cNameBootList      "$pwrp_root/common/db/pwrp_cnf_bootlist.dat"
# define dbs_cNameVolumeList    "$pwrp_root/common/db/pwrp_cnf_volumelist.dat"
# define dbs_cNamePlcVersion    "$pwrp_root/common/db/pwrp_cnf_plcvers_%s.dat"
# define dbs_cNameDistribute    "$pwrp_root/common/db/pwrp_cnf_distribute.dat"
# define dbs_cNameSysObject     "$pwrp_root/common/db/pwrp_cnf_sysobject.dat"
# define dbs_cNameGblVolumeList "$pwra_db/pwr_volumelist.dat"
# define dbs_cNameRttCrr        "rtt_crr_%03.3d_%03.3d_%03.3d_%03.3d.dat"
# define dbs_cNameRttCrrObj     "rtt_crro_%03.3d_%03.3d_%03.3d_%03.3d.dat"
# define dbs_cNameRttCrrCode    "rtt_crrc_%03.3d_%03.3d_%03.3d_%03.3d.dat"
# define dbs_cNameRttPlc        "rtt_plc_%03.3d_%03.3d_%03.3d_%03.3d.dat"

#endif

#define dbs_cNameVolume         "%s%s.dbs" /* <volume name>.dbs  */
#define dbs_cNameAlias          "%spwrp_alias.dat"
#define dbs_cNameAppl           "%sld_appl_%s_%d.txt"
#define dbs_cNameBoot           "%sld_boot_%s_%04d.dat"
#define dbs_cNameNode           "%sld_node_%s_%04d.dat"
#define dbs_cNameRc             "%sld_rc_%s_%04d.dat"

/**
 * A database load file is organised in sections.
 * There can be 32 sections (2^5) and each section can be 128 MB (2^27 bytes).
 */
#define dbs_cSectBits 5
#define dbs_cOffsBits 27

typedef pwr_tUInt32 dbs_tRef;
#define pdr_dbs_tRef(PDR, objp) pdr_pwr_tUInt32(PDR, (pwr_tBitMask *)objp)

#define dbs_cNref (dbs_tRef)0


/* All structs in a file will be aligned on even 8 bytes. */
#define dbs_cAlignInc 7
#define dbs_dAlign(size) (((size) + dbs_cAlignInc) & ~dbs_cAlignInc)
#define dbs_dPadding(size) ((((size) + dbs_cAlignInc) & ~dbs_cAlignInc) - (size))
#define dbs_dMakeRef(sect, offset) (0 | ((sect) << dbs_cOffsBits) | (offset))
#define dbs_cAlignPage 511
#define dbs_dAlignPage(size) (((size) + dbs_cAlignPage) & ~dbs_cAlignPage)

typedef union {
    struct {
        pwr_Endian_4(pwr_Bits(offs, dbs_cOffsBits),
                     pwr_Bits(sect, dbs_cSectBits),,)
    }        b;
    dbs_tRef m;
} dbs_uRefBits;

pwr_tBoolean
pdr_dbs_uRefBits(PDR *pdrs, dbs_uRefBits *objp);



struct dbs_sQlink {
	dbs_tRef self;
	dbs_tRef succ;
	dbs_tRef pred;
};
typedef struct dbs_sQlink dbs_sQlink;
pwr_tBoolean pdr_dbs_sQlink(PDR *pdrs, dbs_sQlink *objp);


enum dbs_eSect {
	dbs_eSect_dir = 0,
	dbs_eSect_volume = 1,
	dbs_eSect_volref = 2,
	dbs_eSect_oid = 3,
	dbs_eSect_object = 4,
	dbs_eSect_rbody = 5,
	dbs_eSect_name = 6,
	dbs_eSect_dbody = 8,
	dbs_eSect_class = 10,
	dbs_eSect_scobject = 13,
	dbs_eSect_fixup = 14,
	dbs_eSect_ = 14 + 1,
};
typedef enum dbs_eSect dbs_eSect;
pwr_tBoolean pdr_dbs_eSect(PDR *pdrs, dbs_eSect *objp);

#define dbs_mSect_volume   pwr_Bit(dbs_eSect_volume)
#define dbs_mSect_volref   pwr_Bit(dbs_eSect_volref)
#define dbs_mSect_oid      pwr_Bit(dbs_eSect_oid)
#define dbs_mSect_object   pwr_Bit(dbs_eSect_object)
#define dbs_mSect_rbody    pwr_Bit(dbs_eSect_rbody)
#define dbs_mSect_name     pwr_Bit(dbs_eSect_name)
#define dbs_mSect_class    pwr_Bit(dbs_eSect_class)
#define dbs_mSect_scobject pwr_Bit(dbs_eSect_scobject)
#define dbs_mSect_dbody    pwr_Bit(dbs_eSect_dbody)
#define dbs_mSect_fixup    pwr_Bit(dbs_eSect_fixup)


enum dbs_eFile {
	dbs_eFile__ = 0,
	dbs_eFile_volume = 1,
	dbs_eFile_ = 1 + 1,
};
typedef enum dbs_eFile dbs_eFile;
pwr_tBoolean pdr_dbs_eFile(PDR *pdrs, dbs_eFile *objp);


typedef union {
  pwr_tBitMask m;
  pwr_32Bits (
    pwr_Bits( isAliasClient , 1),
    pwr_Bits( isMountClient , 1),
    pwr_Bits( isMountClean  , 1),
    pwr_Bits( devOnly       , 1),
    pwr_Bits( readOnly      , 1),
    pwr_Bits( fill0         , 3),,,

    pwr_Bits( io            , 1),
    pwr_Bits( fill1         , 7),,,,,,,

    pwr_Bits( isArrayElem   , 1), /**< For sc only */
    pwr_Bits( hasSubClass   , 1),
    pwr_Bits( fill2         , 6),,,,,,

    pwr_Bits( fill3         , 8),,,,,,,
  ) b;

#define dbs_mFlags__             (0)
#define dbs_mFlags_isAliasClient pwr_Bit(0)
#define dbs_mFlags_isMountClient pwr_Bit(1)
#define dbs_mFlags_isMountClean  pwr_Bit(2)
#define dbs_mFlags_devOnly       pwr_Bit(3)

#define dbs_mFlags_io            pwr_Bit(8)

#define dbs_mFlags_isArrayElem   pwr_Bit(16)
#define dbs_mFlags_hasSubClass   pwr_Bit(17)

#define dbs_mFlags_isClient      (dbs_mFlags_isAliasClient|dbs_mFlags_isMountClient)
#define dbs_mFlags_              (~dbs_mFlags__)
} dbs_mFlags;

#define pdr_dbs_mFlags(PDR, objp) pdr_pwr_tBitMask(PDR, (pwr_tBitMask *)objp)

typedef union {
  pwr_tBitMask m;
  pwr_32Bits (
    pwr_Bits( devOnly       , 1),
    pwr_Bits( fill0         , 7),,,,,,,

    pwr_Bits( fill1         , 8),,,,,,,,
    pwr_Bits( fill2         , 8),,,,,,,,
    pwr_Bits( fill3         , 8),,,,,,,
  ) b;

#define dbs_mBody__             (0)
#define dbs_mBody_devOnly       pwr_Bit(0)

#define dbs_mBody_              (~dbs_mBody__)
} dbs_mBody;

#define pdr_dbs_mBody(PDR, objp) pdr_pwr_tBitMask(PDR, (pwr_tBitMask *)objp)

/* Nota Bene !!!
   The constant dbs_cVersionFormat reflects the version of the load file
   structure as a whole. It must be changed every time there is a change
   in any of the structures of this file.  */

#define dbs_cVersionFormat 3

/**
 * File Information Section.
 */

#define dbs_cVersionFile 2


struct dbs_sBintab {
	dbs_tRef start;
	dbs_tRef end;
	pwr_tUInt32 rsize;
};
typedef struct dbs_sBintab dbs_sBintab;
pwr_tBoolean pdr_dbs_sBintab(PDR *pdrs, dbs_sBintab *objp);

/**
 * @note You can't use pdr_dbs_sFile directly due to the format member.
 */

struct dbs_sFile {
	co_mFormat format;
	pwr_tUInt32 cookie;
	pwr_tUInt32 size;
	pwr_tUInt32 offset;
	pwr_tVersion formatVersion;
	pwr_tVersion version;
	pwr_tVersion sectVersion;
	pwr_tPwrVersion pwrVersion;
	pwr_tTime time;
	dbs_eFile fileType;
	pwr_tObjName userName;
	pwr_tString80 comment;
};
typedef struct dbs_sFile dbs_sFile;
pwr_tBoolean pdr_dbs_sFile(PDR *pdrs, dbs_sFile *objp);

/**
 * Directory section.
 */

#define dbs_cVersionDirectory  1


struct dbs_sSect {
	pwr_tVersion version;
	dbs_eSect type;
	pwr_tUInt32 size;
	pwr_tUInt32 offset;
};
typedef struct dbs_sSect dbs_sSect;
pwr_tBoolean pdr_dbs_sSect(PDR *pdrs, dbs_sSect *objp);

#define dbs_cVersionVolume 1

struct dbs_sVolume {
	pwr_tVid vid;
	pwr_tObjName name;
	pwr_tCid cid;
	pwr_tObjName className;
	pwr_tTime time;
	pwr_tUInt32 cardinality;
	pwr_tUInt32 rbodySize;
	dbs_sBintab name_bt;
	dbs_sBintab oid_bt;
	dbs_sBintab class_bt;
	pwr_tUInt32 dvVersion;
};
typedef struct dbs_sVolume dbs_sVolume;
pwr_tBoolean pdr_dbs_sVolume(PDR *pdrs, dbs_sVolume *objp);

#define dbs_cVersionVolRef 1

struct dbs_sVolRef {
	pwr_tVid vid;
	pwr_tObjName name;
	pwr_tCid cid;
	pwr_tTime time;
	pwr_tUInt32 size;
	pwr_tUInt32 offset;
};
typedef struct dbs_sVolRef dbs_sVolRef;
pwr_tBoolean pdr_dbs_sVolRef(PDR *pdrs, dbs_sVolRef *objp);

#define dbs_cVersionOid 1

struct dbs_sOid {
	pwr_tOid oid;
	dbs_tRef ref;
};
typedef struct dbs_sOid dbs_sOid;
pwr_tBoolean pdr_dbs_sOid(PDR *pdrs, dbs_sOid *objp);

#define dbs_cVersionObject 1

struct dbs_sBodyRef {
	pwr_tTime time;
	pwr_tUInt32 size;
	dbs_tRef ref;
};
typedef struct dbs_sBodyRef dbs_sBodyRef;
pwr_tBoolean pdr_dbs_sBodyRef(PDR *pdrs, dbs_sBodyRef *objp);


struct dbs_sOlink {
	pwr_tOix pred;
	pwr_tOix succ;
};
typedef struct dbs_sOlink dbs_sOlink;
pwr_tBoolean pdr_dbs_sOlink(PDR *pdrs, dbs_sOlink *objp);


struct dbs_sObject {
	pwr_tOid oid;
	pwr_tCid cid;
	pwr_tOid poid;
	pwr_tObjName name;
	pwr_tObjName normname;
	pwr_tUInt32 filler;
	pwr_tTime time;
	pwr_tOid soid;
	pwr_tOid boid;
	pwr_tOid aoid;
	pwr_tOid foid;
	pwr_tOid loid;
	pwr_mClassDef ohFlags;
	dbs_mFlags flags;
	dbs_sBodyRef rbody;
	dbs_sBodyRef dbody;
	dbs_tRef pref;
	dbs_sQlink sib_lh;
	dbs_sQlink sib_ll;
	dbs_sQlink o_ll;
	dbs_sBintab name_bt;
};
typedef struct dbs_sObject dbs_sObject;
pwr_tBoolean pdr_dbs_sObject(PDR *pdrs, dbs_sObject *objp);

#define dbs_cVersionClass 1

struct dbs_sClass {
	pwr_tCid cid;
	pwr_tUInt32 nObjects;
	dbs_sQlink o_lh;
};
typedef struct dbs_sClass dbs_sClass;
pwr_tBoolean pdr_dbs_sClass(PDR *pdrs, dbs_sClass *objp);

#define dbs_cVersionRbody 1
#define dbs_cVersionDbody 1

struct dbs_sBody {
	pwr_tOid oid;
	pwr_tUInt32 size;
	dbs_mBody flags;
};
typedef struct dbs_sBody dbs_sBody;
pwr_tBoolean pdr_dbs_sBody(PDR *pdrs, dbs_sBody *objp);

#define dbs_cVersionName 1

struct dbs_sName {
	pwr_tOix poix;
	pwr_tObjName normname;
	dbs_tRef ref;
};
typedef struct dbs_sName dbs_sName;
pwr_tBoolean pdr_dbs_sName(PDR *pdrs, dbs_sName *objp);

#define dbs_cVersionScObject 1

struct dbs_sScObject {
	pwr_tOid oid;
	pwr_tCid cid;
	pwr_tOid poid;
	pwr_tUInt32 offset;
	pwr_tUInt32 size;
	dbs_mFlags flags;
	pwr_tUInt32 aidx;
	pwr_tUInt32 elem;
};
typedef struct dbs_sScObject dbs_sScObject;
pwr_tBoolean pdr_dbs_sScObject(PDR *pdrs, dbs_sScObject *objp);

#define dbs_cVersionFixup 1


typedef union {
  pwr_tBitMask m;
  pwr_32Bits (
      pwr_Bits( isMapped    , 1),
      pwr_Bits( fill0       , 7),,,,,,,

      pwr_Bits( fill1       , 8),,,,,,,,
      pwr_Bits( fill2       , 8),,,,,,,,
      pwr_Bits( fill3       , 8),,,,,,,
  ) b;

#define dbs_mEnv__           (0)
#define dbs_mEnv_isMapped    pwr_Bit(0)

#define dbs_mEnv_            (~dbs_mEnv__)
} dbs_mEnv;

typedef struct dbs_sMenv dbs_sMenv;
typedef struct {
    //dbs_sFileEnv *fp;
    FILE         *f;
    dbs_sFile    file;
    pwr_tUInt32  nSect;
    dbs_sSect    *sect;
    
    /* the rest is used only if mapped */
    pwr_tUInt32  size;    /**< size of mapped file */
    char         *base;
    //dbs_sVolume  *vp;
    //dbs_sBintab  *name_bt;        /**< search for object with parent and name  */
    //dbs_sBintab  *oid_bt;         /**< search for object with identity  */
    //dbs_sBintab  *class_bt;       /**< search for object with class  */
} dbs_sEnv;

typedef struct {
    dbs_sMenv    *mp;
    pwr_tUInt32  index;
    pwr_tUInt32  nSect;
    dbs_sSect    *sect;
    
    /* the rest is used only if mapped */
    pwr_tUInt32  size;    /**< size of mapped file */
    char         *base;
    dbs_sVolume  *vp;
    dbs_sBintab  *name_bt;        /**< search for object with parent and name  */
    dbs_sBintab  *oid_bt;         /**< search for object with identity  */
    dbs_sBintab  *class_bt;       /**< search for object with class  */
} dbs_sVenv;

struct dbs_sMenv {
    FILE         *f;
    dbs_sFile    file;
    dbs_mEnv     flags;
    pwr_tUInt32  nVolRef;
    
    /* the rest is used only if mapped */
    pwr_tUInt32  size;    /**< size of mapped file */
    char         *base;
    dbs_sVolRef  *vrp;
    dbs_sVenv     venv[1];
};


#define dbs_Qitem(a, b, c) ((b *)((char *)a - offsetof(b, c)))
#define dbs_Qlink(a, b, c) ((dbs_sQlink *)((char *)a + offsetof(b, c)))

pwr_tBoolean    dbs_AlignedRead(pwr_tStatus *sts, void *buf, pwr_tUInt32 size, const dbs_sEnv *ep);
pwr_tBoolean    dbs_Close(pwr_tStatus *sts, dbs_sEnv *ep);
dbs_sEnv       *dbs_Open(pwr_tStatus *sts, dbs_sEnv *ep, const char *filename);
#if defined(OS_LINUX) || defined(OS_LYNX) || defined(OS_MACOS)
dbs_sVolRef    *dbs_VolRef(pwr_tStatus *sts, pwr_tUInt32 index, dbs_sVolRef *vp, const dbs_sEnv *ep);
dbs_sVolume 	*dbs_Volume(pwr_tStatus *sts, dbs_sVolume *vp, const dbs_sEnv *ep);
void           *dbs_Address(pwr_tStatus*, const dbs_sVenv*, dbs_tRef);
void            dbs_Dump(pwr_tStatus*, const dbs_sEnv*);
dbs_tRef        dbs_InDbs(pwr_tStatus*, const dbs_sEnv*, void*, pwr_tUInt32);
dbs_tRef        dbs_ItemReference(pwr_tStatus*, const dbs_sEnv*, void*);
pwr_tBoolean    dbs_QhasOne(pwr_tStatus*, const dbs_sVenv*, dbs_sQlink*);
dbs_tRef        dbs_Qinit(pwr_tStatus*, dbs_sQlink*, dbs_tRef);
dbs_sQlink     *dbs_Qinsert(pwr_tStatus*, dbs_sQlink*, dbs_sQlink*, dbs_sQlink*);
pwr_tBoolean    dbs_QisEmpty(pwr_tStatus*, const dbs_sVenv*, dbs_sQlink*);
pwr_tBoolean    dbs_QisLinked(pwr_tStatus*, const dbs_sVenv*, dbs_sQlink*);
pwr_tBoolean    dbs_QisNull(pwr_tStatus*, const dbs_sVenv*, dbs_sQlink*);
dbs_sQlink     *dbs_Qpred(pwr_tStatus*, const dbs_sVenv*, dbs_sQlink*);
dbs_sQlink     *dbs_Qsucc(pwr_tStatus*, const dbs_sVenv*, dbs_sQlink*);
dbs_tRef        dbs_Reference(pwr_tStatus*, const dbs_sVenv*, void*);

dbs_sMenv       *dbs_Map(pwr_tStatus*, const char*);
dbs_sVenv       *dbs_Vmap(pwr_tStatus*, int index, dbs_sMenv *);
void            dbs_Split(pwr_tStatus *sts, dbs_sMenv *mep, char *dirName);
pwr_tBoolean    dbs_Unmap(pwr_tStatus *sts, dbs_sMenv *);
int             dbs_nVolRef(pwr_tStatus *sts, const dbs_sMenv *mep);

dbs_sObject    *dbs_OidToObject(pwr_tStatus *sts, const dbs_sVenv *vep, pwr_tOid oid);
dbs_sObject    *dbs_NameToObject(pwr_tStatus *sts, const dbs_sVenv *vep, pwr_tOid oid, char *name);
dbs_sObject    *dbs_Parent(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op);
dbs_sObject    *dbs_After(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op);
dbs_sObject    *dbs_Before(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op);
dbs_sObject    *dbs_First(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op);
dbs_sObject    *dbs_Last(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op);
dbs_sObject    *dbs_ClassToObject(pwr_tStatus *sts, const dbs_sVenv *vep, pwr_tCid cid);
dbs_sObject    *dbs_Next(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op);
dbs_sObject    *dbs_Previous(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op);
dbs_sObject    *dbs_Child(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op, char *name);
dbs_sObject    *dbs_Ancestor(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op);
void            dbs_GetVolumeName(pwr_tStatus *sts, dbs_sVenv *vep, char *name);
dbs_sObject    *dbs_VolumeObject(pwr_tStatus *sts, const dbs_sVenv *vep);
dbs_sObject    *dbs_Object(pwr_tStatus *sts, const dbs_sVenv *vep);
void            dbs_ObjectToName(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op, char *name);
void           *dbs_Body(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op, pwr_eBix bix);
dbs_sObject    *dbs_NextHead(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sObject *op);
dbs_sBody      *dbs_NextRbody(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sBody *bp);
dbs_sBody      *dbs_NextDbody(pwr_tStatus *sts, const dbs_sVenv *vep, dbs_sBody *bp);
#endif

#ifdef __cplusplus
}
#endif

#endif