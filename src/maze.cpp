//简单作图: 线条与线框图形
#include <graphics.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "../include/UnionFindSet.h"

//自定义颜色
#define  COLOR_WALL         BLACK
#define  COLOR_BACKGROUND   WHITE
#define  COLOR_TREE         DARKGRAY
#define  COLOR_LOCUS        RED

//迷宫大小设置
#define  MAZE_SIZE  10						//迷宫大小 10 x 10
#define  GRID_NUM   2 * MAZE_SIZE + 1		//迷宫格子数最大值(每行)
#define  STR_TOPICAL 20
//四个方向
#define DIRECTION_NUM 4
//定义四个方向的行进增量
int dx[DIRECTION_NUM] = { -1,  0, 1, 0 };
int dy[DIRECTION_NUM] = {  0, -1, 0, 1 };

enum BLOCK {
	BLOCK_BLANK = 0,
	BLOCK_WALL,
	BLOCK_PATH,
};

enum MazeStyle{
	MAZE_STYLE_GRID = 0,	//格子型
	MAZE_STYLE_WALL	= 1,	//围墙型
};
typedef struct{
	char topical[STR_TOPICAL];
	int scrWidth;
	int scrHeight;
	
} Canvas;

typedef struct {
	int size;
	int gridNum;
	int gridWidth;

	int StaLoc; //起点坐标
	int TerLoc; //终点坐标

	int grid[GRID_NUM][GRID_NUM];


} Maze;

Canvas cur_Canvas ={"迷宫", 0, 0};
Maze maze = {MAZE_SIZE, GRID_NUM, 30, 0, 99};


void initCanvas(Canvas*, Maze);
void initMaze(Maze*);
void fun(Maze* maze);
void drawMaze(Maze, MazeStyle);

int	main(void){
	srand(time(NULL));
	initCanvas(&cur_Canvas, maze);
	initMaze(&maze);
	fun(&maze);
	drawMaze(maze, MAZE_STYLE_WALL);

	getch();
	closegraph();
	return 0;
}

//创建迷宫
void initCanvas(Canvas* cur_Canvas, Maze maze){
	setinitmode(INIT_RENDERMANUAL);
	setcaption(cur_Canvas->topical);
	setbkmode(TRANSPARENT);
	//调整窗口大小
	cur_Canvas->scrWidth  = (maze.gridNum + 1) * maze.gridWidth;
	cur_Canvas->scrHeight = cur_Canvas->scrWidth;
	initgraph(cur_Canvas->scrWidth, cur_Canvas->scrHeight);
}

//迷宫初始化
void initMaze(Maze *maze){
	//初始化
	for (int i = 0; i < maze->gridNum; i++) 
		for (int j = 0; j < maze->gridNum; j++) 
			maze->grid[i][j] = BLOCK_WALL;
		
	for (int i = 1; i < maze->gridNum; i += 2) 
		for (int j = 1; j < maze->gridNum; j += 2) 
			maze->grid[i][j] = BLOCK_BLANK;
}

//绘制迷宫
void drawMaze(Maze maze, MazeStyle style){
	setbkcolor_f(COLOR_BACKGROUND);
	cleardevice();
	//格子内部边缘空隙宽度，取格子宽度1/8
	int padding = maze.gridWidth / 15;
	//根据迷宫样式，进行不同的绘制
	switch (style){
		//方格样式				
		case MAZE_STYLE_GRID:{
			setfillcolor(COLOR_WALL);
			for (int i = 0; i < maze.gridNum; i++) {
				for (int j = 0; j < maze.gridNum; j++) {
					if (maze.grid[i][j] == BLOCK_WALL)
						bar(j * maze.gridWidth + padding, i * maze.gridWidth + padding, (j + 1) * maze.gridWidth - padding, (i + 1) * maze.gridWidth - padding);
				}
			}
		}break;
		//围墙样式
		case MAZE_STYLE_WALL:{
			setcolor(COLOR_WALL);
			setlinewidth(2);
			//横围墙
			for (int i = 0; i < maze.gridNum; i += 2) {
				for (int j = 1; j < maze.gridNum; j += 2) {
					if (maze.grid[i][j] == BLOCK_WALL)
						line((j - 1) * maze.gridWidth + maze.gridWidth / 2, i * maze.gridWidth + maze.gridWidth / 2,
							(j + 1) * maze.gridWidth + maze.gridWidth / 2, i * maze.gridWidth + maze.gridWidth / 2);
				}
			}
			//竖围墙
			for (int i = 1; i < maze.gridNum; i += 2) {
				for (int j = 0; j < maze.gridNum; j += 2) {
					if (maze.grid[i][j] == BLOCK_WALL)
						line(j * maze.gridWidth + maze.gridWidth / 2, (i - 1) * maze.gridWidth + maze.gridWidth / 2,
							j * maze.gridWidth + maze.gridWidth / 2, (i + 1) * maze.gridWidth + maze.gridWidth / 2);
				}
			}
		}break;
	}
}

void fun(Maze* maze){
 	//随机拆墙

	//创建一个随机的拆墙顺序
	//空格左右的可拆墙编号为0 ~ maze.size * (msze.size-1) - 1
	//空格上下的可拆墙编号为maze.size * (msze.size-1) ~ 2 * maze.size * (msze.size-1) - 1
	//这两种墙有点不同，所以分开来
	const int WALL_SIZE = 2 * maze->size * (maze->size - 1);	//所有可拆墙数目
	int* randWall = new int[WALL_SIZE];

	for (int i = 0; i < WALL_SIZE; i++) randWall[i] = i;
	
	//随机打乱
	std::random_shuffle(randWall, randWall + WALL_SIZE);
	//并查集
	UnionFindSet ufSet(100);
	//被简化过
	//根据randWall中的顺序连通所有空格，连通时拆除两个空格之间的墙
	for (int i = 0; i < WALL_SIZE; i++) {
		//如果已全部连通，退出
		if (ufSet.setCount() <= 1)
			break;
		//下面代码压缩过，通过编号计算出墙的索引，两边空格的索引。
		int xWall, yWall, width, tx = 0, ty = 0;
		//空格左右的可拆墙
		if (randWall[i] < WALL_SIZE / 2) {
			width = 10 - 1;
			tx = 1;
		}
		//空格上下的可拆墙
		else {
			randWall[i] -= WALL_SIZE / 2;
			width = 10;
			ty = 1;
		}
		//通过编号计算墙在grid数组中的实际索引
		xWall = randWall[i] % width;
		yWall = randWall[i] / width;
		//墙两边的空格在grid数组中的实际索引
		int x1 = xWall, y1 = yWall, x2 = xWall + tx, y2 = yWall + ty;
		//如果进行了连通操作，那么拆墙
		if (ufSet.unionSet(y1 * 10 + x1, y2 * 10 + x2)) {
			maze->grid[yWall + y2 + 1][xWall + x2 + 1] = 0;
		}
	}
	delete[] randWall;
}