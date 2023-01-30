//ABCDE (골드 5)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node* node_pointer;
typedef struct _node {
	int index;
	node_pointer link;
}node;
node_pointer* group; //사람 수 만큼 누구와 친구 관계인지 저장하는 변수
int* visited; //해당 사람을 방문했는지를 나타내는 변수
int flag = 0; //0이면 친구관계가 없다, 1이면 친구관계가 있다

void dfs(int index, int depth) {
	node_pointer ptr;
	visited[index] = 1;

	if (depth >= 5) {
		flag = 1;
		return;
	}

	for (ptr = group[index]; ptr != NULL; ptr = ptr->link) {
		if (flag == 1) return;
		if (visited[ptr->index] == 0) {
			dfs(ptr->index, depth + 1);
		}
	}
	visited[index] = 0; //해당 길목을 갔을 때 길이 없다면 돌아가게 되는데, 이 때 해당 지점이 방문 표시 되어 있으면 제대로 체크가 안 된다
	return;
}

int main() {
	int N, M; //N은 사람 수, M은 친구 관계 수
	node_pointer temp, ptr;
	int vertex1, vertex2;
	scanf("%d %d", &N, &M);
	group = (node_pointer*)malloc(sizeof(node_pointer) * N);
	visited = (int*)malloc(sizeof(int) * N);

	//group과 visited를 0으로 초기화
	for (int i = 0; i < N; i++) {
		group[i] = NULL;
		visited[i] = 0;
	}

	//친구 관계 수 만큼 관련 정보 group에 저장하기
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &vertex1, &vertex2);

		temp = (node_pointer)malloc(sizeof(node));
		temp->index = vertex2;
		temp->link = group[vertex1];
		group[vertex1] = temp;

		temp = (node_pointer)malloc(sizeof(node));
		temp->index = vertex1;
		temp->link = group[vertex2];
		group[vertex2] = temp;
	}

	for (int i = 0; i < N; i++) {
		dfs(i, 1); //시작 지점을 0번, 1번, 2번...이렇게 바꿔가면서 N명을 시작점으로 가능한지 파악
		if (flag == 1) break;
	}

	printf("%d", flag);
}