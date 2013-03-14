/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CPlayer.cpp,v 1.12 2003/12/30 12:12:05 valo Exp $                 *
 ***************************************************************************/

#include "CPlayer.h"


CPlayer::CPlayer(int x,int y,char *key_bindings_file,int solid)
{	
	set_config_file(key_bindings_file);
	key_left = get_config_int(NULL,"LEFT",0);
	key_right = get_config_int(NULL,"RIGHT",0);
	key_fire  = get_config_int(NULL,"FIRE",0);
	
	this->x = x;
	this->y = y;
	set_config_file(DEFAULT_PLAYER_CONFIG_FILE);
	bonus_frequency = default_bonus_frequency = get_config_int(NULL,"bonus_rate",5);
	more_bonuses_modifier = get_config_int(NULL,"more_bonuses_modifier",1);
	more_bonuses_duration = get_config_int(NULL,"more_bonuses_duration",10);
	
	move_speed = default_move_speed = get_config_int(NULL,"pad_speed",100);
	speed_modifier = get_config_int(NULL,"player_speed_modifier",5);
	
	set_color_conversion(COLORCONV_TOTAL);
	model = load_bitmap("/home/valo/Projects/breakin/graphics/batata.bmp",NULL);
	width = model->w;
	height = model->h;
	
	score = 0;
	last_scored = -30;
	bonus_points = 0;
	
	solid_walls = solid;
	
	immortal_time = get_config_int(NULL,"immortal_time",10);
	
	penetrating = false;
	penetration_time = get_config_int(NULL,"penetration_duration",10);
	
	ball_speed = default_ball_speed = get_config_int(NULL,"ball_speed",5);
	ball_speed_modifier = get_config_int(NULL,"ball_speed_modifier",10);
	
	fast_hit_max_time = get_config_float(NULL,"fast_hit_max_time",0.5);
	
	status_font1 = alfont_load_font(STATUS_FONT1_FILENAME);
	status_font2 = alfont_load_font(STATUS_FONT2_FILENAME);
	alfont_set_font_size(status_font1,50);
	alfont_set_font_size(status_font2,20);
}


CPlayer::~CPlayer()
{
	destroy_bitmap(model);
	alfont_destroy_font(status_font1);
	alfont_destroy_font(status_font2);
}

void CPlayer::Draw(BITMAP *buffer)
{
	draw_sprite(buffer,model,x,y);
}

void CPlayer::ProcessEvents()
{
	if (solid_walls & 1 && solid_walls & 2 && solid_walls & 4 && solid_walls & 8 && (global_timer - time_got_immortal)/FRAMES_PER_SEC >= immortal_time) unsetImmortal();
	if (penetrating && (global_timer - time_got_penetration)/FRAMES_PER_SEC >= penetration_time) removePenetration();
	if (bonus_frequency == more_bonuses_modifier && (global_timer - time_got_more_bonuses)/FRAMES_PER_SEC >= more_bonuses_duration) DecreaseBonusRate();
	if (key[key_left])
	{
		x--;
		for(std::list<CBall*>::iterator inter = balls.begin();inter != balls.end();inter++)
			if ((*inter)->is_OnPad()) (*inter)->setX((*inter)->getX() - 1);
	}
	if (key[key_right])
	{
		x++;
		for(std::list<CBall*>::iterator inter = balls.begin();inter != balls.end();inter++)
			if ((*inter)->is_OnPad()) (*inter)->setX((*inter)->getX() + 1);
	}
	if (key[key_fire])
	{
		for(std::list<CBall*>::iterator inter = balls.begin();inter != balls.end();inter++)
			if ((*inter)->is_OnPad()) (*inter)->FireFromPad();
	}
}

void CPlayer::IncreaseBonusRate()
{
	bonus_frequency = more_bonuses_modifier;
	time_got_more_bonuses = global_timer;
}     

void CPlayer::DecreaseBonusRate()
{
	bonus_frequency = default_bonus_frequency;
}

void CPlayer::AddBall()
{
	/* An assumptation that the pad is at the upper side of the field */
	if (y < 100)
	{
		CBall *b = new CBall(x+5,y+5,4,this);
		balls.push_front(b);
	}
	else
	{
		CBall *b = new CBall(x+5,y-5,4,this);
		balls.push_front(b);
	}
}

void CPlayer::RemoveBall(CBall *ball)
{
	std::list<class CBall*>::iterator inter = balls.begin();
	while (inter != balls.end())
	{
		if ((*inter) == ball)
		{
//			ball = NULL;
			balls.erase(inter);
			return;
		}
		inter++;
	}
}

void CPlayer::incSpeed()
{
	if (move_speed + speed_modifier <= TICKS_PER_FRAME) move_speed += speed_modifier;
}

void CPlayer::decSpeed()
{
	if (move_speed - speed_modifier > 0) move_speed -= speed_modifier;
}

void CPlayer::setImmortal() 
{
	solid_walls |= 0xF;
	time_got_immortal = global_timer;
}

void CPlayer::unsetImmortal() 
{
	solid_walls >>= 4;
	solid_walls &= 0xF;
	solid_walls |= ((solid_walls<<4) & 0xF0); 
}

void CPlayer::setPenetration()
{
	penetrating = true;
	time_got_penetration = global_timer;
}

void CPlayer::removePenetration()
{
	this->penetrating = false;
}

void CPlayer::IncreaseSpeed()
{
	if (ball_speed + ball_speed_modifier <= TICKS_PER_FRAME) ball_speed += ball_speed_modifier;
}

void CPlayer::DecreaseSpeed()
{
	if (ball_speed - ball_speed_modifier >= default_ball_speed) ball_speed -= ball_speed_modifier;
}

/*
	Draws the status bar for the player in a specified buffer on a specified position
*/
void CPlayer::DrawStatusBar(BITMAP *buffer,int x,int y)
{
	int len;
	alfont_textprintf_aa_ex(buffer,status_font1,x,y,makecol(255,255,255),-1,"Score: %d",score);
	len = alfont_text_length(status_font1,"Score: 000000000");
	
	y += 7;
	if (penetrating)
	{
		alfont_textout_centre_aa_ex(buffer,status_font2,"Penetration",x + len,y,makecol(255,255,255),-1);
		alfont_textprintf_centre_aa_ex(buffer,status_font2,x + len,y + alfont_text_height(status_font2),makecol(255,255,255),-1,"%0.2lf",(double)penetration_time - (double)(global_timer - time_got_penetration)/FRAMES_PER_SEC);
	}
	else
	{
		alfont_textout_centre_aa_ex(buffer,status_font2,"Penetration",x + len,y,makecol(255,255,255),-1);
		alfont_textprintf_centre_aa_ex(buffer,status_font2,x + len,y + alfont_text_height(status_font2),makecol(255,255,255),-1,"%0.2lf",0);
	}
	len += (alfont_text_length(status_font2,"Penetration") + 10);
	
	if (solid_walls & 1 && solid_walls & 2 && solid_walls & 4 && solid_walls & 8)
	{
		alfont_textout_centre_aa_ex(buffer,status_font2,"Immortality",x + len,y,makecol(255,255,255),-1);
		alfont_textprintf_centre_aa_ex(buffer,status_font2,x + len,y + alfont_text_height(status_font2),makecol(255,255,255),-1,"%0.2lf",(double)immortal_time - (double)(global_timer - time_got_immortal)/FRAMES_PER_SEC);
	}
	else
	{
		alfont_textout_centre_aa_ex(buffer,status_font2,"Immortality",x + len,y,makecol(255,255,255),-1);
		alfont_textprintf_centre_aa_ex(buffer,status_font2,x + len,y + alfont_text_height(status_font2),makecol(255,255,255),-1,"%0.2lf",0);
	}
	len += (alfont_text_length(status_font2,"Immortality"));
	
	alfont_textout_centre_aa_ex(buffer,status_font2,"Ball speed",x + len,y,makecol(255,255,255),-1);
	alfont_textprintf_centre_aa_ex(buffer,status_font2,x + len,y + alfont_text_height(status_font2),makecol(255,255,255),-1,"x%d",(ball_speed - default_ball_speed)/ball_speed_modifier + 1);
	len += (alfont_text_length(status_font2,"Ball speed") + 20);
	
	alfont_textout_centre_aa_ex(buffer,status_font2,"Paddle speed",x + len,y,makecol(255,255,255),-1);
	alfont_textprintf_centre_aa_ex(buffer,status_font2,x + len,y + alfont_text_height(status_font2),makecol(255,255,255),-1,"x%d",(move_speed - default_move_speed)/speed_modifier + 1);
	len += (alfont_text_length(status_font2,"Paddle speed") + 20);
	
	alfont_textout_centre_aa_ex(buffer,status_font2,"Bonus frequency",x + len,y,makecol(255,255,255),-1);
	alfont_textprintf_centre_aa_ex(buffer,status_font2,x + len,y + alfont_text_height(status_font2),makecol(255,255,255),-1,"%d%%",bonus_frequency);
	len += (alfont_text_length(status_font2,"Bonus frequency"));
	
	if (SecsfromLastHit() <= fast_hit_max_time)
	{
		alfont_textout_centre_aa_ex(buffer,status_font2,"Bonus points",x + len,y,makecol(255,255,255),-1);
		alfont_textprintf_centre_aa_ex(buffer,status_font2,x + len,y + alfont_text_height(status_font2),makecol(255,255,255),-1,"%0.2lf %d",(double)fast_hit_max_time - SecsfromLastHit(),bonus_points);
	}
	else
	{
		alfont_textout_centre_aa_ex(buffer,status_font2,"Bonus points",x + len,y,makecol(255,255,255),-1);
		alfont_textprintf_centre_aa_ex(buffer,status_font2,x + len,y + alfont_text_height(status_font2),makecol(255,255,255),-1,"%0.2lf %d",0.0,bonus_points);
	}
}

int CPlayer::setHit()
{
	if (SecsfromLastHit() <= fast_hit_max_time) bonus_points += 10;
	else bonus_points = 0;
	last_scored = global_timer;
}

