/* 
 * Proview   $Id$
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

#ifndef rt_io_pnak_locals_h
#define rt_io_pnak_locals_h

#include "rt_profinet.h"
#include "rt_pnak.h"

/* rt_io_pnak_locals.h -- Profinet io handling locals. */

typedef struct _PN_Alarm_Data {
    unsigned short alarm_type;
    unsigned short alarm_prio;
    unsigned short rem_alarms;
    unsigned int   slot_number;
    unsigned int   sub_slot_number;
    unsigned int   module_ident_number;
    unsigned int   submodule_ident_number;
    unsigned short alarm_spec;
    unsigned short  data_length;
    unsigned char  *data;
} PN_Alarm_Data;

class PnIOCRData {
 public:
  PnIOCRData() : type(0), number_modules(0), identifier(0), io_data_length(0) {}
  
  unsigned short type;
  unsigned short number_modules;
  unsigned short identifier;
  unsigned short io_data_length;  // bytes of io-data including status;
  unsigned short clean_io_data_length;  // bytes of io-data including status;
  unsigned char  *io_data;  
  unsigned char  *clean_io_data;

  ~PnIOCRData() {}

  int print( ofstream& fp);
};

class PnSubmoduleData {
 public:
  PnSubmoduleData() : subslot_number(0), subslot_idx(0), type(0), state(0), ident_number(0), phys_ident_number(0) {}
  
  unsigned short subslot_number;
  unsigned short subslot_idx;
  unsigned short type;
  unsigned short state;
  unsigned int   ident_number;
  unsigned int   phys_ident_number;

  unsigned short io_in_data_length; // bytes of pure io-data
  unsigned short offset_io_in;      // offset in io-data area for this iocr
  unsigned short offset_clean_io_in;      // offset in io-data area for this iocr
  unsigned short offset_status_in;  // offset in io-data area for this iocr

  unsigned short io_out_data_length; // bytes of pure io-data
  unsigned short offset_io_out;      // offset in io-data area for this iocr
  unsigned short offset_clean_io_out;      // offset in io-data area for this iocr
  unsigned short offset_status_out;  // offset in io-data area for this iocr

  ~PnSubmoduleData() {}

  int print( ofstream& fp);
};

class PnModuleData {
 public:
  PnModuleData() : slot_number(0), slot_idx(0), state(0), ident_number(0), phys_ident_number(0) {}

  unsigned int slot_number;
  unsigned int slot_idx;
  unsigned short state;
  unsigned int ident_number;
  unsigned int phys_ident_number;

  vector<PnSubmoduleData *> submodule_data;

  ~PnModuleData() { 
    for ( unsigned int i = 0; i < submodule_data.size(); i++)
      delete submodule_data[i];
  }

  int print( ofstream& fp);
};

class PnDeviceData {
 public:
  PnDeviceData() : device_ref(0), alarm_ref(0), device_state(0), no_diff_modules(0) {memset(&alarm_data, 0, sizeof(PN_Alarm_Data));}

  unsigned short device_ref;
  unsigned short alarm_ref;
  unsigned short device_state;
  unsigned short no_diff_modules;

  PN_Alarm_Data  alarm_data;

  vector<PnModuleData *> module_data;
  vector<PnIOCRData *> iocr_data;

  ~PnDeviceData() { device_reset();}
  void device_reset() {
    for ( unsigned int i = 0; i < module_data.size(); i++)
      delete module_data[i];
    module_data.clear();
    for ( unsigned int i = 0; i < iocr_data.size(); i++)
      delete iocr_data[i];
    iocr_data.clear();
  }

  int copy_slot( unsigned int slot_idx);
  int cut_slot( unsigned int slot_idx);
  int paste_slot( unsigned int slot_idx);
};

class PnDeviceInfo {
 public:
  PnDeviceInfo() {}
  unsigned char ipaddress[4];
  unsigned char macaddress[6];
  unsigned char subnetmask[4];
  char devname[80];
  int vendorid;
  int deviceid;
};

typedef struct _agent_args {
  void           *local;
  io_sAgent	 *ap;
} agent_args;

class io_sAgentLocal {
 public :
  io_sAgentLocal() {}

  T_PNAK_SERVICE_REQ_RES       service_req_res;
  T_PNAK_SERVICE_CON           service_con;
  unsigned char ipaddress[4];
  unsigned char macaddress[6];
  unsigned char subnetmask[4];

  vector<PnDeviceData *> device_data;
  vector<PnDeviceInfo *> dev_info;

  pthread_t handle_events;
  agent_args args;

};

#endif