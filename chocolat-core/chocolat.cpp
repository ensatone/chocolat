#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
vector<string> words;
map<string,string> variables;
bool usingthis; bool usingthat;
bool usingif;
int ifcount;
int forcount;
string _a; string _b;
string _this;
string _that;
vector<string> forloopnames;
vector<double> forloopinits;
vector<double> forloopfinals;
vector<double> forloopdistances;
vector<string> forloopdirections;
vector<int> forlooppositions;
vector<int> whilelooplocations;
vector<string> fororwhile;
vector<vector<string>> lists;
vector<int> emptylists;
string parentlist;
string resultlistelement;
int whilecount;
vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}
bool isanumber(char character){
    if (character == '0' || character == '1' || character == '2' || character == '3' || character == '4' || character == '5' || character == '6' || character == '7' || character == '8' || character == '9'){
        return true;
    } else {
        return false;
    }
}
void getfromlist(string element, int listcount){
    if (listcount != 0){
    if (::parentlist == ""){
        ::parentlist = element;
        ::parentlist.erase(0,1);
    } else {
        ::parentlist = ::lists[stoi(::parentlist)][stoi(element)];
        ::parentlist.erase(0,1);
    }
    } else {
        ::resultlistelement = ::lists[stoi(::parentlist)][stoi(element)];
    }
}
void findemptylists(string element){
    string listnos = element;
    listnos.erase(0,1);
    int listno = stoi(listnos);
    ::emptylists.push_back(listno);
    for (int j=0; j < ::lists[listno].size(); j++){
        if (::lists[listno][j][0] == '~' && ::lists[listno][j][1] != '~'){
            findemptylists(::lists[listno][j]);
        }
    }
}
void putlist(string element, int listcount, string data){
    if (listcount != 0){
    if (::parentlist == ""){
        ::parentlist = element;
        ::parentlist.erase(0,1);
    } else {
        ::parentlist = ::lists[stoi(::parentlist)][stoi(element)];
        ::parentlist.erase(0,1);
    }
    } else {
        if (::lists[stoi(::parentlist)][stoi(element)][0] == '~' && ::lists[stoi(::parentlist)][stoi(element)][1] != '~'){
            findemptylists(::lists[stoi(::parentlist)][stoi(element)]);
        }
        ::lists[stoi(::parentlist)][stoi(element)] = data;
    }
}
void clonelist (string element){
vector<string> list;
::lists.push_back(list);
    string listnos = element;
    listnos.erase(0,1);
    int listno = stoi(listnos);
    int myid = ::lists.size() - 1;
    for (int j=0;j < ::lists[listno].size(); j++){
        if (::lists[listno][j][0] == '~' && ::lists[listno][j][1] != '~'){
            list.push_back("~" + to_string(::lists.size()));
            clonelist(::lists[listno][j]);
        } else {
            list.push_back(::lists[listno][j]);
        }
    }
    ::lists[myid] = list;
}
void interp(string filename){
    vector<string> cells;
    ifstream file;
    file.open (filename);
    if (!file.is_open()) return;

    string word;
    while (file >> word)
    {
       cells.push_back(word);
    }
for (int i=0;i<cells.size();i++){
if (cells[i]=="rd"){
interp(cells[i+1]);
} else
if (cells[i] == "asstr"){
    string listnos = ::variables["_r1"];
    listnos = listnos.erase(0,1);
    vector<string> data = ::lists[stoi(listnos)];
    string output = "";
    for (int j=0;j<data.size();j++){
        output += data[j];
    }
    ::variables["_return"] = output;
} else
if (cells[i] == "aslist"){
    vector<string> list;
    string listed = "";
    string data = ::variables["_r1"];
    for (int j=0;j<data.size();j++){
        listed = data[j];
        list.push_back(listed);
    }
    ::lists.push_back(list);
::variables["_return"] = "~" + to_string(::lists.size() - 1);
} else
if (cells[i] == "putstr"){
  int putpoint = stoi(::variables["_r2"]);
  string data = ::variables["_r1"];
  string output = "";
    for (int j=0; j<data.size(); j++){
        if (j == putpoint){
            output+=::variables["_r3"];
        } else {
            output+=data[j];
        }
    }
    ::variables["_return"] = output;
} else
if (cells[i] == "addstr"){
string data = "";
            for (int j=1;j<stoi(cells[i+1]);j++){
             data += ::variables["_r"+to_string(j)];
            }
            ::variables["_return"] = data;
} else
if (cells[i] == "at"){
    ::variables["_return"] = ::variables["_r1"][stoi(::variables["_r2"])];
} else
if (cells[i] == "split"){
vector<string> list = split(::variables["_r1"],::variables["_r2"]);
::lists.push_back(list);
::variables["_return"] = "~" + to_string(::lists.size() - 1);
} else
if (cells[i] == "readfile"){
   string data = "";
   string output = "";
   ifstream infile; 
   infile.open(::variables["_r1"]); 
   while (getline(infile,data)){
       output = output + data;
   }
   ::variables["_return"] = output; 
} else
if (cells[i] == "readfileln"){
string data = "";
    vector<string> list;
    ifstream infile;
    infile.open(::variables["_r1"]);
    while (getline(infile,data)){
        list.push_back(data);
    }
::lists.push_back(list);
::variables["_return"] = "~" + to_string(::lists.size() - 1);
} else
if (cells[i] == "writefileln"){
    ofstream outfile;
    outfile.open(::variables["_r1"]);
    outfile << ::variables["_r2"] << endl;
} else
if (cells[i] == "writefile"){
    ofstream outfile;
    outfile.open(::variables["_r1"]);
    outfile << ::variables["_r2"];
} else
if (cells[i] == "syswriteln"){
    cout << ::variables["_r1"] << endl;
} else
if (cells[i] == "remove"){
        string listnos = ::variables["_r2"];
    listnos.erase(0,1);
    int listno = stoi(listnos);
    if (::lists[listno][stoi(::variables["_r1"])][0] == '~' && ::lists[listno][stoi(::variables["_r1"])][1] != '~'){
        findemptylists(::lists[listno][stoi(::variables["_r1"])]);
    }
    ::lists[listno].erase(::lists[listno].begin() + stoi(::variables["_r1"]));
} else
if (cells[i] == "insert"){
    string listnos = ::variables["_r3"];
    listnos.erase(0,1);
    int listno = stoi(listnos);
    ::lists[listno].insert(::lists[listno].begin() + stoi(::variables["_r1"]),::variables["_r2"]);
} else
if (cells[i] == "put"){
        for (int j=1;j<stoi(cells[i+1]) - 1;j++){
        putlist(::variables["_r"+to_string(j)], stoi(cells[i+1]) - 2 - j, ::variables["_r"+to_string(stoi(cells[i+1]) - 1)]);
    }
    ::parentlist = "";
} else
if (cells[i] == "pop"){
    string listnos = ::variables["_r1"];
    listnos.erase(0,1);
    int listno = stoi(listnos);
    if (::lists[listno][::lists[listno].size() - 1][0] == '~' && ::lists[listno][::lists[listno].size() - 1][1] != '~'){
        findemptylists(::lists[listno][::lists[listno].size() - 1]);
        ::lists[listno].pop_back();
    } else {
        ::lists[listno].pop_back();
    }
} else
if (cells[i] == "append"){
    string listnos = ::variables["_r"+to_string(stoi(cells[i+1]) - 1)];
    listnos.erase(0,1);
    int listno = stoi(listnos);
    int appendlistsize = stoi(cells[i+1]) - 1;
    for (int j=1;j < appendlistsize;j++){
        ::lists[listno].push_back(::variables["_r"+to_string(j)]);
    }
} else
if (cells[i] == "size"){
    string listnos = ::variables["_r1"];
    listnos = listnos.erase(0,1);
    ::variables["_return"] = to_string(::lists[stoi(listnos)].size());
} else
if (cells[i] == "glist"){
    for (int j=1;j<stoi(cells[i+1]) + 1;j++){
        getfromlist(::variables["_g"+to_string(j)], stoi(cells[i+1]) - j);
    }
    if (::resultlistelement[0] == '~' && ::resultlistelement[1] == '~'){
        ::resultlistelement.erase(0,1);
    }
    ::variables["_return"] = ::resultlistelement;
    ::parentlist = "";
} else
if (cells[i] == "clonelist"){
    ::variables["_return"] = "~" + to_string(::lists.size());
    clonelist(::variables["_r1"]);
} else
if (cells[i] == "list"){
vector<string> list;
    for (int j=1;j< stoi(cells[i+1]) + 1;j++){
        list.push_back(::variables["_l"+to_string(j)]);
    }
    if (::emptylists.size() != 0){
    if (list.size() == 1 && list[0] == ""){
        list.pop_back();
    }
        ::variables["_return"] = "~" + to_string(::emptylists[::emptylists.size() - 1]);
        ::lists[::emptylists[::emptylists.size() - 1]] = list;
        ::emptylists.pop_back();
    } else {
    if (list.size() == 1 && list[0] == ""){
        list.pop_back();
    }
        ::lists.push_back(list);
            ::variables["_return"] = "~" + to_string(::lists.size() - 1);
    }
} else
if (cells[i] == "endw"){
    if (::whilelooplocations.size() != 0){
        i = ::whilelooplocations[::whilelooplocations.size()-1];
    } else {
        ::fororwhile.pop_back();
    }
} else
if (cells[i] == "startw"){
    ::whilelooplocations.push_back(i);
} else
if (cells[i] == "while"){
    ::fororwhile.push_back("while");
    if (::variables[cells[i+1]] == "false"){
                    for (int j=i+1;j<cells.size();j++){
            if (cells[j] == "while"){
                ::whilecount++;
            } else if (cells[j] == "endw"){
                if (::whilecount == 0){
                    ::whilelooplocations.pop_back();
                    i=j;
                    break;
                }
                ::whilecount--;
            }
        }
    }
} else
if (cells[i] == "bk"){
    if (::whilelooplocations.size() != 0 && ::fororwhile[::fororwhile.size()-1] == "while"){
        for (int j=i; j<cells.size();j++){
            if (cells[j] == "while"){
                ::whilecount++;
            } else if (cells[j] == "endw"){
                if (::whilecount == 0){
                    ::whilelooplocations.pop_back();
                    ::fororwhile.pop_back();
                    i=j;
                    break;
                }
                ::whilecount--;
            }
        }
        continue;
    }
    for (int j=i; j<cells.size(); j++){
        if (cells[j] == "for"){
            ::forcount++;
        } else if (cells[j] == "endf"){
            if (::forcount == 0){
            ::fororwhile.pop_back();
                ::forloopnames.pop_back();
                ::forloopinits.pop_back();
                ::forloopfinals.pop_back();
                ::forloopdistances.pop_back();
                ::forloopdirections.pop_back();
                ::forlooppositions.pop_back();
                i = j;
                break;
            }
            ::forcount--;
        }
    }
} else
if (cells[i] == "for"){
    ::fororwhile.push_back("for");
    ::forloopnames.push_back("_for."+::variables["_r1"]);
    ::variables["_for."+::variables["_r1"]]=::variables["_r2"];
    ::forloopinits.push_back(stod(::variables["_r2"]));
    ::forloopfinals.push_back(stod(::variables["_r3"]));
    ::forloopdistances.push_back(stod(::variables["_r4"]));
    ::forlooppositions.push_back(i);
    if (stod(::variables["_r3"])>stod(::variables["_r2"])){
        ::forloopdirections.push_back("forward");
    } else {
        ::forloopdirections.push_back("reverse");
    }
} else
if (cells[i] == "endf"){
    if (::whilelooplocations.size() != 0 && cells[i+1] == "ctn" && ::fororwhile[::fororwhile.size()-1] == "while"){
     for (int j=i;j>0;j--){
         if (cells[j] == "while"){
             i=j;
             break;
         }
     }
     continue;
    }
    if (::forloopnames.size() != 0){
        double initval = ::forloopinits[::forloopinits.size()-1];
        double finalval = ::forloopfinals[::forloopfinals.size()-1];
        double distanceval = ::forloopdistances[::forloopdistances.size()-1];
        string direction = ::forloopdirections[::forloopdirections.size()-1];
        if (direction == "forward"){
                    ::forloopinits[::forloopinits.size()-1]+=distanceval;
            ::variables[::forloopnames[::forloopnames.size()-1]] = to_string(::forloopinits[::forloopinits.size()-1]);
            
   for (int j = ::variables[::forloopnames[::forloopnames.size()-1]].size() - 1; j >= 0; j--){
            if (::variables[::forloopnames[::forloopnames.size()-1]][j] == '0'){
                  ::variables[::forloopnames[::forloopnames.size()-1]].erase(j,1);
            } else if (::variables[::forloopnames[::forloopnames.size()-1]][j] == '.'){
                ::variables[::forloopnames[::forloopnames.size()-1]].erase(j,1);
                break;
            } else {
                break;
            }
    }
            initval = ::forloopinits[::forloopinits.size()-1];
            if (initval >= finalval + distanceval){
                ::forloopnames.pop_back();
                ::forloopinits.pop_back();
                ::forloopfinals.pop_back();
                ::forloopdistances.pop_back();
                ::forloopdirections.pop_back();
                ::forlooppositions.pop_back();
                ::fororwhile.pop_back();
                if (cells[i+1] == "ctn"){
                    for (int j=i+1; j<cells.size(); j++){
                        if (cells[j] == "for"){
                            ::forcount++;
                        } else if (cells[j] == "endf"){
                             if (::forcount == 0){
                                 i = j;
                                 break;
                             }
                            ::forcount--;
                        }
                    }
                }
            } else {
                i = ::forlooppositions[::forlooppositions.size()-1];
            }
        } else if (direction == "reverse"){
            ::forloopinits[::forloopinits.size()-1]-=distanceval;
            ::variables[::forloopnames[::forloopnames.size()-1]] = to_string(::forloopinits[::forloopinits.size()-1]);
            
               for (int j = ::variables[::forloopnames[::forloopnames.size()-1]].size() - 1; j >= 0; j--){
            if (::variables[::forloopnames[::forloopnames.size()-1]][j] == '0'){
                  ::variables[::forloopnames[::forloopnames.size()-1]].erase(j,1);
            } else if (::variables[::forloopnames[::forloopnames.size()-1]][j] == '.'){
                ::variables[::forloopnames[::forloopnames.size()-1]].erase(j,1);
                break;
            } else {
                break;
            }
    }
            
            initval = ::forloopinits[::forloopinits.size()-1];
            if (initval + distanceval <= finalval){
                ::forloopnames.pop_back();
                ::forloopinits.pop_back();
                ::forloopfinals.pop_back();
                ::forloopdistances.pop_back();
                ::forloopdirections.pop_back();
                ::forlooppositions.pop_back();
                ::fororwhile.pop_back();
                if (cells[i+1] == "ctn"){
                    for (int j=i+1; j<cells.size(); j++){
                        if (cells[j] == "for"){
                            ::forcount++;
                        } else if (cells[j] == "endf"){
                             if (::forcount == 0){
                                 i = j;
                                 break;
                             }
                            ::forcount--;
                        }
                    }
                }
            }else{
                i = ::forlooppositions[::forlooppositions.size()-1];
            }
        }
    }
} else
if (cells[i]=="els"){
    if (usingif == false){
        ::usingif = true;
    } else if (usingif == true){
    ::ifcount = 0;
        for (int j=i;j<cells.size();j++){
            if (cells[j] == "endif"){
            ::ifcount--;
                if (::ifcount == 0){
                  i=j;
                  break;
                }
            }else if(cells[j] == "if" || cells[j] == "elf" || cells[j] == "els"){
                ::ifcount++;
            }
        }
    }
} else
if (cells[i]=="elf"){
    if (usingif == false){
        if (::variables[cells[i+1]] == "true"){
            ::usingif = true;
        } else if (::variables[cells[i+1]] == "false"){
        ::ifcount = 0;
            for (int j=i;j<cells.size();j++){
                if (cells[j] == "endif"){
                ::ifcount--;
                    if (::ifcount == 0){
                    i=j;
                    break;
                    }
                }else if(cells[j] == "if" || cells[j] == "elf" || cells[j] == "els"){
                    ::ifcount++;
                }
            }
        }
    } else if (usingif == true){
    ::ifcount = 0;
        for (int j=i;j<cells.size();j++){
            if (cells[j] == "endif"){
            ::ifcount--;
                if (::ifcount == 0){
                  i=j;
                  break;
                }
            }else if(cells[j] == "if" || cells[j] == "elf" || cells[j] == "els"){
                ::ifcount++;
            }
        }
    }
} else
if (cells[i]=="if"){
if (::variables[cells[i+1]] == "true"){
  ::usingif = true;
} else if (::variables[cells[i+1]] == "false"){
  ::usingif = false;
  ::ifcount = 0;
  for (int j=i;j<cells.size();j++){
      if (cells[j] == "endif"){
      ::ifcount--;
      if (::ifcount == 0){
          i = j;
          break;
          }
      }else if(cells[j] == "if" || cells[j] == "elf" || cells[j] == "els"){
          ::ifcount++;
      }
  }
}
} else
if (cells[i] == "m<="){
    if (stod(::variables[cells[i+2]]) <= stod(::variables[cells[i+3]])){
        ::variables[cells[i+1]] = "true";
    } else {
        ::variables[cells[i+1]] = "false"; 
    }
} else
if (cells[i] == "m>="){
    if (stod(::variables[cells[i+2]]) >= stod(::variables[cells[i+3]])){
        ::variables[cells[i+1]] = "true";
    } else {
        ::variables[cells[i+1]] = "false"; 
    }
} else
if (cells[i] == "m<"){
    if (stod(::variables[cells[i+2]]) < stod(::variables[cells[i+3]])){
        ::variables[cells[i+1]] = "true";
    } else {
        ::variables[cells[i+1]] = "false"; 
    }
} else 
if (cells[i]=="m>"){
    if (stod(::variables[cells[i+2]]) > stod(::variables[cells[i+3]])){
        ::variables[cells[i+1]] = "true";
    } else {
        ::variables[cells[i+1]] = "false"; 
    }
} else
if (cells[i]=="m=="){
    if (::variables[cells[i+2]] == ::variables[cells[i+3]]){
        ::variables[cells[i+1]] = "true";
    } else {
        ::variables[cells[i+1]] = "false"; 
    }
} else
if (cells[i] == "m!="){
    if (::variables[cells[i+2]] != ::variables[cells[i+3]]){
        ::variables[cells[i+1]] = "true";
    } else {
        ::variables[cells[i+1]] = "false"; 
    }
} else
if (cells[i] == "m&"){
    if (::variables[cells[i+2]] == "true" && ::variables[cells[i+3]] == "true"){
        ::variables[cells[i+1]] = "true";
    } else {
        ::variables[cells[i+1]] = "false"; 
    }
} else
if (cells[i] == "m|"){
    if (::variables[cells[i+2]] == "true" || ::variables[cells[i+3]] == "true"){
        ::variables[cells[i+1]] = "true";
    } else {
        ::variables[cells[i+1]] = "false"; 
    }
} else
if (cells[i]=="m%"){
::_a=::variables[cells[i+1]];
::_b=::variables[cells[i+2]];
::_a.erase(remove(::_a.begin(), ::_a.end(), '.'), ::_a.end());
::_b.erase(remove(::_b.begin(), ::_b.end(), '.'), ::_b.end());

::variables[cells[i+1]]=to_string( stoi(::_a)%stoi(::_b) );


 if (::variables[cells[i+1]].find('.') != std::string::npos){
    for (int j = ::variables[cells[i+1]].size() - 1; j >= 0; j--){
            if (::variables[cells[i+1]][j] == '0'){
                  ::variables[cells[i+1]].erase(j,1);
            } else if (::variables[cells[i+1]][j] == '.'){
                ::variables[cells[i+1]].erase(j,1);
                break;
            } else {
                break;
            }
    }

 }

 
} else 
if (cells[i]=="m/"){
::variables[cells[i+1]]=to_string( stod(::variables[cells[i+1]])/stod(::variables[cells[i+2]]) );

 if (::variables[cells[i+1]].find('.') != std::string::npos){
    for (int j = ::variables[cells[i+1]].size() - 1; j >= 0; j--){
            if (::variables[cells[i+1]][j] == '0'){
                  ::variables[cells[i+1]].erase(j,1);
            } else if (::variables[cells[i+1]][j] == '.'){
                ::variables[cells[i+1]].erase(j,1);
                break;
            } else {
                break;
            }
    }

 }

 
} else
if (cells[i] == "m^"){
 ::variables[cells[i+1]]=to_string( pow(stod(::variables[cells[i+1]]),stod(::variables[cells[i+2]])) );


 if (::variables[cells[i+1]].find('.') != std::string::npos){
    for (int j = ::variables[cells[i+1]].size() - 1; j >= 0; j--){
            if (::variables[cells[i+1]][j] == '0'){
                  ::variables[cells[i+1]].erase(j,1);
            } else if (::variables[cells[i+1]][j] == '.'){
                ::variables[cells[i+1]].erase(j,1);
                break;
            } else {
                break;
            }
    }

 }

 
} else 
if (cells[i]=="m*"){
::variables[cells[i+1]]=to_string( stod(::variables[cells[i+1]])*stod(::variables[cells[i+2]]) );


 if (::variables[cells[i+1]].find('.') != std::string::npos){
    for (int j = ::variables[cells[i+1]].size() - 1; j >= 0; j--){
            if (::variables[cells[i+1]][j] == '0'){
                  ::variables[cells[i+1]].erase(j,1);
            } else if (::variables[cells[i+1]][j] == '.'){
                ::variables[cells[i+1]].erase(j,1);
                break;
            } else {
                break;
            }
    }

 }

 
} else 
if (cells[i]=="m-"){
::variables[cells[i+1]]=to_string( stod(::variables[cells[i+1]])-stod(::variables[cells[i+2]]) );

 if (::variables[cells[i+1]].find('.') != std::string::npos){
    for (int j = ::variables[cells[i+1]].size() - 1; j >= 0; j--){
            if (::variables[cells[i+1]][j] == '0'){
                  ::variables[cells[i+1]].erase(j,1);
            } else if (::variables[cells[i+1]][j] == '.'){
                ::variables[cells[i+1]].erase(j,1);
                break;
            } else {
                break;
            }
    }

 }

} else 
if (cells[i]=="m+"){
::variables[cells[i+1]]=to_string( stod(::variables[cells[i+1]])+stod(::variables[cells[i+2]]) );
 if (::variables[cells[i+1]].find('.') != std::string::npos){
    for (int j = ::variables[cells[i+1]].size() - 1; j >= 0; j--){
            if (::variables[cells[i+1]][j] == '0'){
                  ::variables[cells[i+1]].erase(j,1);
            } else if (::variables[cells[i+1]][j] == '.'){
                ::variables[cells[i+1]].erase(j,1);
                break;
            } else {
                break;
            }
    }

 }

} else 
if (cells[i]=="syswrite"){
cout << ::variables["_r1"];
} else
if (cells[i]=="object"){
    ::variables["_obj"] = "_"+::variables["_r1"];
} else
if (cells[i]=="obj"){
::variables["_obj"]=cells[i+1];
} else
if (cells[i]=="st"){
::_this=cells[i+1];
} else
if (cells[i]=="sth"){
::_that=cells[i+1];
} else
if (cells[i]=="uths"){
::usingthat=true;
} else
if (cells[i]=="uthf"){
::usingthat=false;
} else
if (cells[i]=="uts"){
::usingthis=true;
} else
if (cells[i]=="utf"){
::usingthis=false;
} else
if (cells[i]=="cv"){
if (::usingthis==true){
cells[i+1]=::_this+"."+cells[i+1];
}
if (::usingthat==true){
cells[i+2]=::_that+"."+cells[i+2];
}
string donar = cells[i+1];
string receiver = cells[i+2];
if (donar[1] == '.'){
donar = ::variables["_obj"]+donar.erase(0,1);
}
if (receiver[1] == '.'){
receiver = ::variables["_obj"]+receiver.erase(0,1);
}
if (::variables[donar][0] == '~' && ::variables[donar][1] != '~' && receiver != "_return" && isanumber(donar[2]) == false){
    findemptylists(::variables[donar]);
}
::variables[donar]=::variables[receiver];
} else 
if (cells[i]=="svs"){
vector<string> variable_data;
for (int l=i;;){ l++;
if (cells[l]!="svf"){
variable_data.push_back(cells[l]);
}else {
string variable_value="";
string variable_name=variable_data[0];
if (variable_name[1] == '.'){
variable_name = ::variables["_obj"]+variable_name.erase(0,1);
}
for (int s=1;s<variable_data.size();s++){
if (s!=variable_data.size()-1){
variable_value += variable_data[s].erase(0,1)+" ";
}else{
variable_value += variable_data[s].erase(0,1);
}
}
if (::usingthis!=true){::variables[variable_name]=variable_value;}else{::variables[::_this+"."+variable_name]=variable_value;}
}

if (cells[l]=="svf"){
break;
}
}
}
}
}
int main(){
::usingthis=false; ::usingthat=false;
::variables["_return"] = "0";
::variables["_null"] = "";
::forcount = 0;
::whilecount = 0;
::parentlist = "";
interp("main.ccl");
return 0;
}
