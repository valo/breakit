/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CMainMenu.cpp,v 1.6 2003/12/30 12:12:05 valo Exp $               *
 ***************************************************************************/

#include "CMainMenu.h"


CMainMenu::CMainMenuBackground::CMainMenuBackground()
{
	back = load_bitmap("/home/valo/Projects/breakin/graphics/background.bmp",NULL);
	fast_back = get_compiled_sprite(back,0);
	tmp_back = NULL;
}

CMainMenu::CMainMenuBackground::~CMainMenuBackground()
{
	destroy_bitmap(back);
	destroy_compiled_sprite(fast_back);
}

void CMainMenu::CMainMenuBackground::Draw(BITMAP *buffer)
{
	if (tmp_back) /*blit(tmp_back,buffer,0,0,0,0,tmp_back->w,tmp_back->h)*/;
	else draw_compiled_sprite(buffer,fast_back,0,0);
}

CMainMenu::CCredits::CCredits()
{
	font = alfont_load_font(GUI_FONT_FILENAME);
	alfont_set_font_size(font,30);
	title_font = alfont_load_font(GUI_FONT_FILENAME);
	alfont_set_font_size(title_font,40);
}

CMainMenu::CCredits::~CCredits()
{
	alfont_destroy_font(font);
	alfont_destroy_font(title_font);
}

void CMainMenu::CCredits::Draw(BITMAP *buffer)
{
	alfont_textout_centre_aa_ex(buffer,title_font,"Programmers",x,y,text_color,-1);
	alfont_textout_centre_aa_ex(buffer,font,"Valentin Mihov",x,y + alfont_get_font_height(title_font) + 5,text_color,-1);
	alfont_textout_centre_aa_ex(buffer,title_font,"Graphic Designers",x,y + alfont_get_font_height(font) + alfont_get_font_height(title_font) + 15,text_color,-1);
	alfont_textout_centre_aa_ex(buffer,font,"Valentin Mihov",x,y + alfont_get_font_height(font) + 2*alfont_get_font_height(title_font) + 15,text_color,-1);
}

CMainMenu::CMainMenu()
{
	/* New game button */
	btn_new_game.w = 300;
	btn_new_game.h = 40;
	btn_new_game.x = SCREEN_W/2 - btn_new_game.w/2;
	btn_new_game.y = 250;
	btn_new_game.color = makecol(158,139,255);
	btn_new_game.border_color = makecol(88,77,141);
	btn_new_game.text_color = makecol(237,67,52);
	btn_new_game.caption = "New Game";
	btn_new_game.over_trans = 200;
	btn_new_game.idle_trans = 150;
	
	/* Options button */
	btn_options.w = 300;
	btn_options.h = 40;
	btn_options.x = SCREEN_W/2 - btn_options.w/2;
	btn_options.y = 320;
	btn_options.color = makecol(158,139,255);
	btn_options.border_color = makecol(88,77,141);
	btn_options.text_color = makecol(237,67,52);
	btn_options.caption = "Options";
	btn_options.over_trans = 200;
	btn_options.idle_trans = 150;

	/* Hall of fame button */
	btn_halloffame.w = 300;
	btn_halloffame.h = 40;
	btn_halloffame.x = SCREEN_W/2 - btn_halloffame.w/2;
	btn_halloffame.y = 390;
	btn_halloffame.color = makecol(158,139,255);
	btn_halloffame.border_color = makecol(88,77,141);
	btn_halloffame.text_color = makecol(237,67,52);
	btn_halloffame.caption = "Hall of Fame";
	btn_halloffame.over_trans = 200;
	btn_halloffame.idle_trans = 150;

	/* Credits button */
	btn_credits.w = 300;
	btn_credits.h = 40;
	btn_credits.x = SCREEN_W/2 - btn_credits.w/2;
	btn_credits.y = 460;
	btn_credits.color = makecol(158,139,255);
	btn_credits.border_color = makecol(88,77,141);
	btn_credits.text_color = makecol(237,67,52);
	btn_credits.caption = "Credits";
	btn_credits.over_trans = 200;
	btn_credits.idle_trans = 150;
	
	/* Quit button */
	btn_quit.w = 200;
	btn_quit.h = 40;
	btn_quit.x = SCREEN_W - btn_quit.w - 10;
	btn_quit.y = SCREEN_H - 40 - 10;
	btn_quit.color = makecol(158,139,255);
	btn_quit.border_color = makecol(88,77,141);
	btn_quit.text_color = makecol(237,67,52);
	btn_quit.caption = "Quit";
	btn_quit.over_trans = 200;
	btn_quit.idle_trans = 150;

	/* Singleplayer button */
	btn_singleplayer.w = 300;
	btn_singleplayer.h = 40;
	btn_singleplayer.x = SCREEN_W/2 - btn_singleplayer.w/2;
	btn_singleplayer.y = 250;
	btn_singleplayer.color = makecol(158,139,255);
	btn_singleplayer.border_color = makecol(88,77,141);
	btn_singleplayer.text_color = makecol(237,67,52);
	btn_singleplayer.caption = "Single Player";
	btn_singleplayer.over_trans = 200;
	btn_singleplayer.idle_trans = 150;
	
	/* Multiplayer button */
	btn_multiplayer.w = 300;
	btn_multiplayer.h = 40;
	btn_multiplayer.x = SCREEN_W/2 - btn_multiplayer.w/2;
	btn_multiplayer.y = 320;
	btn_multiplayer.color = makecol(158,139,255);
	btn_multiplayer.border_color = makecol(88,77,141);
	btn_multiplayer.text_color = makecol(237,67,52);
	btn_multiplayer.caption = "Multiplayer";
	btn_multiplayer.over_trans = 200;
	btn_multiplayer.idle_trans = 150;
		
	/* Back button */
	btn_back.w = 200;
	btn_back.h = 40;
	btn_back.x = SCREEN_W - btn_back.w - 10;
	btn_back.y = SCREEN_H - 40 - 10;
	btn_back.color = makecol(158,139,255);
	btn_back.border_color = makecol(88,77,141);
	btn_back.text_color = makecol(237,67,52);
	btn_back.caption = "Back";
	btn_back.over_trans = 200;
	btn_back.idle_trans = 150;
	
	/* Single player game menu */
	btn_exit_program.w = 300;
	btn_exit_program.h = 40;
	btn_exit_program.x = SCREEN_W/2 - btn_exit_program.w/2;
	btn_exit_program.y = 250;
	btn_exit_program.color = makecol(158,139,255);
	btn_exit_program.border_color = makecol(88,77,141);
	btn_exit_program.text_color = makecol(237,67,52);
	btn_exit_program.caption = "Exit Program";
	btn_exit_program.over_trans = 200;
	btn_exit_program.idle_trans = 150;
	btn_end_game.w = 300;
	btn_end_game.h = 40;
	btn_end_game.x = SCREEN_W/2 - btn_end_game.w/2;
	btn_end_game.y = 320;
	btn_end_game.color = makecol(158,139,255);
	btn_end_game.border_color = makecol(88,77,141);
	btn_end_game.text_color = makecol(237,67,52);
	btn_end_game.caption = "End Game";
	btn_end_game.over_trans = 200;
	btn_end_game.idle_trans = 150;
	btn_resume.w = 300;
	btn_resume.h = 40;
	btn_resume.x = SCREEN_W/2 - btn_resume.w/2;
	btn_resume.y = 390;
	btn_resume.color = makecol(158,139,255);
	btn_resume.border_color = makecol(88,77,141);
	btn_resume.text_color = makecol(237,67,52);
	btn_resume.caption = "Resume";
	btn_resume.over_trans = 200;
	btn_resume.idle_trans = 150;
	pnl_back.border_color = makecol(88,77,141);
	pnl_back.caption = "Game Menu";
	pnl_back.caption_color = makecol(237,67,52);
	pnl_back.color = makecol(253,208,74);
	pnl_back.x = 230;
	pnl_back.y = 200;
	pnl_back.w = SCREEN_W - 465;
	pnl_back.h = SCREEN_H - 350;
	pnl_back.alpha = 200;
	
	/* Init credits */
	credits.x = SCREEN_W/2;
	credits.y = 250;
	credits.text_color = 0;
	
	edt_singleplayer_name.w = 300;
	edt_singleplayer_name.h = 40;
	edt_singleplayer_name.x = SCREEN_W/2 - edt_singleplayer_name.w/2;
	edt_singleplayer_name.y = 320;
	edt_singleplayer_name.border_color = makecol(88,77,141);
	edt_singleplayer_name.text_color = makecol(0,0,0);
	edt_singleplayer_name.color = makecol(253,208,74);
	strcpy(edt_singleplayer_name.text,"Player1");
	pnl_singleplayer_name_back.alpha = 50;
	pnl_singleplayer_name_back.border_color = makecol(88,77,141);
	pnl_singleplayer_name_back.caption = "Enter your name:";
	pnl_singleplayer_name_back.caption_color = makecol(237,67,52);
	pnl_singleplayer_name_back.x = SCREEN_W/2 - edt_singleplayer_name.w/2 - 60;
	pnl_singleplayer_name_back.y = 250;
	pnl_singleplayer_name_back.w = 420;
	pnl_singleplayer_name_back.h = 150;

	curr_menu = 1;
	
}


CMainMenu::~CMainMenu()
{
}

void CMainMenu::Show()
{
	CBreakinOnePlayer *game = NULL;
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);
	char player_name1[255];
	CHallOfFame *hall = new CHallOfFame();
	/* Here should be the main loop of the GUI frontend */
	install_int_ex(frame_counter,SECS_TO_TIMER(1));
	install_int_ex(frame_leader,BPS_TO_TIMER(FRAMES_PER_SEC));
	while (curr_menu)
	{
		switch (curr_menu)
		{
			case 1 :
			/* Main menu */
			
				/* Process events */
				if (btn_new_game.clicked)
				{
					btn_new_game.clicked = 0;
					mouse_b = 0;
					curr_menu = 2;
					break;
				}
				if (btn_halloffame.clicked)
				{
					btn_halloffame.clicked = 0;
					mouse_b = 0;
					curr_menu = 9;
					break;
				}
				if (btn_credits.clicked)
				{
					btn_credits.clicked = 0;
					mouse_b = 0;
					curr_menu = 3;
					break;
				}
				if (btn_quit.clicked) curr_menu = 0;
				
				/* Draw everything */
				if (target_frames >= curr_frames)
				{
					btn_options.ProcessEvents();
					btn_new_game.ProcessEvents();
					btn_halloffame.ProcessEvents();
					btn_credits.ProcessEvents();
					btn_quit.ProcessEvents();
					
					back.Draw(buffer);
					btn_options.Draw(buffer);
					btn_new_game.Draw(buffer);
					btn_halloffame.Draw(buffer);
					btn_credits.Draw(buffer);
					btn_quit.Draw(buffer);
				}
			break;
			case 2 :
			/* New game menu */
			
				/* Process events */
				if (btn_singleplayer.clicked)
				{
					btn_singleplayer.clicked = 0;
					mouse_b = 0;
					curr_menu = 8;
				}
				if (btn_back.clicked || key[KEY_ESC])
				{
					btn_back.clicked = FALSE;
					mouse_b = 0;
					key[KEY_ESC] = 0;
					curr_menu = 1;
				}
				/* Draw everything */
				if (target_frames >= curr_frames)
				{
					btn_singleplayer.ProcessEvents();
					btn_multiplayer.ProcessEvents();
					btn_back.ProcessEvents();
					
					back.Draw(buffer);
					btn_singleplayer.Draw(buffer);
					btn_multiplayer.Draw(buffer);
					btn_back.Draw(buffer);
				}
			break;
			case 3 :
			/* Credits */
			
				/* Process events */
				if (btn_back.clicked || key[KEY_ESC])
				{
					btn_back.clicked = 0;
					mouse_b = 0;
					key[KEY_ESC] = 0;
					curr_menu = 1;
				}
				/* Draw everything */
				if (target_frames >= curr_frames)
				{
					btn_back.ProcessEvents();
					
					back.Draw(buffer);
					btn_back.Draw(buffer);
					credits.Draw(buffer);
				}
			break;
			case 5:
			/* Single player */
			
				/* Check whether the game window is initialized */
				if (!game)
				{
					game = new CBreakinOnePlayer();
					game->SetPlayerName(player_name1);
				}
				
				/* Process events */
				if (game->isGameOver())
				{
					curr_menu = 9;  // Goto the hall of fame
					game->UpdateBestScores();
					delete hall;
					hall = new CHallOfFame();
					break;
				}
				if (key[KEY_ESC])
				{
					key[KEY_ESC] = 0;
					curr_menu = 7;
					break;
				}
				
				/* Draw all */
				if (target_frames >= curr_frames)
				{
					// The game must update only FRAMES_PER_SEC time a sec.
					game->ProcessEvents();
					clear(buffer);
					game->DrawScene(buffer,0,0);
				}
			break;
			case 7:
			/* Single player game menu */
			
				/* If the screen is not captured then capture it */
				if (back.tmp_back == NULL)
				{
					back.tmp_back = create_bitmap(SCREEN_W,SCREEN_H);
					blit(screen,back.tmp_back,0,0,0,0,SCREEN_W,SCREEN_H);
				}
				
				/* Process events */
				if (btn_exit_program.clicked)
				{
					curr_menu = 0;
					btn_exit_program.clicked = 0;
					mouse_b = 0;
					destroy_bitmap(back.tmp_back);
					back.tmp_back = NULL;
				}
				if (btn_end_game.clicked)
				{
					curr_menu = 1;
					btn_end_game.clicked = 0;
					mouse_b = 0;
					destroy_bitmap(back.tmp_back);
					back.tmp_back = NULL;
					delete game;
					game = NULL;
					break;
				}
				if (btn_resume.clicked || key[KEY_ESC])
				{
					curr_menu = 5;
					btn_resume.clicked = 0;
					mouse_b = 0;
					destroy_bitmap(back.tmp_back);
					back.tmp_back = NULL;
					break;
				}
				
				/* Draw everything */
				if (target_frames >= curr_frames)
				{
					btn_exit_program.ProcessEvents();
					btn_end_game.ProcessEvents();
					btn_resume.ProcessEvents();
					
					back.Draw(buffer);
					pnl_back.Draw(buffer);
					btn_exit_program.Draw(buffer);
					btn_end_game.Draw(buffer);
					btn_resume.Draw(buffer);
				}
			break;
			case 8:
				// Asks for the name of the player
				edt_singleplayer_name.ProcessEvents();
				if (btn_back.clicked || key[KEY_ESC])
				{
					btn_back.clicked = FALSE;
					key[KEY_ESC] = 0;
					mouse_b = 0;
					curr_menu = 2;
					break;
				}
				if (key[KEY_ENTER])
				{
					strcpy(player_name1,edt_singleplayer_name.text);
					key[KEY_ENTER] = 0;
					curr_menu = 5;
					break;
				}
				
				if (target_frames >= curr_frames)
				{
					btn_back.ProcessEvents();
					
					back.Draw(buffer);
					pnl_singleplayer_name_back.Draw(buffer);
					edt_singleplayer_name.Draw(buffer);
					btn_back.Draw(buffer);
				}
			break;
			case 9:
				// Hall of fame
				if (key[KEY_ENTER] || key[KEY_ESC])
				{
					key[KEY_ENTER] = 0;
					key[KEY_ESC] = 0;
					curr_menu = 1;
					break;
				}
				
				if (target_frames >= curr_frames)
				{
					back.Draw(buffer);
					hall->Draw(buffer,140,220);
				}
			break;
		}
		if (target_frames >= curr_frames)
		{
			textprintf(buffer,font,0,0,makecol(255,255,255),"%d",fps);
			acquire_screen();
//			vsync();
			show_mouse(buffer);
			blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
			show_mouse(NULL);
			release_screen();
			
			curr_frames++;
		}
	}
	end:
	delete game;
	delete hall;
	remove_int(frame_counter);
	remove_int(frame_leader);
}
