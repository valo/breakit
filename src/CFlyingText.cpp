/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CFlyingText.cpp,v 1.3 2003/12/30 12:12:05 valo Exp $                                                                  *
 ***************************************************************************/

#include "CFlyingText.h"

#include <stdlib.h>
CFlyingText::CFlyingText(int x,int y,char *line1,char *line2,int color,int sx,int sy,int trans_speed,int start_trans)
  : CObject(x,y)
{
	font = alfont_load_font(FLYINGTEXT_FONT_FILE);
	alfont_set_font_size(font,20);
	strcpy(this->line1,line1);
	strcpy(this->line2,line2);
	speedy = sy;
	speedx = sx;
	this->trans_speed = trans_speed;
	trans = start_trans;
	this->color = color;
}

CFlyingText::~CFlyingText()
{
	alfont_destroy_font(font);
}

void CFlyingText::Draw(BITMAP *buffer)
{
	alfont_textout_centre_aa_trans(buffer,font,line1,x,y,color,trans);
	if (line2[0] != '\0') alfont_textout_centre_aa_trans(buffer,font,line2,x,y+alfont_text_height(font),color,trans);
}

void CFlyingText::Move()
{
	x += speedx;
	y += speedy;
	trans += trans_speed;
	if (trans >= 255) exists = 0;
}
