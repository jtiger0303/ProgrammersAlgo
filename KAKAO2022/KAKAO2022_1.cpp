#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    map<string, int> mp; //아이디를 0, 1, 2의 인덱스로 변환
    int n = id_list.size();
    set<int> s[1004]; //s[i]: i를 신고한 사람의 집합
    vector<int> cnt(n);

    for (int i = 0; i < n; i++) {
        mp[id_list[i]] = i;
    }
    for (auto& i : report) {
        stringstream ss(i);
        string id1, id2;
        ss >> id1 >> id2;
        s[mp[id2]].insert(mp[id1]);
    }
    for (int i = 0; i < n; i++) {
        if (s[i].size() < k) continue;
        for (auto x : s[i]) cnt[x]++;
    }
    return cnt;
}