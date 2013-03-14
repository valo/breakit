/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CBall.cpp,v 1.13 2003/12/30 12:12:05 valo Exp $                   *
 ***************************************************************************/

#include "CBall.h"


CBall::CBall(int x,int y,int radius,CPlayer *owner)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->angle = 2*M_PI - M_PI_4;
	this->owner = owner;
	this->is_onpad = 1;
}

CBall::~CBall()
{
	this->owner = NULL;
}

void CBall::MoveX()
{
	if (!is_onpad) x += speedx();
}

void CBall::MoveY()
{
	if (!is_onpad) y += speedy();
}

void CBall::Draw(BITMAP *buffer)
{
	circlefill(buffer,(int)round(x),(int)round(y),radius,makecol(255,255,255));
}

double CBall::speedx() { return ONE_BALL_STEP*cos(angle); }
double CBall::speedy() { return ONE_BALL_STEP*sin(angle); }

void CBall::MirrorY() { angle = 2*M_PI - angle; }
void CBall::MirrorX() { angle = M_PI - angle; }

void CBall::MirrorXKoef(double x,double y,int w,int h)
{
	MirrorX();
}

void CBall::MirrorYKoef(double x,double y,int w,int h)
{
	double xp;
	x -= this->x;
	y -= this->y;
	if (y > 0) xp = y/tan(angle);
	else xp = (y + h)/tan(angle);
	angle = M_PI + M_PI_4 + M_PI_2*((xp-x)/w);
}

void CBall::ProcessEvents()
{
}

int CBall::getSpeed()
{
	return owner->getBallSpeed();
}
