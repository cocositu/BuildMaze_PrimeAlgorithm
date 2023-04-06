//简单作图: 线条与线框图形
#include <graphics.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

//四个方向
#define DIRECTION_NUM 4

//自定义颜色
#define  COLOR_WALL         BLACK
#define  COLOR_BACKGROUND   WHITE
#define  COLOR_TREE         DARKGRAY
#define  COLOR_LOCUS        RED

//迷宫大小设置
#define  MAZE_SIZE  10						//迷宫大小 10 x 10
#define  GRID_NUM   2 * (MAZE_SIZE + 1) + 1		//迷宫格子数最大值(每行)

//定义四个方向的行进增量
int dx[DIRECTION_NUM] = { -1,  0, 1, 0 };
int dy[DIRECTION_NUM] = {  0, -1, 0, 1 };

enum BLOCK {
	BLOCK_BLANK = 0,
	BLOCK_WALL,
	BLOCK_PATH,
};

enum MazeStyle
{
	MAZE_STYLE_GRID = 0,	//格子型
	MAZE_STYLE_WALL	= 1,	//围墙型
};

typedef struct 
{
	int size;
	int gridNum;
	int gridWidth;
	int grid[GRID_NUM][GRID_NUM];

	int StaLoc; //起点坐标
	int TerLoc; //终点坐标
} Maze;

time_t ti;
Maze maze = {MAZE_SIZE, GRID_NUM, 0, 0};

int scrWidth = 0;
int scrHeight = 0;

void createMaze(Maze);
void initMaze(Maze*);
void drawMaze(Maze, MazeStyle);
int  main(){


	initMaze(&maze);
	createMaze(maze);
	drawMaze(maze, MAZE_STYLE_WALL);
	//printf("HelloWorld\n");
	getch();
	getch();
	int i = 0x01;
	printf("...%d\n",i);
	closegraph();
	return 0;
}

//创建迷宫
void createMaze(Maze maze){
	setinitmode(INIT_RENDERMANUAL);
	setcaption("迷宫");
	setbkmode(TRANSPARENT);
	//调整窗口大小
	scrWidth = (maze.gridNum + 2) * maze.gridWidth;
	scrHeight = (maze.gridNum + 2) * maze.gridWidth;
	initgraph(scrWidth, scrHeight);
}


//迷宫初始化
void initMaze(Maze *maze){

	//预设窗口宽高为600左右
	maze->gridWidth = (int)ceil(600.0f / maze->gridNum);	

	//初始化
	for (int i = 1; i < maze->gridNum - 1; i++) {
		for (int j = 1; j < maze->gridNum - 1; j++) {
			maze->grid[i][j] = BLOCK_WALL;
		}
	}

	for (int i = 2; i < maze->gridNum; i += 2) {
		for (int j = 2; j < maze->gridNum; j += 2) {
			maze->grid[i][j] = BLOCK_BLANK;
		}
	}
}


//绘制带路径的迷宫
void drawMaze(Maze maze, MazeStyle style){
	setbkcolor_f(COLOR_BACKGROUND);
	cleardevice();

	//格子内部边缘空隙宽度，取格子宽度1/8
	int padding = maze.gridWidth / 15;

	//根据迷宫样式，进行不同的绘制
	switch (style){
		case MAZE_STYLE_GRID:	//方格样式
		{
			setfillcolor(COLOR_WALL);
			for (int i = 0; i < maze.gridNum; i++) {
				for (int j = 0; j < maze.gridNum; j++) {
					if (maze.grid[i][j] == BLOCK_WALL)
						bar((j+1) * maze.gridWidth + padding, (i+1) * maze.gridWidth + padding, (j + 2) * maze.gridWidth - padding, (i + 2) * maze.gridWidth - padding);
				}
			}
			break;
		}
		case MAZE_STYLE_WALL:	//围墙样式
		{
			setcolor(COLOR_WALL);
			setlinewidth(2);
		//横围墙
		for (int i = 1; i < maze.gridNum; i += 2) {
			for (int j = 2; j < maze.gridNum; j += 2) {
				if (maze.grid[i][j] == BLOCK_WALL)
					line((j - 1) * maze.gridWidth + maze.gridWidth / 2, i * maze.gridWidth + maze.gridWidth / 2,
						(j + 1) * maze.gridWidth + maze.gridWidth / 2, i * maze.gridWidth + maze.gridWidth / 2);
			}
		}
		//竖围墙
		for (int i = 2; i < maze.gridNum; i += 2) {
			for (int j = 1; j < maze.gridNum; j += 2) {
				if (maze.grid[i][j] == BLOCK_WALL)
					line(j * maze.gridWidth + maze.gridWidth / 2, (i - 1) * maze.gridWidth + maze.gridWidth / 2,
						j * maze.gridWidth + maze.gridWidth / 2, (i + 1) * maze.gridWidth + maze.gridWidth / 2);
			}
		}
		break;
		}
	}
}