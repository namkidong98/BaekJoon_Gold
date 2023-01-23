//�丶��(��� 5) - 3����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct pos {
	int height;
	int row;
	int col;
	int day; //���� °����
}pos;

int main() {
	int row, col, height, i, j, k;
	int target = 0; //���� ���� ���� �丶��(0���� ����� ��)�� ����
	//case1: �ʱⰪ�� 0�̸� ��� �丶�䰡 ���� ���·� 0 ���
	//case2: 0�� �ƴϾ��ٰ� 0�� �Ǹ� while�� ���� & �ּҳ�¥ ���
	//case3: 0�� �ƴϾ��ٰ� 0�� �ȵǸ� ��� ������ ���ϴ� ���·� -1 ���

	scanf("%d %d %d", &col, &row, &height);
	row += 2; col += 2; height += 2;
	int*** matrix = (int***)malloc(sizeof(int**) * height);
	int*** visited = (int***)malloc(sizeof(int**) * height);
	for (i = 0; i < height; i++) {
		matrix[i] = (int**)malloc(sizeof(int*) * row);
		visited[i] = (int**)malloc(sizeof(int*) * row);
	}
	for (i = 0; i < height; i++) {
		for (j = 0; j < row; j++) {
			matrix[i][j] = (int*)malloc(sizeof(int) * col);
			visited[i][j] = (int*)malloc(sizeof(int) * col);
		}
	}

	//�ʱ� �� ����
	for (i = 0; i < height; i++) {
		for (j = 0; j < row; j++) {
			for (k = 0; k < col; k++) {
				//�� �׵θ� -2�� ó���ؼ� ����
				if (i == 0 || i == height - 1 || j == 0 || j == row - 1 || k == 0 || k == col - 1) matrix[i][j][k] = -2;
				else {
					scanf("%d", &matrix[i][j][k]);
					if (matrix[i][j][k] == 0) target++; //���� ���� �丶�䰡 �Էµ� ������ 1���� ����
				}
				visited[i][j][k] = 0; //�湮 �������� 0, �湮������ 1 (0���� �ʱ�ȭ)
			}
		}
	}

	pos* queue = (pos*)malloc(sizeof(pos) * (row - 2) * (col - 2) * (height - 2));
	int front, rear, cur_height, cur_row, cur_col, cur_day;
	front = rear = -1;

	//ù ���࿡�� 1�� ������ queue�� add
	for (i = 1; i < height - 1; i++) {
		for (j = 1; j < row - 1; j++) {
			for (k = 1; k < col - 1; k++) {
				if (matrix[i][j][k] == 1) {
					visited[i][j][k] = 1; //�ش� ��ġ �湮 ��� �����
					queue[++rear].height = i; queue[rear].row = j; queue[rear].col = k; queue[rear].day = 0;//�ش� ��ġ queue�� add
				}
			}
		}
	}
	
	if (target == 0) { //���ʿ� ���� ���� �丶�䰡 ���� ���� --> ����� ������ ��� �丶�䰡 �;��ִ� ����
		printf("0");
		return 0;
	}

	while (front != rear) { //queue�� �� ������ �ݺ�
		cur_height = queue[++front].height; cur_row = queue[front].row; cur_col = queue[front].col; cur_day = queue[front].day; //queue���� ���ο� ��ġ ��������

		//6����(��, �Ʒ�, ��, ��, ��, ��)�� Ž���Ͽ� �̵��� �� �ִ� ���� �丶�信 �湮
		//�湮��� �����, �丶�並 ���� �丶��� �ٲٰ�, ���� ���� �丶�� ���� 1�� ���̰�, �ش� ��ġ�� queue�� add
		if (matrix[cur_height][cur_row + 1][cur_col] == 0 && visited[cur_height][cur_row + 1][cur_col] == 0) { //��
			visited[cur_height][cur_row + 1][cur_col] = 1; //�湮 ��� �����
			matrix[cur_height][cur_row + 1][cur_col] = 1; //���� �丶��� �ٲٱ�
			target--; //���� ���� �丶�� 1�� �پ��
			queue[++rear].height = cur_height; queue[rear].row = cur_row + 1; queue[rear].col = cur_col; queue[rear].day = cur_day + 1; //�ش� ��ġ queue�� add
		}
		if (matrix[cur_height][cur_row - 1][cur_col] == 0 && visited[cur_height][cur_row - 1][cur_col] == 0) { //��
			visited[cur_height][cur_row - 1][cur_col] = 1; //�湮 ��� �����
			matrix[cur_height][cur_row - 1][cur_col] = 1; //���� �丶��� �ٲٱ�
			target--; //���� ���� �丶�� 1�� �پ��
			queue[++rear].row = cur_row - 1; queue[rear].col = cur_col; queue[rear].height = cur_height; queue[rear].day = cur_day + 1; //�ش� ��ġ queue�� add
		}
		if (matrix[cur_height][cur_row][cur_col + 1] == 0 && visited[cur_height][cur_row][cur_col + 1] == 0) { //��
			visited[cur_height][cur_row][cur_col + 1] = 1; //�湮 ��� �����
			matrix[cur_height][cur_row][cur_col + 1] = 1; //���� �丶��� �ٲٱ�
			target--; //���� ���� �丶�� 1�� �پ��
			queue[++rear].row = cur_row; queue[rear].col = cur_col + 1; queue[rear].height = cur_height; queue[rear].day = cur_day + 1; //�ش� ��ġ queue�� add
		}
		if (matrix[cur_height][cur_row][cur_col - 1] == 0 && visited[cur_height][cur_row][cur_col - 1] == 0) { //��
			visited[cur_height][cur_row][cur_col - 1] = 1; //�湮 ��� �����
			matrix[cur_height][cur_row][cur_col - 1] = 1; //���� �丶��� �ٲٱ�
			target--; //���� ���� �丶�� 1�� �پ��
			queue[++rear].row = cur_row; queue[rear].col = cur_col - 1; queue[rear].height = cur_height; queue[rear].day = cur_day + 1; //�ش� ��ġ queue�� add
		}
		if (matrix[cur_height + 1][cur_row][cur_col] == 0 && visited[cur_height + 1][cur_row][cur_col] == 0) { //��
			visited[cur_height + 1][cur_row][cur_col] = 1; //�湮 ��� �����
			matrix[cur_height + 1][cur_row][cur_col] = 1; //���� �丶��� �ٲٱ�
			target--; //���� ���� �丶�� 1�� �پ��
			queue[++rear].row = cur_row; queue[rear].col = cur_col; queue[rear].height = cur_height + 1; queue[rear].day = cur_day + 1; //�ش� ��ġ queue�� add
		}
		if (matrix[cur_height - 1][cur_row][cur_col] == 0 && visited[cur_height - 1][cur_row][cur_col] == 0) { //�Ʒ�
			visited[cur_height - 1][cur_row][cur_col] = 1; //�湮 ��� �����
			matrix[cur_height - 1][cur_row][cur_col] = 1; //���� �丶��� �ٲٱ�
			target--; //���� ���� �丶�� 1�� �پ��
			queue[++rear].row = cur_row; queue[rear].col = cur_col; queue[rear].height = cur_height - 1; queue[rear].day = cur_day + 1; //�ش� ��ġ queue�� add
		}
	}

	if (target != 0) { //queue�� �� ������ �ݺ��ص� ���� ���� �丶�䰡 ���� ������
		printf("-1");
	}
	else { //���� �丶�䰡 �� ���� ��Ȳ
		printf("%d", cur_day); //queue�� �ִ� ������ ��ġ�� ���� �ִ� day�� ���(�ּ� ��¥)
	}
}