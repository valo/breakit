/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CBall.h,v 1.8 2003/12/25 00:06:21 valo Exp $                     *
 ***************************************************************************/

#ifndef _CBALL_H_
#define _CBALL_H_

#include <allegro.h>
#include <math.h>
#include "CPlayer.h"

extern volatile int global_timer;

/**
 * 
 * Valentin Mihov
 **/
class CBall
{

public:
  CBall(int x,int y,int radius,class CPlayer *owner);
  ~CBall();
  
  void MoveX();
  void MoveY();
  void Draw(BITMAP *buffer);
  void MirrorX();
  void MirrorY();
  void MirrorXKoef(double x,double y,int w,int h);
  void MirrorYKoef(double x,double y,int w,int h);
  
  double speedx();
  double speedy();
  
  double getX()       { return x;                  }
  double getY()       { return y;                  }
  int getRadius()     { return radius;             }
  int getSpeed();
  void setX(double x) { this->x = x;               }
  void setY(double y) { this->y = y;               }
  int is_OnPad()      { return is_onpad;           }
  CPlayer* getOwner() { return owner;              }
  void FireFromPad()  { is_onpad = 0;              }
  
  void ProcessEvents();
  
protected:

  double angle; // The angle of the movement of the ball
  double x,y;   // The current position of the ball
  int radius;
  int is_onpad;
  class CPlayer *owner;
  
  friend class CMasterofPuppets;
};

#endif
