/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CBlock.cpp,v 1.6 2003/12/30 12:12:05 valo Exp $                     *
 ***************************************************************************/

#include "CBlock.h"


CBlock::CBlock(int health)
{
	this->health = health;
	if (health >= MAXHEALTH - 1) points_giver = bonus_giver = 0;
	else points_giver = bonus_giver = 1;
	is_animating = 0;
	trans = 0;
	trans_speed = 20;
}

CBlock::~CBlock()
{
}

void CBlock::Draw(BITMAP *buffer,int x1,int y1,int x2,int y2)
{
	if (is_animating)
	{
		trans += trans_speed;
		if (trans >= 255)
		{
			is_animating = 0;
			trans = 0;
			draw_sprite(buffer,blocks[health-1],x1,y1);
			return;
		}
		drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
		set_trans_blender(0,0,0,trans);
		draw_trans_sprite(buffer,blocks[health-1],x1,y1);
		solid_mode();
	}
	else draw_sprite(buffer,blocks[health-1],x1,y1);
}

void CBlock::Hit(CBall *ball)
{
	if (health < MAXHEALTH - 1)
	{
		health--;
		is_animating = 1;
		trans = 0;
	}
}

int CBlock::getHealth() { return health; }
