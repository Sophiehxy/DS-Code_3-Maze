#pragma once
#include<iostream>
using namespace std;
#include<cassert>
#include<stack>


void GetMazeMap(int *a,int row,int col)//���ļ��л�ȡ�Թ�ͼ
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
				++j;//���ڴ˴���ԭ���ǣ����ڵ��ո����������ʱ����ֹ����ֵ
			}

		}
	}
	fclose(fOut);
}

void Display(int* a, int row, int col)//��ӡ�Թ�
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

struct Pos    //��ʾ����λ��
{
	size_t _row;
	size_t _col;
};

bool CheckIsAccess(int* a, int rowSize, int colSize,Pos cur)
{
	if ((cur._row > 0 && cur._row<rowSize)
		&& (cur._col>0 && cur._col < colSize)//�ж�cur�ı߽��Ƿ�Խ��
		&& (a[cur._row*colSize + cur._col] == 0))//�ж�cur�����Ƿ�ͨ·
	{
		return true;
	}
	return false;
}

stack<Pos> GetEntry(int* a, int rowSize, int colSize, Pos entry)//entry��ʾ���λ��
{
	stack<Pos> path;//ջ�д��Pos���͵����꣬����ͨ·
	path.push(entry);//���Թ����ѹջ
	while (!path.empty())
	{
		Pos cur = path.top();
		Pos next = cur;

		//�жϳ���
		if (next._row == rowSize - 1)  //���Թ��ĳ��ڽ����±�Ե
		{
			return path;
		}
		//��̽��һ����ͨ�з���

		//��̽������
		next._row--;
		if (CheckIsAccess(a, 10, 10, next))
		{
			a[cur._row*colSize + cur._col] = 2;//���߹��ĵ���Ϊ2
			path.push(next);
			continue;
		}
		//��̽������
		next = cur;
		next._row++;
		if (CheckIsAccess(a, 10, 10, next))
		{
			a[cur._row*colSize + cur._col] = 2;//���߹��ĵ���Ϊ2
			path.push(next);
			continue;
		}
		//��̽������
		next = cur;
		next._col--;
		if (CheckIsAccess(a, 10, 10, next))
		{
			a[cur._row*colSize + cur._col] = 2;//���߹��ĵ���Ϊ2
			path.push(next);
			continue;
		}
		//��̽������
		next = cur;
		next._col++;
		if (CheckIsAccess(a, 10, 10, next))
		{
			a[cur._row*colSize + cur._col] = 2;//���߹��ĵ���Ϊ2
			path.push(next);
			continue;
		}
		
		//����,���������������������������ʾ��ͨ·
		Pos top = path.top();
		if (a[cur._row*colSize + cur._col] = 2)
			a[cur._row*colSize + cur._col] = 3;//���߹��ĵ���Ϊ3
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