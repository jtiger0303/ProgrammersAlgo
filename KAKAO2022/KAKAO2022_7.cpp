#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };
int n, m;
int visited[5][5]; //방문 여부
vector<vector<int>> block;
//현재 상태에서 둘 다 최적의 플레이를 할 때 남은 이동 횟수
int solve(int y, int x, int opy, int opx) {
    // 현재 플레이어의 좌표: y, x. 상대 플레이어의 좌표: opy, opx
    if (visited[y][x]) return 0;
    int ret = 0;

    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny < 0 || ny >= n || nx < 0 || nx >= m || visited[ny][nx] || !block[ny][nx]) continue;
        visited[y][x] = 1;

        //플레이어를 i방향으로 이동시켰을 때 턴의 수
        // 다음 함수를 호출할 때 opy, opx, ny, nx 순으로 호출해야 함에 주의
        int val = solve(opy, opx, ny, nx) + 1;

        //방문 표시 해제
        visited[y][x] = 0;

        //1. 현재 저장된 턴은 패배인데 새로 계산된 턴은 승리한 경우
        if (ret % 2 == 0 && val % 2 == 1) ret = val; //바로 갱신
        //2. 현재 저장된 턴과 새로 계산된 턴이 모두 패배한 경우
        else if (ret % 2 == 0 && val % 2 == 0) {
            //최대한 늦게 지는 것을 선택
            ret = max(ret, val);
        }
        //3. 현재 저장된 턴과 새로 계산된 턴이 모두 승리한 경우
        else if (ret % 2 == 1 && val % 2 == 1) {
            ret = min(ret, val); //최대한 이기는 걸 선택
        }
    }
    return ret;
}
int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    n = board.size();
    m = board[0].size();
    block = board;
    return solve(aloc[0], aloc[1], bloc[0], bloc[1]);
}