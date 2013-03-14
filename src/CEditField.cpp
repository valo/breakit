/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CEditField.cpp,v 1.3 2003/12/30 12:12:05 valo Exp $              *
 ***************************************************************************/

#include "CEditField.h"


CEditField::CEditField()
  : CComponent()
{
	border_color = color = text_color = 0;
	font = alfont_load_font(GUI_FONT_FILENAME);
	alfont_set_font_size(font,30);
	text[0] = '\0';
}


CEditField::~CEditField()
{
	alfont_destroy_font(font);
}

void CEditField::Draw(BITMAP *buffer)
{
	rectfill(buffer,x,y,x + w,y + h,color);
	rect(buffer,x,y,x + w,y + h,border_color);
	alfont_textprintf_aa_ex(buffer,font,x + 3,y + h/2 - alfont_get_font_height(font)/2,text_color,-1,"%s<",text);
}

void CEditField::ProcessEvents()
{
	for (int i = KEY_A; i <= KEY_Z;i++)
		if (key[i])
		{
			text[strlen(text)+1] = '\0';
			if (key[KEY_LSHIFT] || key[KEY_RSHIFT]) text[strlen(text)]   = 'A' + i - KEY_A;
			else text[strlen(text)]   = 'a' + i - KEY_A;
			key[i] = 0;
			return;
		}
	for (int i = KEY_0; i <= KEY_9;i++)
		if (key[i])
		{
			text[strlen(text)+1] = '\0';
			text[strlen(text)]   = '0' + i - KEY_A;
			key[i] = 0;
			return;
		}
	if (key[KEY_BACKSPACE])
	{
		text[strlen(text)-1] = '\0';
		key[KEY_BACKSPACE] = 0;
	}
}
