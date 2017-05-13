#include "Parser.h"

// TODO : check eof everywhere !

using namespace std;

Parser::Parser(Lexer * lexer) : _lex(lexer) {}

XmlElemPtr Parser::parse() {
	return _visitRoot();
}

XmlElemPtr Parser::_visitRoot() {
	vector<XmlElemPtr> * elements = _visitElements();
	return XmlElement::makeRoot(elements);
}

vector<XmlElemPtr> * Parser::_visitElements() {
	if (_lex->isEof())
		return nullptr;
	vector<XmlElemPtr> * elements = nullptr;
	XmlElemPtr elem;
	do {
		elem = _visitElement();
		if (elem != nullptr) {
			if (elements == nullptr)
				elements = new vector<XmlElemPtr>();
			elements->push_back(elem);
		}
	} while (elem != nullptr && !_lex->isEof());
	return elements;
}

XmlElemPtr Parser::_visitElement() {
	_lex->next();
	if (!_lex->isEof()) {
		_lex->rewind();
		XmlTagPtr openTag = _visitOpenTag();
		if (openTag->isSingleTag())
			return XmlElement::make(openTag);
		TokenPtr next = _lex->next();
		_lex->rewind();
		if (next->type == TokenType::OTHER) {
			string content = _visitValue();
			XmlTagPtr closeTag = _visitCloseTag();
			return XmlElement::make(openTag, closeTag, content);
		}
		else {
			if (_isNextClosingTag()) {
				XmlTagPtr closeTag = _visitCloseTag();
				return XmlElement::make(openTag, closeTag);
			}
			else {
				vector<XmlElemPtr> * elements = new vector<XmlElemPtr>();
				while (!_isNextClosingTag() && !_lex->isEof()) {
					elements->push_back(_visitElement());
				}
				if (_lex->isEof())
					throw new MissingClosingTagException(openTag->getName(), openTag->getPosition());
				else {
					XmlTagPtr closeTag = _visitCloseTag();
					return XmlElement::make(openTag, closeTag, elements);
				}
			}
		}
	} 
	return XmlNullElement();
}

vector<XmlAttrPtr> * Parser::_visitAttributes() {
	vector<XmlAttrPtr> * attributes = nullptr;
	while (true) {
		TokenPtr next = _lex->next();
		_lex->rewind();
		if (next->type != TokenType::OTHER)
			break;
		if (!attributes)
			attributes = new vector<XmlAttrPtr>();
		attributes->push_back(_visitAttribute());
	}
	return attributes;
}

XmlAttrPtr Parser::_visitAttribute() {
	TokenPtr next = _lex->next();
	string ident = next->value;
	next = _lex->next();
	if (next->type != TokenType::EQUAL)
		throw new SyntaxErrorException("=", next->value, Position(next->line, next->column));
	next = _lex->next();
	if (next->type != TokenType::DOUBLE_QUOTE)
		throw new SyntaxErrorException("\"", next->value, Position(next->line, next->column));
	string value = _visitValue();
	next = _lex->next();
	if (next->type != TokenType::DOUBLE_QUOTE)
		throw new SyntaxErrorException("\"", next->value, Position(next->line, next->column));
	return XmlAttribute::make(ident, value);
}

XmlTagPtr Parser::_visitOpenTag() {
	TokenPtr next = _lex->next();
	Position pos = Position(next->line, next->column);
	if (next->type != TokenType::LEFT_ARROW)
		throw new SyntaxErrorException("<", next->value, pos);
	
	string ident = _visitIdentifier();
	string nameSpace;

	next = _lex->next();
	if (next->type == TokenType::COLON) {
		nameSpace = ident;
		ident = _visitIdentifier();
		next = _lex->next();
	}

	if (next->type == TokenType::RIGHT_ARROW) {
		return XmlTag::make(ident, nameSpace, pos);
	}
	else if (next->type == TokenType::SLASH) {
		_lex->next();
		return XmlTag::make(ident, nameSpace, pos, true, true);
	}
	else {
		_lex->rewind();
		vector<XmlAttrPtr> * attributes = _visitAttributes();
		next = _lex->next();
		if (next->type == TokenType::RIGHT_ARROW)
			return XmlTag::make(ident, nameSpace, attributes, pos);
		if (next->type == TokenType::SLASH)
			return XmlTag::make(ident, nameSpace, attributes, pos, true);
		throw new UnexpectedTokenException(next->value, Position(next->line, next->column));
	}
}

XmlTagPtr Parser::_visitCloseTag() {
	TokenPtr next = _lex->next();
	Position pos = Position(next->line, next->column);
	if (next->type != TokenType::LEFT_ARROW)
		throw new SyntaxErrorException("<", next->value, pos);
	next = _lex->next();
	if (next->type != TokenType::SLASH)
		throw new SyntaxErrorException("/", next->value, pos);
	
	string ident = _visitIdentifier();
	string nameSpace;
	
	next = _lex->next();
	if (next->type == TokenType::COLON) {
		nameSpace = ident;
		ident = _visitIdentifier();
		next = _lex->next();
	}

	if (next->type != TokenType::RIGHT_ARROW)
		throw new SyntaxErrorException(">", next->value, pos);
	return XmlTag::make(ident, nameSpace, pos, true, false);
}

string Parser::_visitValue() {
	TokenPtr next = _lex->next();
	stringstream ss;
	ss << next->value;
	while (true) {
		next = _lex->next();
		if (next->type != TokenType::OTHER)
			break;
		ss << next->value;
	}
	_lex->rewind();
	return ss.str();
}

string Parser::_visitIdentifier() {
	TokenPtr next = _lex->next();
	if (next->type != TokenType::OTHER)
		throw new SyntaxErrorException("identifier", next->value, Position(next->line, next->column));
	if (_isIdentifier(next->value))
		return next->value;
	throw new BadIdentifierErrorException(next->value, Position(next->line, next->column));
}

// Closing taf := </Identifier>
bool Parser::_isNextClosingTag() {
	TokenPtr next = _lex->next();
	if (next->type != TokenType::LEFT_ARROW) {
		_lex->rewind();
		return false;
	}
	next = _lex->next();
	_lex->rewind(2);
	if (next->type != TokenType::SLASH)
		return false;
	return true;
}

// Identifier
bool Parser::_isIdentifier(string str) const {
	if (str[0] < 'A' || str[0] > 'z' || (str[0] > 'Z' && str[0] < 'a'))
		return false;
	for (unsigned int i = 1; i < str.size(); i++) {
		if ((str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z') && (str[i] < '0' || str[i] > '9') && str[i] != '_') {
			return false;
		}
	}
	return true;
}