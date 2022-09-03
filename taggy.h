#ifndef TAGGY_H
#define TAGGY_H
#include <QDialog>

#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#include<unordered_map>
#include<set>

namespace Ui{
class Taggy;
}

class Taggy :public QDialog
{
public:
    void saveTagsToFile(unordered_map<string,set<string>> um,string address){
        string fileAddress=address;
        while(address[address.size()-1]!='\\' && address[address.size()-1]!='/' )
	{
            address.pop_back();
        }
        address.pop_back();
        unordered_map<string,set<string>> :: iterator it;
        string finalAdd=address+"/tags.b";
        char* c = const_cast<char*>(finalAdd.c_str());
        fstream newfile;
        newfile.open(c,ios::out);
        if(!newfile.is_open())cout<<"An error occurred!"<<endl;
        for(it=um.begin();it!=um.end();it++){
                newfile<<it->first<<endl;
            set<string> s=it->second;
            newfile<<s.size()<<endl;
            for(auto k=s.begin();k!=s.end();k++){
                    newfile<<*k<<endl;
            }
        }
        newfile.close();
    }

    unordered_map<string,set<string>> loadTagsToFile(string address){
        string fileAddress=address;
        while(address[address.size()-1]!='\\' && address[address.size()-1]!='/' ){
            address.pop_back();
        }
        address.pop_back();
        //cout<<fileAddress<<endl;
        //cout<<address<<endl;
        string key;set<string> val;
        string finalAdd=address+"/tags.b";
        //cout<<finalAdd<<endl;
        char* c = const_cast<char*>(finalAdd.c_str());
        fstream newfile;
        newfile.open(c,ios::in);
        if(!newfile.is_open())cout<<"An error occurred!"<<endl;
        unordered_map<string,set<string>> res;
        while(getline(newfile,key)){
                int n=0;
                string ch;
                getline(newfile,ch);
                for(char c:ch){
                    n=n*10+(c-'0');
                }
                //cout<<"flag:"<<ch<<endl;
                //cout<<n<<endl;
                set<string> s;
                for(int i=0;i<n;i++){
                    string temp;
                    getline(newfile,temp);
                    s.insert(temp);
                }
                res[key]=s;
            //fread(&val,1,1,f);
            //res[key]=val;
        }
        newfile.close();
        return res;
    }

    void saveFilesToTag(unordered_map<string,set<string>> um){
        unordered_map<string,set<string>> :: iterator it;
        string userpath = getenv("USERPROFILE");
        string finalAdd=userpath+"\\Documents\\fileTags.b";
        //cout<<finalAdd<<endl;
        char* c = const_cast<char*>(finalAdd.c_str());
        fstream newfile;
        newfile.open(c,ios::out);
        if(!newfile.is_open())cout<<"An error occurred!"<<endl;
        for(it=um.begin();it!=um.end();it++){
                newfile<<it->first<<endl;
            set<string> s=it->second;
            newfile<<s.size()<<endl;
            for(auto k=s.begin();k!=s.end();k++){
                    newfile<<*k<<endl;
            }
        }
        newfile.close();
    }

    unordered_map<string,set<string>> loadFilesToTag(){
        string key;set<string> val;
        string userpath = getenv("USERPROFILE");
        string finalAdd=userpath+"\\Documents\\fileTags.b";
        char* c = const_cast<char*>(finalAdd.c_str());
        fstream newfile;
        newfile.open(c,ios::in);
        if(!newfile.is_open())cout<<"An error occurred!"<<endl;
        unordered_map<string,set<string>> res;
        while(getline(newfile,key)){
                int n=0;
                string ch;
                getline(newfile,ch);
                for(char c:ch){
                    n=n*10+(c-'0');
                }
                //cout<<"flag:"<<ch<<endl;
                //cout<<n<<endl;
                set<string> s;
                for(int i=0;i<n;i++){
                    string temp;
                    getline(newfile,temp);
                    s.insert(temp);
                }
                res[key]=s;
            //fread(&val,1,1,f);
            //res[key]=val;
        }
        newfile.close();
        return res;
    }

public:
    void addTag2(string address,string tag){
            string fileName,temp=address;
            while(temp[temp.size()-1]!='\\' && temp[temp.size()-1]!='/' ){
                fileName.push_back(temp[temp.size()-1]);
                temp.pop_back();
            }
            reverse(fileName.begin(),fileName.end());
            cout<<"fileName:"<<fileName<<endl;
            unordered_map<string,set<string>> um=loadTagsToFile(address);
            set<string> s;
            if(um.count(fileName)){
                s=um[fileName];
            }
            s.insert(tag);
            um[fileName]=s;
            saveTagsToFile(um,address);
            um=loadFilesToTag();
            set<string> s2;
            if(um.count(tag)){
                s2=um[tag];
            }
            s2.insert(address);
            um[tag]=s2;
            saveFilesToTag(um);
     }

    vector <string> searching(string tag)
    {
        vector <string> ans;
        fstream centralfile;
        string userpath = getenv("USERPROFILE");
        string finalAdd=userpath+"\\Documents\\fileTags.b";
        char* c = const_cast<char*>(finalAdd.c_str());
        centralfile.open(c, ios::in);
        while(!centralfile.eof())
        {
            string temp="";
            getline(centralfile, temp);
            int isfound=0;
            for(int i=0; i<tag.size(); i++)
            {
                if(temp[i]==tag[i])
                    isfound=1;
                else
                {
                    isfound=0;
                    break;
                }
            }
            if(isfound)
            {
                string t;
                getline(centralfile, t);
                int n=stoi(t);
                for(int i=0; i<n; i++)
                {
                    string file;
                    getline(centralfile, file);
                    ans.push_back(file);
                }
                break;
            }
        }
        return ans;
    }
};

#endif // TAGGY_H
