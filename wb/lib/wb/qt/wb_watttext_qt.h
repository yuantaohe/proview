/*
 * Proview   Open Source Process Control.
 * Copyright (C) 2005-2017 SSAB EMEA AB.
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
 **/

#ifndef wb_watttext_qt_h
#define wb_watttext_qt_h

/* wb_watttext_qt.h -- Object attribute editor */

#ifndef wb_watttext_h
#include "wb_watttext.h"
#endif

#include <QLabel>
#include <QTextEdit>

class WAttTextQtWidget;

class WAttTextQt : public WAttText {
public:
  WAttTextQt(QWidget* wa_parent_wid, void* wa_parent_ctx,
      ldh_tSesContext wa_ldhses, pwr_sAttrRef wa_aref, int wa_editmode,
      pwr_tStatus* status);
  QLabel* msg_label;
  QWidget* button_ok;
  QWidget* button_apply;
  QWidget* button_cancel;
  QTextEdit* textbuffer;
  int input_max_length;
  int init;

  void message(char severity, const char* message);
  void pop();
  void set_editmode(int editmode, ldh_tSesContext ldhses);
  void set_attr_value();

private:
  WAttTextQtWidget* toplevel;
};

class WAttTextQtWidget : public QWidget {
  Q_OBJECT

public:
  WAttTextQtWidget(WAttTextQt* parent_ctx, QWidget* parent)
      : QWidget(), atxt(parent_ctx)
  {
  }

protected:
  void focusInEvent(QFocusEvent* event);
  void closeEvent(QCloseEvent* event);

public slots:
  void activate_save();
  void activate_saveandclose();
  void activate_copy();
  void activate_cut();
  void activate_paste();
  void activate_help();
  void activate_ok();
  void activate_apply();
  void action_text_inserted();

private:
  WAttTextQt* atxt;
};

#endif