//���ϻ��� (���5)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct pos {
	int row;
	int col;
}pos;

int	row, col;
int visited[101][101];
char map[101][101];

void bfs(int start_row, int start_col) {
	int front, rear, cur_row, cur_col, next_row, next_col, dir;
	pos queue[10000];
	int d_row[4] = { -1, 0, 1, 0 };
	int d_col[4] = { 0, 1, 0 ,-1 };
	char target = map[start_row][start_col]; //�ش� ������ RGB��
	front = rear = -1;

	queue[++rear].row = start_row; queue[rear].col = start_col; visited[start_row][start_col] = 1; //���� ���� �Է�
	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; //queue���� ��ġ ��������

		dir = 0;
		while (dir < 4) { //4������ Ž��
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir]; //����Ǵ� ��ǥ ����
			if (next_row >= 0 && next_row < row && next_col >= 0 && next_col < col) { //����Ǵ� ��ǥ�� map�� ���� �ȿ� �ִٸ�
				if (visited[next_row][next_col] == 0 && map[next_row][next_col] == target) { //�׸��� �湮���� �ʾҰ� ���� ������ ���� RGB���̸�
					queue[++rear].row = next_row; //queue�� �߰��ϰ� �湮 ��� �����
					queue[rear].col = next_col;
					visited[next_row][next_col] = 1;
				}
			}
			dir++; //���� ���� Ž��
		}
	}
}

int main() {
	int count = 0;
	scanf("%d", &row); col = row;
	for (int i = 0; i < row; i++) {
		scanf("%s", &map[i]);
	}

	//���� map�� ������ bfs�ؼ� ������ ���� ���ϱ�
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (visited[i][j] == 0) {
				bfs(i, j);
				count++;
			}
		}
	}
	printf("%d ", count);

	//���� ������ ���� �ʱ�ȭ �� map���� green�� red�� ��ȯ(���ϻ����� ���)
	count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			visited[i][j] = 0;
			if (map[i][j] == 'G') map[i][j] = 'R';
		}
	}

	//���ϻ����� ����� map�� ������ bfs�ؼ� ������ ���� ���ϱ�
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (visited[i][j] == 0) {
				bfs(i, j);
				count++;
			}
		}
	}
	printf("%d", count);
}