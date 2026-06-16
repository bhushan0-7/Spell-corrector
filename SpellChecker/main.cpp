#include "Node.hpp"
#include <iostream>
#include <fstream>

int EditDistance(string a,string b){
    int m=a.size(),n=b.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));

    for(int i=0;i<=m;i++) dp[i][0]=i;
    for(int j=0;j<=n;j++) dp[0][j]=j;

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(a[i-1]==b[j-1]) dp[i][j]=min({dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]});
            else dp[i][j]=min({dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]+1});;
        }
    }
    return dp[m][n];
}

string toLower(string& s) {
    string res;
    for(int i=0;i<s.size();i++){
        if(s[i]>='A' && s[i]<='Z') res.push_back(s[i]-'A'+'a');
        else res.push_back(s[i]);
    }
    return res;
}

void Word_Tree::insert(string word){
    if(!root){
        root=make_unique<Node>(word);
        return;
    }
    else {
        Node* curr=root.get();
        while(1){
            int dist=EditDistance(word,curr->word);
            if(dist==0) return;
            if(curr->children.find(dist)==curr->children.end()){
                curr->children[dist]=make_unique<Node>(word);
                return;
            }
            else {
                curr=curr->children[dist].get();
            }
        }
    }
    return;
}

void Word_Tree::search(string word,vector<pair<int,string>>& suggestions,int maxD){
    if(!root) return;
    stack<Node*> s;
    s.push(root.get());
    while(!s.empty()) {
        Node* temp=s.top();
        s.pop();
        if(temp->word!=""){
            int dist=EditDistance(word,temp->word);
            if(dist<=maxD) suggestions.push_back({dist,temp->word});
            for(auto& it:temp->children) {
                if(it.first <= maxD+dist && it.first >= dist-maxD) s.push(it.second.get());
            }
        }
    }
}

int main() {
    Word_Tree tree;
    ifstream file("words.txt");
    string word;
    while(file){
        file>>word;
        if(word!="") tree.insert(toLower(word));
    }
    cout << "Enter a word:";
    string input;cin>>input;
    string query = toLower(input);

    vector<pair<int, string>> suggestions;
    tree.search(query, suggestions, 2);
    sort(suggestions.begin(),suggestions.end(),compare());

    if (suggestions.empty()) {
        cout << "No suggestions found for '" << input << "\n";
    } else {
       cout<<"Did you mean?"<<endl;
       for(int i=0;i<min(10,int(suggestions.size()));i++) {
        cout<<suggestions[i].second<<endl;
       }
    }
    return 0;
}
