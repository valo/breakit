/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CMainMenu.h,v 1.5 2003/12/30 12:12:05 valo Exp $                                                                  *
 ***************************************************************************/

#ifndef _CMAINMENU_H_
#define _CMAINMENU_H_

#include "CButton.h"
#include "CPanel.h"
#include "CEditField.h"
#include "CBreakinOnePlayer.h"

extern volatile int curr_frames,target_frames;
extern void frame_counter();
extern void frame_leader();

/**
 * 
 * Valentin Mihov
 **/
class CMainMenu
{

	class CMainMenuBackground
	{
		public :
		CMainMenuBackground();
		~CMainMenuBackground();
		
		void Draw(BITMAP *buffer);
		
		BITMAP *tmp_back;
		
		private :
		BITMAP *back;
		COMPILED_SPRITE *fast_back;
	};

	class CCredits
	{
		public:
		int x,y;
		int text_color;
		
		CCredits();
		~CCredits();
		
		void Draw(BITMAP *buffer);
		
		private :
		ALFONT_FONT *font;
		ALFONT_FONT *title_font;
	};
	
public:
  CMainMenu();
  ~CMainMenu();

  void Show();

private:
  CMainMenuBackground back;
  CCredits credits;

  /* Curr menu : 
	0 - Quit; 
	1 - Main menu; 
	2 - New game menu; 
	3 - Credits; 
	4 - Options; 
	5 - Single Player; 
	6 - Multiplayer
	7 - Single player game menu
	8 - Top players
	9 - Ask for player's name before starting singleplayer
  */
  int curr_menu;

  /* Main menu */
  CButton btn_new_game,btn_options,btn_credits,btn_quit,btn_halloffame;

  /* New game buttons */
  CButton btn_singleplayer,btn_multiplayer;

  /* Back button */
  CButton btn_back;
  
  /* Single player game menu */
  CButton btn_resume,btn_end_game,btn_exit_program;
  CPanel pnl_back;
  
  /* Dialog for entering player's name in singleplayer */
  CEditField edt_singleplayer_name;
  CPanel pnl_singleplayer_name_back;
};

#endif
