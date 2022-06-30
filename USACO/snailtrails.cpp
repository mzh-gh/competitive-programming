// mzh

/*
Informal proof/explanation:
First, let's ignore the side walls and only consider paths that don't involve Bessie "flying out into space".
If the number of paths increases exponentially, the number of barriers needed to maintain the paths do as well. For example, if one path splits into two, we'll need 2 barriers to maintain the two paths. If each of those splits into two, we'll need four more, etc. So, the maximum number of splits is actually ~log(B). Since the number of paths = 2^splits, there will be at most B paths.

Since we can't revisit past positions, the maximum possible path length is N^2.

If we consider side walls, not much really changes. Since we can make at most one additional "split" and move along the walls, we won't have to perform more than ~8N additional operations for each path.

This makes for a total of a O(B * (N^2 + 8 * N)), which should take ~3e6 operations at most.
*/

#include <bits/stdc++.h>

using namespace std;

#define int int64_t

int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};

int n, w;
int state[120][120];

int in(int r, int c) {
  return r >= 0 && r < n && c >= 0 && c < n;
}

int dfs(int r, int c, int d) {
  state[r][c] = 1;
  int ans = 0;
  if (in(r + dr[d], c + dc[d]) && state[r + dr[d]][c + dc[d]] == 0) {
    ans = dfs(r + dr[d], c + dc[d], d);
  } else if (in(r + dr[d], c + dc[d]) && state[r + dr[d]][c + dc[d]] == 1) {
    ans = 0;
  } else {
    for (int D : {(d + 3) % 4, (d + 1) % 4}) {
      if (in(r + dr[D], c + dc[D]) && state[r + dr[D]][c + dc[D]] == 0) {
        ans = max(ans, dfs(r + dr[D], c + dc[D], D));
      }
    }
  }
  state[r][c] = 0;
  return ans + 1;
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> w;
  for (int i = 0; i < w; i++) {
    string s;
    cin >> s;
    state[stoi(s.substr(1)) - 1][s[0] - 'A'] = 2;
  }
  cout << max(dfs(0, 0, 1), dfs(0, 0, 2));
}