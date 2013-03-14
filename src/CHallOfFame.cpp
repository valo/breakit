
#include "CHallOfFame.h"


CHallOfFame::CHallOfFame()
{
	// Init the scores
	FILE *f = fopen(BEST_SCORES_FILENAME,"rb");
	int i = 0;
	int res;
	while (!feof(f))
	{
		res = fread(names[i],sizeof(names[i][0]),255,f);
		if (!res) break;
		fread(&scores[i],sizeof(scores[i]),1,f);
		if (!res) break;
		i++;
	}
	for (;i < 10;i++)
	{
		strcpy(names[i],"Unknown");
		scores[i] = 0;
	}
	fclose(f);
	
	// Init the graphic stuff
	panel.caption = "Hall of Fame";
	panel.alpha = 50;
	panel.border_color = makecol(88,77,141);
	panel.caption_color = 0;
	panel.w = 500;
	panel.h = 350;
	
	font = alfont_load_font(GUI_FONT_FILENAME);
	alfont_set_font_size(font,20);
}

void CHallOfFame::Save()
{
	// Init the scores
	FILE *f = fopen(BEST_SCORES_FILENAME,"wb");
	int i = 0;
	for (i = 0;i < 10;i++)
	{
		fwrite(names[i],sizeof(names[i][0]),255,f);
		fwrite(&scores[i],sizeof(scores[i]),1,f);
	}
	fclose(f);
}

CHallOfFame::~CHallOfFame()
{
}


void CHallOfFame::Draw(BITMAP *buffer,int x,int y)
{
	int i;
	panel.x = x;
	panel.y = y;
	panel.Draw(buffer);
	y += 50;
	x += 20;
	for (i = 0;i < 10;i++)
	{
		alfont_textprintf_aa_ex(buffer,font,x,y,0,-1,"%2d.%s",i + 1,names[i],scores[i]);
		alfont_textprintf_right_aa_ex(buffer,font,x + panel.w - alfont_text_length(font,"000"),y,0,-1,"%d",scores[i]);
		y += alfont_text_height(font) + 10;
	}
}

void CHallOfFame::AddEntry(char name[255],int score)
{
	CHallOfFame *hall = new CHallOfFame();
	int i,tmp;
	for (i = 0;i < 10;i++)
		if (!(hall->scores[i] >= score)) break;
	if (i == 10){ delete hall; return; }
	tmp = i;
	i++;
	for (;i < 10;i++)
	{
		hall->scores[i] = hall->scores[i - 1];
		strcpy(hall->names[i],hall->names[i - 1]);
	}
	
	i = tmp;
	hall->scores[i] = score;
	strcpy(hall->names[i],name);
	hall->Save();
	delete hall;
}
