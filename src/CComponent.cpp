/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CComponent.cpp,v 1.1 2003/11/07 20:05:26 valo Exp $                                                                  *
 ***************************************************************************/

#include "CComponent.h"


CComponent::CComponent()
{
	w = h = 10;
	x = y = 0;
	have_mouse = 0;
}


CComponent::~CComponent()
{
}

void CComponent::ProcessEvents()
{
	if (mouse_x >= x && mouse_x <= x + w && mouse_y >= y && mouse_y <= y+h)
	{
		if (mouse_b) MouseClick();
		else
		{
			if (have_mouse) MouseOver();
			else MouseIn();
		}
	}
	else
		if (have_mouse) MouseOut();
		else Idle();
}

