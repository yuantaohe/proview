/* 
 * Proview   Open Source Process Control.
 * Copyright (C) 2005-2014 SSAB EMEA AB.
 *
 * This file is part of Proview.
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
 * along with Proview. If not, see <http://www.gnu.org/licenses/>
 *
 * Linking Proview statically or dynamically with other modules is
 * making a combined work based on Proview. Thus, the terms and 
 * conditions of the GNU General Public License cover the whole 
 * combination.
 *
 * In addition, as a special exception, the copyright holders of
 * Proview give you permission to, from the build function in the
 * Proview Configurator, combine Proview with modules generated by the
 * Proview PLC Editor to a PLC program, regardless of the license
 * terms of these modules. You may copy and distribute the resulting
 * combined work under the terms of your choice, provided that every 
 * copy of the combined work is accompanied by a complete copy of 
 * the source code of Proview (the version used to produce the 
 * combined work), being distributed under the terms of the GNU 
 * General Public License plus this exception.
 */

#ifndef sev_dbhdf5_h
#define sev_dbhdf5_h
#if defined PWRE_CONF_HDF5

#include <vector>

#include "pwr.h"
#include "pwr_class.h"
#include "sev_db.h"
#include <hdf5.h>

using namespace std;

typedef struct {
  int items_alloc;
  int objectitems_alloc;
  int objectitemattr_alloc;
  int next_items_idx;
  int next_objectitems_idx;
  int next_objectitemattr_idx;
  int next_item_id;
  int dum[3];
} sev_sCmn;

typedef struct {
  unsigned int data_size;
  int data_type;
  int first_idx;
  int last_idx;
  unsigned first_time;
  unsigned last_time;
} sev_sHeader;

typedef struct {
  unsigned int time;
  unsigned int ntime;
  int eventtype;
  int eventprio;
  unsigned int eventid_nix;
  unsigned int eventid_birthtime;
  unsigned int eventid_idx;
  char eventtext[80];
  char eventname[80];
} sev_sEventDb;

typedef struct {
  float current_load;
  float medium_load;
  float storage_rate;
  float medium_storage_rate;
  unsigned int datastore_msg_cnt;
  unsigned int dataget_msg_cnt;
  unsigned int items_msg_cnt;
  unsigned int eventstore_msg_cnt;
} sev_sStatDb;

typedef enum {
  sev_eDataType_,
  sev_eDataType_Boolean,
  sev_eDataType_BooleanHt,
  sev_eDataType_BooleanDb,
  sev_eDataType_BooleanHtDb,
  sev_eDataType_Int8,
  sev_eDataType_Int8Ht,
  sev_eDataType_Int8Db,
  sev_eDataType_Int8HtDb,
  sev_eDataType_Int16,
  sev_eDataType_Int16Ht,
  sev_eDataType_Int16Db,
  sev_eDataType_Int16HtDb,
  sev_eDataType_Int32,
  sev_eDataType_Int32Ht,
  sev_eDataType_Int32Db,
  sev_eDataType_Int32HtDb,
  sev_eDataType_Int64,
  sev_eDataType_Int64Ht,
  sev_eDataType_Int64Db,
  sev_eDataType_Int64HtDb,
  sev_eDataType_UInt8,
  sev_eDataType_UInt8Ht,
  sev_eDataType_UInt8Db,
  sev_eDataType_UInt8HtDb,
  sev_eDataType_UInt16,
  sev_eDataType_UInt16Ht,
  sev_eDataType_UInt16Db,
  sev_eDataType_UInt16HtDb,
  sev_eDataType_UInt32,
  sev_eDataType_UInt32Ht,
  sev_eDataType_UInt32Db,
  sev_eDataType_UInt32HtDb,
  sev_eDataType_UInt64,
  sev_eDataType_UInt64Ht,
  sev_eDataType_UInt64Db,
  sev_eDataType_UInt64HtDb,
  sev_eDataType_Float32,
  sev_eDataType_Float32Ht,
  sev_eDataType_Float32Db,
  sev_eDataType_Float32HtDb,
  sev_eDataType_Float64,
  sev_eDataType_Float64Ht,
  sev_eDataType_Float64Db,
  sev_eDataType_Float64HtDb,
  sev_eDataType_Time,
  sev_eDataType_TimeHt,
  sev_eDataType_TimeDb,
  sev_eDataType_TimeHtDb,
  sev_eDataType_DeltaTime,
  sev_eDataType_DeltaTimeHt,
  sev_eDataType_DeltaTimeDb,
  sev_eDataType_DeltaTimeHtDb,
  sev_eDataType_String8,
  sev_eDataType_String8Ht,
  sev_eDataType_String8Db,
  sev_eDataType_String8HtDb,
  sev_eDataType_String16,
  sev_eDataType_String16Ht,
  sev_eDataType_String16Db,
  sev_eDataType_String16HtDb,
  sev_eDataType_String32,
  sev_eDataType_String32Ht,
  sev_eDataType_String32Db,
  sev_eDataType_String32HtDb,
  sev_eDataType_String40,
  sev_eDataType_String40Ht,
  sev_eDataType_String40Db,
  sev_eDataType_String40HtDb,
  sev_eDataType_String80,
  sev_eDataType_String80Ht,
  sev_eDataType_String80Db,
  sev_eDataType_String80HtDb,
  sev_eDataType_String132,
  sev_eDataType_String132Ht,
  sev_eDataType_String132Db,
  sev_eDataType_String132HtDb,
  sev_eDataType_String256,
  sev_eDataType_String256Ht,
  sev_eDataType_String256Db,
  sev_eDataType_String256HtDb,
  sev_eDataType__,
  sev_eDataType_Unknown = 10001
} sev_eDataType;

typedef struct {
  pwr_tUInt32 time;
} sev_sDataType_Any;

typedef struct {
  pwr_tUInt32 time;
  pwr_tBoolean value;
} sev_sDataType_Boolean;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tBoolean value;
} sev_sDataType_BooleanHt;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tBoolean value;
} sev_sDataType_BooleanDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tBoolean value;
} sev_sDataType_BooleanHtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tInt8 value;
} sev_sDataType_Int8;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tInt8 value;
} sev_sDataType_Int8Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tInt8 value;
} sev_sDataType_Int8Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tInt8 value;
} sev_sDataType_Int8HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tInt16 value;
} sev_sDataType_Int16;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tInt16 value;
} sev_sDataType_Int16Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tInt16 value;
} sev_sDataType_Int16Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tInt16 value;
} sev_sDataType_Int16HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tInt32 value;
} sev_sDataType_Int32;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tInt32 value;
} sev_sDataType_Int32Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tInt32 value;
} sev_sDataType_Int32Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tInt32 value;
} sev_sDataType_Int32HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tInt64 value;
} sev_sDataType_Int64;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tInt64 value;
} sev_sDataType_Int64Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tInt64 value;
} sev_sDataType_Int64Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tInt64 value;
} sev_sDataType_Int64HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt8 value;
} sev_sDataType_UInt8;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt8 value;
} sev_sDataType_UInt8Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tUInt8 value;
} sev_sDataType_UInt8Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tUInt8 value;
} sev_sDataType_UInt8HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt16 value;
} sev_sDataType_UInt16;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt16 value;
} sev_sDataType_UInt16Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tUInt16 value;
} sev_sDataType_UInt16Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tUInt16 value;
} sev_sDataType_UInt16HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 value;
} sev_sDataType_UInt32;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 value;
} sev_sDataType_UInt32Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tUInt32 value;
} sev_sDataType_UInt32Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tUInt32 value;
} sev_sDataType_UInt32HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt64 value;
} sev_sDataType_UInt64;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt64 value;
} sev_sDataType_UInt64Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tUInt64 value;
} sev_sDataType_UInt64Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tUInt64 value;
} sev_sDataType_UInt64HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tFloat32 value;
} sev_sDataType_Float32;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tFloat32 value;
} sev_sDataType_Float32Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tFloat32 value;
} sev_sDataType_Float32Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tFloat32 value;
} sev_sDataType_Float32HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tFloat64 value;
} sev_sDataType_Float64;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tFloat64 value;
} sev_sDataType_Float64Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tFloat64 value;
} sev_sDataType_Float64Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tFloat64 value;
} sev_sDataType_Float64HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 value;
} sev_sDataType_Time;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 value;
  pwr_tUInt32 nvalue;
} sev_sDataType_TimeHt;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tUInt32 value;
} sev_sDataType_TimeDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tUInt32 value;
  pwr_tUInt32 nvalue;
} sev_sDataType_TimeHtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tInt64 value;
} sev_sDataType_DeltaTime;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tInt64 value;
  pwr_tInt64 nvalue;
} sev_sDataType_DeltaTimeHt;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tInt64 value;
} sev_sDataType_DeltaTimeDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tInt64 value;
  pwr_tInt64 nvalue;
} sev_sDataType_DeltaTimeHtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tString8 value;
} sev_sDataType_String8;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tString8 value;
} sev_sDataType_String8Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tString8 value;
} sev_sDataType_String8Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tString8 value;
} sev_sDataType_String8HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tString16 value;
} sev_sDataType_String16;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tString16 value;
} sev_sDataType_String16Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tString16 value;
} sev_sDataType_String16Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tString16 value;
} sev_sDataType_String16HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tString32 value;
} sev_sDataType_String32;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tString32 value;
} sev_sDataType_String32Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tString32 value;
} sev_sDataType_String32Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tString32 value;
} sev_sDataType_String32HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tString40 value;
} sev_sDataType_String40;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tString40 value;
} sev_sDataType_String40Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tString40 value;
} sev_sDataType_String40Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tString40 value;
} sev_sDataType_String40HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tString80 value;
} sev_sDataType_String80;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tString80 value;
} sev_sDataType_String80Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tString80 value;
} sev_sDataType_String80Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tString80 value;
} sev_sDataType_String80HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tString132 value;
} sev_sDataType_String132;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tString132 value;
} sev_sDataType_String132Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tString132 value;
} sev_sDataType_String132Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tString132 value;
} sev_sDataType_String132HtDb;

typedef struct {
  pwr_tUInt32 time;
  pwr_tString256 value;
} sev_sDataType_String256;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tString256 value;
} sev_sDataType_String256Ht;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 jump;
  pwr_tString256 value;
} sev_sDataType_String256Db;

typedef struct {
  pwr_tUInt32 time;
  pwr_tUInt32 ntime;
  pwr_tUInt32 jump;
  pwr_tString256 value;
} sev_sDataType_String256HtDb;

typedef union {
  sev_sDataType_Any		dtAny;
  sev_sDataType_Boolean		dtBoolean;
  sev_sDataType_BooleanHt      	dtBooleanHt;
  sev_sDataType_BooleanDb      	dtBooleanDb;
  sev_sDataType_BooleanHtDb    	dtBooleanHtDb;
  sev_sDataType_Int8		dtInt8;
  sev_sDataType_Int8Ht		dtInt8Ht;
  sev_sDataType_Int8Db		dtInt8Db;
  sev_sDataType_Int8HtDb       	dtInt8HtDb;
  sev_sDataType_Int16		dtInt16;
  sev_sDataType_Int16Ht		dtInt16Ht;
  sev_sDataType_Int16Db		dtInt16Db;
  sev_sDataType_Int16HtDb      	dtInt16HtDb;
  sev_sDataType_Int32		dtInt32;
  sev_sDataType_Int32Ht		dtInt32Ht;
  sev_sDataType_Int32Db		dtInt32Db;
  sev_sDataType_Int32HtDb      	dtInt32HtDb;
  sev_sDataType_Int64		dtInt64;
  sev_sDataType_Int64Ht		dtInt64Ht;
  sev_sDataType_Int64Db		dtInt64Db;
  sev_sDataType_Int64HtDb      	dtInt64HtDb;
  sev_sDataType_UInt8		dtUInt8;
  sev_sDataType_UInt8Ht		dtUInt8Ht;
  sev_sDataType_UInt8Db		dtUInt8Db;
  sev_sDataType_UInt8HtDb      	dtUInt8HtDb;
  sev_sDataType_UInt16		dtUInt16;
  sev_sDataType_UInt16Ht       	dtUInt16Ht;
  sev_sDataType_UInt16Db       	dtUInt16Db;
  sev_sDataType_UInt16HtDb     	dtUInt16HtDb;
  sev_sDataType_UInt32		dtUInt32;
  sev_sDataType_UInt32Ht       	dtUInt32Ht;
  sev_sDataType_UInt32Db       	dtUInt32Db;
  sev_sDataType_UInt32HtDb     	dtUInt32HtDb;
  sev_sDataType_UInt64		dtUInt64;
  sev_sDataType_UInt64Ht       	dtUInt64Ht;
  sev_sDataType_UInt64Db       	dtUInt64Db;
  sev_sDataType_UInt64HtDb     	dtUInt64HtDb;
  sev_sDataType_Float32		dtFloat32;
  sev_sDataType_Float32Ht      	dtFloat32Ht;
  sev_sDataType_Float32Db      	dtFloat32Db;
  sev_sDataType_Float32HtDb    	dtFloat32HtDb;
  sev_sDataType_Float64		dtFloat64;
  sev_sDataType_Float64Ht      	dtFloat64Ht;
  sev_sDataType_Float64Db      	dtFloat64Db;
  sev_sDataType_Float64HtDb    	dtFloat64HtDb;
  sev_sDataType_Time		dtTime;
  sev_sDataType_TimeHt      	dtTimeHt;
  sev_sDataType_TimeDb      	dtTimeDb;
  sev_sDataType_TimeHtDb    	dtTimeHtDb;
  sev_sDataType_DeltaTime      	dtDeltaTime;
  sev_sDataType_DeltaTimeHt    	dtDeltaTimeHt;
  sev_sDataType_DeltaTimeDb    	dtDeltaTimeDb;
  sev_sDataType_DeltaTimeHtDb  	dtDeltaTimeHtDb;
  sev_sDataType_String8		dtString8;
  sev_sDataType_String8Ht      	dtString8Ht;
  sev_sDataType_String8Db      	dtString8Db;
  sev_sDataType_String8HtDb    	dtString8HtDb;
  sev_sDataType_String16       	dtString16;
  sev_sDataType_String16Ht     	dtString16Ht;
  sev_sDataType_String16Db     	dtString16Db;
  sev_sDataType_String16HtDb   	dtString16HtDb;
  sev_sDataType_String32       	dtString32;
  sev_sDataType_String32Ht     	dtString32Ht;
  sev_sDataType_String32Db     	dtString32Db;
  sev_sDataType_String32HtDb   	dtString32HtDb;
  sev_sDataType_String40       	dtString40;
  sev_sDataType_String40Ht     	dtString40Ht;
  sev_sDataType_String40Db     	dtString40Db;
  sev_sDataType_String40HtDb   	dtString40HtDb;
  sev_sDataType_String80       	dtString80;
  sev_sDataType_String80Ht     	dtString80Ht;
  sev_sDataType_String80Db     	dtString80Db;
  sev_sDataType_String80HtDb   	dtString80HtDb;
  sev_sDataType_String132      	dtString132;
  sev_sDataType_String132Ht    	dtString132Ht;
  sev_sDataType_String132Db    	dtString132Db;
  sev_sDataType_String132HtDb  	dtString132HtDb;
  sev_sDataType_String256      	dtString256;
  sev_sDataType_String256Ht    	dtString256Ht;
  sev_sDataType_String256Db    	dtString256Db;
  sev_sDataType_String256HtDb  	dtString256HtDb;
} sev_uDataType;

class sev_dbhdf5 : public sev_db {
 public:

  static const unsigned int constMaxColNameLength = 64;
  static const unsigned int m_cItemsInitSize = 50;
  static const unsigned int m_cItemsExtendSize = 50;

  hid_t m_file;
  hid_t m_item_mtype;
  hid_t m_objectitem_mtype;
  hid_t m_objectattributes_mtype;
  hid_t m_event_mtype;
  hid_t m_stat_mtype;
  hid_t m_header_mtype;
  hid_t m_value_mtype[sev_eDataType__];
  sev_sCmn m_cmn;

  sev_dbhdf5() { memset(&m_cmn,0,sizeof(m_cmn)); memset(m_value_mtype, 0, sizeof(m_value_mtype));}
  ~sev_dbhdf5();

  int open_db();
  int check_item( pwr_tStatus *sts, pwr_tOid oid, char *oname, char *aname, 
		  pwr_tDeltaTime storagetime, pwr_eType type, unsigned int size, 
		  char *description, char *unit, pwr_tFloat32 scantime, 
		  pwr_tFloat32 deadband, pwr_tMask options, unsigned int *idx);
  int add_item( pwr_tStatus *sts, pwr_tOid oid, char *oname, char *aname, 
		pwr_tDeltaTime storagetime, pwr_eType type, unsigned int size, 
		char *description, char *unit, pwr_tFloat32 scantime, 
		pwr_tFloat32 deadband, pwr_tMask options, unsigned int *idx);  
  int store_value( pwr_tStatus *sts, int item_idx, int attr_idx,
		   pwr_tTime time, void *buf, unsigned int size);
  int get_values( pwr_tStatus *sts, pwr_tOid oid, pwr_tMask options, float deadband, char *aname, 
		  pwr_eType type, unsigned int size, pwr_tFloat32 scantime, pwr_tTime *creatime,
		  pwr_tTime *starttime, 
		  pwr_tTime *endtime, int maxsize, pwr_tTime **tbuf, void **vbuf, unsigned int *bsize);
  int delete_old_data( pwr_tStatus *sts, char *tablename, 
		       pwr_tMask options, pwr_tTime limit, pwr_tFloat32 scantime, pwr_tFloat32 garbagecycle);
  int delete_item( pwr_tStatus *sts, pwr_tOid oid, char *aname);

  int get_items( pwr_tStatus *sts);
  int store_item( pwr_tStatus *sts, char *tabelname, pwr_tOid oid, char *oname, char *aname, 
		  pwr_tDeltaTime storagetime, pwr_eType vtype, unsigned int vsize, 
		  char *description, char *unit, pwr_tFloat32 scantime, 
		  pwr_tFloat32 deadband, pwr_tMask options, unsigned int *idx);
  int update_item( sev_item *item);
  int remove_item( pwr_tStatus *sts, pwr_tOid oid, char *aname);
  static sev_db *open_database();
  static char *oid_to_table( pwr_tOid oid, char *aname);
  int check_objectitem( pwr_tStatus *sts, char *tablename, pwr_tOid oid, char *oname, char *aname, 
			pwr_tDeltaTime storagetime,
			char *description, pwr_tFloat32 scantime, 
			pwr_tFloat32 deadband, pwr_tMask options, unsigned int attrnum,
			sev_sHistAttr *attr, unsigned int *idx);
  int add_objectitem( pwr_tStatus *sts, char *tablename, pwr_tOid oid, char *oname, char *aname, 
		      pwr_tDeltaTime storagetime, 
		      char *description, pwr_tFloat32 scantime, 
		      pwr_tFloat32 deadband, pwr_tMask options, unsigned int attrnum,
		      sev_sHistAttr *attr, unsigned int *idx);  
  int store_objectitem( pwr_tStatus *sts, char *tablename, pwr_tOid oid, char *oname, char *aname, 
			pwr_tDeltaTime storagetime, char *description, pwr_tFloat32 scantime, 
			pwr_tFloat32 deadband, pwr_tMask options, unsigned int attrnum,
			sev_sHistAttr *attr, unsigned int *idx);
  int create_objecttable( pwr_tStatus *sts, char *tablename, pwr_tMask options, float deadband, 
			  pwr_tDeltaTime storage_time, pwr_tFloat32 scantime, 
			  unsigned int attrnum, sev_sHistAttr *attr);
  int store_objectvalue( pwr_tStatus *sts, int item_idx, int attr_idx,
                             pwr_tTime time, void *buf,  void *oldbuf, unsigned int size);
  int get_item( pwr_tStatus *sts, sev_item *item, pwr_tOid oid, char *attributename);
  int get_item( pwr_tStatus *sts, unsigned int *idx, pwr_tOid oid, char *attributename);
  int get_objectitem( pwr_tStatus *sts, sev_item *item, pwr_tOid oid, char *attributename);
  int get_objectitems( pwr_tStatus *sts);
  int get_objectitemattributes( pwr_tStatus *sts, sev_item *item, char *tablename);
  int check_objectitemattr( pwr_tStatus *sts, char *tablename, pwr_tOid oid, char *aname, char *oname, 
			    pwr_eType type, unsigned int size, unsigned int *idx);
  int delete_old_objectdata( pwr_tStatus *sts, char *tablename, 
                             pwr_tMask options, pwr_tTime limit, pwr_tFloat32 scantime, pwr_tFloat32 garbagecycle);
  int check_deadband(pwr_eType type, unsigned int size, pwr_tFloat32 deadband, void *value, void *oldvalue);
  int get_objectvalues( pwr_tStatus *sts, sev_item *item, unsigned int size, pwr_tTime *starttime, pwr_tTime *endtime, 
			                  int maxsize, pwr_tTime **tbuf, void **vbuf, unsigned int *bsize);
  int delete_event_table( pwr_tStatus *sts, char *tablename);
  int create_event_table( pwr_tStatus *sts, char *tablename, pwr_tMask options, 

			  pwr_tDeltaTime storage_time, pwr_tFloat32 scantime);
  int store_event( pwr_tStatus *sts, int item_idx, sev_event *ep);
  int checkAndUpdateVersion(unsigned int version);
  int create_table( pwr_tStatus *sts, char *tablename, pwr_eType type, 
		    unsigned int size, pwr_tMask options, float deadband,
		    pwr_tDeltaTime storage_time, pwr_tFloat32 scantime);
  int delete_table( pwr_tStatus *sts, char *tablename);
  int handle_objectchange(pwr_tStatus *sts, char *tablename, unsigned int item_idx, bool newObject);
  int handle_itemchange(pwr_tStatus *sts, char *tablename, unsigned int item_idx);
  int store_stat( sev_sStat *stat);

  int create_db( char *dbname);
  int create_types();
  int read_cmn();
  int write_cmn();
  int items_extend();
  int objectitems_extend();
  int objectitemattr_extend();
  sev_eDataType get_datatype( pwr_eType type, pwr_tMask options, unsigned int size);
  int get_mdatatype( sev_eDataType type, unsigned int size, hid_t *mtype);
  int get_fdatatype( sev_eDataType type, unsigned int size, hid_t *ftype);
  void free_mdatatype();
  int time_to_idx( hid_t dataset_id, hid_t memspace_id, hid_t dataspace_id,
		   hid_t mtype, unsigned int stime, int size, int low_idx, int high_idx, unsigned int low_time,
		   unsigned int high_time, int resolution, unsigned int prev_time, int *iter, int *ridx);
  int get_time( hid_t dataset_id, hid_t memspace_id, hid_t dataspace_id, 
		hid_t mtype, int idx, unsigned int *time);
  int get_objectitem_datatype( int item_idx, hid_t *atype, unsigned int *size, int *value_offset);

};
#endif
#endif