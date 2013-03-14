/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CEditField.h,v 1.1 2003/11/07 20:05:26 valo Exp $                                                                  *
 ***************************************************************************/

#ifndef _CEDITFIELD_H_
#define _CEDITFIELD_H_

#include "CComponent.h"
#include "defines.h"
#include <allegro.h>
#include <alfont.h>
#include <string.h>

/**
 * 
 * Valentin Mihov
 **/
class CEditField : public CComponent
{

public:
  int border_color,color,text_color;
  char text[100];

  CEditField();
  ~CEditField();
  
  void Draw(BITMAP *buffer);
  void ProcessEvents();
  
private:
  ALFONT_FONT *font;
};

#endif
