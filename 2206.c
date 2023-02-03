//�� �μ��� �̵��ϱ�(���3)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int row;
	int col;
	int len; //���� �������� �̵��ϴµ� �ɸ� �Ÿ�
	int wall; //0�̸� ���� ���� �� �μ� ����, 1�̸� ���� �μ� ����
}node;

int row, col;
char** map;
node* queue;
int visited [1000][1000][2]; //visited[row][col][2]�� 0�� ���� �Ⱥμ��� ���� ��, 1�� ���� �μ��� ���� ��
int d_row[4] = { 1, 0, -1, 0 };
int d_col[4] = { 0, 1, 0, -1 };

int bfs() {
	int exit_row = row - 1; int exit_col = col - 1;
	int front, rear, dir; front = rear = -1;
	int cur_row, cur_col, cur_len, cur_wall, next_row, next_col;

	//���� ��ǥ queue�� �ְ� �湮 ��� �����
	queue[++rear].row = 0; queue[rear].col = 0; queue[rear].len = 1; queue[rear].wall = 0;
	visited[0][0][0] = 1;
	while (front != rear) {
		//queue���� ���ο� ��ġ ��������
		cur_row = queue[++front].row; cur_col = queue[front].col; cur_len = queue[front].len; cur_wall = queue[front].wall;

		if (cur_row == exit_row && cur_col == exit_col) break;

		dir = 0;
		while (dir < 4) {
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir]; //4���⿡ ���� ���� ���� ��ġ�� ����

			if (next_row < row && next_row >= 0 && next_col < col && next_col >= 0) { //���� �ȿ� ������

				//case1: �̵��� �� �ִ� ���̰� ���� �湮���� �ʾ�����(�̹� ���� �ν��� ����, �ƴ� ���� �ִ�)
				if (map[next_row][next_col] == '0' && visited[next_row][next_col][cur_wall] == 0) { 
					queue[++rear].row = next_row; queue[rear].col = next_col; queue[rear].len = cur_len + 1; queue[rear].wall = cur_wall;
					visited[next_row][next_col][cur_wall] = 1;
				}

				//case2: �̵��� �� ���� �������� ���� ���� ���� �ʾƼ� �հ� �̵��� �� �ִ� ���̸�
				if (map[next_row][next_col] == '1' && cur_wall == 0) {
					queue[++rear].row = next_row; queue[rear].col = next_col; queue[rear].len = cur_len + 1; queue[rear].wall = 1;
					visited[next_row][next_col][1] = 1;
				}
			}
			dir++;
		}
	}

	if (cur_row == exit_row && cur_col == exit_col) {
		return cur_len;
	}
	else {
		return -1;
	}
}


int main() {
	int result;
	scanf("%d %d", &row, &col);
	queue = (node*)malloc(sizeof(node) * row * col * 3);
	map = (char**)malloc(sizeof(char*) * row);
	for (int i = 0; i < row; i++) map[i] = (char*)malloc(sizeof(char) * (col + 1));
	for (int i = 0; i < row; i++) {
		scanf("%s", map[i]);
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			for (int k = 0; k < 2; k++) {
				visited[i][j][k] = 0;
			}
		}
	}

	result = bfs();
	printf("%d", result);
}