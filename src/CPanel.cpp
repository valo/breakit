
#include "CPanel.h"


CPanel::CPanel()
  : CComponent()
{
	font = alfont_load_font(GUI_FONT_FILENAME);
	alfont_set_font_size(font,45);
	caption = "";
	color = caption_color = 0;
}


CPanel::~CPanel()
{
	alfont_destroy_font(font);
}

void CPanel::Draw(BITMAP *buffer)
{
	rect(buffer,x,y,x + w,y + h,border_color);
	drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
	set_trans_blender(0,0,0,alpha);
	rectfill(buffer,x + 1,y + 1,x + w - 1,y + h - 1,color);
	solid_mode();
	alfont_textout_centre_aa_ex(buffer,font,caption,x + w/2,y,caption_color,-1);
}
