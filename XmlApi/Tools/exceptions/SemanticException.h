#pragma once

#include <iostream>

#include "../../XmlTag.h"

class SemanticException {
public:
	SemanticException(XmlTagPtr openTag, XmlTagPtr closeTag) : _openTag(openTag), _closeTag(closeTag) {}

	virtual std::string toString() const {
		return "[SEMANTIC ERROR] Semantic error on tags <" + _openTag->getName() + "> and </" + _closeTag->getName() + ">.";
	}

protected:
	XmlTagPtr _openTag, _closeTag;
};

class InvalidTagNameException : public SemanticException {
public:
	InvalidTagNameException(XmlTagPtr openTag, XmlTagPtr closeTag) : SemanticException(openTag, closeTag) {}

	virtual std::string toString() const {
		return "[SEMANTIC ERROR] Invalid names on tags <" + _openTag->getName() + "> and </" + _closeTag->getName() + ">.";
	}
};

class InvalidTagNamespaceException : public SemanticException {
public:
	InvalidTagNamespaceException(XmlTagPtr openTag, XmlTagPtr closeTag) : SemanticException(openTag, closeTag) {}

	virtual std::string toString() const {
		return "[SEMANTIC ERROR] Invalid namespace on tag <" + _closeTag->getName() + "> : '" + _openTag->getNamespace() + "' and '" + _closeTag->getNamespace() + "'";
	}
};