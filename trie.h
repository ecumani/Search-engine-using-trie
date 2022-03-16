#include<bits/stdc++.h>
using namespace std;


class trienode
{
    public:
    unordered_map<char,trienode*> child;
    bool eow;
    trienode();


};

class trie
{
    public:
    int nodes;
    int words;
    trienode* root;
    trie();
    void insert(string);
    void remove(string);
    bool sremove(trienode*,string,int);
    vector<string> searchPrefix(string);
    trienode* searchExact(string);
    void draw(trienode*,int);

};

trienode::trienode()
{
    eow=false;
}


trie::trie()
{
    root=new trienode();
}

void trie::insert(string s)
{
    trienode* current=root;
    int i;
    for(i=0;i<s.size();i++)
    {
        char c=s[i];
        //if c is found moves to its child
        if(current->child.find(c)!=current->child.end())
        {
            current=current->child[c];
        }
        //if c not found inserts a um in the child and moves to its child
        else
        {
            current->child.insert(make_pair(c,new trienode()));
            current=current->child[c];
        }
    }
    //when string ends making eow true
    current->eow=true;
}

trienode* trie::searchExact(string s)
{
    trienode* current=root;
    int i;
    //gets time-start
    auto start =chrono::high_resolution_clock::now();
    for(i=0;i<s.size();i++)
    {
        char c=s[i];
        //if c is found goes to child
        if(current->child.find(c)!=current->child.end())
        {
            current=current->child[c];
        }
        //c not found returns null
        else
        {
            return NULL;
        }
    }
    //gets time-end
    auto stop=chrono::high_resolution_clock::now();
    //gets time taken in nano sec
    auto tt=chrono::duration_cast<chrono::nanoseconds>(stop-start);
    //prints the result in ms
    cerr<<"\033[35m\n"<<current->eow<<" results in "<<double(tt.count()/double(1000000))<<" ms.\033[0m\n\n";
    //if the last c is not eow then returns null
    return current->eow ? current:NULL;

}

//does dfs and pushes words into results vector
void wordsDFS(trienode *current,string pre,vector<string> &results)
{
    if(current==NULL)
    {    
        return;
    }
    if(current->eow)
    {
        results.push_back(pre);
    }
    //we use recursion and range based for loop
    for(auto i : current->child)
    {
        wordsDFS(i.second,(pre+i.first),results);
    }
}

vector<string> trie::searchPrefix(string s)
{
    auto start=chrono::high_resolution_clock::now();
    int i;
    
    trienode* current=root;
    vector<string> results;

    for(i=0;i<s.size();i++)
    {
        char c=s[i];
        //if c is found it moves to its child
        if(current->child.find(c)!=current->child.end())
        {
            current=current->child[c];
        }
        //if the prefix is not present a empty results is returened
        else
        {
            return results;
        }
    }
    
    //if prefix is found a dfs is performed keapint the last char of the prefix as the root
    //all words is stored in results
    wordsDFS(current,s,results);
    
    auto stop=chrono::high_resolution_clock::now();
    auto tt=chrono::duration_cast<chrono::nanoseconds>(stop-start);
    cerr<<"\033[35m\n"<<results.size()<<" results in "<<double(tt.count() / double(1000000))<<" ms.\033[0m\n\n";

    //now we return the results filled with words
    return results;
}

void trie::remove(string s)
{
    sremove(root,s,0);
}

bool trie::sremove(trienode* current,string s,int i)
{
    //if string is found make eow false and return whether it has child
    if(i==s.length())
    {
        if(!current->eow)
        {
            return false;
        }

        current->eow=false;

        return current->child.size()==0;

    }

    char c=s[i];
    //string not present return false
    if(!current->child[c])
    {
        return false;
    }
    
    //recursive call if c is present
    bool delCurrentnode=sremove(current->child[c],s,i+1);

    //if the node has no children and not a eow then delete it
    //in rest cases either delcurrentnode is false or ~eow is false so node is not deleted
    if (delCurrentnode)
    {
        current->child.erase(c);
        return !current->eow&&current->child.size()==0;
    }
    
    //for the rest cases it should return false
    return false;
}

//draws the trie from current node
void trie::draw(trienode *current,int d=0)
{
    int i;
    if(!current)
    {
        current=root;
    }

    //ranged for loop basically does dfs and prints the ch along the way
    for (auto c: current->child)
    {
        //d indicates the depth
        for (i=0;i<d;i++)
        {
            cout<<"_";
        }

        cout<<c.first<<"\n";
        draw(c.second,d+1);
    }
}



/*int main()
{
    trie A;
    A.insert("happy");
    A.insert("happier");
    A.insert("happiest");
    A.insert("theme");
    A.insert("themes");
    A.insert("bad");
    A.insert("thus");
    A.draw(NULL);
    A.remove("themes");
    A.draw(NULL);

}*/