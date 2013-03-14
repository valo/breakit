#ifndef _CHALLOFFAME_H_
#define _CHALLOFFAME_H_

#include <allegro.h>
#include <alfont.h>
#include "CPanel.h"
#include <stdio.h>
#include <string.h>

/**
 * 
 * Valentin Mihov
 **/
class CHallOfFame
{
private:
  char names[10][255];
  int scores[10];
  
  CPanel panel;
  ALFONT_FONT *font;
  
  void Save();


public:
  CHallOfFame();
  ~CHallOfFame();
  
  void Draw(BITMAP *buffer,int x,int y);
  
  static void AddEntry(char name[255],int score);
};

#endif
