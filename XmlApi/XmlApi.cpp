#include "XmlApi.h"
#include "Tools/exceptions/LexerException.h"
#include "Tools/exceptions/ParserException.h"
#include "Tools/exceptions/SemanticException.h"

using namespace std;

XmlApi::XmlApi(const string fileName) : _fileName(fileName) {
	_parse();
}
XmlApi::XmlApi(const char * fileName) : _fileName(fileName) {
	_parse();
}

XmlElemPtr XmlApi::getRoot() const {
	return _root;
}

void XmlApi::_parse() {
	try {
		Lexer lex(_fileName);
		lex.setKeys({ "<", ">", "\"", "/", ":", "?", "=", "\n", " ", "\n", "\r", "\t" });
		lex.setSkips({ " ", "\n", "\r", "\t" });
		Parser parser(&lex);
		_root = parser.parse();
		_root->checkSemantic();
	}
	catch (LexerException * e) {
		cout << e->toString() << endl;
	}
	catch (ParserException * e) {
		cout << e->toString() << endl;
	}
	catch (SemanticException * e) {
		cout << e->toString() << endl;
	}
}

void XmlApi::print() {
	_root->print(cout, 0);
	cout << endl;
	cout.flush();
}