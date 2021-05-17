#include "SpreadsheetCell.h"

#include <iostream>

SpreadsheetCell::SpreadsheetCell(double initialValue) {
	setValue(initialValue);
}
SpreadsheetCell::SpreadsheetCell(std::string_view initialValue) {
	setString(initialValue);
}
SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src) : mValue(src.mValue) {}

void SpreadsheetCell::setValue(double inValue) {
	this->mValue = inValue;
}
double SpreadsheetCell::getValue() const {
	return this->mValue;
}
void SpreadsheetCell::setString(std::string_view inString) {
	this->mValue = stringToDouble(inString);
}
std::string SpreadsheetCell::getString() const {
	return doubleToString(this->mValue);
}
std::string SpreadsheetCell::doubleToString(double inValue) const {
	return std::to_string(inValue);
}
double SpreadsheetCell::stringToDouble(std::string_view inString) const {
	return strtod(inString.data(), nullptr);
}


void SpreadsheetCell::Test() {
	SpreadsheetCell aThirdCell("Test");
	SpreadsheetCell aFourthCell(4.4);
}