#pragma once

extern  "C"
{
	#include "lua.h"
}

class LInputStream
{
	public:
		/*double getTotalLength();
		bool isExhausted();
		double getPosition();
		bool setPosition (double newPosition);
		void skipNextBytes (double numBytesToSkip);
		int readIntoMemoryBlock (LMemoryBlock &destBlock, double maxNumBytesToRead);
		*/
		static void wrapForLua (lua_State *L);
};