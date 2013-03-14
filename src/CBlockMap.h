/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   Hold information about the blocks on the map,ex. health, location     *
 *                                                                         *
 *   $Id: CBlockMap.h,v 1.5 2003/12/26 17:51:11 valo Exp $                                                                  *
 ***************************************************************************/

#ifndef _CBLOCKMAP_H_
#define _CBLOCKMAP_H_

#include "CBlock.h"
#include "CBall.h"
#include <stdlib.h>
#include <allegro.h>

/**
 * 
 * Valentin Mihov
 **/
class CBlockMap
{

public:
  CBlockMap(char *level_filename);
  ~CBlockMap();
  
  void Draw(BITMAP *buffer);
  void Hit(int x,int y,CBall *ball);
  void ProcessEvents();
  
  int getWidth();
  int getHeight();
  int getRealWidth();
  int getRealHeight();
  int getBlockWidth()  { return block_w; }
  int getBlockHeight() { return block_h; }
  CBlock* getBlock(int w,int h) { return blocks[w][h]; }
  int is_Finished()    { return finished; }
  
protected:
  CBlock ***blocks;
  int width,height;
  int block_w,block_h;
  int finished;
  
};

#endif
