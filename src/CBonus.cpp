/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CBonus.cpp,v 1.10 2003/12/26 17:51:11 valo Exp $                                                                  *
 ***************************************************************************/

#include "CBonus.h"


CBonus::CBonus(int x,int y)
  : CObject(x,y)
{
	char filename[512];
	set_config_file(DEFAULT_PLAYER_CONFIG_FILE);
	speedy = get_config_int(NULL,"bonus_falling_speed",10);
	type = (BonusType)(random()%BONUS_COUNT);
	set_color_conversion(COLORCONV_TOTAL);
	sprintf(filename,"/home/valo/Projects/breakin/graphics/bonus-%d.bmp",type + 1);
	model = load_bitmap(filename,NULL);
}

/*CBonus::CBonus()
  : CObject(0,0)
{
	speedy = 10;
	type = (BonusType)(random()%BONUS_COUNT);
}*/

CBonus::~CBonus()
{
	destroy_bitmap(model);
}

void CBonus::Draw(BITMAP *buffer)
{
	draw_sprite(buffer,model,x,y);
}

void CBonus::Move() { y += speedy; }

char* CBonus::Identify() { return "CBonus"; }

char* CBonus::getName()
{
	switch (type)
	{
		case SlowPad       : return "Slow pad";      break;
		case AddBalls      : return "More balls";    break;
		case LongerPad     : return "Long pad";      break;
		case ShorterPad    : return "Short pad";     break;
		case FastPad       : return "Fast pad";      break;
		case FastBalls     : return "Fast balls";    break;
		case SlowBalls     : return "Slow balls";    break;
		case PenetrateBall : return "Penetration!";  break;
		case MoreBonuses   : return "More bonuses!"; break;
		case Immortallity  : return "Immortality!";  break;
	}
}

void CBonus::GetBonus(CPlayer *player)
{
	switch (type)
	{
		case AddBalls      :
			TRACE("Taking add ball\n");
			player->AddBall();
		break;
		case LongerPad     :
		break;
		case ShorterPad    :
		break;
		case FastPad       :
			TRACE("Taking inc speed\n");
			player->incSpeed();
		break;
		case SlowPad       :
			TRACE("Taking dec speed\n");
			player->decSpeed();
		break;
		case FastBalls     :
			TRACE("Taking fast balls\n");
			player->IncreaseSpeed();
		break;
		case SlowBalls     :
			TRACE("Taking slow balls\n");
			player->DecreaseSpeed();
		break;
		case PenetrateBall :
			TRACE("Taking penetration\n");
			player->setPenetration();
		break;
		case MoreBonuses   :
			TRACE("Taking bonus rating\n");
			player->IncreaseBonusRate();
		break;
		case Immortallity  :
			TRACE("Taking immotality\n");
			player->setImmortal();
		break;
	}
}
