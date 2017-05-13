#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

#include "XmlTag.h"
#include "Tools\exceptions\SemanticException.h"

#define ROOT_NAME "ROOT"
#define OFFSET 2

class XmlElement;
typedef std::shared_ptr<XmlElement> XmlElemPtr;
typedef XmlElemPtr XmlNullElement;

class XmlElement {
public:
	XmlElement(XmlTagPtr openTag, XmlTagPtr closeTag);
	XmlElement(XmlTagPtr openTag, XmlTagPtr closeTag, std::string content);
	XmlElement(XmlTagPtr openTag, XmlTagPtr closeTag, std::vector<XmlElemPtr> * elements);
	XmlElement(XmlTagPtr singleTag);
	~XmlElement(); // don't forget to free vectors !

	static XmlElemPtr make(XmlTagPtr opentag, XmlTagPtr claseTag);
	static XmlElemPtr make(XmlTagPtr openTag, XmlTagPtr closeTag, std::string content);
	static XmlElemPtr make(XmlTagPtr openTag, XmlTagPtr closeTag, std::vector<XmlElemPtr> * elements);
	static XmlElemPtr make(XmlTagPtr singleTag);
	static XmlElemPtr makeRoot(std::vector<XmlElemPtr> * elements);

	std::string toString() const;
	void print(std::ostream & out, int offset = 0);

	XmlTagPtr getOpenTag() const;
	XmlTagPtr getCloseTag() const;
	bool isSingle() const;
	std::vector<XmlElemPtr> * getElements() const;
	std::string getContent() const;
	void checkSemantic();

private:
	void _shift(std::ostream & out, int offset);

	XmlTagPtr _openTag;
	XmlTagPtr _closeTag;
	bool _isSingle;
	std::vector<XmlElemPtr> * _elements;
	std::string _content;
};