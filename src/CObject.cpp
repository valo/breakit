/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CObject.cpp,v 1.3 2003/10/31 20:54:00 valo Exp $                                                                  *
 ***************************************************************************/

#include "CObject.h"


CObject::CObject(int x,int y)
{
	this->x = x;
	this->y = y;
	exists = 1;
}

void CObject::Draw(BITMAP *buffer)
{
}

void CObject::Move() {}

char* CObject::Identify() { return "CObject"; }
