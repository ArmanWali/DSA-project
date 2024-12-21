#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

// Function prototypes
class Stack;
class Graph;
class CrowdControl;

class Stack {
    vector<string> stack;

public:
    void push(string name);
    void pop();
    string top();
    bool empty();
    void clear();
    void display();
};

class Graph {
    unordered_map<string, vector<pair<string, int>>> adjList;

public:
    void addEdge(string u, string v, int weight);
    void displayGraph();
    void bfs(string start);
    void dfs(string start);
    void ambulanceRouteOptimization(string start, string end);

private:
    void dfsUtil(string node, unordered_map<string, bool>& visited);
};

class CrowdControl {
    Stack crowdStack;
    queue<string> crowdQueue;

public:
    void addPersonToStack(string name);
    void removePersonFromStack();
    void emptyCrowdStack();
    void displayCrowdStack();
    void addPersonToQueue(string name);
    void removePersonFromQueue();
    void emptyCrowdQueue();
    void displayCrowdQueue();
};

// Stack methods
void Stack::push(string name) {
    stack.push_back(name);
}

void Stack::pop() {
    if (!stack.empty()) {
        stack.pop_back();
    }
}

string Stack::top() {
    if (!stack.empty()) {
        return stack.back();
    }
    return "";
}

bool Stack::empty() {
    return stack.empty();
}

void Stack::clear() {
    stack.clear();
}

void Stack::display() {
    if (stack.empty()) {
        cout << "Stack is empty." << endl;
    } else {
        cout << "Stack contents: ";
        for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
}

// Graph methods
void Graph::addEdge(string u, string v, int weight) {
    adjList[u].push_back({v, weight});
    adjList[v].push_back({u, weight});
}

void Graph::displayGraph() {
    cout << "Graph Representation:" << endl;
    for (auto& node : adjList) {
        cout << node.first << " -> ";
        for (auto& neighbor : node.second) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
}

void Graph::bfs(string start) {
    queue<string> q;
    unordered_map<string, bool> visited;

    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal starting from " << start << ": ";
    while (!q.empty()) {
        string node = q.front();
        q.pop();
        cout << node << " ";

        for (auto& neighbor : adjList[node]) {
            if (!visited[neighbor.first]) {
                visited[neighbor.first] = true;
                q.push(neighbor.first);
            }
        }
    }
    cout << endl;
}

void Graph::dfsUtil(string node, unordered_map<string, bool>& visited) {
    cout << node << " ";
    visited[node] = true;

    for (auto& neighbor : adjList[node]) {
        if (!visited[neighbor.first]) {
            dfsUtil(neighbor.first, visited);
        }
    }
}

void Graph::dfs(string start) {
    unordered_map<string, bool> visited;
    cout << "DFS Traversal starting from " << start << ": ";
    dfsUtil(start, visited);
    cout << endl;
}

void Graph::ambulanceRouteOptimization(string start, string end) {
    unordered_map<string, int> distance;
    unordered_map<string, string> parent;
    for (auto& node : adjList) {
        distance[node.first] = INT_MAX;
    }
    distance[start] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        string current = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        if (current == end) break;

        for (auto& neighbor : adjList[current]) {
            int newDist = currentDist + neighbor.second;
            if (newDist < distance[neighbor.first]) {
                distance[neighbor.first] = newDist;
                pq.push({newDist, neighbor.first});
                parent[neighbor.first] = current;
            }
        }
    }

    if (distance[end] == INT_MAX) {
        cout << "No route found from " << start << " to " << end << endl;
    } else {
        cout << "Optimized Route (Ambulance): ";
        string node = end;
        Stack path;
        while (node != start) {
            path.push(node);
            node = parent[node];
        }
        path.push(start);
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
        cout << " | Distance: " << distance[end] << endl;
    }
}

// CrowdControl methods
void CrowdControl::addPersonToStack(string name) {
    crowdStack.push(name);
    cout << name << " added to Stack." << endl;
}

void CrowdControl::removePersonFromStack() {
    if (!crowdStack.empty()) {
        cout << crowdStack.top() << " removed from Stack." << endl;
        crowdStack.pop();
    } else {
        cout << "No one in the Stack." << endl;
    }
}

void CrowdControl::emptyCrowdStack() {
    if (!crowdStack.empty()) {
        cout << "People removed from Stack in order: ";
        while (!crowdStack.empty()) {
            cout << crowdStack.top() << " ";
            crowdStack.pop();
        }
        cout << endl;
    } else {
        cout << "Crowd Stack is already empty." << endl;
    }
    cout << "Crowd Stack has been emptied." << endl;
}

void CrowdControl::displayCrowdStack() {
    crowdStack.display();
}

void CrowdControl::addPersonToQueue(string name) {
    crowdQueue.push(name);
    cout << name << " added to Queue." << endl;
}

void CrowdControl::removePersonFromQueue() {
    if (!crowdQueue.empty()) {
        cout << crowdQueue.front() << " removed from Queue." << endl;
        crowdQueue.pop();
    } else {
        cout << "No one in the Queue." << endl;
    }
}

void CrowdControl::emptyCrowdQueue() {
    if (!crowdQueue.empty()) {
        cout << "People removed from Queue in order: ";
        while (!crowdQueue.empty()) {
            cout << crowdQueue.front() << " ";
            crowdQueue.pop();
        }
        cout << endl;
    } else {
        cout << "Crowd Queue is already empty." << endl;
    }
    cout << "Crowd Queue has been emptied." << endl;
}

void CrowdControl::displayCrowdQueue() {
    if (crowdQueue.empty()) {
        cout << "Queue is empty." << endl;
    } else {
        cout << "Queue contents: ";
        queue<string> tempQueue = crowdQueue;
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << " ";
            tempQueue.pop();
        }
        cout << endl;
    }
}

int main() {
    Graph emergencyGraph;
    CrowdControl crowdControl;

    emergencyGraph.addEdge("Hospital", "Fire Station", 5);
    emergencyGraph.addEdge("Hospital", "Police Station", 3);
    emergencyGraph.addEdge("Fire Station", "Accident Site", 8);
    emergencyGraph.addEdge("Police Station", "Accident Site", 6);
    emergencyGraph.addEdge("Hospital", "Accident Site", 10);

    int choice;
    do {
        cout << "\nEmergency Services Menu:" << endl;
        cout << "1. Display Graph" << endl;
        cout << "2. BFS Traversal (Enter starting location, e.g., Hospital)" << endl;
        cout << "3. DFS Traversal (Enter starting location, e.g., Hospital)" << endl;
        cout << "4. Ambulance Route Optimization (Enter starting and destination locations, e.g., Hospital and Accident Site)" << endl;
        cout << "5. Add Person to Crowd Stack (Enter name of person)" << endl;
        cout << "6. Remove Person from Crowd Stack" << endl;
        cout << "7. Display Crowd Stack" << endl;
        cout << "8. Add Person to Crowd Queue (Enter name of person)" << endl;
        cout << "9. Remove Person from Crowd Queue" << endl;
        cout << "10. Display Crowd Queue" << endl;
        cout << "11. Empty Crowd Stack" << endl;
        cout << "12. Empty Crowd Queue" << endl;
        cout << "13. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            emergencyGraph.displayGraph();
            break;

        case 2: {
            string start;
            cout << "Enter starting location (e.g., Hospital): ";
            cin >> start;
            emergencyGraph.bfs(start);
            break;
        }

        case 3: {
            string start;
            cout << "Enter starting location (e.g., Hospital): ";
            cin >> start;
            emergencyGraph.dfs(start);
            break;
        }

        case 4: {
            string start, end;
            cout << "Enter starting location (e.g., Hospital): ";
            cin >> start;
            cout << "Enter destination location (e.g., Accident Site): ";
            cin >> end;
            emergencyGraph.ambulanceRouteOptimization(start, end);
            break;
        }

        case 5: {
            string name;
            cout << "Enter person name to add to Stack: ";
            cin >> name;
            crowdControl.addPersonToStack(name);
            break;
        }

        case 6:
            crowdControl.removePersonFromStack();
            break;

        case 7:
            crowdControl.displayCrowdStack();
            break;

        case 8: {
            string name;
            cout << "Enter person name to add to Queue: ";
            cin >> name;
            crowdControl.addPersonToQueue(name);
            break;
        }

        case 9:
            crowdControl.removePersonFromQueue();
            break;

        case 10:
            crowdControl.displayCrowdQueue();
            break;

        case 11:
            crowdControl.emptyCrowdStack();
            break;

        case 12:
            crowdControl.emptyCrowdQueue();
            break;

        case 13:
            cout << "Exiting Emergency Services System." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 13);

    return 0;
}
