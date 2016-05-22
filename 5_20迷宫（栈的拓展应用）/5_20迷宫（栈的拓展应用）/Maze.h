#pragma once
#include<iostream>
using namespace std;
#include<cassert>
#include<stack>


void GetMazeMap(int *a,int row,int col)//从文件中获取迷宫图
{
	FILE* fOut = fopen("maze.txt", "r");
	assert(fOut);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; )
		{
			char ch = fgetc(fOut);
			if (ch == '0' || ch == '1')
			{
				a[i*col + j] = ch - '0';
				++j;//放在此处的原因是，当于当空格或其他符号时，防止被赋值
			}

		}
	}
	fclose(fOut);
}

void Display(int* a, int row, int col)//打印迷宫
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cout << a[i*row + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

struct Pos    //表示坐标位置
{
	size_t _row;
	size_t _col;
};

bool CheckIsAccess(int* a, int rowSize, int colSize,Pos cur)
{
	if ((cur._row > 0 && cur._row<rowSize)
		&& (cur._col>0 && cur._col < colSize)//判断cur的边界是否越界
		&& (a[cur._row*colSize + cur._col] == 0))//判断cur方向是否通路
	{
		return true;
	}
	return false;
}

stack<Pos> GetEntry(int* a, int rowSize, int colSize, Pos entry)//entry表示入口位置
{
	stack<Pos> path;//栈中存放Pos类型的坐标，构成通路
	path.push(entry);//将迷宫入口压栈
	while (!path.empty())
	{
		Pos cur = path.top();
		Pos next = cur;

		//判断出口
		if (next._row == rowSize - 1)  //记迷宫的出口仅在下边缘
		{
			return path;
		}
		//试探下一个可通行方向

		//试探方向：上
		next._row--;
		if (CheckIsAccess(a, 10, 10, next))
		{
			a[cur._row*colSize + cur._col] = 2;//将走过的点标记为2
			path.push(next);
			continue;
		}
		//试探方向：下
		next = cur;
		next._row++;
		if (CheckIsAccess(a, 10, 10, next))
		{
			a[cur._row*colSize + cur._col] = 2;//将走过的点标记为2
			path.push(next);
			continue;
		}
		//试探方向：左
		next = cur;
		next._col--;
		if (CheckIsAccess(a, 10, 10, next))
		{
			a[cur._row*colSize + cur._col] = 2;//将走过的点标记为2
			path.push(next);
			continue;
		}
		//试探方向：右
		next = cur;
		next._col++;
		if (CheckIsAccess(a, 10, 10, next))
		{
			a[cur._row*colSize + cur._col] = 2;//将走过的点标记为2
			path.push(next);
			continue;
		}
		
		//回溯,如果其余三个方向均不跳出，则表示无通路
		Pos top = path.top();
		if (a[cur._row*colSize + cur._col] = 2)
			a[cur._row*colSize + cur._col] = 3;//将走过的点标记为3
		path.pop();

		

	}
}


void Test()
{
	int* a = new int[10*10];
	GetMazeMap(a, 10, 10);
	Display(a, 10, 10);
	Pos entry = { 1, 0 };
	GetEntry(a, 10, 10, entry);
	Display(a, 10, 10);

}