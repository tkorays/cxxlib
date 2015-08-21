#include "CmdDispatcher.h"

#include <iostream>

using namespace std;


jx::CmdDispatcher::CmdDispatcher(){
	
}

jx::CmdDispatcher::CmdDispatcher(int argc, char** argv, bool ignorefirst=false){
	for (int i = 0; i < argc; i++){
		if (ignorefirst && i==0){ continue; }
		this->params.push_back(std::string(argv[i]));
	}
}

void jx::CmdDispatcher::Reset(int argc, char** argv, bool ignorefirst = false){
	this->params.clear();
	for (int i = 0; i < argc; i++){
		if (ignorefirst && i == 0){ continue; }
		this->params.push_back(std::string(argv[i]));
	}
}

void jx::CmdDispatcher::Dispatch(string cmd, jx::CmdFunc func){
	if (!func){
		//this->ErrorReport(EN_INVALID_FUNCTION);
		return;
	}
	if (this->callmap.find(cmd) == this->callmap.end()){
		this->callmap.insert(pair<string, jx::CmdFunc>(cmd, func));
	}
}

void jx::CmdDispatcher::Process(){
	if (this->params.size() < 1){
		this->ErrorReport(EN_NO_INPUT_COMMAND,"please input a command");
		return;
	}
	map<string, jx::CmdFunc>::const_iterator it = this->callmap.find(this->params[0]);
	if (it != this->callmap.end()){
		if (it->second == 0){ 
			this->ErrorReport(EN_INVALID_FUNCTION,"setting error!call function is invalid.");
			return; 
		}
		((jx::CmdFunc)it->second)(this->params);
	}
	else{
		this->ErrorReport(EN_INVALID_COMMAND,"command is not found!");
	}
}

void jx::CmdDispatcher::ErrorReport(EN_ERROR err,string desc){
	switch (err){
	case EN_INVALID_FUNCTION:
		cout << "!!ERROR!! INVALID_FUNCTION," <<  desc << endl;
		break;
	case EN_NO_INPUT_COMMAND:
		cout << "!!ERROR!! NO_INPUT_COMMAND," << desc << endl;
		break;
	case EN_INVALID_COMMAND:
		cout << "!!ERROR!! INVALID_COMMAND," << desc << endl;
		break;
	default:
		break;
	}
}


void jx::CmdDispatcher::Listen(){
	string tmp;
	char c[2] = { '\0', '\0' };
	bool run = true;
	while (run){
		cout << ">> ";
		tmp.clear();
		this->params.clear();
		while (c[0] = getchar(), c[0] != '\n'){
			if (c[0] == ' ' || c[0] == '\t'){
				if (tmp.size()){
					this->params.push_back(tmp);
				}
				tmp.clear();
				continue;
			}
			tmp.append(c);
		}
		if (tmp.size()){
			this->params.push_back(tmp);
		}
		if (this->params.size() && this->params[0] == "exit"){
			run = false;
		}
		if (run){
			this->Process();
		}
	}
}

void jx::CmdDispatcher::Help(){
	cout << "Help:" << " [OriginExe] Cmd [options]" << endl;
	cout << "command list:" << endl;
	for (map<string, jx::CmdFunc>::iterator it = this->callmap.begin(); it != this->callmap.end(); it++){
		cout << "\t* " << it->first << endl;
	}
}
