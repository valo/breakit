/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CBlockMap.cpp,v 1.6 2003/12/26 17:51:11 valo Exp $                                                                  *
 ***************************************************************************/

#include "CBlockMap.h"

CBlockMap::CBlockMap(char *level_filename)
{
	FILE *f = fopen(level_filename,"rt");
	int a,i,j;
	fscanf(f,"%d%d",&width,&height);
	fscanf(f,"%d%d",&block_w,&block_h);
	blocks = new CBlock**[width];
	for (i = 0;i < width;i++)
		blocks[i] = new CBlock*[height];
	for (i = 0;i < height;i++)
		for (j = 0;j < width;j++)
		{
			fscanf(f,"%d",&a);
			if (a) blocks[j][i] = new CBlock(a);
			else blocks[j][i] = NULL;
		}
	fclose(f);
	finished = 0;
}


CBlockMap::~CBlockMap()
{
	for (int i = 0;i < width;i++)
		delete[] blocks[i];
	delete[] blocks;
}

void CBlockMap::Draw(BITMAP *buffer)
{
	for (int i = 0;i < width;i++)
		for(int j = 0;j < height;j++)
			if (blocks[i][j]) blocks[i][j]->Draw(buffer,i*block_w,j*block_h,(i+1)*block_w-1,(j+1)*block_h-1);
}

void CBlockMap::Hit(int x,int y,CBall *ball)
{
	blocks[x][y]->Hit(ball);
	if (!blocks[x][y]->getHealth())
	{
		delete blocks[x][y];
		blocks[x][y] = NULL;
	}
}

int CBlockMap::getWidth()  { return width; }
int CBlockMap::getHeight() {  return height; }
int CBlockMap::getRealWidth() { return width*block_w; }
int CBlockMap::getRealHeight() { return height*block_h; }

void CBlockMap::ProcessEvents()
{
	int i,j;
	for (i = 0;i < width;i++)
		for (j = 0;j < height;j++)
			if (blocks[i][j] && !blocks[i][j]->isSolid()) { finished = 0; return; }
	finished = 1;
}
