//벽 부수고 이동하기 4(골드 2)
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

	//초기 위치를 queue에 넣는다
	queue[++rear].row = start_row; queue[rear].col = start_col; visited[start_row][start_col] = 1;
	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; //queue에서 위치 가져오기

		dir = 0;
		while (dir < 4) { //4가지 방향을 탐색하면서
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir++]; //예상되는 다음 좌표를 갱신하고
			if (next_row >= ROW || next_row < 0 || next_col >= COL || next_col < 0) continue; //범위 밖이면 패스
			if (map[next_row][next_col] == 0 && visited[next_row][next_col] == 0) { //map에서 0인 지점이면서 아직 방문되지 않은 지점은
				queue[++rear].row = next_row; queue[rear].col = next_col; //queue에 추가하기
				visited[next_row][next_col] = 1;
			}
		}
	}


	int plus = rear + 1; //그룹의 멤버 수를 구한 것으로 이제 인접한 1에다가 할당량을 추가시켜주면 된다
	pos save[1001 * 1001];
	int top = 0;

	front = -1; //이미 bfs로 인접한 0의 위치들은 queue에 있으므로 front만 초기화해서 탐색하면 된다
	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; //queue에서 위치 가져오고
		dir = 0;
		while (dir < 4) { //4방향을 탐색해서
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir++];
			if (next_row >= ROW || next_row < 0 || next_col >= COL || next_col < 0) continue; //범위 밖이면 패스하고
			if (map[next_row][next_col] != 0 && visited[next_row][next_col] == 0) { //범위 안이고 map에서 0이 아닌 지점인 동시에 아직 방문되지 않은 곳(같은 그룹에서 중복해서 더하는 것을 방지하기 위해)
				map[next_row][next_col] += plus; //그룹의 멤버수를 더해주고
				visited[next_row][next_col] = 1; //같은 그룹에서 중복해서 더하지 않기 위한 장치를 해놓고
				save[top].row = next_row; save[top++].col = next_col; //그 위치를 이번 bfs가 끝나고 초기화 해줘야 하기 때문에 해당 위치를 stack에다가 저장
			}
		}
	}

	//stack에 저장해둔 visited를 1로 바꿔둔 지점을 다음 시행을 위해 원상복구 시켜 놓는 작업
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
			if (map[i][j] == 0 && visited[i][j] == 0) { //0인 지점을 기준으로 그룹이 몇개인지 세고 근처에 인접한 1에다가 그룹의 멤버 수만큼을 추가한다
				bfs(i, j);
			}
		}
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			printf("%d", map[i][j] % 10); //10으로 나눈 수를 출력해야 한다
		}
		printf("\n");
	}
}