#include "XmlElement.h"

using namespace std;

XmlElement::XmlElement(XmlTagPtr openTag, XmlTagPtr closeTag) : _openTag(openTag), _closeTag(closeTag), _isSingle(false), _elements(nullptr) {}
XmlElement::XmlElement(XmlTagPtr openTag, XmlTagPtr closeTag, string content) : _openTag(openTag), _closeTag(closeTag), _isSingle(false), _content(content), _elements(nullptr) {}
XmlElement::XmlElement(XmlTagPtr openTag, XmlTagPtr closeTag, vector<XmlElemPtr> * elements) : _openTag(openTag), _closeTag(closeTag), _isSingle(false), _elements(elements) {}
XmlElement::XmlElement(XmlTagPtr singleTag) : _openTag(singleTag), _isSingle(true) {}

XmlElement::~XmlElement() {
	if (_elements)
		delete _elements;
}

XmlElemPtr XmlElement::make(XmlTagPtr openTag, XmlTagPtr closeTag) {
	return make_shared<XmlElement>(openTag, closeTag);
}

XmlElemPtr XmlElement::make(XmlTagPtr openTag, XmlTagPtr closeTag, string content) {
	return make_shared<XmlElement>(openTag, closeTag, content);
}

XmlElemPtr XmlElement::make(XmlTagPtr openTag, XmlTagPtr closeTag, vector<XmlElemPtr> * elements) {
	return make_shared<XmlElement>(openTag, closeTag, elements);
}

XmlElemPtr XmlElement::make(XmlTagPtr singleTag) {
	return make_shared<XmlElement>(singleTag);
}

XmlElemPtr XmlElement::makeRoot(vector<XmlElemPtr> * elements) {
	return make_shared<XmlElement>(XmlTag::make(ROOT_NAME, Position(0, 0)), XmlTag::make(ROOT_NAME, Position(0, 0), true, false), elements);
}

string XmlElement::toString() const {
	stringstream ss;
	ss << _openTag->toString();
	if (_elements)
		ss << " { " << _elements->size() << " elements }";
	if (!_isSingle)
		ss << _closeTag->toString();
	return ss.str();
}

void XmlElement::print(ostream & out, int offset) {
	_openTag->print(out, offset);
	out << endl;
	if (_elements != nullptr) {
		for (auto & it : *_elements) {
			it->print(out, offset + OFFSET);
			out << endl;
		}
	}
	else if (_content.size() > 0) {
		_shift(out, offset + OFFSET);
		out << _content << endl;
	}
	if (!_isSingle)
		_closeTag->print(out, offset);
}

XmlTagPtr XmlElement::getOpenTag() const { return _openTag; }
XmlTagPtr XmlElement::getCloseTag() const { return _closeTag; }
vector<XmlElemPtr> * XmlElement::getElements() const { return _elements; }
string XmlElement::getContent() const { return _content; }
bool XmlElement::isSingle() const { return _isSingle; }

void XmlElement::_shift(ostream & out, int offset) {
	for (int i = 0; i < offset; i++)
		out << " ";
}