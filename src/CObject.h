/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CObject.h,v 1.4 2003/10/31 20:54:00 valo Exp $                                                                  *
 ***************************************************************************/

#ifndef _COBJECT_H_
#define _COBJECT_H_

#include <allegro.h>

/**
 * 
 * Valentin Mihov
 **/
class CObject
{

public:
  bool exists;

  CObject(int x,int y);
  CObject() { x = y = 0;exists = true; }
  virtual ~CObject() { }
  
  virtual void Draw(BITMAP *buffer);
  virtual void Move();
  virtual char* Identify();
  
  bool does_exist() { return exists; }
  int getX() { return x; }
  int getY() { return y; }
  void setX(int x) { this->x = x; }
  void setY(int y) { this->y = y; }
  
protected: 
  int x,y;
};

#endif
