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

//CheckerInfo class

CheckerInfo::CheckerInfo() : CheckerInfo(false, false, false, false, false, false, "") {}

CheckerInfo::CheckerInfo(bool isUpdateNeededWhenSetConfirmed, bool isUpdateNeededWhenBlankConfirmed, bool isUpdateNeededWhenBlockRangeChanged, bool isSetConfirmable, bool isBlankConfirmable, bool isBlockRangeChangeable, string checkerName)
{
	this->isUpdateNeededWhenSetConfirmed = isUpdateNeededWhenSetConfirmed;
	this->isUpdateNeededWhenBlankConfirmed = isUpdateNeededWhenBlankConfirmed;
	this->isUpdateNeededWhenBlockRangeChanged = isUpdateNeededWhenBlockRangeChanged;
	this->isSetConfirmable = isSetConfirmable;
	this->isBlankConfirmable = isBlankConfirmable;
	this->isBlockRangeChangeable = isBlockRangeChangeable;
	this->checkerName = checkerName;
}

bool CheckerInfo::get_isUpdateNeededWhenSetConfirmed() const
{
	return isUpdateNeededWhenSetConfirmed;
}

bool CheckerInfo::get_isUpdateNeededWhenBlankConfirmed() const
{
	return isUpdateNeededWhenBlankConfirmed;
}

bool CheckerInfo::get_isUpdateNeededWhenBlockRangeChanged() const
{
	return isUpdateNeededWhenBlockRangeChanged;
}

bool CheckerInfo::get_isSetConfirmable() const
{
	return isSetConfirmable;
}

bool CheckerInfo::get_isBlankConfirmable() const
{
	return isBlankConfirmable;
}

bool CheckerInfo::get_isBlockRangeChangeable() const
{
	return isBlockRangeChangeable;
}

string CheckerInfo::get_checkerName() const
{
	return checkerName;
}

