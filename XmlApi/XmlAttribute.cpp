#include "XmlAttribute.h"

using namespace std;

XmlAttribute::XmlAttribute(string name, string value) : _name(name), _value(value) {}

XmlAttrPtr XmlAttribute::make(string name, string value) {
	return make_shared<XmlAttribute>(name, value);
}

string XmlAttribute::toString() const {
	stringstream ss;
	ss << _name << "=\"" << _value << "\"";
	return ss.str();
}

void XmlAttribute::print(ostream & out, int offset) const {
	out << _name << "=\"" << _value << "\"";
}

string XmlAttribute::getName() const { return _name; }
string XmlAttribute::getValue() const { return _value; }

void XmlAttribute::_shift(ostream & out, int offset) {
	for (int i = 0; i < offset; i++)
		out << " ";
}