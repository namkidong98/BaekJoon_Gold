//숨바꼭질 2(골드4)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100001

typedef struct _pos {
	int pos;
	int times;
}pos;

int N, K;
pos queue[MAX * 10]; //동일한 지점들도 반복적으로 포함될 수 있으니 MAX보다 크게 잡아야 한다
int visited[MAX] = { 0 };
int front, rear;
int min = MAX;
int count = 0;


void calculate() {
	int cur_pos, cur_times;
	front = rear = -1;

	//시작 지점 삽입
	queue[++rear].pos = N; queue[rear].times = 0; visited[N] = 1;

	while (front != rear) {
		cur_pos = queue[++front].pos; cur_times = queue[front].times; //queue에서 위치 가져오기
		visited[cur_pos] = 1; //이 부분을 아래 각각의 시행 아래에 포함시키면,
							  //동일한 times에서 K에 도달하는 다른 경우의 수가 카운팅 안되므로 위쪽에서 새로운 위치를 가져왔을 때 visited를 1로 갱신해야 한다.

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