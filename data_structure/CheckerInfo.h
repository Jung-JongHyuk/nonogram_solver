#pragma once

#include <string>
using namespace std;

class CheckerInfo
{
	public:
		CheckerInfo();
		CheckerInfo(bool isUpdateNeededWhenSetConfirmed, bool isUpdateNeededWhenBlankConfirmed, bool isUpdateNeededWhenBlockRangeChanged, bool isSetConfirmable, bool isBlankConfirmable, bool isBlockRangeChangeable, string checkerName);
	
		bool get_isUpdateNeededWhenSetConfirmed() const;
		bool get_isUpdateNeededWhenBlankConfirmed() const;
		bool get_isUpdateNeededWhenBlockRangeChanged() const;
		bool get_isSetConfirmable() const;
		bool get_isBlankConfirmable() const;
		bool get_isBlockRangeChangeable() const;
		string get_checkerName() const;
	
	private:
		bool isUpdateNeededWhenSetConfirmed, isUpdateNeededWhenBlankConfirmed, isUpdateNeededWhenBlockRangeChanged;
		bool isSetConfirmable, isBlankConfirmable, isBlockRangeChangeable;
		string checkerName;
};

