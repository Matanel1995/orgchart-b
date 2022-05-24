#include <string>
#include <iterator>
#include <vector>
#include <iostream>
#include "Node.hpp"
#include <queue>

using namespace std;
namespace ariel{
    class OrgChart{
        public:
            Node *root;
            OrgChart();
            OrgChart(const OrgChart & other);//copy constructor
            OrgChart(OrgChart && other)noexcept;
            ~OrgChart();
            OrgChart &add_root(const string & title);
            OrgChart &add_sub(const string & father, const string &son);
            Node* searchNode(const string &title)const;
            friend ostream & operator<<(ostream& out, const OrgChart &org);
            OrgChart &operator=(const OrgChart & other);
            OrgChart &operator=(OrgChart && other)noexcept;
            // creating sub class for iterator
            class Iterator{
                private:
                    vector <Node*> myNodes;
                    Node* tempNode;
                public:
                Iterator(Node* node, const string &method);
                void iter_begin_level_order(Node *node);
                void iter_begin_reverse_order(Node *node);
                void iter_begin_preorder(Node *node);
                vector<Node*> getNodes();
                string * operator->();
                bool operator!=(const Iterator &other);
                string operator*();
                Iterator &operator++();
            };
            Iterator begin_level_order()const;
            Iterator end_level_order()const;
            Iterator begin_reverse_order()const;
            Iterator reverse_order()const;
            Iterator begin_preorder()const;
            Iterator end_preorder()const;
            Iterator begin()const;
            Iterator end()const;
        }; // class OrgChart
} // namespace ariel
