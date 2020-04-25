#include <iostream>
#include <cstring>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

using namespace rapidjson;

using namespace std;
void testJson();
void testReadJsonFile();

int main(int argc, char *argv[]) {
    std::cout << "start test:" << std::endl;
	testJson();
	testReadJsonFile();
    system("pause");
}


void testReadJsonFile()
{
	const char* json = "{\"project\":\"rapidjson\",\"stars\":100}";
	Document d;
	d.Parse(json);

	//create a json file
	ofstream ofs("test.json");
	OStreamWrapper osw(ofs);

	Writer<OStreamWrapper> owriter(osw);
	d.Accept(owriter);

	//read it
	ifstream ifs("test.json");
	IStreamWrapper isw(ifs);

	Document docRead;
	docRead.ParseStream(isw);


	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	docRead.Accept(writer);

	const char* output = buffer.GetString();

	std::cout << output << std::endl;
}

void testJson() {
	// 1. Parse a JSON string into DOM.
	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
	Document d;
	d.Parse(json);

	// 2. Modify it by DOM.
	Value& s = d["stars"];
	s.SetInt(s.GetInt() + 1);

	// 3. Stringify the DOM
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);

	// Output {"project":"rapidjson","stars":11}
	std::cout << buffer.GetString() << std::endl;

}
