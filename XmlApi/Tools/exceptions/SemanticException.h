#pragma once

#include <iostream>

#include "../../XmlTag.h"

class SemanticException {
public:
	SemanticException(XmlTagPtr openTag, XmlTagPtr closeTag) : _openTag(openTag), _closeTag(closeTag) {}

	virtual std::string toString() const {
		return "[SEMANTIC ERROR] Invalid closing tag <" + _closeTag->getName() + "> for open tag <" + _openTag->getName() + ">.";
	}

protected:
	XmlTagPtr _openTag, _closeTag;
};