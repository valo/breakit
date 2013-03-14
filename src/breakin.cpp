#include "defines.h"
#include <stdio.h>
#include <allegro.h>
#include "CAllegroDisplay.h"
#include "CBreakinOnePlayer.h"
#include "CMainMenu.h"

volatile int curr_frames = 0;
volatile int fps = 0;
volatile int target_frames;
volatile int global_timer = 0;
BITMAP *blocks[MAXHEALTH];

void frame_counter()
{
	fps = curr_frames;
	curr_frames = 0;
	target_frames = 0;
}

void frame_leader()
{
	target_frames++;
	global_timer++;
}

int my_trace(const char *msg)
{
	printf(msg);
	fflush(stdout);
	return 1;
}

void LoadAllMedia()
{
	int i;

	set_color_conversion(COLORCONV_TOTAL);
	for (i = 0;i < MAXHEALTH - 1;i++)
	{
		char filename[50];
		sprintf(filename,"/home/valo/Projects/breakin/graphics/block-strong%d.bmp",i+1);
		blocks[i] = load_bitmap(filename,NULL);
	}
}

int main(int argc, char *argv[])
{
  register_trace_handler(my_trace);
  CAllegroDisplay *display = new CAllegroDisplay(800,600,16,"errors.log");
  LoadAllMedia();
  CMainMenu menu;
  menu.Show();
  delete display;
  return 0;
}
END_OF_MAIN()
