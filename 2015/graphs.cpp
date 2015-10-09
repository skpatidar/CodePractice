// Graphs : DFS and BFS / Dijkastra, Kruskal, Prim's and A*
// http://www.geeksforgeeks.org/shortest-path-exactly-k-edges-directed-weighted-graph/
// http://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/
// http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-mst-for-adjacency-list-representation/

#include "utility.h"
#include <set>

struct node;
struct edge;

typedef vector<node*>::iterator nIter;
typedef vector<edge*>::iterator eIter;

typedef struct edge {
    int val;
    struct node* from;
    struct node* to;
} edge;

typedef struct node {
    string name;
    int val;
    vector<edge*> edges;
} node;

class Graph {
    private:
    vector<node*> nodes;
    vector<edge*> edges;
    
    int numNodes;
    int numEdges;
    
    public:
    vector<edge*> mst;
    
    Graph() { nodes.clear(); edges.clear(); mst.clear(); numNodes = 0; numEdges = 0; };
    void deleteGraph(); 
    void printGraph();    
    
    int addNode(string name, int val);
    int delNode(string x);
    int addEdge(string x, string y, int val);
    int delEdge(string x, string y);
    void printEdges(vector<edge*>&);
    
    int deleteEdgeFromNode(node* n, string x);
    int deleteEdgesOfNode(string x);
    
    bool isNodeExists(string x);
    bool isAdjacent(string x, string y);
    vector<node*> getNeighbors(string x);
    
    int  getNodeVal(string x);
    void setNodeVal(string x, int val);
    node* getNode(string x); 
    
    int  getEdgeVal(string x, string y);
    void setNodeVal(string x, string y, int val);
    edge* getEdge(string x, string y);
    
    // Algorithms
    void kruskalMST();
    void primMST();

    void swap(vector<edge*> &A, int i, int j);
    void quickSort(vector<edge*> &A, int lo, int hi);
    void qSort(vector<edge*> &A);
        
};

void Graph::printGraph() {
    cout << "Graph : \n";
    nIter nodeIter = nodes.begin();
    while (nodeIter != nodes.end()) {
        cout << "Node : " << (*nodeIter)->name << "[" << (*nodeIter)->val << "] : Edges : ";
        vector<edge*>& edges = (*nodeIter)->edges;
        eIter edgeIter = edges.begin();
        while(edgeIter != edges.end()) {
            cout << "[" << (*edgeIter)->from->name << "<-[" << (*edgeIter)->val <<  "]->" << (*edgeIter)->to->name << "] ";
            edgeIter++;
        }
        cout << "\n";
        nodeIter++;
    }
}

void Graph::deleteGraph() {
    cout << "Graph : \n";
    
    // Delete Edges
    vector<edge*>::iterator edgeIter = edges.begin();
    while (edgeIter != edges.end()) {
        cout << "Deleting edge : " << "[" << (*edgeIter)->from->name << "<->" << (*edgeIter)->to->name << "]\n";
        delete(*edgeIter);
        edgeIter++;
    }
    
    // Delete Nodes
    vector<node*>::iterator nodeIter = nodes.begin();
    while (nodeIter != nodes.end()) {
        cout << "Deleting node : " << (*nodeIter)->name << "\n";
        delete(*nodeIter);
        nodeIter++;
    }
}

bool Graph::isNodeExists(string name) {
    nIter nodeIter = nodes.begin();
    while(nodeIter != nodes.end()) {
        if ((*nodeIter)->name == name) 
            return true;
        nodeIter++;
    }
    return false; 
}

node* Graph::getNode(string name) {
    nIter nodeIter = nodes.begin();
    while(nodeIter != nodes.end()) {
        if ((*nodeIter)->name == name) 
            return (*nodeIter);
        nodeIter++;
    }
    return NULL; 
}

bool Graph::isAdjacent(string x, string y) {
    eIter edgeIter = edges.begin();
    while(edgeIter != edges.end()) {
        if ((*edgeIter)->from->name == x && (*edgeIter)->to->name == y)
            return true;
        edgeIter++;
    }
    return false;  
}

int Graph::addNode(string name, int val) {
    if (name == "" || isNodeExists(name)) {
        cout << "Node exists or node name = " << name << " is null\n";
        return 1;
    }
    node* newNode = new node;
    newNode->name = name;
    newNode->val = val; 
    nodes.push_back(newNode);
    cout << "Adding node : " << name << "\n";
    numNodes++;
    return 0;
}

int Graph::addEdge(string nodeX, string nodeY, int val) {
    if (isAdjacent(nodeX, nodeY)) {
        cout << "Edge already exists\n";
        return 1;
    }
    
    node* from = getNode(nodeX);
    node* to = getNode(nodeY);
    if (from == NULL || to == NULL) {
        cout << "Nodes connecting the edge do not exist\n";
        return 2;  
    }
    
    edge* newEdge = new edge;
    newEdge->from = from;
    newEdge->to = to;
    newEdge->val = val;
    edges.push_back(newEdge);
    
    from->edges.push_back(newEdge);
    to->edges.push_back(newEdge);
    
    cout << "Adding Edge [" << nodeX << "<->" << nodeY << "]\n";
    numEdges++;
    return 0;
}

int Graph::deleteEdgeFromNode(node* n, string x) {
    vector<edge*>& edgeList = n->edges;
    eIter edgeIter = edgeList.begin();
    
    while(edgeIter != edgeList.end()) {
        if ((*edgeIter)->from->name == x || (*edgeIter)->to->name == x) {
            cout << "Deleting edge of node : " << x << "\n";
            edgeList.erase(edgeIter);
            return 0;
        }
        edgeIter++;
    }
    cout << "Did not find an edge for Node : " << x << "\n";
    return 1;
}

void Graph::printEdges(vector<edge*>& _edges) {
    eIter edgeIter = _edges.begin();
    cout << "EdgeList [" << _edges.size() << "] : ";
    while(edgeIter != _edges.end()) {
        cout << "[" << (*edgeIter)->from->name << "<->" << (*edgeIter)->to->name << "] ";
        edgeIter++;
    }
    cout << "\n";
}

int Graph::deleteEdgesOfNode(string x) {
    eIter edgeIter = edges.begin();        
    while(edgeIter != edges.end()) {
        printEdges(edges);
        if ((*edgeIter)->from->name == x || (*edgeIter)->to->name == x) {
            if ((*edgeIter)->from->name == x) {
                deleteEdgeFromNode((*edgeIter)->to, x);
            } else {
                deleteEdgeFromNode((*edgeIter)->from, x);
            }
            edges.erase(edgeIter);
        }
        if (edgeIter != edges.end()) edgeIter++;
    }
    return 0;
}

int Graph::delNode(string x) {
    // Delete all edges from this node
    deleteEdgesOfNode(x);

    cout << "Deleted all edges connecting to node : " << x << "\n";
    
    // Delete 
    nIter nodeIter = nodes.begin();
    while(nodeIter != nodes.end()) {
        if ((*nodeIter)->name == x) {
            nodes.erase(nodeIter);
            break;
        }
        nodeIter++;
    }
    numNodes--;
    return 0;
}

int Graph::delEdge(string x, string y) {
    eIter edgeIter = edges.begin();        
    while(edgeIter != edges.end()) {
        if ( ((*edgeIter)->from->name == x || (*edgeIter)->to->name == x) && ((*edgeIter)->from->name == y || (*edgeIter)->to->name == y) ) {
            if ((*edgeIter)->from->name == x) {
                deleteEdgeFromNode((*edgeIter)->from, y);
                deleteEdgeFromNode((*edgeIter)->to, x);
            } else {
                deleteEdgeFromNode((*edgeIter)->from, x);
                deleteEdgeFromNode((*edgeIter)->to, y);
            }
            edges.erase(edgeIter);
        }
        if (edgeIter != edges.end()) edgeIter++;
    }
    numEdges--;
    return 0;
}

void Graph::swap(vector<edge*> &A, int i, int j) {
    edge* temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void Graph::quickSort(vector<edge*> &A, int lo, int hi) {
    if (hi < lo) return;
    
    int pivot = lo, swapIndex = lo+1;
    for (int i=lo+1; i <= hi; i++) {
        if (A[i]->val < A[pivot]->val) {
            swap(A, i, swapIndex);
            swapIndex++;
        }
    }
    swap(A, pivot, swapIndex-1);
    quickSort(A, lo, swapIndex - 2);
    quickSort(A, swapIndex, hi);
}

void Graph::qSort(vector<edge*> &A) {
    quickSort(A, 0, (A.size()-1));
}

void printSets(vector<set<node* > >& A) {
    cout << "Printing " << A.size() << " number of sets :\n";
    vector<set<node* > >::iterator iter = A.begin();
    while(iter != A.end()) {
        cout << "\t{";
        set<node*>::iterator sIter = (*iter).begin();
        while(sIter != (*iter).end()) {
            cout << (*sIter)->name << ", ";
            sIter++;
        }
        cout << "}\n";
        iter++;
    }
}

void Graph::primMST() {
    
}

void Graph::kruskalMST() {
    // Sort Edges 
    // Pick least weight edge, unless forming a cycle in existing MST
    // Stop at V-1 edges in MST

    // Sort
    vector<edge*> sortedEdges = edges;
    qSort(sortedEdges);
    printEdges(sortedEdges);

    /*
    vector<set<node*> > nodeSets; 
    nIter nodeIter = nodes.begin(); 
    while(nodeIter != nodes.end()) {
        set<node*> s; 
        s.insert(*nodeIter);
        nodeSets.push_back(s);
        nodeIter++;
    }
    printSets(nodeSets);
    */
    
    vector<node*> nodeSets;
    vector<int> parentNode;
    nIter nodeIter = nodes.begin(); 
    while(nodeIter != nodes.end()) {
        nodeSets.push_back(*nodeIter); 
        parentNode.push_back(-1);
        nodeIter++;
    }
    
    nodeIter = nodeSets.begin(); 
    while(nodeIter != nodeSets.end()) {
        cout << "Node : " << (*nodeIter)->name << " : " << parentNode[nodeIter - nodeSets.begin()] << "\n";
        nodeIter++;
    }
    
    // Add edges to mst 
    while(mst.size() < (numNodes-1) && sortedEdges.size() > 0) {
        edge* curEdge = sortedEdges[0];
        string from = curEdge->from->name;
        string to = curEdge->to->name;
        
        nodeIter = nodeSets.begin(); 
        bool sameSet = 0;
        while(nodeIter != nodeSets.end()) {
            if ((*nodeIter)->name == from) {
                int i = nodeIter - nodeSets.begin();
                while ( !sameSet && parentNode[i] != -1) {
                    if (nodeSets[parentNode[i]]->name == to) {
                        sameSet = 1;
                    }
                    i = parentNode[i];
                }
            }
            nodeIter++;
        }
        if (sameSet) {
            cout << "Node : " << from << " and Node : " << to << " belong to same set\n";
            cout << "Skip edge and continue\n";
        } else {
            cout << "Node : " << from << " and Node : " << to << " belong to different sets and the edge can be used\n";
            // Set 'from' set to merge with 'to'
            nodeIter = nodeSets.begin(); 
            int i = 0;
            while(nodeIter != nodeSets.end()) {
                if ((*nodeIter)->name == from) {
                    i = nodeIter - nodeSets.begin();
                    while ( parentNode[i] != -1) {
                        i = parentNode[i];
                    }
                }
                nodeIter++;
            }
            
            //
            nodeIter = nodeSets.begin();
            while(nodeIter != nodeSets.end()) {
                if ((*nodeIter)->name == to) {
                    int c = nodeIter - nodeSets.begin();
                    parentNode[i] = c; 
                }
                nodeIter++;
            }
            mst.push_back(curEdge);
            cout << "NumNodes = " << numNodes << " MST Size = " << mst.size() << "\n";
            
            /* Print Set status
            nodeIter = nodeSets.begin(); 
            while(nodeIter != nodeSets.end()) {
                cout << "Node : " << (*nodeIter)->name << " : " << parentNode[nodeIter - nodeSets.begin()] << "\n";
                nodeIter++;
            }*/
        }
        sortedEdges.erase(sortedEdges.begin());
    }
}

int main() {
    Graph *g = new Graph;
    
    #if 0 
    {
    g->printGraph();
    g->addNode("A", 1);
    g->addNode("B", 2);
    g->addNode("C", 3);
    g->printGraph();
    
    g->addEdge("A", "B", 1);
    g->addEdge("A", "C", 1);
    g->addEdge("C", "B", 1);
    
    g->printGraph();
    g->delNode("B");
    g->printGraph();
    
    g->addNode("B", 2);
    g->addEdge("B", "A", 1);
    g->printGraph();
    g->delEdge("B", "A");
    g->printGraph();
    
    g->delNode("B");
    g->printGraph();
    
    g->deleteGraph();
    }
    #endif 
    
    {
    g->addNode("A", 0); g->addNode("B", 0); g->addNode("C", 0); g->addNode("D", 0);
    g->addNode("E", 0); g->addNode("F", 0); g->addNode("G", 0); g->addNode("H", 0);
    g->addEdge("A", "B", 1); g->addEdge("B", "C", 2); g->addEdge("C", "D", 2); g->addEdge("C", "E", 3);
    g->addEdge("D", "E", 2); g->addEdge("D", "G", 1); g->addEdge("E", "F", 2); g->addEdge("F", "G", 1);
    g->addEdge("F", "H", 2); g->addEdge("G", "H", 4); g->addEdge("A", "G", 3); g->addEdge("A", "H", 3);
    
    g->printGraph();
    }
    
    //g->kruskalMST();
    g->primMST();
    g->printEdges(g->mst);
    
    return 0;
}