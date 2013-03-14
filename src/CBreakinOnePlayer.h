/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   Encapsulates a single player game                                     *
 *                                                                         *
 *   $Id: CBreakinOnePlayer.h,v 1.14 2003/12/30 12:12:05 valo Exp $         *
 ***************************************************************************/

#ifndef _CBREAKINONEPLAYER_H_
#define _CBREAKINONEPLAYER_H_

#include "CBall.h"
#include "CBlockMap.h"
#include "CPlayer.h"
#include "CAllegroDisplay.h"
#include "CMasterofPuppets.h"
#include <allegro.h>
#include <string.h>
#include "CObject.h"
#include "CFlyingText.h"
#include <list>
#include "CHallOfFame.h"

/**
 * 
 * Valentin Mihov
 **/
 
extern volatile int fps;
extern volatile int curr_frames,target_frames;
extern void frame_counter();
extern void frame_leader();

class CBreakinOnePlayer
{

public:
  CBreakinOnePlayer();
  ~CBreakinOnePlayer();
  
  void ProcessEvents();
  void DrawScene(BITMAP *buffer,int x,int y);
  int isGameOver() { return is_gameover; }
  void SetPlayerName(char *name) { strcpy(player->name,name); }
  void UpdateBestScores() { CHallOfFame::AddEntry(player->name,player->getScore()); }
  
protected:
  CBlockMap *map;
  CPlayer *player;
  int is_gameover;
  std::list<CObject*> objects;
  int die_penalty;
  
  char campain[100][512];
  int level_br;
  int curr_level;
  
  void ClearUnusedObjects();
  void LoadNextLevel();
  
  friend class CMasterofPuppets;
};

#endif
