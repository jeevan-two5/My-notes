#include <bits/stdc++.h>
using namespace std;

int n, m;

struct node {
    int val;
    int cost;
    int d;
    node() {
        val = 0;
        cost = 0;
        d = 0;
    }
};

vector<vector<node>> table;
vector<int> req;
vector<int> avail;
vector<int> u, v;

// ------------------- VOGEL METHOD -------------------
void implement_vogel() {
    vector<int> temp_avail = avail;
    vector<int> temp_req = req;

    while (true) {
        vector<pair<int, int>> row_penalty(n, {-1, INT_MAX});
        vector<pair<int, int>> col_penalty(m, {-1, INT_MAX});

        for (int i = 0; i < n; i++) {
            if (temp_avail[i] > 0) {
                int first_min = INT_MAX, second_min = INT_MAX, min_index = -1;
                for (int j = 0; j < m; j++) {
                    if (temp_req[j] > 0) {
                        if (table[i][j].cost < first_min) {
                            second_min = first_min;
                            first_min = table[i][j].cost;
                            min_index = j;
                        } else if (table[i][j].cost < second_min) {
                            second_min = table[i][j].cost;
                        }
                    }
                }
                row_penalty[i] = {second_min - first_min, min_index};
            }
        }

        for (int j = 0; j < m; j++) {
            if (temp_req[j] > 0) {
                int first_min = INT_MAX, second_min = INT_MAX, min_index = -1;
                for (int i = 0; i < n; i++) {
                    if (temp_avail[i] > 0) {
                        if (table[i][j].cost < first_min) {
                            second_min = first_min;
                            first_min = table[i][j].cost;
                            min_index = i;
                        } else if (table[i][j].cost < second_min) {
                            second_min = table[i][j].cost;
                        }
                    }
                }
                col_penalty[j] = {second_min - first_min, min_index};
            }
        }

        int max_penalty = -1, row_or_col = -1, index = -1;
        bool is_row = false;

        for (int i = 0; i < n; i++) {
            if (temp_avail[i] > 0 && row_penalty[i].first > max_penalty) {
                max_penalty = row_penalty[i].first;
                index = i;
                row_or_col = row_penalty[i].second;
                is_row = true;
            }
        }

        for (int j = 0; j < m; j++) {
            if (temp_req[j] > 0 && col_penalty[j].first > max_penalty) {
                max_penalty = col_penalty[j].first;
                index = j;
                row_or_col = col_penalty[j].second;
                is_row = false;
            }
        }

        if (max_penalty == -1)
            break;

        if (is_row) {
            int i = index;
            int j = row_or_col;
            int allocation = min(temp_avail[i], temp_req[j]);
            table[i][j].val = allocation;
            temp_avail[i] -= allocation;
            temp_req[j] -= allocation;
        } else {
            int j = index;
            int i = row_or_col;
            int allocation = min(temp_avail[i], temp_req[j]);
            table[i][j].val = allocation;
            temp_avail[i] -= allocation;
            temp_req[j] -= allocation;
        }
    }
}

// ------------------- NORTH WEST CORNER RULE -------------------
void implement_nwcr() {
    vector<int> temp_avail = avail;
    vector<int> temp_req = req;

    int i = 0, j = 0;
    while (i < n && j < m) {
        int allocation = min(temp_avail[i], temp_req[j]);
        table[i][j].val = allocation;
        temp_avail[i] -= allocation;
        temp_req[j] -= allocation;

        if (temp_avail[i] == 0 && temp_req[j] == 0) {
            i++;
            j++;
        } else if (temp_avail[i] == 0) {
            i++;
        } else if (temp_req[j] == 0) {
            j++;
        }
    }
}

// ------------------- OPTIMALITY CHECK -------------------
pair<int, int> check_optimal() {
    u.assign(n, INT_MAX);
    v.assign(m, INT_MAX);
    u[0] = 0;

    bool updated;
    for (int k = 0; k < n + m - 1; k++) {
        updated = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (table[i][j].val != 0) {
                    if (u[i] != INT_MAX && v[j] == INT_MAX) {
                        v[j] = table[i][j].cost - u[i];
                        updated = true;
                    } else if (v[j] != INT_MAX && u[i] == INT_MAX) {
                        u[i] = table[i][j].cost - v[j];
                        updated = true;
                    }
                }
            }
        }
        if (!updated)
            break;
    }

    bool optimal = true;
    pair<int, int> min_ind = {-1, -1};
    int min_val = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i][j].val == 0) {
                table[i][j].d = table[i][j].cost - (u[i] + v[j]);
                if (table[i][j].d < min_val) {
                    min_val = table[i][j].d;
                    min_ind = {i, j};
                    optimal = false;
                }
            }
        }
    }

    if (optimal)
        return {-1, -1};
    return min_ind;
}

// ------------------- COST CALCULATION -------------------
void print_final_cost() {
    int total_cost = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i][j].val > 0)
                total_cost += table[i][j].val * table[i][j].cost;
        }
    }
    cout << "Total transportation cost = " << total_cost << endl;
}

// ------------------- DEGENERACY CHECK -------------------
void check_degeneracy() {
    int occupied = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (table[i][j].val > 0)
                occupied++;

    int required = n + m - 1;
    cout << "Number of occupied cells = " << occupied << endl;
    cout << "Required (m + n - 1) = " << required << endl;

    if (occupied < required)
        cout << "→ The solution is **Degenerate**." << endl;
    else if (occupied == required)
        cout << "→ The solution is **Non-Degenerate**." << endl;
    else
        cout << "→ Invalid basic feasible solution (too many allocations)." << endl;
}

// ------------------- MAIN -------------------
int main() {
    cout << "Enter number of sources: ";
    cin >> n;
    cout << "Enter number of destinations: ";
    cin >> m;

    table.resize(n, vector<node>(m));

    cout << "Enter cost matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> table[i][j].cost;

    cout << "Enter availability:\n";
    avail.resize(n);
    for (int i = 0; i < n; i++)
        cin >> avail[i];

    cout << "Enter requirements:\n";
    req.resize(m);
    for (int i = 0; i < m; i++)
        cin >> req[i];

    cout << "\nChoose IBFS method:\n1. North West Corner Rule\n2. Vogel Approximation Method\nEnter choice: ";
    int choice;
    cin >> choice;

    if (choice == 1)
        implement_nwcr();
    else
        implement_vogel();

    cout << "\nInitial Basic Feasible Solution:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << setw(5) << table[i][j].val;
        cout << endl;
    }

    print_final_cost();
    cout << endl;

    // ✅ Check for degeneracy
    check_degeneracy();
    cout << endl;

    // ✅ Check for optimality
    pair<int, int> result = check_optimal();
    if (result == make_pair(-1, -1))
        cout << "→ The current solution is **Optimal**." << endl;
    else
        cout << "→ The current solution is **Not Optimal**." << endl;

    return 0;
}


