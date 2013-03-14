/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CComponent.h,v 1.1 2003/11/07 20:05:26 valo Exp $                                                                  *
 ***************************************************************************/

#ifndef _CCOMPONENT_H_
#define _CCOMPONENT_H_

#include <allegro.h>

/**
 * 
 * Valentin Mihov
 **/
class CComponent
{

public:
  int x,y;
  int w,h;
  CComponent();
  ~CComponent();
  
  virtual void Draw(BITMAP *buffer) {}
  virtual void MouseClick() {}
  virtual void MouseOver() {}
  virtual void MouseIn()  { have_mouse = 1; }
  virtual void MouseOut() { have_mouse = 0; }
  virtual void ProcessEvents();
  virtual void Idle() {}
  
  protected:
    int have_mouse;
};

#endif
