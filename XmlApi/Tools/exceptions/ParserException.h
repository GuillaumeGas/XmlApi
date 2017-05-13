#pragma once

#include <iostream>

#include "../Position.h"

class ParserException {
public:
	ParserException(const std::string msg, Position pos) : _msg(msg), _pos(pos) {}
	ParserException(const char * msg, Position pos) : _msg(msg), _pos(pos) {}
	ParserException() : _msg(""), _pos({ 0, 0 }) {}

	virtual std::string toString() const {
		return "[PARSE ERROR] " + _msg + " at " + _pos.toString();
	}

protected:
	std::string _msg;
	Position _pos;
};

class SyntaxErrorException : public ParserException {
public:
	SyntaxErrorException(const std::string expected, std::string given, Position pos) : _given(given), _expected(expected) {
		_pos = pos;
	}

	virtual std::string toString() const {
		return "[PARSE ERROR] '" + _expected + "' expected, but '" + _given + "' was given at " + _pos.toString();
	}

protected:
	std::string _given;
	std::string _expected;
};

class BadIdentifierErrorException : public ParserException {
public:
	BadIdentifierErrorException(std::string ident, Position pos) : _ident(ident) {
		_pos = pos;
	}

	virtual std::string toString() const {
		return "[PARSE ERROR] The identifier '" + _ident + "' is malformed at " + _pos.toString();
	}

protected:
	std::string _ident;
};

class MissingClosingTagException : public ParserException {
public:
	MissingClosingTagException(std::string ident, Position pos) : _ident(ident) {
		_pos = pos;
	}

	virtual std::string toString() const {
		return "[PARSE ERROR] Missing closing tag for " + _ident + " at " + _pos.toString();
	}

protected:
	std::string _ident;
};

class UnexpectedTokenException : public ParserException {
public:
	UnexpectedTokenException(std::string token, Position pos) : _token(token) {
		_pos = pos;
	}

	virtual std::string toString() const {
		return "[PARSE ERROR] Unexpected token '" + _token + "' at " + _pos.toString();
	}

protected:
	std::string _token;
};