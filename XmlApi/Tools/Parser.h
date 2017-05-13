#pragma once

#include <iostream>
#include <vector>

#include "Lexer.h"
#include "Token.h"
#include "Position.h"
#include "exceptions\ParserException.h"
#include "../XmlElement.h"
#include "../XmlAttribute.h"
#include "../XmlTag.h"

class Parser {
public:
	Parser(Lexer * lexer);

	XmlElemPtr parse();

protected:
	XmlElemPtr _visitRoot();
	std::vector<XmlElemPtr> * _visitElements();
	XmlElemPtr _visitElement();
	std::vector<XmlAttrPtr> * _visitAttributes();
	XmlAttrPtr _visitAttribute();
	XmlTagPtr _visitOpenTag();
	XmlTagPtr _visitCloseTag();
	std::string _visitValue();
	std::string _visitIdentifier();
	bool _isNextClosingTag();
	bool _isIdentifier(std::string str) const;

	Lexer * _lex;
};
