/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CBonus.h,v 1.8 2003/12/26 17:51:11 valo Exp $                                                                  *
 ***************************************************************************/

#ifndef _CBONUS_H_
#define _CBONUS_H_

#include "CObject.h"
#include <allegro.h>
#include <stdlib.h>
#include "CPlayer.h"
#include <stdio.h>

#define BONUS_COUNT 10

/**
 * 
 * Valentin Mihov
 **/
class CBonus : public CObject
{

/* All kind of bonuses */
  enum BonusType { 
	SlowPad,        // OK
	AddBalls,       // OK
	LongerPad,
	ShorterPad,
	FastPad,        // OK
	FastBalls,      // OK
	SlowBalls,      // OK
	PenetrateBall,  // OK
	MoreBonuses,    // OK
	Immortallity    // OK
	};
	
public:
//  CBonus();
  CBonus(int x,int y);
  ~CBonus();
  
  void Draw(BITMAP *buffer);
  void Move();
  char* Identify();
  char* getName();
  void GetBonus(CPlayer *player);
  
protected:
  int speedy;  // The speed of falling of the bonus
  BonusType type;
  BITMAP *model;
  
};

#endif
