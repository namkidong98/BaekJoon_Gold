//서울 지하철 2호선(골드 3)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* node_pointer;
typedef struct node {
	int vertex;
	node_pointer link;
}node;

typedef struct pos {
	int vertex;
	int distance;
}pos;

int num_of_vertex;
node_pointer* group; // 1부터 N까지
int* edge_num; //각 지하철역에서 순환선까지의 거리를 저장
int* ans; //각 지하철역에서 순환선까지의 거리를 저장
int* visited; //각 지하철역이 방문되었는지를 저장

int standard = 0;

int stack[3001];
int final_top = 0;

pos queue[3001];
int front = -1;
int rear = -1;

int end = 0;
void dfs(int index, int top) {
	int cur_index;
	node_pointer ptr;

	stack[++top] = index; visited[index] = 1;
	for (ptr = group[index]; ptr != NULL; ptr = ptr->link) {

		if (top >= 2 && ptr->vertex == standard) { //순환선이 완성되면
			for (int i = 0; i <= top; i++) { //현재 stack에 있는 지하철역의 ans를 모두 0으로 설정
				ans[stack[i]] = 0;
			}
			ans[ptr->vertex] = 0;
			final_top = top;
			end = 1; //dfs 종료 표시
			return;
		}

		if (visited[ptr->vertex] == 0) {
			dfs(ptr->vertex, top);
		}

		if (end == 1) return;
	}
}

void bfs() {
	int index, cur_distance; node_pointer ptr;

	while (front != rear) {
		index = queue[++front].vertex; cur_distance = queue[front].distance; visited[index] = 1; ans[index] = cur_distance;
		
		for (ptr = group[index]; ptr != NULL; ptr = ptr->link) {
			if (visited[ptr->vertex] == 0) {
				queue[++rear].vertex = ptr->vertex; queue[rear].distance = cur_distance + 1;
			}
		}
	}
}

int main() {
	int vertex1, vertex2; 
	node_pointer temp;

	scanf("%d", &num_of_vertex); //전체 지하철역의 숫자를 입력 받는다
	group = (node_pointer*)malloc(sizeof(node_pointer) * (num_of_vertex + 1));
	visited = (int*)malloc(sizeof(int) * (num_of_vertex + 1));
	ans = (int*)malloc(sizeof(int) * (num_of_vertex + 1));
	edge_num = (int*)malloc(sizeof(int) * (num_of_vertex + 1));
	
	for (int i = 0; i <= num_of_vertex; i++) { //초기화
		group[i] = NULL;
		ans[i] = -1;
		visited[i] = 0;
		edge_num[i] = 0;
	}

	for (int i = 0; i < num_of_vertex; i++) { //지하철역의 숫자만큼 간선도 입력 받는다
		scanf("%d %d", &vertex1, &vertex2);

		//vertex1 기준으로 vertex2 추가
		temp = (node_pointer)malloc(sizeof(node));
		temp->vertex = vertex2;
		temp->link = group[vertex1];
		group[vertex1] = temp;
		edge_num[vertex1]++;

		//vertex2 기준으로 vertex1 추가
		temp = (node_pointer)malloc(sizeof(node));
		temp->vertex = vertex1;
		temp->link = group[vertex2];
		group[vertex2] = temp;
		edge_num[vertex2]++;
	}
	
	for (int i = 1; i <= num_of_vertex; i++) { //트리 형태의 노선이 생기는 경우 해당 분기점은 노선이 3개 이상이 된다
		if (edge_num[i] >= 3) {
			standard = i; //기준이 되는 분기점을 standard로 설정
			dfs(standard, -1);
			if (end == 1) { //3개 이상의 노선을 가진 분기점인 동시에 순환선의 일부인 경우
				break;
			}
			else {//3개 이상이 된 분기점이지만 순환선의 일부는 아닌 경우
				for (int j = 0; j <= num_of_vertex; j++) visited[j] = 0; //다음 분기점에서의 dfs를 위해 visited 초기화
			}
		}
		
	}

	if (standard == 0) { //순환선만 있고 트리 형태의 노선이 없는 경우
		for (int i = 1; i <= num_of_vertex; i++) printf("0 ");
		return 0;
	}

	for (int i = 0; i <= num_of_vertex; i++) visited[i] = 0; //bfs를 위한 visited 초기화
	for (int i = 0; i <= final_top; i++) visited[stack[i]] = 1; //순환선은 재방문 하면 안되니 visited 1로 설정

	for (int i = 0; i <= final_top; i++) { //순환선과 트리 형식의 노선의 분기점이 되는 지하철 역들 queue에 넣기
		if (edge_num[stack[i]] >= 3) {
			queue[++rear].vertex = stack[i];
			queue[rear].distance = 0;
		}
	}
	bfs(); //순환선의 분기점들을 queue에 넣은 상태로 bfs를 이용하여 남은 지하철역들을 방문하여 거리 측정하여 ans를 갱신

	for (int i = 1; i <= num_of_vertex; i++) printf("%d ", ans[i]); //답 출력
}