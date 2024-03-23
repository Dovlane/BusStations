#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <sstream>
using namespace std;

class MyErrorException : public exception {
protected:
	static const string question_to_try_again;
	string beginning;
	string end;
	string error_message;
public:
	MyErrorException(const char* s);
	const char* what() const;
};


class NonExistingStationException : public MyErrorException {
public:
	NonExistingStationException(const char* s);
};

class NonExistingLineException : public MyErrorException {
public:
	NonExistingLineException(const char* s);
};

class IrregularPathException : public MyErrorException {
public:
	IrregularPathException(const char* s);
};

// It is never used, this exception is there just in case that suddenly some invalid data exception occurs
class NoExistingRouteException : public MyErrorException {
public:
	NoExistingRouteException(const char* s);
};

class FileOpenException : public MyErrorException {
public:
	FileOpenException(const char* s);
};


#endif