// imports
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>
#include <algorithm>
#include <chrono>
#define INF INT_MAX
#define MAX 1073741824
using namespace std;

 
// Implementation of priority queue
class PriorityQueue {
private:
    vector<pair<int, int>> arr;
    void heapfiyUP(int index) {
        int pIndex = (index - 1) / 2;
        if (pIndex <= 0)     return;
        if (arr[index].first < arr[pIndex].second) {
            swap(arr[index], arr[pIndex]);
            heapfiyUP(pIndex);
        }
    }
    void heapifyDOWN(int index) {
        if (index >= arr.size())     return;
        int leftIndex = 2 * index + 1;
        int rightIndex = 2 * index + 2;
        int minIndex = index;
        if (leftIndex < arr.size() && arr[leftIndex].second < arr[minIndex].second) minIndex = leftIndex;
        if (rightIndex < arr.size() && arr[rightIndex].second < arr[minIndex].second) minIndex = rightIndex;
        if (minIndex != index) {
            swap(arr[minIndex], arr[index]);
            heapifyDOWN(minIndex);
        }
    }
public:
    PriorityQueue() { }
    void push(pair<int, int> p) {
        arr.push_back(p);
        heapfiyUP(arr.size() - 1);
    }
    pair<int, int> pop() {
        pair<int, int> p = arr[0];
        arr[0] = arr[arr.size() - 1];
        arr.pop_back();
        heapifyDOWN(0);
        return p;
    }
    void updateKey(pair<int, int> p) {
        int index = -1;
        for (int i = 0; i < arr.size(); ++i)
            if (arr[i].first == p.first) {
                index = i;
                break;
            }
        if (index == -1)        return;
        if (p.second < arr[index].second) {
            arr[index].second = p.second;
            heapfiyUP(index);
        }
        else if (p.second > arr[index].second) {
            arr[index].second = p.second;
            heapifyDOWN(index);
        }
    }
    bool empty() {
        return (arr.size() == 0);
    }
};


// converts the vector to string!
string vect_to_str(vector<int>& vect) {
    stringstream text;
    text << "{";
    int N = vect.size();
    for (int i = 0; i < N; ++i)
        if (i != N - 1) text << vect[i] + 1 << ",";
        else                    text << vect[i] + 1;
    text << "}";
    return text.str();
}

// prints a separator
void separator(int x) {
    for (int i = 0; i < x; ++i) cout << "-";
    cout << endl;
}

// driver function
int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        cout << "Error: #arguments must be at least 3 and at most 4" << endl;
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];
    int sourceNode = atoi(argv[2]) - 1;
    bool printImmediate = false;
    if (argc == 4) printImmediate = (atoi(argv[3]) == 1);

    // read the input file
    fstream fin(filename, ios::in);
    if (!fin.is_open()) {
        cout << "Failed to open " << filename << endl;
        exit(EXIT_FAILURE);
    }

    // get the time before processing
    auto start = chrono::steady_clock::now();

    // read the number of vertices
    int N, source, dest, weight;
    fin >> N;

    // store the network
    vector<vector<pair<int, int>>> adj;
    for (int i = 0; i < N; ++i) {
        vector<pair<int, int>> vect;
        adj.push_back(vect);
    }

    // read the file
    while (!fin.eof()) {
        // read values from file!
        fin >> source >> dest >> weight;
        // check if there is a link
        if (weight < MAX) adj[source - 1].push_back(make_pair(dest - 1, weight));
    }
    // close the file after reading
    fin.close();


    // display the information
    // need this array to be dynamic
    int distance[N];
    int parent[N];
    for (int i = 0; i < N; ++i) {
        distance[i] = INF;
        parent[i] = -1;
    }
    fin.close();
    // left align the content
    cout << left;

    // compute the information
    vector<int> popped;
    int step = 0;
    PriorityQueue pq;
    pq.push(make_pair(sourceNode, 0));
    distance[sourceNode] = 0;
    parent[sourceNode] = 1;

    // print output if required!
    if (printImmediate) {
        separator(10 + 50 + (N - 1) * 10);
        cout << setw(10) << "Step" << setw(50) << "N'";
        for (int i = 0; i < N; ++i)
            if (i != sourceNode)
                cout << setw(10) << (i + 1);
        cout << endl;
        separator(10 + 50 + (N - 1) * 10);
    }

    // apply Dijkstra's algorithm!
    while (!pq.empty()) {
        pair<int, int> item = pq.pop();
        popped.push_back(item.first);


        int u = item.first;
        int d = item.second;

        vector<pair<int, int>>& vect = adj[u];
        for (pair<int, int>& p : vect) {
            int v = p.first;
            int w = p.second;
            if (distance[v] == INF) {
                distance[v] = distance[u] + w;
                parent[v] = u;
                pq.push(make_pair(v, distance[v]));
            }
            else if (distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                parent[v] = u;
                pq.updateKey(make_pair(v, distance[v]));
            }
        }

        // print if required!
        if (printImmediate) {
            cout << setw(10) << step++ << setw(50) << vect_to_str(popped);
            for (int i = 0; i < N; ++i)
                if (i != sourceNode) {
                    if (find(popped.begin(), popped.end(), i) != popped.end()) {
                        cout << setw(10) << "";
                    }
                    else {
                        cout << setw(10) << ((distance[i] != INF ? to_string(distance[i]) : "INF") + "," + to_string(parent[i] + 1));
                    }
                }
            cout << endl;
        }

    }

    // print if required
    if (printImmediate) cout << endl << endl;

    cout << "FORWARDING TABLE:" << endl;
    separator(40);
    cout << setw(20) << "Destination" << " | " << setw(20) << "Link" << endl;
    separator(40);
    for (int i = 0; i < N; ++i)
        if (i != sourceNode) {
            if (parent[i] == sourceNode) {
                cout << setw(20) << (i + 1) << " | " << setw(20) <<
                    ("(" + to_string(sourceNode + 1) + "," + to_string(parent[i] + 1) + ")") << endl;
            }
            else {
                cout << setw(20) << (i + 1) << " | " << setw(20) <<
                    ("(" + to_string(parent[parent[i]] + 1) + "," + to_string(parent[i] + 1) + ")") << endl;
            }
        }


    // get the time after processing
    auto end = chrono::steady_clock::now();

    // compute the difference
    cout << "\nExecution time: " << chrono::duration <double, milli>(end - start).count() << "ms" << endl;
    return 0;
}