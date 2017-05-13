#pragma once

#include <iostream>
#include <sstream>
#include <memory>

class XmlAttribute;
typedef std::shared_ptr<XmlAttribute> XmlAttrPtr;

class XmlAttribute {
public:
	XmlAttribute(std::string name, std::string value);

	static XmlAttrPtr make(std::string name, std::string value);

	std::string toString() const;
	void print(std::ostream & out, int offset = 0) const;

	std::string getName() const;
	std::string getValue() const;

private:
	void _shift(std::ostream & out, int offset);

	std::string _name;
	std::string _value;
};