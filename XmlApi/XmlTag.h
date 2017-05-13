#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

#include "XmlAttribute.h"
#include "Tools\Position.h"

class XmlTag;
typedef std::shared_ptr<XmlTag> XmlTagPtr;

class XmlTag {
public:
	XmlTag(std::string name, Position pos, bool isClose = false, bool isSingle = false);
	XmlTag(std::string name, std::vector<XmlAttrPtr> * attributes, Position pos, bool isSingle = false);

	static XmlTagPtr make(std::string name, Position pos, bool isClose = false, bool isSingle = false);
	static XmlTagPtr make(std::string name, std::vector<XmlAttrPtr> * attributes, Position pos, bool isSingle = false);

	std::string toString() const;
	void print(std::ostream & out, int offset = 0) const;

	std::string getName() const;
	std::vector<XmlAttrPtr> * getAttributes() const;
	bool isCloseTag() const;
	bool isSingleTag() const;
	Position getPosition() const;

private:
	void _shift(std::ostream & out, int offset) const;

	std::string _name;
	std::vector<XmlAttrPtr> * _attributes;
	bool _isClose;
	bool _isSingle;
	Position _pos;
};