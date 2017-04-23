#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;
string pwd = get_current_dir_name();
int pipecount = 0;
void prompt(){
  cout<<"1730sh:"<<pwd<<"/$";
}
void fillargs(string commandline, vector<string> &args){
  string give="";
  for(uint i =0 ;i<commandline.length();i++){
    if(commandline[i]==' '){continue;}
    give+=commandline[i];
    if(commandline[i+1]==' ' && commandline[i+2]!= ' '){
      args.push_back(give);
      give = "";
    }
  }
  args.push_back(give);
}
void fillprocesses(vector<string> args, vector<vector<string>>&processes){
  vector<string>sorter;
  for(uint i=0;i<args.size();i++){
    bool redirect = false;
    if(redirect == true){
      redirect = false;
      continue;
    }
    if(args[i][0]=='|'){
      pipecount++;
      processes.push_back(sorter);
      sorter.clear();
      continue;
    }//if a pipe is encountered
    if(args[i][0]=='>'&&args[i][1]=='>'){
      redirect = true;
      continue;
    }//if append
    if(args[i][0]=='>'){
      redirect = true;
      continue;
    }//if truncate
    if(args[i][0]=='<'){
      redirect = true;
      continue;
    }//stdin
    if(args[i][0]=='e'&&args[i][1]=='>'&&args[i][2]=='>'){
      redirect = true;
      continue;
    }
    sorter.push_back(args[i]);
  }
  processes.push_back(sorter);
}
int main(){
  bool run = true;
  while(run){
    prompt();
    string commandline;
    vector<string>args;
    vector<vector<string>>processes;
    getline(cin,commandline);
    fillargs(commandline,args);
    fillprocesses(args,processes);

    if(pipecount == 0 && strcmp(args[0].c_str(),"cd")==0){
      chdir(args[1].c_str());
      pwd =  get_current_dir_name();
      cout<<"1730sh: cd:"<<args[1]<<": No such file or directory"<<endl;
    }
    else if(pipecount == 0 && (strcmp(args[0].c_str(),"help")==0)|(strcmp(args[0].c_str(),"h")==0))
      {cout<<"MAXIMUM LUVV SHELL v1.0"<<endl
           <<"AUTHORS: ANDREW STOUT, CALEB GERBER."<<endl
           <<"Built in functions: cd, exit, help."<<endl
           <<"Other commands the same as UNIX"<<endl;
      }
    else if(pipecount == 0 && (strcmp(args[0].c_str(),"exit")==0)){
      return(EXIT_SUCCESS);
    }
    else{cout<<"1730sh:"<<args[0]<<": command not found"<<endl;}
  }
}

