#ifndef __JX_CMDDISPATCHER_H_
#define __JX_CMDDISPATCHER_H_

#include <map>
#include <string>
#include <vector>


namespace jx{
	typedef void(*CmdFunc)(std::vector<std::string>& argv);
	typedef enum{
		EN_INVALID_FUNCTION,
		EN_NO_INPUT_COMMAND,
		EN_INVALID_COMMAND
	}EN_ERROR;

	class CmdDispatcher{
	private:
		std::map<std::string, CmdFunc> callmap;
		std::vector<std::string> params;
		CmdDispatcher(const CmdDispatcher&);
		

	public:
		CmdDispatcher();
		CmdDispatcher(int argc, char** argv, bool ignorefirst );
		void Reset(int argc, char** argv, bool ignorefirst );
		void Dispatch(std::string cmd,CmdFunc func);
		void Listen();
		void Process();
		void ErrorReport(EN_ERROR err,std::string desc);
		void Help();
	};
}

#endif // __JX_CMDDISPATCHER_H_