//�� �μ��� �̵��ϱ� 4(��� 2)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _pos {
	int row;
	int col;
}pos;

int ROW, COL;
int map[1001][1001];
int visited[1001][1001];
int save[1001][1001];
int d_row[4] = { -1, 0, 1, 0 };
int d_col[4] = { 0, 1, 0, -1 };

void bfs(int start_row, int start_col) {
	pos queue[1001 * 1001];
	int front, rear, cur_row, cur_col, next_row, next_col, dir;
	front = rear = -1;

	//�ʱ� ��ġ�� queue�� �ִ´�
	queue[++rear].row = start_row; queue[rear].col = start_col; visited[start_row][start_col] = 1;
	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; //queue���� ��ġ ��������

		dir = 0;
		while (dir < 4) { //4���� ������ Ž���ϸ鼭
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir++]; //����Ǵ� ���� ��ǥ�� �����ϰ�
			if (next_row >= ROW || next_row < 0 || next_col >= COL || next_col < 0) continue; //���� ���̸� �н�
			if (map[next_row][next_col] == 0 && visited[next_row][next_col] == 0) { //map���� 0�� �����̸鼭 ���� �湮���� ���� ������
				queue[++rear].row = next_row; queue[rear].col = next_col; //queue�� �߰��ϱ�
				visited[next_row][next_col] = 1;
			}
		}
	}


	int plus = rear + 1; //�׷��� ��� ���� ���� ������ ���� ������ 1���ٰ� �Ҵ緮�� �߰������ָ� �ȴ�
	pos save[1001 * 1001];
	int top = 0;

	front = -1; //�̹� bfs�� ������ 0�� ��ġ���� queue�� �����Ƿ� front�� �ʱ�ȭ�ؼ� Ž���ϸ� �ȴ�
	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; //queue���� ��ġ ��������
		dir = 0;
		while (dir < 4) { //4������ Ž���ؼ�
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir++];
			if (next_row >= ROW || next_row < 0 || next_col >= COL || next_col < 0) continue; //���� ���̸� �н��ϰ�
			if (map[next_row][next_col] != 0 && visited[next_row][next_col] == 0) { //���� ���̰� map���� 0�� �ƴ� ������ ���ÿ� ���� �湮���� ���� ��(���� �׷쿡�� �ߺ��ؼ� ���ϴ� ���� �����ϱ� ����)
				map[next_row][next_col] += plus; //�׷��� ������� �����ְ�
				visited[next_row][next_col] = 1; //���� �׷쿡�� �ߺ��ؼ� ������ �ʱ� ���� ��ġ�� �س���
				save[top].row = next_row; save[top++].col = next_col; //�� ��ġ�� �̹� bfs�� ������ �ʱ�ȭ ����� �ϱ� ������ �ش� ��ġ�� stack���ٰ� ����
			}
		}
	}

	//stack�� �����ص� visited�� 1�� �ٲ�� ������ ���� ������ ���� ���󺹱� ���� ���� �۾�
	for (int i = 0; i < top; i++) {
		cur_row = save[i].row; cur_col = save[i].col;
		visited[cur_row][cur_col] = 0;
	}
}

int main() {    
	char temp[1001][1001];
	scanf("%d %d", &ROW, &COL);
	for (int i = 0; i < ROW; i++) scanf("%s", temp[i]);
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (temp[i][j] == '1') map[i][j] = 1;
			else if (temp[i][j] == '0') map[i][j] = 0;
		}
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (map[i][j] == 0 && visited[i][j] == 0) { //0�� ������ �������� �׷��� ����� ���� ��ó�� ������ 1���ٰ� �׷��� ��� ����ŭ�� �߰��Ѵ�
				bfs(i, j);
			}
		}
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			printf("%d", map[i][j] % 10); //10���� ���� ���� ����ؾ� �Ѵ�
		}
		printf("\n");
	}
}