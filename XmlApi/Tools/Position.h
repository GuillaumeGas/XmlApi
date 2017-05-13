#pragma once

#include <string>
#include <sstream>

struct Position {
	Position(int line, int column) : line(line), column(column) {}

	int line, column;

	std::string toString() const {
		std::stringstream ss;
		ss << "(" << line << ", " << column << ")";
		return ss.str();
	}
};