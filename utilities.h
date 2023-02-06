#include<bits/stdc++.h>
using namespace std;

//stroring data from file to words
vector<string> getArrff(string s)
{
    fstream fi(s);

    string word;
    vector<string> words;
    if(!fi)
    {
        cerr<<"\nFile not opened "<<s<<" Error Occured \n";
        return words;
    }

    while(!fi.eof())
    {
        getline(fi,word);
        if(word.size())
        {
            words.push_back(word);
        }
        //check if getline works
        word="\0";
    }

    return words;

}

//does linear search for prefix
vector<string> LinSerPre(vector<string> w,string str)
{
    vector<string> results;

    int i;
    auto start=chrono::high_resolution_clock::now();
    
    //so prefix matches we append else we move on to next iteration
    for (auto s:w)
    {
        bool f=true;
        for(i=0;i<str.size();i++)
        {
            if(str[i]!=s[i])
            {
                f=false;
                break;
            }

            
        }
        if(f)
        results.push_back(s);
    }


    auto stop=chrono::high_resolution_clock::now();
    auto tt=chrono::duration_cast<chrono::nanoseconds>(stop-start);

    cerr<<"\033[35m\n"<<results.size()<<" results in "<<double(tt.count()/double(1000000))<<" ms.\033[0m\n\n";

    return results;
}



//does linear search for finding a excat string
bool LinSerExat(vector<string> w,string str)
{
    auto start=chrono::high_resolution_clock::now();

    bool f=false;

    for(auto s:w)
    {
        if(s==str)
        {
            f=true;
            break;
        }
    }

    auto stop=chrono::high_resolution_clock::now();
    auto tt=chrono::duration_cast<chrono::nanoseconds>(stop-start);

    cerr<<"\033[35m\n"<<f<<" results in "<<double(tt.count()/double(1000000))<<" ms.\033[0m\n\n";

    //we return the flag
    return f;
}

//for doing universal(substring) search we use knuth-morris-pratt(KMP) pattern mathing algorithm
//time complexity is O(P+S)
//in normal way it is O(P*S)

//we create the longest prefix suffix array
//basically this array keeps track the lps of each iteration
void LPSarray(string p,int len,int *lps)//len is length of pattern of 
{
    int j=0;

    //its always 0
    lps[0]=0;

    int i=1;

    while(i<len)
    {
        //if the charecters are same
        if(p[i]==p[j])
        {
            //j is increased by 1
            j++;
            //j becomes the value of lps[i] 
            lps[i]=j;
            //and i is incremented by 1 for next iterartion
            i++;
        }

        //pat[i]!=pat[j]
        else
        {
            
            
            if(j!=0)
            {
                //we give the value of j as j-1 iteration in lps or jump j to lps[j-1]th position
                j=lps[j-1];
                //we dont increment i here because we  
                //we must get either j=0 or the there suould be a suffix prefix to inrease i

            }

            //if j==0
            else
            {
                lps[i]=0;

                i++;
            }
        }
    }
}

//finds the occurrences of pattern in text
int KMPsearch(string p,string txt)
{
    int patlen=p.size();

    int txtlen=txt.size();

    //creating the lps array
    int lps[patlen];

    LPSarray(p,patlen,lps);

    int i=0;//iterator for txt
    int j=0;//iterator for pat

    while(i<txtlen)
    {
        //so charecters are matching
        if(p[j]==txt[i])
        {
            //we move both pat and text to the next index
            i++;
            j++;
        }
        
        //this happens only when the patten is found 
        if(j==patlen)
        {
            //here for our case we need not find all patterns
            //if a pattern is found that is enough
            return i-j;
            
        }

        //there is a mismatch after j charecters are matched
        else if(i<txtlen&&p[j]!=txt[i])
        {
            
            //here if j is not 0 j becomes the previous val in lps array
            if(j!=0)
            {
                j=lps[j-1];
                //till there is a match or j=0 we not incraese i
            }
            //if j=0 we go for next iteration
            else
            {
                i++;
            }
        }
    }

    //pattern not present we return -1
    return -1;
}


//universal search

vector<string> usearch(vector<string> s,string pat)
{
    vector<string> results;

    auto start=chrono::high_resolution_clock::now();

    for(auto str:s)
    {
        if(KMPsearch(pat,str)!=-1)
        {
            results.push_back(str);
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    auto tt=chrono::duration_cast<chrono::nanoseconds>(stop-start);

    cerr<<"\033[35m\n"<<results.size()<< " results in "<<double(tt.count()/double(1000000))<<" ms.\033[0m\n\n";

    return results;

}
