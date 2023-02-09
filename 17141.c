//������ 2(��� 4)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _pos {
	int row;
	int col;
	int time;
}pos;

int N, M;
int row, col;
int** map;
int** visited;
int num_of_wall = 0;
pos* queue;
pos virus[10]; //���̷����� ���� �� �ִ� ��ġ(map���� 2�� ǥ�õ� ��)���� ��� ������ ����
int virus_count = 0; //���̷����� ���� �� �ִ� ��ġ�� �� ����(map���� 2�� ǥ�õ� ���� �� ����)
int use[10]; //�� ���࿡�� ����� ���̷��� ��ġ�� index�� �����ϴ� ����
int total; //bfs�� ���� ���� ���� ������ ��� ���� �湮�ߴ��� Ȯ���ϱ� ���� ����
int min = -1; //���̷����� �۶߸��� ���� �ּ� �ð��� �����ϴ� ����
int d_row[4] = { 1, 0, -1, 0 }; //�� ���� 4���⿡ ���� ��ȭ��
int d_col[4] = { 0, 1, 0 ,-1 }; //�� ���� 4���⿡ ���� ��ȭ��

void clear() { //bfs ���� ���� ������ ���� visited ������ �ʱ�ȭ �ϱ� ���� �Լ�
	for (int i = 0;  i < row; i++) {
		for (int j = 0; j < col; j++) {
			visited[i][j] = 0;
		}
	}
}

int bfs() {
	int front, rear, cur_row, cur_col, cur_time, next_row, next_col, dir;
	front = rear = -1; cur_time = 0;

	for (int i = 0; i < M; i++) { //use���� ����ϱ�� ������ ���̷��� ��ġ���� queue�� �ִ´�(�ʱ� ����)
		queue[++rear].row = virus[use[i]].row;
		queue[rear].col = virus[use[i]].col;
		queue[rear].time = 0;
		visited[virus[use[i]].row][virus[use[i]].col] = 1;
	}

	while (front != rear) { //queue�� ������ ����� ������ bfs Ž��
		cur_row = queue[++front].row; cur_col = queue[front].col; cur_time = queue[front].time; //queue���� ���ο� ��ġ ��������

		dir = 0; 
		while (dir < 4) { //4���� ������ Ž��
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir]; //4���⿡ ���� ��ȭ���� �����Ͽ� ������ ��ġ�� ����
			if (next_row < row && next_row >= 0 && next_col < col && next_col >= 0) { //������ ��ġ�� map�� ���� �ȿ� �ְ�
				if (visited[next_row][next_col] == 0 && map[next_row][next_col] != 1) { //������ ��ġ�� �湮���� �ʾ����� ���� �ƴ� �����̸�
					//�ش� ������ queue�� add�ϰ� �湮 ��� �����
					queue[++rear].row = next_row;
					queue[rear].col = next_col;
					queue[rear].time = cur_time + 1;
					visited[next_row][next_col] = 1;
				}
			}
			dir++; //���� �ٲٱ�
		}
	}

	if (rear == total - 1) return cur_time; //while loop�� ����ǰ� ���� ������ ��� ������ rear�� ��� �ִٸ� --> ������ ��ġ������ ���� �ð�(time)�� ��ȯ
	else return -1; //�׷��� ���� ��쿡�� ��� ������ bfs�� �������� ���ߴٴ� �ǹ��̰� �� ��쿡�� -1�� ��ȯ

}

void choose(int count, int current) { //�������� ���̷��� ��ġ �� M���� �����ϰ� bfs�� �ѱ�� ������ �ϴ� �Լ�
	int result;
	if (count == M) {
		result = bfs();

		if (min == -1) min = result; //��ó������ ����� �׳� min�� ����
		else if (result != -1 && result < min) min = result; //�������� bfs�� ����� min���� ������ �ּڰ� ����

		clear(); //���� ������ ���� visited �ʱ�ȭ
	}

	else {
		for (int i = current; i < virus_count; i++) { //���̷����� ���� �� �ִ� ��ġ��ŭ(virus_count) Ž���ϸ鼭
			if (virus[i].time == 0) { //virus[].time�� 1�̸� �̿��� ��, 0�̸� �̿� ���� ������ ��� --> ��� ���� ���̸�
				use[count] = i; //����ϱ� ���� index�� ��� use���ٰ� index�� ���
				virus[i].time = 1; //�ش� ������ ����ߴٴ� ǥ�ø� �����
				choose(count + 1, i + 1); //���� ���� �����Ϸ� �̵�
				virus[i].time = 0; //��Ͱ� ������ ���� �̹� ���࿡�� ��ȭ�� �־��� ���� ����Ű��
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	row = col = N;
	map = (int**)malloc(sizeof(int*) * row);
	visited = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++) {
		map[i] = (int*)malloc(sizeof(int) * col);
		visited[i] = (int*)malloc(sizeof(int) * col);
	}
	queue = (pos*)malloc(sizeof(pos) * row * col);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			scanf("%d", &map[i][j]);
			visited[i][j] = 0; //�湮����� 0���� �ʱ�ȭ
			if (map[i][j] == 1) {
				num_of_wall++;
			}
			else if (map[i][j] == 2) {
				virus[virus_count].row = i;
				virus[virus_count++].col = j;
			}
		}
	}

	total = (row * col) - num_of_wall;

	choose(0, 0);

	printf("%d", min);
}