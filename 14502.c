//������(���4)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct pos {
	int row;
	int col;
}pos;

int row, col; //map�� ��� ���� ����
int** map;
int** visited; //bfs���� ���� ������ �ش� ��ǥ�� �湮�Ǿ������� ����
int max = 0; //���� ������ �ִ� ���� �����ϴ� ����(�� ������ ���� ��)
int front, rear;
pos* queue;
int d_row[4] = { 1, 0, -1, 0 }; //4������ ���� ��������
int d_col[4] = { 0, 1, 0, -1 }; //4������ ���� ��������
int num_of_one = 0; //map���� 1�� ������ ����

void clear();
void choose(int count, int cur_row, int cur_col);
void bfs();
void count(int num_of_two);

int main() {
	scanf("%d %d", &row, &col);
	map = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++) map[i] = malloc(sizeof(int) * col);
	visited = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++) visited[i] = malloc(sizeof(int) * col);
	queue = (pos*)malloc(sizeof(pos) * row * col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) num_of_one++;
			visited[i][j] = 0;
		}
	}
	choose(0, 0, 0); //0���� ���� ����� ��Ȳ, ���� ������ 0��, 0��

	printf("%d", max);
}

void choose(int count, int cur_row, int cur_col) {
	if (count == 3) { //3���� ���� ������ ��
		bfs(); //�� ��Ȳ���� ���̷����� bfs�� ��Ʈ���� ���� ������ �ִ븦 ���
		clear(); //visited�� ���� ������ ���� �ʱ�ȭ
	}
	else {
		for (int i = cur_row; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i == cur_row && j < cur_col) continue; //�׳� j = cur_col���� �ϴϱ� �����Ǵ� ���̽����� �־���(cur_row�� �����ϸ� j=0���� ��������)
				if (map[i][j] == 0 && count < 3) {
					map[i][j] = 1; //�� �����
					choose(count + 1, i, j);
					map[i][j] = 0; //��Ͱ� ������ ���� �� ���󺹱�
				}
			}
		}
	}
}

void bfs() {
	int cur_row, cur_col, next_row, next_col, dir;
	int num_of_two;
	front = rear = -1;

	//�ʱ���� 2�� ����(���̷����� �ִ� ����) queue�� �ֱ�
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (map[i][j] == 2) {
				queue[++rear].row = i;
				queue[rear].col = j;
				visited[i][j] = 1;
			}
		}
	}

	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col;

		dir = 0;
		while (dir < 4) { //4���� ���⿡ ����
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir]; //����Ǵ� ���� ��ǥ�� �����ϰ�
			if (next_row < row && next_row >= 0 && next_col < col && next_col >= 0) { //�� ��ǥ�� map�� ���� �ȿ� ������
				if (visited[next_row][next_col] == 0 && map[next_row][next_col] == 0) { //map���� ��ĭ�� �ش��ϰ� ���� �湮���� ���� ���̸�
					visited[next_row][next_col] = 1; //�湮 ����� �����
					queue[++rear].row = next_row; queue[rear].col = next_col; //�ش� ��ǥ�� queue�� �ֱ�
				}
			}
			dir++; //���� ���� ������
		}
	}

	num_of_two = rear + 1; //rear���� 0���� rear���� queue�� �� ��ǥ���� ������ ���´� 0���ʹϱ� 1�� ���ϸ� map���� 2�� ������ �� ������ �ǹ��Ѵ�
	count(num_of_two);
}

void count(int num_of_two) {
	int total = row * col; //��ü ��ǥ�� ������ ���ϰ�
	int count = total - num_of_two - (num_of_one + 3); //1�� ����(���� 1�� ���� + ���� ���� ���� ���� 3��), 2�� ������ ��� ����, �ش� ������ 0�� ����
	if (count > max) max = count; //�� 0�� ����(�� ���� ������ ����)�� �ִ뺸�� �� ũ�� ����
}

void clear() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			visited[i][j] = 0;
		}
	}
}