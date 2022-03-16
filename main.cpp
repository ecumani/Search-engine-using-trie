#include<bits/stdc++.h>
#include<dirent.h>

#include "trie.h"
#include "utilities.h"


using namespace std;


void imptrie();



int main(int argc,char **argv)
{
    string filename;

    trie tr;

    vector<string> data;
    vector<string> namesOfFiles;

    DIR *dir;
    struct dirent *diread;

    int i=0;
    
    //this is for cml line arguments
    if(argc >1)
    {
        filename = argv[1];
        data =getArrff(filename);
    }

    else
    {
        cout<<"Enter File name to load data from\n ";
        //this part is to find the data files present in the datas directory
        if((dir=opendir("datas"))!=nullptr)
        {
            while((diread=readdir(dir))!=nullptr)
            {
                namesOfFiles.push_back(diread->d_name);
            }
            closedir(dir);
        }
        else
        {
            perror("error in opendir");
            return EXIT_FAILURE;
        }
        
        for(i=0;i<namesOfFiles.size();i++)
        {
            if(namesOfFiles[i][0]!='.')
            {
                cout<<namesOfFiles[i];
            
                if(i!=namesOfFiles.size()-1)
                {
                    cout<<" | ";
                }
            }
        }
        cout<<" :"<<endl;

        cin>>filename;
        cerr<<"loding ...";
        data=getArrff("datas/"+filename);
        cout<<"Done.\n";


    }

    for(string word :data)
    {
        tr.insert(word);
    }

    int choice;

    //cmd line argument will do universal search
    if (argc>2)
    {
        string pa=argv[2];
        for(string s: usearch(data,pa))
        {
            cout<<s<<endl;
        }
        return EXIT_SUCCESS;
    }

    do
    {
        cout<<"Your chosen file is "<<filename<<endl;
        
        cout<<"---------------------\n";
        cout<<"MENU\n";
        cout<<"1. Exact Search.\n";
        cout<<"2. Prefix Search.\n";
        cout<<"3. Universal Search\n";
        cout<<"4. Implement a Trie\n";
        cout<<"0. Exit\n";

        cin>>choice;
        //to get /n
        getchar();

        string pat;

        

        switch(choice)
        {
            case 1:
            
            if(choice)
            {
                cout<<"Enter search text (leave empty to list all) :";
                getline(cin,pat);
            }
            cout<<"Exact search using trie\n";
            if(tr.searchExact(pat))
            {
                cout<<"String Exists.\n";
            }
            else
            {
                cout<<"Not found. :(\n";
            }
            cout<<"\nIn linear search\n";
            if(LinSerExat(data,pat))
            {
                cout<<"String Exists.\n";
            }
            else
            {
                cout<<"Not found. :(\n";
            }
            break;
        
            case 2:
            
            if(choice)
            {
                cout<<"Enter search text (leave empty to list all) :";
                getline(cin,pat);
            }
            //here we do just return all itmes with the given prefix
            //so linear prefix seach is acctullay much efficient than using a trie
            //but for doing a weighted prefix search trie is more efficient than bruteforcing
            cout<<"Prefix search using trie\n";
            for(string s:tr.searchPrefix(pat))
            {
                cout<<s<<"\n";
            }
            cout<<"\nTime taken in linear prefix search\n";
            for(string s:LinSerPre(data,pat))
            {
                cout<<s<<"\n";
            }
            break;

            case 3:
            if(choice)
            {
                cout<<"Enter search text (leave empty to list all) :";
                getline(cin,pat);
            }
            for(string s:usearch(data,pat))
            {
                cout<<s<<"\n";
            }
            break;

            case 4:
            imptrie();
            
            
            
           
        
        
        }
        if(choice!=4)
        {
            cout<<"\n\npress any key to continue...";
            getchar();
        }
        system("cls");

    }while(choice);

    return EXIT_SUCCESS;
}



void imptrie()
{
    system("cls");
    trie temp;
    int choice;
    string s;

    do
    {
        cout<<"---------------------\n";
        cout<<"MENU-Implement Trie\n";
        cout<<"1. Insert.\n";
        cout<<"2. Remove.\n";
        cout<<"3. Draw (visualize)\n";
        cout<<"0. Back\n";
        

        cin>>choice;
            //to get /n
        getchar();

        switch(choice)
        {
            case 1:
            cout<<"Enter the string to insert:\n";
            cin>>s;
            getchar();
            temp.insert(s);
            cout<<"Inserted sucessfully\n";
            break;
                
            case 2:
            cout<<"Enter the string to remove:\n";
            cin>>s;
            getchar();
            temp.remove(s);
            cout<<"if the string was present it was sucessfully removed\n";
            break;
                
            case 3:
            temp.draw(NULL);

        }
        cout<<"\npress any key to continue...\n";
        getchar();
        system("cls");

    }while(choice);
    
    return;
}