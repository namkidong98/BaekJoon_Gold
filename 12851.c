//���ٲ��� 2(���4)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100001

typedef struct _pos {
	int pos;
	int times;
}pos;

int N, K;
pos queue[MAX * 10]; //������ �����鵵 �ݺ������� ���Ե� �� ������ MAX���� ũ�� ��ƾ� �Ѵ�
int visited[MAX] = { 0 };
int front, rear;
int min = MAX;
int count = 0;


void calculate() {
	int cur_pos, cur_times;
	front = rear = -1;

	//���� ���� ����
	queue[++rear].pos = N; queue[rear].times = 0; visited[N] = 1;

	while (front != rear) {
		cur_pos = queue[++front].pos; cur_times = queue[front].times; //queue���� ��ġ ��������
		visited[cur_pos] = 1; //�� �κ��� �Ʒ� ������ ���� �Ʒ��� ���Խ�Ű��,
							  //������ times���� K�� �����ϴ� �ٸ� ����� ���� ī���� �ȵǹǷ� ���ʿ��� ���ο� ��ġ�� �������� �� visited�� 1�� �����ؾ� �Ѵ�.

		if (count > 0 && cur_pos == K && cur_times == min) count++;
		if (count == 0 && cur_pos == K) {
			min = cur_times; count++; 
		}

		if (cur_times < min) {
			if (cur_pos + 1 < MAX && visited[cur_pos + 1] == 0) {
				queue[++rear].pos = cur_pos + 1;
				queue[rear].times = cur_times + 1;
			}
			if (cur_pos - 1 >= 0 && visited[cur_pos - 1] == 0) {
				queue[++rear].pos = cur_pos - 1;
				queue[rear].times = cur_times + 1;
			}
			if (cur_pos * 2 < MAX && visited[cur_pos * 2] == 0) {
				queue[++rear].pos = cur_pos * 2;
				queue[rear].times = cur_times + 1;
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &K);
	calculate();
	printf("%d\n%d", min, count);
}