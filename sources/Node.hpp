#include <string>
#include <vector>
using namespace std;
class Node{
    public:
    string title;
    vector<Node*> subNode;
    Node(const string & title){
        this->title = title;
    }
    ~Node(){

    }
};