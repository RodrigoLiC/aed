#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Compare {
    bool operator()(const vector<int>& v1, const vector<int>& v2) {
        return v1[2] < v2[2];
    }
};

class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        vector<vector<int>> v;
        vector<vector<int>> b;
        for (int i = 0; i < row; i++) {
            vector<int> temp;
            vector<int> temp2;
            for (int j = 0; j < col; j++) {
                temp.push_back(0);
                temp2.push_back(0);
            }
            v.push_back(temp);
            b.push_back(temp2);
        }
        for (int i = 0; i < cells.size(); i++) {
            v[cells[i][0] - 1][cells[i][1] - 1] = i + 1;
        }

        vector<vector<int>> tagged_cells;
        int size = cells.size();
        for(int i = 0; i < size; i++) {
            vector<int> temp;
            temp.push_back(cells[i][0] - 1);
            temp.push_back(cells[i][1] - 1);
            temp.push_back(i+1);
            tagged_cells.push_back(temp);
        }

        priority_queue<vector<int>, vector<vector<int>>, Compare> pendientes;

        for (int i = 0; i < col; i++) {
            int k = v[0][i];
            pendientes.push(tagged_cells[k - 1]);
        }

        vector<vector<int>> visitados;
        for (int i = 0; i < tagged_cells.size()*4; i++) {
            vector<int> curr = pendientes.top();
            visitados.push_back(curr);
            pendientes.pop();

            if (curr[0] == row - 1) {
                break;
            }

            vector<vector<int>> adj = getAdjacent(curr[0], curr[1], v, b);
            for (int j = 0; j < adj.size(); j++) {
                pendientes.push(adj[j]);
            }
        }

        // obtener el minimo valor de visitados
        int mini = visitados[0][2];
        for (int i = 1; i < visitados.size(); i++) {
            if (visitados[i][2] < mini) {
                mini = visitados[i][2];
            }
        }

        return mini - 1;
    }

    vector<vector<int>> getAdjacent(int row, int col, vector<vector<int>>& v, vector<vector<int>>& b) {
        vector<vector<int>> adj;

        if (row - 1 >= 0) {
            if (b[row-1][col] == 0) {
                vector<int> temp = {row - 1, col, v[row-1][col]};
                adj.push_back(temp);
                b[row-1][col] = 1;
            }
        }
        if (row + 1 < v.size()) {
            if (b[row+1][col] == 0) {
                vector<int> temp = {row + 1, col, v[row+1][col]};
                adj.push_back(temp);
                b[row+1][col] = 1;
            }
        }
        if (col - 1 >= 0) {
            if (b[row][col-1] == 0) {
                vector<int> temp = {row, col - 1, v[row][col-1]};
                adj.push_back(temp);
                b[row][col-1] = 1;
            }
        }
        if (col + 1 < v[0].size()) {
            if (b[row][col+1] == 0) {
                vector<int> temp = {row, col + 1, v[row][col+1]};
                adj.push_back(temp);
                b[row][col+1] = 1;
            }
        }

        return adj;
    }
};
