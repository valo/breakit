/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CFlyingText.h,v 1.2 2003/12/26 17:51:11 valo Exp $                                                                  *
 ***************************************************************************/

#ifndef _CFLYINGTEXT_H_
#define _CFLYINGTEXT_H_

#include "CObject.h"
#include <allegro.h>
#include <cstring>
#include <alfont.h>
#include "defines.h"

/**
 * 
 * Valentin Mihov
 **/
class CFlyingText : public CObject
{

public:
  CFlyingText(int x,int y,char *line1,char *line2,int color,int sx,int sy,int trans_speed,int start_trans);
  ~CFlyingText();
  
  void Draw(BITMAP *buffer);
  void Move();
  char* Identify() { return "CFlyingText"; }  
  
protected:
  ALFONT_FONT *font;
  char line1[30],line2[30];
  int color,speedx,speedy,trans,trans_speed;
};

#endif
