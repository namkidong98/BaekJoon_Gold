//연구소 2(골드 4)
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
pos virus[10]; //바이러스를 놓을 수 있는 위치(map에서 2로 표시된 곳)들을 모두 저장한 변수
int virus_count = 0; //바이러스를 놓을 수 있는 위치의 총 개수(map에서 2로 표시된 곳의 총 개수)
int use[10]; //각 시행에서 사용할 바이러스 위치의 index를 저장하는 변수
int total; //bfs가 끝난 이후 벽을 제외한 모든 곳을 방문했는지 확인하기 위한 변수
int min = -1; //바이러스를 퍼뜨리기 위한 최소 시간을 저장하는 변수
int d_row[4] = { 1, 0, -1, 0 }; //열 기준 4방향에 따른 변화값
int d_col[4] = { 0, 1, 0 ,-1 }; //행 기준 4방향에 따른 변화값

void clear() { //bfs 이후 다음 시행을 위해 visited 변수를 초기화 하기 위한 함수
	for (int i = 0;  i < row; i++) {
		for (int j = 0; j < col; j++) {
			visited[i][j] = 0;
		}
	}
}

int bfs() {
	int front, rear, cur_row, cur_col, cur_time, next_row, next_col, dir;
	front = rear = -1; cur_time = 0;

	for (int i = 0; i < M; i++) { //use에서 사용하기로 정해진 바이러스 위치들을 queue에 넣는다(초기 설정)
		queue[++rear].row = virus[use[i]].row;
		queue[rear].col = virus[use[i]].col;
		queue[rear].time = 0;
		visited[virus[use[i]].row][virus[use[i]].col] = 1;
	}

	while (front != rear) { //queue가 완전히 비워질 때까지 bfs 탐색
		cur_row = queue[++front].row; cur_col = queue[front].col; cur_time = queue[front].time; //queue에서 새로운 위치 가져오고

		dir = 0; 
		while (dir < 4) { //4가지 방향을 탐색
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir]; //4방향에 따른 변화값을 적용하여 예정된 위치를 갱신
			if (next_row < row && next_row >= 0 && next_col < col && next_col >= 0) { //예정된 위치가 map의 범위 안에 있고
				if (visited[next_row][next_col] == 0 && map[next_row][next_col] != 1) { //예정된 위치가 방문되지 않았으며 벽이 아닌 지점이면
					//해당 지점을 queue에 add하고 방문 기록 남기기
					queue[++rear].row = next_row;
					queue[rear].col = next_col;
					queue[rear].time = cur_time + 1;
					visited[next_row][next_col] = 1;
				}
			}
			dir++; //방향 바꾸기
		}
	}

	if (rear == total - 1) return cur_time; //while loop이 종료되고 벽을 제외한 모든 지점이 rear에 들어 있다면 --> 마지막 위치에서의 시행 시간(time)을 반환
	else return -1; //그렇지 않은 경우에는 모든 지점을 bfs로 도달하지 못했다는 의미이고 이 경우에는 -1을 반환

}

void choose(int count, int current) { //여러개의 바이러스 위치 중 M개를 선택하고 bfs로 넘기는 역할을 하는 함수
	int result;
	if (count == M) {
		result = bfs();

		if (min == -1) min = result; //맨처음에는 결과를 그냥 min에 대입
		else if (result != -1 && result < min) min = result; //다음부터 bfs의 결과가 min보다 작으면 최솟값 갱신

		clear(); //다음 시행을 위해 visited 초기화
	}

	else {
		for (int i = current; i < virus_count; i++) { //바이러스를 놓을 수 있는 위치만큼(virus_count) 탐색하면서
			if (virus[i].time == 0) { //virus[].time이 1이면 이용한 곳, 0이면 이용 안한 곳으로 사용 --> 사용 안한 곳이면
				use[count] = i; //사용하기 위한 index를 담는 use에다가 index를 담고
				virus[i].time = 1; //해당 지점을 사용했다는 표시를 남기고
				choose(count + 1, i + 1); //다음 지점 선택하러 이동
				virus[i].time = 0; //재귀가 끝나고 나면 이번 시행에서 변화를 주었던 곳을 상쇄시키기
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
			visited[i][j] = 0; //방문기록은 0으로 초기화
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