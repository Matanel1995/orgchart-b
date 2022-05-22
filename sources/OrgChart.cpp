#include <stack>
#include "OrgChart.hpp"

using namespace std;
using namespace ariel;

OrgChart::OrgChart(){
    this->root = nullptr;
}

OrgChart::~OrgChart(){

}

OrgChart& OrgChart::add_root(const string & title){
    //check the title is not empty
    if(title.empty()){
        throw std::runtime_error("Cant enter with no name!");
    }
    if(this->root == nullptr){ // no root before this one so create new one
        Node* newRoot = new Node(title);
        this->root = newRoot;
    }
    else{// allready have root, need only to change his name 
        this->root->title = title;
    }
    return *this;
}

OrgChart& OrgChart::add_sub(const string & father, const string &son){
    // SEARCH FOR THE FATHER NODE
    if(father.empty() || son.empty()){
        throw std::runtime_error("Cant enter with no name!");
    }
    Node* tempFather = searchNode(father);
    if (tempFather != nullptr)
    {
        Node* newNode = new Node(son);
        tempFather->subNode.push_back(newNode);
    }
    else{
        throw std::runtime_error("No such emplyer");
    }
    return *this;
}

Node* OrgChart::searchNode(const string &title)const{
    //Function to search and return node

    //if the tree is empty (no root) throw exeption
    if(this->root == nullptr){
        throw std::runtime_error("Cant search for node in empty tree!");
    }
    //search for the node
    std::queue<Node*> tempQueue; // Queue for insert visited nodes
    tempQueue.push(this->root);
    while (!tempQueue.empty()) // while queue is not empty
    {
        Node* temp = tempQueue.front();
        if(temp->title == title){
            return temp; // found the node and return it
        }
        // check all node subs if found return it if now add to queue becouse ill need to check their subs
        for(unsigned int i=0; i<temp->subNode.size();i++){
            if(temp->subNode.at(i)->title == title){
                return temp->subNode.at(i);
            }
            // that not the node so ill add him to queue in order to search his subs
            tempQueue.push(temp->subNode.at(i));
        }
        tempQueue.pop();//remove main node for this iteration
    }
    return nullptr;
}

ostream & ariel::operator<<(ostream& out, const OrgChart &org){
    OrgChart::Iterator it = OrgChart::Iterator(org.root,"LEVEL");
    vector<Node*> myNodes = it.getNodes();
    for(unsigned int i=0; i<myNodes.size();i++){
        out << myNodes.at(i)->title << "---" ;
    }
    return out;
}

OrgChart::Iterator::Iterator(Node* node, const string &method){
    //creating the corret Iterator 
    if(node != nullptr){
        if(method == "LEVEL"){
            iter_begin_level_order(node);
            this->tempNode = this->getNodes().at(0);
        }
        else if (method == "REVERSE"){
            iter_begin_reverse_order(node);
            this->tempNode = this->getNodes().at(0);
        }
        else if(method == "PREORDER"){
            iter_begin_preorder(node);
            this->tempNode = this->getNodes().at(0);
        }
        else{
            throw std::runtime_error("Cant create Iterator!");
        }
    }
    else{
        this->tempNode = nullptr;
    }
}

void OrgChart::Iterator::iter_begin_level_order(Node *node){
    //imlementing level order with queue
    std::queue<Node*> tempQueue;
    if(node == nullptr){
        throw std::runtime_error("Cant iter on NULL");
    }
    //adding nodes to iterator nodes vector
    tempQueue.push(node);
    this->myNodes.push_back(node);// adding root to my vector
    Node* tempNode= node;
    while(!tempQueue.empty()){
        for(unsigned int i=0; i<tempNode->subNode.size();i++){
            this->myNodes.push_back(tempNode->subNode.at(i)); // adding to iterator vector
            tempQueue.push(tempNode->subNode.at(i)); // adding to my queue
        }
        tempQueue.pop();// removing the node (finished with him)
        tempNode = tempQueue.front();
    }

}

void OrgChart::Iterator::iter_begin_preorder(Node *node){
    //implementing preorder 
    this->myNodes.push_back(node);
    for(unsigned int i=0;i<node->subNode.size();i++){
        iter_begin_preorder(node->subNode.at(i));
    }
}

void OrgChart::Iterator::iter_begin_reverse_order(Node *node){
    //implementing reverse level order 
    std::queue<Node*> tempQueue;
    std::stack<Node*> tempStack;
    if(node == nullptr){
        throw std::runtime_error("Cant iter on NULL");
    }
        //adding nodes to iterator nodes vector
    tempQueue.push(node);
    //this->myNodes.push_back(node);// adding root to my vector
    Node* tempNode= node;
    while(!tempQueue.empty()){
        tempStack.push(tempNode);// adding node to stack
        for(unsigned int i=0; i<tempNode->subNode.size();i++){ // adding all noed subs to queue
            tempQueue.push(tempNode->subNode.at(tempNode->subNode.size()-i-1)); // adding to my queue
        }
        tempQueue.pop();// removing the node (finished with him)
        tempNode = tempQueue.front(); // updating the new "root"
    }
    while(!tempStack.empty()){ // adding all nodes to my iterator vector
        this->myNodes.push_back(tempStack.top());
        tempStack.pop();
    }
}

vector<Node*> OrgChart::Iterator::getNodes(){
    return this->myNodes;
}

string* OrgChart::Iterator::operator->(){
    return &(this->tempNode->title);
}

bool OrgChart::Iterator::operator!=(const Iterator &other){
    return this->tempNode != other.tempNode;
}

string OrgChart::Iterator::operator*(){
    return this->tempNode->title;
}

OrgChart::Iterator & OrgChart::Iterator::operator++(){
    if(this->myNodes.size() > 1){
        this->myNodes.erase(this->myNodes.begin());
        this->tempNode = this->myNodes.at(0);
    }
    else{
        this->tempNode = nullptr;
    }
    return *this;
}

OrgChart::Iterator OrgChart::begin_level_order()const{
    if(this->root == nullptr){
        throw std::runtime_error("Null");
    }
    Iterator temp = Iterator(this->root,"LEVEL");
    return temp;
}
OrgChart::Iterator OrgChart::end_level_order()const{
    if(this->root == nullptr){
        throw std::runtime_error("Null");
    }
    Iterator temp = Iterator(nullptr,"Null");
    return temp;
}
OrgChart::Iterator OrgChart::begin_reverse_order()const{
    if(this->root == nullptr){
        throw std::runtime_error("Null");
    }
    Iterator temp = Iterator(this->root,"REVERSE");
    return temp;
}
OrgChart::Iterator OrgChart::reverse_order()const{
    if(this->root == nullptr){
        throw std::runtime_error("Null");
    }
    Iterator temp = Iterator(nullptr,"Null");
    return temp;
}
OrgChart::Iterator OrgChart::begin_preorder()const{
    if(this->root == nullptr){
        throw std::runtime_error("Null");
    }
    Iterator temp = Iterator(this->root,"PREORDER");
    return temp;
}
OrgChart::Iterator OrgChart::end_preorder()const{
    if(this->root == nullptr){
        throw std::runtime_error("Null");
    }
    Iterator temp = Iterator(nullptr,"Null");
    return temp;
}
OrgChart::Iterator OrgChart::begin()const{
    if(this->root == nullptr){
        throw std::runtime_error("Null");
    }
    Iterator temp = Iterator(this->root,"LEVEL");
    return temp;
}
OrgChart::Iterator OrgChart::end()const{
    if(this->root == nullptr){
        throw std::runtime_error("Null");
    }
    Iterator temp = Iterator(nullptr,"Null");
    return temp;
}