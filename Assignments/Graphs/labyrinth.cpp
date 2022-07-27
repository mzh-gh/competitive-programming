#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

vector<int> dr{-1, 0, 1, 0}, dc{0, 1, 0, -1};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, sr, sc, x, y;
  cin >> n >> m >> sr >> sc >> x >> y;
  sr--; sc--;
  vector<vector<char>> grid(n, vector<char>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> grid[i][j];
    }
  }

  deque<pair<int, int>> q;
  vector<vector<int>> cost(n, vector<int>(m, 1e9));
  q.push_front({sr, sc});
  cost[sr][sc] = 0;
  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop_front();
    for (int i = 0; i < 4; i++) {
      int nr = r + dr[i], nc = c + dc[i];
      bool w = i == 3;
      if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '*' && cost[r][c] + w < cost[nr][nc]) {
        if (w == 1) {
          q.push_back({nr, nc});
        } else {
          q.push_front({nr, nc});
        }
        cost[nr][nc] = cost[r][c] + w;
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans += grid[i][j] != '*' && cost[i][j] <= x && cost[i][j] + j - sc <= y;
    }
  }
  cout << ans;
}