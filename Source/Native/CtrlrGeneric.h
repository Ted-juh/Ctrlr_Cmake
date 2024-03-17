#pragma once
#include "CtrlrNative.h"

class CtrlrGeneric : public CtrlrNative
{
	public:
		CtrlrGeneric(CtrlrManager &owner) {}
		~CtrlrGeneric() {}
		const int getMemoryUsage(){}
		const short getCpuUsage(){}
		void timerCallback(){}
};