#ifndef NODE_HPP
#define NODE_HPP

#include "common.hpp"

struct Node {
    string word;
    unordered_map <int,unique_ptr<Node>> children;
    Node(){}
    Node(string w){
        this->word=w;
    }
};

class Word_Tree{
    public:
        unique_ptr<Node> root;
        Word_Tree(): root(nullptr){}
        void insert(string word);
        void search(string word,vector<pair<int,string>>& suggestions,int maxD);
};

class compare{
    public:
        bool operator()(pair<int,string> &a,pair<int,string> &b) {
            if(a.first==b.first) return a.second < b.second;
            return a.first < b.first;
        }
};


#endif