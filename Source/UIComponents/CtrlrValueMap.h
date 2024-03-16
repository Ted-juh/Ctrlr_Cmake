#pragma once
#include "CtrlrMacros.h"

struct CtrlrValue
{
	CtrlrValue(const int _numericValue, const String &_textRepresentation)
		: numericValue(_numericValue), textRepresentation(_textRepresentation)
	{}
	CtrlrValue()
	{}

	static const String toString(const CtrlrValue &value)
	{
		return ("\"" + value.textRepresentation + "\" [" + _STR(value.numericValue) + "]");
	}
	JUCE_LEAK_DETECTOR(CtrlrValue);

	int		numericValue;
	String	textRepresentation;
};

class CtrlrValueMap
{
	public:
		CtrlrValueMap(const String &stringToParseAsMap);
		CtrlrValueMap();
		~CtrlrValueMap();
		void parseString (const String &stringToParseAsMap);
		void copyFrom (const CtrlrValueMap &map);
		int getMappedMax() const;
		int getMappedMin() const;
		int getNonMappedMax() const;
		int getNonMappedMin() const;
		int getNumValues() const;
		int getIndexForValue(const int value) const;
		int getMappedValue(const int valueIndex) const;
		int getNonMappedValue(const String &textRepresentation) const;
		int getMappedValue(const String &textRepresentation) const;
		const String getTextForIndex(const int valueIndex) const;
		void increment();
		void decrement();
		bool mappedValueExists (const int mappedValue);
		int getCurrentNonMappedValue() const;
		int getCurrentMappedValue() const;
		const String getCurrentText() const;
		void setCurrentNonMappedValue(const int _currentValue);
		void setCurrentMappedValue(const int _currentValue);
		void setPair (const int index, const int value, const String &text);
		void clear();

		const Array<CtrlrValue> &getMap() const;
		const Array<int> &getNumericValues() const;
		const HashMap<int,String> &getAdditionalData() const;
		void addAdditionalData (const int index, const String &data);
		void fillCombo (ComboBox &comboToFill, const bool clearBeforeFill);
		const String toString() const;

		static void wrapForLua(lua_State *L);

		JUCE_LEAK_DETECTOR(CtrlrValueMap);

	private:
		int currentValue;
		Array<CtrlrValue> values;
		Array<int> numericValues;
		HashMap<int,String> additionalData;
};
