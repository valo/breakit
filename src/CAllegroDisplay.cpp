/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CAllegroDisplay.cpp,v 1.10 2003/12/30 12:12:05 valo Exp $                     *
 ***************************************************************************/

#include "CAllegroDisplay.h"


CAllegroDisplay::CAllegroDisplay(int width,int height,int color_depth,char *error_file)
{
  /*
    Init the error log handler
  */
  error_log = fopen(error_file,"at");
  if (error_file == NULL) 
  {
    error_log = stdout;
    PrintError("Error opening error_log file!!!\n");
  }
  
  /*
    Init allegro graphic library
  */
  allegro_init();
  install_timer();
  install_keyboard();
  install_mouse();
  alfont_init();
  
  show_mouse(NULL);
  /*
    Try to init display resolution
  */
  set_color_depth(color_depth);
  if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,width,height,0,0)) fatalError(allegro_error);
  set_display_switch_mode(SWITCH_PAUSE);
  srandom(time(0));
}


CAllegroDisplay::~CAllegroDisplay()
{
  fclose(error_log);
  alfont_exit();
  allegro_exit();
}

void CAllegroDisplay::fatalError(char *msg)
{
  PrintError(msg);
  exit(0);
}

void CAllegroDisplay::PrintError(char *msg)
{
  fprintf(error_log,msg);
}
