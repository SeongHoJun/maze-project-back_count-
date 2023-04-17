#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_SIZE 10
#define MAX_SIZE 100


typedef struct {
	short r;
	short c;
}element;

typedef struct {
	element* data;
	int capacity;
	int top;
} StackType;

element here = { 1,0 }, entry = { 1,0 };
char maze[MAZE_SIZE][MAZE_SIZE] = {

		{'1','1','1','1','1','1','1','1','1','1'},

		{'e','1','0','1','0','0','0','1','0','1'},

		{'0','0','0','1','0','0','0','1','0','1'},

		{'0','1','0','0','0','1','1','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','0','0','1','0','1','1'},

		{'1','0','1','1','1','0','1','1','0','1'},

		{'1','1','0','0','0','0','0','0','0','x'},

		{'1','1','1','1','1','1','1','1','1','1'}

};

void init_stack(StackType* sp)
{
	sp->top = -1;
	sp->capacity = 1;
	sp->data = (element*)malloc(sp->capacity * sizeof(element));
}

int is_empty(StackType* sp)
{
	return (sp->top == -1);
}
int is_full(StackType* sp)
{
	return (sp->top == (MAX_SIZE - 1));
}

void push(StackType* sp, element item)
{
	if (is_full(sp))
	{
		sp->capacity = sp->capacity * 2;
		sp->data = (element*)realloc(sp->data, sp->capacity * sizeof(element));
	}
	sp->data[++(sp->top)] = item;
}

element pop(StackType* sp)
{
	if (is_empty(sp))
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
	{
		return sp->data[(sp->top)--];
		exit(1);
	}
}

element peek(StackType* sp)
{
	if (is_empty(sp))
	{
		fprintf(stderr, "스택 공백 에러\n");
	}
	else return sp->data[sp->top];
}

int push_loc(StackType* sp, int r, int c)
{
	if (r < 0 || c < 0)	return 0;
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(sp, tmp);
		return 1;
	}
	return 0;
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n--------------------\n");
	for (int r = 0; r < MAZE_SIZE; r++)
	{
		for (int c = 0; c < MAZE_SIZE; c++)
		{
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}

}
int main(void)
{
	int path = 0;
	int back_count = 0;
	int r, c;
	StackType sp;

	init_stack(&sp);
	here = entry;
	while (maze[here.r][here.c] != 'x')
	{
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		maze_print(maze);
		path=push_loc(&sp, r - 1, c);
		path=path+push_loc(&sp, r + 1, c);
		path=path+push_loc(&sp, r, c - 1);
		path=path+push_loc(&sp, r, c + 1);

		if (path == 0)
		{
			back_count++;
		}

		if (is_empty(&sp))
		{
			printf("실패\n");
		}
		else
			here = pop(&sp);
	}
	printf("성공\n");
	printf("Back count: %d", back_count);
	return 0;
}
