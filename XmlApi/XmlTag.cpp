#include "XmlTag.h"

using namespace std;

XmlTag::XmlTag(string name, Position pos, bool isClose, bool isSingle) : _name(name), _attributes(nullptr), _isClose(isClose), _isSingle(isSingle), _pos(pos) {}
XmlTag::XmlTag(string name, vector<XmlAttrPtr> * attributes, Position pos, bool isSingle) : _name(name), _attributes(attributes), _isClose(false), _isSingle(isSingle), _pos(pos) {}

XmlTagPtr XmlTag::make(string name, Position pos, bool isClose, bool isSingle) {
	return make_shared<XmlTag>(name, pos, isClose, isSingle);
}

XmlTagPtr XmlTag::make(string name, vector<XmlAttrPtr> * attributes, Position pos, bool isSingle) {
	return make_shared<XmlTag>(name, attributes, pos, isSingle);
}

string XmlTag::toString() const {
	stringstream ss;
	ss << "<" << _name;
	if (_attributes) {
		ss << " ";
		for (auto & it : *_attributes)
			it->toString();
	}
	ss << "> (" << _pos.line << ", " << _pos.column << ")";
	return ss.str();
}

void XmlTag::print(ostream & out, int offset) const {
	_shift(out, offset);
	out << "<" << _name;
	if (_attributes != NULL) {
		out << " ";
		for (auto & it : *_attributes)
			it->print(out);
	}
	out << "> (" << _pos.line << ", " << _pos.column << ")";
}

string XmlTag::getName() const {
	return _name;
}

vector<XmlAttrPtr> * XmlTag::getAttributes() const {
	return _attributes;
}

bool XmlTag::isCloseTag() const {
	return _isClose;
}

bool XmlTag::isSingleTag() const {
	return _isSingle;
}

Position XmlTag::getPosition() const {
	return _pos;
}

void XmlTag::_shift(ostream & out, int offset) const {
	for (int i = 0; i < offset; i++)
		out << " ";
}