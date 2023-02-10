//숨바꼭질(골드 4)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _pos {
	int pos;
	int time;
	int last_index;
}pos;

int N, K;
int visited[100001] = { 0, };
pos queue[100001];
int* result;

int main() {
	int front, rear, cur_pos, cur_time, index; front = rear = -1;
	scanf("%d %d", &N, &K);

	//초기 위치 넣기
	queue[++rear].pos = N; queue[rear].time = 0;
	queue[rear].last_index = 0; visited[N] = 1;
	while (front != rear) {
		cur_pos = queue[++front].pos; cur_time = queue[front].time; // queue에서 새로운 위치 가져오기

		if (cur_pos == K) break;

		if (cur_pos <= 100000) { // X + 1
			if (visited[cur_pos + 1] == 0) {
				queue[++rear].pos = cur_pos + 1;
				queue[rear].time = cur_time + 1;
				queue[rear].last_index = front;
				visited[cur_pos + 1] = 1;
			}
		}

		if (cur_pos > 0) { // X - 1
			if (visited[cur_pos - 1] == 0) {
				queue[++rear].pos = cur_pos - 1;
				queue[rear].time = cur_time + 1;
				queue[rear].last_index = front;
				visited[cur_pos - 1] = 1;
			}
		}

		if (cur_pos * 2 <= 100000 && cur_pos < K) { // X * 2
			if (visited[cur_pos * 2] == 0) {
				queue[++rear].pos = cur_pos * 2;
				queue[rear].time = cur_time + 1;
				queue[rear].last_index = front;
				visited[cur_pos * 2] = 1;
			}
		}
	}

	printf("%d\n", cur_time);

	index = front;
	result = (int*)malloc(sizeof(int) * cur_time);
	for (int i = cur_time - 1; i >= 0; i--) {
		result[i] = queue[index].pos;
		index = queue[index].last_index;
	}

	printf("%d ", N);
	for (int i = 0; i < cur_time; i++) {
		printf("%d ", result[i]);
	}
}