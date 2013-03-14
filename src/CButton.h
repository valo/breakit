/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CButton.h,v 1.1 2003/11/07 20:05:26 valo Exp $                                                                  *
 ***************************************************************************/

#ifndef _CBUTTON_H_
#define _CBUTTON_H_

#include "CComponent.h"
#include <alfont.h>
#include "defines.h"

/**
 * 
 * Valentin Mihov
 **/
class CButton : public CComponent
{

public:
  int color,border_color,text_color;
  char *caption;
  int over_trans,idle_trans;
  int clicked;
  
  CButton();
  ~CButton();
  
  void Draw(BITMAP *buffer);
  void MouseOver();
  void Idle();
  void MouseClick();
  
private:
  int trans;
  ALFONT_FONT *font;
};

#endif
