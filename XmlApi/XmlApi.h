#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Tools\Parser.h"
#include "Tools\Lexer.h"
#include "XmlElement.h"
#include "XmlAttribute.h"

class XmlApi {
public:
	XmlApi(const std::string fileName);
	XmlApi(const char * fileName);

	XmlElemPtr getRoot() const;
	void print();

private:
	void _parse();

	std::string _fileName;
	XmlElemPtr _root;
};