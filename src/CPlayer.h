/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   This class holds info about a player's location, score etc.           *
 *                                                                         *
 *   $Id: CPlayer.h,v 1.10 2003/12/30 12:12:05 valo Exp $                   *
 ***************************************************************************/

#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "defines.h"
#include <allegro.h>
#include <alfont.h>
#include <list>
#include "CBall.h"

/**
 * 
 * Valentin Mihov
 **/
 extern volatile int global_timer;
 
class CPlayer
{

public:
  std::list<class CBall*> balls;
  int bonus_points;
  char name[255];
  
  CPlayer(int x,int y,char *key_bindings_file,int solid);
  ~CPlayer();
  
  void Draw(BITMAP *buffer);
  void DrawStatusBar(BITMAP *buffer,int x,int y);
  void ProcessEvents();
  
  /* Paddle speed modifiers */
  int getSpeed() { return move_speed;  }
  void incSpeed();
  void decSpeed();
  
  void AddBall();
  void RemoveBall(CBall*);
  
  /* Bonus rate modifiers */
  int getBonusRate() { return bonus_frequency; }
  void IncreaseBonusRate();
  void DecreaseBonusRate();
  
  /* Score modifiers */
  int getScore() { return score; }
  int incScore(int mod) { score = (score+mod)<0?0:score+mod; }
  int setHit();
  double SecsfromLastHit() { return (double)(global_timer - last_scored)/30; }
  
  /* Immortality methods */
  void setImmortal();
  void unsetImmortal();
  
  /* Penetration methods */
  int is_Penetrating(){ return penetrating;   }
  void setPenetration();
  void removePenetration();

  /* Speed modifiers */
  void IncreaseSpeed();
  void DecreaseSpeed();

  int getX()      { return x;      }
  int getY()      { return y;      }
  int getWidth()  { return width;  }
  int getHeight() { return height; }
  int getBallSpeed()  { return ball_speed;  }
  
protected:
  int x,y;
  int key_left,key_right,key_fire;
  int width,height;
  
  int move_speed;
  int default_move_speed;
  int speed_modifier;
  
  unsigned char solid_walls; // Bit mask storning which walls are solid and in high part default settings
  int default_width;
  
  int bonus_frequency,default_bonus_frequency;
  int more_bonuses_modifier,time_got_more_bonuses;
  int more_bonuses_duration;
  
  int score,last_scored;
  double fast_hit_max_time;
  
  int time_got_immortal;
  int immortal_time;
  
  bool penetrating;
  int time_got_penetration;
  int penetration_time;
  
  int ball_speed,default_ball_speed;
  int ball_speed_modifier;
  
  BITMAP *model;
  
  ALFONT_FONT *status_font1,*status_font2;
 
  
  friend class CMasterofPuppets;
  friend class CBreakinOnePlayer;
};

#endif
