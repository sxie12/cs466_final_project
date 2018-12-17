#include <iostream>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <ctime>

using namespace std;

#define SZN 15
#define x first
#define y second
#define _ ios_base::sync_with_stdio(0); 
#define debug

typedef pair<int, int> PII;


struct node {
    int mask; // bitmask for state
    int nxt[SZN]; // edges;
} nodes[SZN<<1];

int n, m;
int mat[SZN][SZN], mat_cpy[SZN][SZN];

// two state perfect phylogeny
int M_mask[SZN<<1]; // sorted col bitmask
int mat2[SZN][SZN<<1];
int num[SZN<<1];
vector<PII> v;
int num_nodes;
bool used[SZN<<1];

vector<PII> zeroes;
set<string> solutions;


bool add_node(int row, int m) {
    int cur = 0;
    for (int i = m-1; i >= 0; --i) {
        if (M_mask[row] & (1<<i)) {
            if (nodes[cur].nxt[i] == -1) {
                if (used[i]) return 0;
                used[i] = 1;
                nodes[cur].nxt[i] = ++num_nodes;
                nodes[num_nodes].mask = nodes[cur].mask | (1<<i);
                memset(nodes[num_nodes].nxt, -1, sizeof(nodes[num_nodes].nxt));
            }
            cur = nodes[cur].nxt[i];
        }
    }

    return 1;
}

void clear() {
    nodes[0].mask = 0;
    memset(nodes[0].nxt, -1, sizeof(nodes[0].nxt));
    memset(used, 0, sizeof(used));
    num_nodes = 0;
}

bool cmp(const PII& a, const PII& b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x > b.x;
}

void add_solution() {
    string sol = "";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sol += (mat[i][j] + '0');
            sol += " ";
        }
        sol += "\n";
    }
    solutions.insert(sol); // figure out a way to make sol distinct
}


bool solve_two_state_phylogeny() {
    memset(mat2, 0, sizeof(mat2));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mat[i][j] == 1) {
                mat2[i][j<<1|1] = 1;
            } else if (mat[i][j] == 2) {
                mat2[i][j<<1] = mat2[i][j<<1|1] = 1;
            }
        }
    }
    memset(num, 0, sizeof(num));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m<<1; ++j)
            num[j] += mat2[i][j];

    for (int j = 0; j < m<<1; ++j)
        v.emplace_back(num[j], j);
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < n; ++i) {
        M_mask[i] = 0;
        for (int j = 0; j < v.size(); ++j)
            M_mask[i] = (M_mask[i]<<1) | mat2[i][v[j].y];
    }
    v.clear();

    clear();
    bool good = 1;
    for (int i = 0; i < n; ++i) {
        good = add_node(i, m<<1);
        if (!good) break;
    }

    return good;
}

void print_all_completions() {
    for (string s : solutions)
        cout << s << "\n";
}

void solve() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!mat[i][j])
                zeroes.emplace_back(i, j);
    for (int i = 0; i < 1<<zeroes.size(); ++i) {
        memcpy(mat, mat_cpy, sizeof(mat));
        for (int j = 0; j < zeroes.size(); ++j)
            if (i & (1<<j))
                mat[zeroes[j].x][zeroes[j].y] = 2;
        if (solve_two_state_phylogeny())
            add_solution();
    }
    print_all_completions();
}


/* Compile with 
 g++ -std=c++11 -O2 -Wall brute_force.cpp 
 */
int main(int argc, char* argv[]) { _ // disable sync with stdio
    clock_t t = 0;
    if (argc == 2 && !strcmp(argv[1], "-time")) {
        t = clock();
    }
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> mat[i][j];
    memcpy(mat_cpy, mat, sizeof(mat));

    solve();
    if (argc == 2 && !strcmp(argv[1], "-time")) {
        t = clock() - t;
        cout << "Time elapsed: " << ((double) t / CLOCKS_PER_SEC) << "\n";
    }

    return 0;
}
