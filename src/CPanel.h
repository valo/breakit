
#ifndef _CPANEL_H_
#define _CPANEL_H_

#include "CComponent.h"
#include <allegro.h>
#include <alfont.h>
#include "defines.h"

/**
 * 
 * Valentin Mihov
 **/
class CPanel : public CComponent
{

public:
  CPanel();
  ~CPanel();
  
  char* caption;
  int color,caption_color,border_color;
  int alpha;
  
  void Draw(BITMAP *buffer);
  
private:
  ALFONT_FONT *font;
};

#endif
