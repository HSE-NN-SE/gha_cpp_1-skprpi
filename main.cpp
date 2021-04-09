#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

int timer = 0;

int min(int a, int b){
    if ( a < b){
        return a;
    }
    return b;
}

int max(int a, int b){
    if ( a > b){
        return a;
    }
    return b;
}

void find_bridge(int pos, int prev, vector<bool>& visited,
                 vector<int> &t_in, vector<int>& t_up, vector<vector<int>>& p, set<pair<int,
        int>>& ans, map<pair<int, int>, vector<int>>& mp){
    visited[pos] = true;
    t_in[pos] = t_up[pos] = timer++;
    for (auto & next_pos: p[pos]){
        if (next_pos == prev) continue;
        if (visited[next_pos]){
            t_up[pos] = min(t_up[pos], t_in[next_pos]);
        } else {
            find_bridge(next_pos, pos, visited, t_in, t_up, p, ans, mp);
            t_up[pos] = min(t_up[pos], t_up[next_pos]);
            if (t_up[next_pos] > t_in[pos] && mp[make_pair(min(next_pos, pos), max(next_pos, pos))].size() == 1){
                ans.emplace(min(pos, next_pos), max(pos, next_pos));
            }
        }
    }
}



int main() {
    int n, m;
    cin >> n >> m;
    vector<bool> visited(n + 1, false);
    vector<int> t_in(n + 1, 0);
    vector<int> t_up(n + 1, 0);
    set<pair<int, int>> ans;
    vector<vector<int>> p(n + 1);
    map<pair<int, int>, vector<int>> mp;
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        p[a].emplace_back(b);
        p[b].emplace_back(a);
        mp[make_pair(min(a, b), max(a, b))].push_back(i + 1);
    }

    for (int i = 1; i < n + 1; i++){
        if (!visited[i]){
            find_bridge(i, -1, visited, t_in, t_up, p, ans, mp);
        }
    }
    set<int> final_ans;
    for (auto & el: ans){
        for (auto & e: mp[el]){
            final_ans.emplace(e);
        }
    }
    cout << final_ans.size() << endl;
    for (auto & el: final_ans){
        cout << el << endl;
    }


    return 0;
}