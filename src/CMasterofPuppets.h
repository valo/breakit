/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CMasterofPuppets.h,v 1.9 2003/12/26 17:51:11 valo Exp $          *
 ***************************************************************************/

#ifndef _CMASTEROFPUPPETS_H_
#define _CMASTEROFPUPPETS_H_

#include "CBall.h"
#include "CPlayer.h"
#include "CBlockMap.h"
#include "CBreakinOnePlayer.h"
#include "CBonus.h"
#include <cstring>
#include "CFlyingText.h"
#include <list>

/**
 * 
 * Valentin Mihov
 **/
class CMasterofPuppets
{

public:
  
  static int CMasterofPuppets::Control(CPlayer *player,CBlockMap *map,CBall *ball,std::list<CObject*> *objects,int tick);
  static void CheckBonusTake(class CPlayer *player,std::list<CObject*> *objects,class CBlockMap *map);
  
private:

  static double VectorS(double x1,double y1,double x2,double y2,double x3,double y3);
  static int InterLines(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4);
  static int is_box_hit(double x1,double y1,double w,double h,CBall *ball);
  static void CalcHitwithBox(int x1,int y1,int w,int h,CBall *ball,int hit_mask);
  static void CalcHitwithPlayer(int x1,int y1,int w,int h,CBall *ball,int hit_mask);
  static int OverlapRects(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
  static void CheckBallWallCollusion(CBall *ball,CBlockMap *map);
};

#endif
