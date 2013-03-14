/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CBreakinOnePlayer.cpp,v 1.16 2003/12/30 12:12:05 valo Exp $       *
 ***************************************************************************/

#include "CBreakinOnePlayer.h"

CBreakinOnePlayer::CBreakinOnePlayer()
{
	// Load the singleplayer campain
	set_config_file(SINGLEPLAYER_CAMPAIN_FILENAME);
	level_br = get_config_int(NULL,"level_count",0);
	for (int i = 0;i < level_br;i++)
	{
		char entry[255];
		sprintf(entry,"level_filename_%d",i);
		strcpy(campain[i],get_config_string(NULL,entry,NULL));
	}
	curr_level = 0;
	
	if (!level_br)
	{
		is_gameover = TRUE;
		return;
	}
	map = new CBlockMap(campain[0]);
	player = new CPlayer(map->getRealWidth()/2,map->getRealHeight()-15,PLAYER1_CONFIG_FILE,187);
	set_config_file(DEFAULT_PLAYER_CONFIG_FILE);
	die_penalty = get_config_int(NULL,"die_penalty",25);
	player->AddBall();
	is_gameover = 0;
}


CBreakinOnePlayer::~CBreakinOnePlayer()
{
	delete map;
	delete player;
}

void CBreakinOnePlayer::DrawScene(BITMAP *buffer2,int x,int y)
{
	if (is_gameover) return;
	// Draw the map
	map->Draw(buffer2);
	
	// Draw the objects
	for (std::list<CObject*>::iterator inter = objects.begin();inter != objects.end();inter++)
		(*inter)->Draw(buffer2);
		
	// Draw the player
	player->Draw(buffer2);
	
	// Draw the balls
	for (std::list<CBall*>::iterator inter = player->balls.begin();inter != player->balls.end();inter++)
		(*inter)->Draw(buffer2);
		
	// Draw some debug info
	textprintf(buffer2,font,0,0,makecol(255,255,255),"%d %s",fps,player->name);
	player->DrawStatusBar(buffer2,0,SCREEN_H - 50);
}

void CBreakinOnePlayer::ProcessEvents()
{
	std::list<CBall*>::iterator curr;
	if (is_gameover) return;
	/* Make many ticks and move the ball with very low speed in order to calculate accurate */
	/* Start of the processing of the info */
	for (int i = 0;i < TICKS_PER_FRAME;i++)
	{
		if (i%(TICKS_PER_FRAME/player->getSpeed()) == 0) player->ProcessEvents();
		ClearUnusedObjects();
		curr = player->balls.begin();
		while (curr != player->balls.end())
		{
			std::list<CBall*>::iterator tmp = curr;
			tmp++;
			(*curr)->ProcessEvents();
			CMasterofPuppets::Control(player,map,*curr,&objects,i);
			curr = tmp;
		}
		// Check whether the player is alive
		if (player->balls.size() == 0)
		{
			int tmp = (player->getScore()*(100 - die_penalty))/100;
			char name[255];
			char str[20];
			sprintf(str,"-%d",player->getScore() - tmp);
			CFlyingText *t = new CFlyingText((int)player->getX() + player->getWidth()/2,(int)player->getY() - (int)player->getHeight(),"You die!!!",str,makecol(0,255,0),0,-2,5,0);
			objects.push_front(t);
			strcpy(name,player->name);
			delete player;
			player = new CPlayer(map->getRealWidth()/2,map->getRealHeight() - 15,PLAYER1_CONFIG_FILE,187);
			strcpy(player->name,name);
			player->AddBall();
			player->incScore(tmp);
		}
	}
	
	for (std::list<CObject*>::iterator curr = objects.begin();curr != objects.end();curr++)
		(*curr)->Move();
	CMasterofPuppets::CheckBonusTake(player,&objects,map);
	
	map->ProcessEvents();
	/* Checks whether the current map is over and if so load the next */
	if (map->is_Finished()) LoadNextLevel();
}

void CBreakinOnePlayer::ClearUnusedObjects()
{
	std::list<CObject*>::iterator curr;
	curr = objects.begin();
	while(curr != objects.end())
	{
		if (!((*curr)->does_exist()))
		{
			std::list<CObject*>::iterator tmp = curr;
			tmp++;
			delete (*curr);
			objects.erase(curr);
			curr = tmp;
		}
		else curr++;
	}
}

void CBreakinOnePlayer::LoadNextLevel()
{
	// Recreate the player
	int tmp = player->getScore();
	char name[255];
	strcpy(name,player->name);
	delete player;
	player = new CPlayer(map->getRealWidth()/2,map->getRealHeight()-15,PLAYER1_CONFIG_FILE,187);
	strcpy(player->name,name);
	player->incScore(tmp);
	player->AddBall();
	
	// Clear all objects
	objects.clear();
	
	// Load the new map
	delete map;
	map = NULL;
	curr_level++;
	// Check whether the campain is over
	if (curr_level >= level_br)
	{
		is_gameover = TRUE;
		return;
	}
	map = new CBlockMap(campain[curr_level]);
}

