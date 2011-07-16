/***********************************************************************
 **
 **   vlapisys_linux.cpp
 **
 **   This file is part of libkfrgcs.
 **
 ************************************************************************
 **
 **   Copyright (c):  2002 by Heiner Lamprecht
 **
 **   This file is distributed under the terms of the General Public
 **   Licence. See the file COPYING for more information.
 **
 **   $Id$
 **
 ***********************************************************************/

#include "vla_support.h"
#include "Device/Port.hpp"

#include <stdio.h>
#if defined(HAVE_POSIX) || !defined(_WIN32_WCE)
#include <time.h>
#endif

int noninteractive=1;

/***********************************************************************
 *
 * vlapi_sys
 *
 **********************************************************************/


/** serial output of single character to the VL */
VLA_ERROR VLA_SYS::serial_out(const byte outbyte)
{
  port->Write(outbyte);
  return VLA_ERR_NOERR;
}


/**
 * serial input of single character from the VL
 * returns 0 if character has been received, and -1 when no character
 * was in the receive buffer
 */
VLA_ERROR VLA_SYS::serial_in(byte *inbyte)
{
  int i = port->GetChar();
  if (i != EOF) {
    *inbyte = i;
    return VLA_ERR_NOERR;
  } else {
    return VLA_ERR_NOCHAR;
  }
}


/** clear serial input- and output-buffers */
VLA_ERROR VLA_SYS::serial_empty_io_buffers()
{
  port->Flush();
  return VLA_ERR_NOERR;
}

// text for the status line
//
const char *statustext[] = {
  "sending command to FR",
  "command is being processed",
  "datatransfer in progress ... (press <Q> to abort)",
  "writing database & FDF to FR",
  "data transfer interrupted by user - press any key",
  "data transfer unsuccessful, try lower baudrate - press any key",
  "no data was received from FR - press any key",
  "user-interrupt !",
  "please connect the VOLKSLOGGER and press OK",
  "connection established - press OK",
  "connection not established - press OK",
  "intentionally left blank ...",
  "error: command not implemented",
  "error: wrong FR connected",
  "error: no response from FR"
};

void VLA_SYS::show(VLS_TXT_ID txtid)
{
  //JMW  cout << statustext[txtid] << endl;

  if(noninteractive)  return;
  if (txtid == VLS_TXT_NIL)  return;
}


void VLA_SYS::showwait(VLS_TXT_ID txtid)
{
  //JMW  cout << statustext[txtid] << endl;

  if(noninteractive)  return;
}
