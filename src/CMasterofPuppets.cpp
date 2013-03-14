/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CMasterofPuppets.cpp,v 1.14 2003/12/26 17:51:11 valo Exp $        *
 ***************************************************************************/

#include "CMasterofPuppets.h"
#include <stdio.h>

double CMasterofPuppets::VectorS(double x1,double y1,double x2,double y2,double x3,double y3)
{
	return x1*y2+y1*x3+x2*y3-x1*y3-y1*x2-y2*x3;
}

int CMasterofPuppets::InterLines(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
{
	if (VectorS(x1,y1,x2,y2,x3,y3)*VectorS(x1,y1,x2,y2,x4,y4) <= 0 && 
		VectorS(x3,y3,x4,y4,x1,y1)*VectorS(x3,y3,x4,y4,x2,y2) <= 0) return 1;
	return 0;
}

/*
	Determines whether a box is hitted by the ball
	Returns a mask with describing which walls was hitted : 
	   ____4____
	 5/         \8
	  |         |
	  |         |
	 1|         |2
	  |         |
	 6\________/7
	       3
*/
int CMasterofPuppets::is_box_hit(double x1,double y1,double w,double h,CBall *ball)
{
	int res = 0;
	/* A small translation for convinience */
	x1 = x1 - ball->x;
	y1 = y1 - ball->y;
	
	/* First the four sides of the eightgon */
	if (InterLines(0,0,ball->speedx(),ball->speedy(),x1 - ball->radius,y1,x1 - ball->radius,y1 + h)) res |= 1;
	if (InterLines(0,0,ball->speedx(),ball->speedy(),x1 + w + ball->radius,y1,x1 + w + ball->radius,y1 + h)) res |= 2;
	if (InterLines(0,0,ball->speedx(),ball->speedy(),x1,y1 + h + ball->radius,x1 + w,y1 + h + ball->radius)) res |= 4;
	if (InterLines(0,0,ball->speedx(),ball->speedy(),x1,y1 - ball->radius,x1 + w,y1 - ball->radius)) res |= 8;
	
	/* And now the corners */
	if (InterLines(0,0,ball->speedx(),ball->speedy(),x1 - ball->radius,y1,x1,y1 - ball->radius)) res |= 16;
	if (InterLines(0,0,ball->speedx(),ball->speedy(),x1 - ball->radius,y1 + h,x1,y1 + h + ball->radius)) res |= 32;
	if (InterLines(0,0,ball->speedx(),ball->speedy(),x1 + w + ball->radius,y1 + h,x1 + w,y1 + h + ball->radius)) res |= 64;
	if (InterLines(0,0,ball->speedx(),ball->speedy(),x1 + w + ball->radius,y1,x1 + w,y1 - ball->radius)) res |= 128;
	
	return res;
}

/*
	Calculates the new coords of a ball after the hit of a box
*/
void CMasterofPuppets::CalcHitwithBox(int x,int y,int w,int h,CBall *ball,int hit_mask)
{
	/* check whether there are walls hitted */
	if (!hit_mask) return;
	
	/*
		Find the walls which possibly the ball hits
	*/
	if (ball->speedy() >= 0)
	{
		if (ball->speedx() >=0 )
		{
			if (hit_mask & 16) { ball->MirrorX();ball->MirrorY();return; }
			if (hit_mask & 8 ) 
			{ 
				ball->x += ball->speedx(); 
				ball->y = 2*(y - ball->y - ball->radius) - ball->speedy() + ball->y;
				ball->MirrorY();
				return;
			}
			if (hit_mask & 1 )
			{ 
				ball->y += ball->speedy();
				ball->x = 2*(x - ball->x - ball->radius) - ball->speedx() + ball->x;
				ball->MirrorX();
				return;
			}
		}
		else
		{
			if (hit_mask & 128) { ball->MirrorX();ball->MirrorY();return; }
			if (hit_mask & 8 ) 
			{ 
				ball->x += ball->speedx(); 
				ball->y = 2*(y - ball->y - ball->radius) - ball->speedy() + ball->y;
				ball->MirrorY();
				return;
			}
			if (hit_mask & 2 )
			{ 
				ball->y += ball->speedy();
				ball->x = 2*(x + w - ball->x + ball->radius) - ball->speedx() + ball->x;
				ball->MirrorX();
				return;
			}
		}
	}
	else
	{
		if (ball->speedx() >=0 )
		{
			if (hit_mask & 32) {ball->MirrorX();ball->MirrorY();return; }
			if (hit_mask & 4 ) 
			{ 
				ball->x += ball->speedx(); 
				ball->y = 2*(y + h - ball->y + ball->radius) - ball->speedy() + ball->y;
				ball->MirrorY();
				return;
			}
			if (hit_mask & 1 )
			{ 
				ball->y += ball->speedy();
				ball->x = 2*(x - ball->x - ball->radius) - ball->speedx() + ball->x;
				ball->MirrorX();
				return;
			}
		}
		else
		{
			if (hit_mask & 64) { ball->MirrorX();ball->MirrorY();return; }
			if (hit_mask & 4 ) 
			{ 
				ball->x += ball->speedx(); 
				ball->y = 2*(y + h - ball->y + ball->radius) - ball->speedy() + ball->y;
				ball->MirrorY();
				return;
			}
			if (hit_mask & 2 )
			{ 
				ball->y += ball->speedy();
				ball->x = 2*(x + w - ball->x + ball->radius) - ball->speedx() + ball->x;
				ball->MirrorX();
				return;
			}
		}
	}
}

/*
	Calculates the new coords of a ball after the hit of a player
	TODO : Performs some more steering which is not done when hitting a box
*/
void CMasterofPuppets::CalcHitwithPlayer(int x,int y,int w,int h,CBall *ball,int hit_mask)
{
	/* check whether there are walls hitted */
	if (!hit_mask) return;
	
	/*
		Find the walls which possibly the ball hits
	*/
	if (ball->speedy() >= 0)
	{
		if (ball->speedx() >=0 )
		{
			if (hit_mask & 16) { ball->MirrorX();ball->MirrorY();return; }
			if (hit_mask & 8 ) 
			{ 
				ball->x += ball->speedx(); 
				ball->MirrorYKoef(x,y,w,h);
				return;
			}
			if (hit_mask & 1 )
			{ 
				ball->y += ball->speedy();
				ball->MirrorXKoef(x,y,w,h);
				return;
			}
		}
		else
		{
			if (hit_mask & 128) { ball->MirrorX();ball->MirrorY();return; }
			if (hit_mask & 8 ) 
			{ 
				ball->x += ball->speedx(); 
				ball->MirrorYKoef(x,y,w,h);
				return;
			}
			if (hit_mask & 2 )
			{ 
				ball->y += ball->speedy();
				ball->MirrorXKoef(x,y,w,h);
				return;
			}
		}
	}
	else
	{
		if (ball->speedx() >=0 )
		{
			if (hit_mask & 32) {ball->MirrorX();ball->MirrorY();return; }
			if (hit_mask & 4 ) 
			{ 
				ball->x += ball->speedx(); 
				ball->MirrorYKoef(x,y,w,h);
				return;
			}
			if (hit_mask & 1 )
			{ 
				ball->y += ball->speedy();
				ball->MirrorXKoef(x,y,w,h);
				return;
			}
		}
		else
		{
			if (hit_mask & 64) { ball->MirrorX();ball->MirrorY();return; }
			if (hit_mask & 4 ) 
			{ 
				ball->x += ball->speedx(); 
				ball->MirrorYKoef(x,y,w,h);
				return;
			}
			if (hit_mask & 2 )
			{ 
				ball->y += ball->speedy();
				ball->MirrorXKoef(x,y,w,h);
				return;
			}
		}
	}
}

void CMasterofPuppets::CheckBonusTake(CPlayer *player,std::list<CObject*> *objects,CBlockMap *map)
{
	for (std::list<CObject*>::iterator inter = objects->begin();inter != objects->end();inter++)
		if (strcmp((*inter)->Identify(),"CBonus") == 0)
		{
			/* The object is bonus, so try to detect collusion with the player */
			if (OverlapRects(player->x,player->y + player->height,player->x + player->width,player->y,(*inter)->getX(),(*inter)->getY() + 20,(*inter)->getX() + 50,(*inter)->getY()))
			{
				CFlyingText *text = new CFlyingText((*inter)->getX(),(*inter)->getY(),((CBonus*)(*inter))->getName(),"",makecol(0,255,0),0,-1,5,0);
				((CBonus*)(*inter))->GetBonus(player);
				objects->push_front(text);
				(*inter)->exists = false;
			}
			else /* Check whether the block is inside the map */
				if (!OverlapRects((*inter)->getX(),(*inter)->getY() + 20,(*inter)->getX() + 50,(*inter)->getY(),0,map->getRealHeight(),map->getRealWidth(),0))
					(*inter)->exists = false;
		}
}

/*
	This controls the correct movement of the ball and the player on the map
*/
int CMasterofPuppets::Control(CPlayer *player,CBlockMap *map,CBall *ball,std::list<CObject*> *objects,int tick)
{
	int mask,i,j;
	int curr_block_x = (int)(ball->x / map->getBlockWidth());
	int curr_block_y = (int)(ball->y / map->getBlockHeight());
	/*
		First clear the mess made by all stuff
	*/
	/* Check whether the paddle is in the map */
	if (player->x+player->width > map->getRealWidth())
	{
		if (ball->is_OnPad()) 
				ball->setX(ball->getX() - (player->x + player->width - map->getRealWidth()));
		player->x = map->getRealWidth() - player->width;
	}
	if (player->x < 0)
	{
		if (ball->is_OnPad())
				ball->setX(ball->getX() - player->x);
		player->x = 0;
	}
	
	/* Check whether it is time to process the ball */
	if (tick%(TICKS_PER_FRAME/ball->getSpeed()) == 0)
	{
	/*
		Block detection check
	*/
		for (i = curr_block_x - 1; i <= curr_block_x + 1;i++)
			for(j = curr_block_y - 1;j <= curr_block_y + 1;j++)
				if (!(i == curr_block_x && j == curr_block_y) && i < map->getWidth() && j < map->getHeight() && i >= 0 && j >=0)
				{
					if (map->getBlock(i,j) && (mask = is_box_hit(i*map->getBlockWidth(),j*map->getBlockHeight(),map->getBlockWidth(),map->getBlockHeight(),ball)))
					{
						/*
							Try to generate bonus
						*/
						if (map->getBlock(i,j)->isBonusGiver())
						{
							if ((rand() % 100 + 1) <= player->getBonusRate())
							{
								CBonus *obj = new CBonus(i*map->getBlockWidth(),j*map->getBlockHeight());
								objects->push_front(obj);
							}
						}
						if (map->getBlock(i,j)->isPointsGiver())
						{
							char text[10];
							player->setHit();
							sprintf(text,"%d +",10 + player->bonus_points);
							CFlyingText *t = new CFlyingText((int)ball->x,(int)ball->y,text,"",makecol(0,255,0),0,-2,5,0);
							player->incScore(10 + player->bonus_points);
							map->Hit(i,j,ball);
							objects->push_front(t);
						}
						if (!player->is_Penetrating()) CalcHitwithBox(i*map->getBlockWidth(),j*map->getBlockHeight(),map->getBlockWidth(),map->getBlockHeight(),ball,mask);
						goto end;
					}
				}
		end:
		/*
			Player detection check
		*/
		if (mask = is_box_hit(player->x,player->y,player->width,player->height,ball))
				CalcHitwithPlayer(player->x,player->y,player->width,player->height,ball,mask);

		/*           
			Move the ball && check wall collusion
		*/
		CheckBallWallCollusion(ball,map);
	}
}

int CMasterofPuppets::OverlapRects(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
	if (x1 <= x4 && x2 >= x3 && y1 >= y4 && y2 <= y3) return 1;
	return 0;
}

void CMasterofPuppets::CheckBallWallCollusion(CBall *ball,CBlockMap *map)
{
	if (ball->is_OnPad()) return;
	
	if (ball->x + ball->speedx() > map->getRealWidth() - ball->getRadius())
	{
		if (ball->getOwner()->solid_walls & 2)
		{
			ball->setX(2*(map->getRealWidth() - ball->getRadius() - ball->getX()) - ball->speedx() + ball->getX());
			ball->MirrorX();
		}
		else
		{
			ball->getOwner()->RemoveBall(ball);
			return;
		}
	}
	else
		if (ball->getX() + ball->speedx() < 0 + ball->getRadius())
		{
			if (ball->getOwner()->solid_walls & 1)
			{
				ball->setX(2*(ball->getRadius() - ball->getX()) - ball->speedx() + ball->getX());
				ball->MirrorX();
			}
			else
			{
				ball->getOwner()->RemoveBall(ball);
				return;
			}
		}
		else ball->MoveX();

	if (ball->getY()+ball->speedy() > map->getRealHeight() - ball->getRadius())
	{
		if (ball->getOwner()->solid_walls & 4)
		{
			ball->setY(2*(map->getRealHeight() - ball->getRadius() - ball->getY()) - ball->speedy() + ball->getY());
			ball->MirrorY();
		}
		else
		{
			ball->getOwner()->RemoveBall(ball);
			return;
		}
	}
	else
		if (ball->getY() + ball->speedy() < 0 + ball->getRadius()) /*return 0; // Game over*/
		{
			if (ball->getOwner()->solid_walls & 8)
			{
				ball->setY(2*(ball->getRadius()-ball->getY())-ball->speedy()+ball->getY());
				ball->MirrorY();
			}
			else
			{
				ball->getOwner()->RemoveBall(ball);
				return;
			}
		}
		else ball->MoveY();
}
