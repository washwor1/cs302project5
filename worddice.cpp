//Andy Zeng and Walter Ashworth
//github: https://github.com/washwor1/cs302project5
//Word Dice
//Using give "Word Dices" to create words
//Sources:
// - https://cdn-uploads.piazza.com/paste/jrqj5fym2a117g/3454cdce55b4df380050bf4ac1703114dd5f427cfc4ba6e4fb432b76b5e759d4/CS302_Lab9_10-25-21.pdf
// - https://www.youtube.com/playlist?list=PLQFSAfh8OMT6qqWxJlcRrK7poAk5VcmxS

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

typedef enum{SOURCE, SINK, WORD, DICE} Node_Type;

class Edge{
    public:
    //from -> to
    class Node *to; //node edge is pointing to
    class Node *from; //node edge is pointing from
    Edge(class Node *to, class Node *from, bool reverse_edge = false); //constructor for edges
    ~Edge(){}; //default destructor
    Edge *reverse; //edge going the other way
    int original; //original weight per edge
    int residual; //allows for updated weighting during Edmonds-Karp
};

class Node{
    public:
    Node(int id, Node_Type type, string word = ""); //constructor for nodes
    ~Node(){}; //default destructor
    int id; //node id
    Node_Type type; //type of node it is (source, sink, word or dice)
    vector<bool> letters; //length 26 with letters contained in word set to 1
    int visited; //for BFS
    vector<Edge*> adj; //adjacency list
    Edge *backedge; //previous edge for Edmonds-Karp
};

class Graph{
    public:
    Graph(); //constructor initializes graph with source node
    ~Graph(); //destructor to deallocate memory of graph
    Node *source; //not necessary but makes code more readable
    vector<Node *> nodes; //holds the nodes
    vector<int> spellingIds; //order of flow to spell word
    int min_nodes; //min number of dice nodes
    void add_dice_to_graph(string die, int id); //add dice nodes to graph
    void add_word_to_graph(string word, int id); //add word (letter) nodes to graph
    bool BFS(); //breadth first search for Edmonds-Karp
    bool spell_word(); //runs Edmonds-Karp to see if we can spell the word
    void delete_word_from_graph(); //deletes the word nodes but leaves the dice nodes
    void print_node_order(string word); //print spelling Ids and word
};

bool Graph::BFS(){
    //Reset Backedges
    int size = nodes.size();
     for(int i = 0; i < size; i++){
        nodes[i]->visited = false;
        nodes[i]->backedge = NULL;
    }
    //bfs
    queue<int> bfs;
    bfs.push(SOURCE);
    while(bfs.size()){
        int node = bfs.front();
        bfs.pop();

        nodes[node]->visited = true;
        Node* next;
        Edge* edge;

        //loop through nodes adj list
        for(int i = 0; (size_t)i < nodes[node]->adj.size(); i++){
            next = nodes[node] -> adj[i]->to;
            edge = nodes[node] -> adj[i];

            //Add Unvisited node to queue
            if(!next->visited && edge -> original == 1){
                //Set its backEdge
                next -> backedge = edge -> reverse;
                bfs.push(next->id);
                //Path Found
                if(next->type == SINK)
                    return true;
            }
        }
    }
    return false;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        cerr << "./worddice input1.txt input2.txt" << endl;
        exit(1);
    }
    string Dices = argv[1];
    string words = argv[2];
    fstream re;
    re.open (Dices, std::fstream::in | std::fstream::out | std::fstream::app);

}