#include <iostream>
#include <string>

#include "XmlApi.h"

using namespace std;

int main(int argc, char ** argv) {
	string file = "C:\\Users\\guillaume\\Documents\\Visual Studio 2015\\Projects\\XmlApi\\test.xml";
	XmlApi xml(file);
	xml.print();

	// Base way
	/*XmlElemPtr root = xml.getRoot();
	root->print(cout);*/
	//vector<XmlAttrPtr> * attribs = root->getAttributes(); // may be null
	//vector<XmlElemPtr> * elems = root->getElements(); // may be null
	//XmlElemPtr a = elems->at(0);
	//cout << a->getName() << endl;
	// if content and no elems
	//cout << a->getString() << endl;
	//cout << a->getInt() << endl;
	//// ...
	//XmlAttrPtr e = attribs->at(0);
	//cout << e->getName() << endl;
	//cout << e->getString() << endl;
	//cout << e->getInt() << endl;
	// ...

	// Reader way
	/*XmlReader reader(xml);
	XmlElemPtr elem = reader.nextElement();
	XmlAttrPtr e = reader->nextAttrib();*/

	//try {
	//	Lexer lex("test.xml");
	//	lex.setKeys({ "<", ">", "\"", ":", "?", "=", "\n", " ", "\n", "\r", "\t" });
	//	lex.setSkips({ " ", "\n", "\r", "\t" });
	//	// add comments

	//	while (!lex.isEof()) {
	//		cout << lex.next()->toString() << endl;
	//	}
	//}
	//catch (LexerException * e) {
	//	cout << e->toString() << endl;
	//}

	system("PAUSE");

	return 0;
}