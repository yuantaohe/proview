! 
!  ProviewR   Open Source Process Control.
!  Copyright (C) 2005-2018 SSAB EMEA AB.
! 
!  This file is part of ProviewR.
!
!  This program is free software; you can redistribute it and/or 
!  modify it under the terms of the GNU General Public License as 
!  published by the Free Software Foundation, either version 2 of 
!  the License, or (at your option) any later version.
!
!  This program is distributed in the hope that it will be useful 
!  but WITHOUT ANY WARRANTY; without even the implied warranty of 
!  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
!  GNU General Public License for more details.
!
!  You should have received a copy of the GNU General Public License 
!  along with ProviewR. If not, see <http://www.gnu.org/licenses/>
! 
!  Linking ProviewR statically or dynamically with other modules is
!  making a combined work based on ProviewR. Thus, the terms and
!  conditions of the GNU General Public License cover the whole 
!  combination.
! 
!  In addition, as a special exception, the copyright holders of
!  ProviewR give you permission to, from the build function in the
!  ProviewR Configurator, combine ProviewR with modules generated by the
!  ProviewR PLC Editor to a PLC program, regardless of the license
!  terms of these modules. You may copy and distribute the resulting
!  combined work under the terms of your choice, provided that every 
!  copy of the combined work is accompanied by a complete copy of 
!  the source code of ProviewR (the version used to produce the
!  combined work), being distributed under the terms of the GNU 
!  General Public License plus this exception.
!
!  rt_csup_msg.msg -- <short description>
!

.facility	CSUP,211 /prefix = CSUP__		! Cycle supervision

errcrenam	<create port name '%s'>					/error
errefobj	<reference object '%s'>					/error
errgetnodobj	<access node config object>				/error
errgetwdgobj	<access watchdog config object>				/error
errgettyp	<get first cycle supervision object>			/error
erringettim	<get system time, cannot check for delay>		/error
errinmhcall	<returned from MH-call>					/error
errtrnnam	<translate port name '%s'>				/error
errwait		<executing wait statement>				/error
illname		<watchdog name, failed to create/map object>		/error
namalrexist	<create port name '%s', name already exists>		/warning
nolimtochk	<no limit to check>					/error
nostartim	<time of next loop unknown, unable to check for delay>	/error
nottowatch	<cycle time/port absent, object deleted '%s'>		/error
nulpoint	<null pointer, can't use watchdog object>		/error
success		<normal, successful completion>				/succ
linkerror	<link error '%s'>					/error
linklog		<link log '%s'>						/info
insvirmem	<insufficient virtual memory>				/error

.end
