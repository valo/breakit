/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CBlock.h,v 1.6 2003/12/30 12:12:05 valo Exp $                                                                  *
 ***************************************************************************/

#ifndef _CBLOCK_H_
#define _CBLOCK_H_

#include <allegro.h>
#include "CBall.h"

extern BITMAP *blocks[MAXHEALTH];
/**
 * 
 * Valentin Mihov
 **/
class CBlock
{
public:
  CBlock(int health);
  ~CBlock();
  
  void Draw(BITMAP *buffer,int x1,int y1,int x2,int y2);
  void Hit(CBall *ball);
  
  int getHealth();
  int isPointsGiver() { return points_giver;            }
  int isBonusGiver()  { return bonus_giver;             }
  int isSolid()       { return health >= MAXHEALTH - 1; }
  
protected:
  int health,points_giver,bonus_giver;
  int is_animating;
  int trans,trans_speed;
  int frame;
  
  friend class CMasterofPuppets;
};

#endif
