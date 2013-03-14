/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   Interface used for drawing on the screen with allegro  library        *
 *                                                                         *
 *   $Id: CAllegroDisplay.h,v 1.3 2003/12/30 12:12:05 valo Exp $           *
 ***************************************************************************/

#ifndef _CALLEGRODISPLAY_H_
#define _CALLEGRODISPLAY_H_

#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <alfont.h> 

/**
 * 
 * Valentin Mihov
 **/
class CAllegroDisplay
{

public:
  /*
    Constructor, which initializes the resolution and the color depth
  */
  CAllegroDisplay(int width,int height,int color_depth,char *error_file);
  ~CAllegroDisplay();
  
protected:

  FILE *error_log;
  
private:

  void PrintError(char *msg);
  void fatalError(char *msg);
};

#endif
