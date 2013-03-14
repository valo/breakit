/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CButton.cpp,v 1.1 2003/11/07 20:05:26 valo Exp $                                                                  *
 ***************************************************************************/

#include "CButton.h"


CButton::CButton() : CComponent()

{
	trans = 150;
	color = border_color = text_color = makecol(0,0,0);
	font = alfont_load_font(GUI_FONT_FILENAME);
	alfont_set_font_size(font,40);
	clicked = 0;
}


CButton::~CButton()
{
	alfont_destroy_font(font);
}

void CButton::MouseClick()
{
	clicked = 1;
	trans = 255;
}

void CButton::MouseOver()
{
	if (trans + 5 < over_trans) trans += 5;
}

void CButton::Draw(BITMAP *buffer)
{
	if (trans)
	{
		drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
		set_trans_blender(0,0,0,trans);
	}
	else solid_mode();
	rectfill(buffer,x,y,x + w,y + h,color);
	solid_mode();
	alfont_textout_centre_aa_trans(buffer,font,caption,x + w/2,y + h/2 - alfont_get_font_height(font)/2,text_color,255 - trans);
	rect(buffer,x,y,x + w,y + h,border_color);
}

void CButton::Idle()
{
	if (trans > idle_trans) trans -= 5;
}

