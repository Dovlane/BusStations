#include "Exception.h"

const string MyErrorException::question_to_try_again = "Try again:";

MyErrorException::MyErrorException(const char* s) : exception(s) {}

const char* MyErrorException::what() const throw () {
	return error_message.c_str();
}

NonExistingStationException::NonExistingStationException(const char* s) : MyErrorException(s) {
	this->beginning = "[Error] There is no station ";
	this->end = " in the given data.";
	string str_s = "";
	str_s += "(\"";
	str_s += s;
	str_s += "\")";
	this->error_message = beginning + str_s + end + question_to_try_again;
}

NonExistingLineException::NonExistingLineException(const char* s) : MyErrorException(s) {
	this->beginning = "[Error] There is no line ";
	this->end = " in the given data.";
	string str_s = "";
	str_s += "(\"";
	str_s += s;
	str_s += "\")";
	this->error_message = beginning + str_s + end + question_to_try_again;
}

IrregularPathException::IrregularPathException(const char* s) : MyErrorException(s) {
	this->beginning = "[Error] On the path ";
	this->end = " there is no file.";
	string str_s = "";
	str_s += "\"";
	str_s += s;
	str_s += "\"";
	this->error_message = beginning + str_s + end + question_to_try_again;
}

NoExistingRouteException::NoExistingRouteException(const char* s) : MyErrorException(s) {
	this->beginning = "[Error] The route between ";
	this->end = " does not exist.";
	string str_s = "";
	str_s += "\"";
	str_s += s;
	str_s += "\"";
	this->error_message = beginning + str_s + end + question_to_try_again;
}

FileOpenException::FileOpenException(const char* s) : MyErrorException(s) {
	this->beginning = "[Error] The file ";
	this->end = " could not be opened.";
	string str_s = "";
	str_s += "\"";
	str_s += s;
	str_s += "\"";
	this->error_message = beginning + str_s + end + question_to_try_again;
}