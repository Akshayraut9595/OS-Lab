#include <bits/stdc++.h>
using namespace std;

bool notpresent(vector<char>&pageframe, char ch){
    for(int i=0;i<pageframe.size();i++){
        if(pageframe[i] == ch){
            return  false;
        }
    }
    return true;
}

int getidx(vector<char>&pageframe, char ch){
    for(int i=0;i<pageframe.size();i++){
        if(pageframe[i] == ch){
            return i;
        }
    }
    return 0;
}

void printPageframe(vector<char>&pageframe){
    cout<<"Pageframe is ";
    for(int i=0;i<pageframe.size();i++){
        cout<<pageframe[i]<<" ";
    }
    cout<<endl;
}

void fifo(string s, int pfs){
    vector<char> pageframe;
    queue<char> q;
    int pc = 0;
    for(int i=0;i<s.size();i++){
        cout<<"\nInteserting "<<s[i]<<endl;
        if(notpresent(pageframe, s[i])){
            if(pageframe.size() == pfs){
                int idx = getidx(pageframe, q.front());
                pageframe[idx] = s[i];
                q.pop();
            }
            else{
                pageframe.push_back(s[i]);
            }
            q.push(s[i]);
            pc++;
        }
        else{
            cout<<"No need to insert ";
        }
        printPageframe(pageframe);
    }

    cout<<"Total pageframe count is "<<pc<<endl;
}

char getchar(map<char, int> mp){
    int min = INT_MAX;
    char ch = '0';
    for(auto it:mp){
        if(it.second < min){
            min = it.second;
            ch = it.first;
        }
    }

    return ch;
}

void lru(string s, int pfs){
    vector<char> pageframe;
    map<char, int> mp;
    int pc = 0;
    int ts = 0;
    for(int i=0;i<s.size();i++){
        cout<<"\nInserting "<<s[i]<<endl;
        if(notpresent(pageframe, s[i])){
            if(pageframe.size() == pfs){
                char ch = getchar(mp);
                int idx = getidx(pageframe, ch);
                pageframe[idx] = s[i];
                mp.erase(ch);
            }
            else{
                pageframe.push_back(s[i]);
            }
            pc++;
        }
        else{
            cout<<"No need to insert ";
        }
        mp[s[i]] = ts;
        ts++;
        printPageframe(pageframe);
    }

    cout<<"\nTotal pageframe count is "<<pc<<endl;
}

char getlru(vector<char>&pageframe, string s, int idx){
    map<char, int> mp;
    for(int i=0;i<pageframe.size();i++){
        mp[pageframe[i]] = INT_MAX;
        for(int j=s.size()-1;j>=idx;j--){
            if(s[j] == pageframe[i]){
                mp[s[j]] = j;
            }
        }

        if(mp[pageframe[i]] == INT_MAX){
            return pageframe[i];
        }
    }

    if(mp.size() == 0){
        return pageframe[0];
    }

    int max = INT_MIN;
    char ch = pageframe[0];
    for(auto it:mp){
        if(it.second > max){
            max = it.second;
            ch = it.first;
        }
    }

    return ch;
}

void optimal(string s, int pfs){
    vector<char>pageframe; 
    int pc = 0;
    for(int i=0;i<s.size();i++){
        cout<<"\nInserting "<<s[i]<<endl;

        if(notpresent(pageframe, s[i])){
            if(pageframe.size() == pfs){
                char ch = getlru(pageframe, s, i);
                int idx = getidx(pageframe,ch);
                pageframe[idx] = s[i];
            }
            else{
                pageframe.push_back(s[i]);
            }
            pc++;
        }
        else{
            cout<<"No need to insert ";
        }

        printPageframe(pageframe);
    }

    cout<<"Total pageframe count is "<<pc<<endl;
}

int main(){
    string s; // s = 637216357271
    cout<<"Enter the string : ";
    cin>>s;

    cout<<"Enter the pageframe size : ";
    int pfs;
    cin>>pfs; // pfs = 3

    // fifo(s, pfs);
    // lru(s,pfs);
    optimal(s,pfs);
    return 0;
}
