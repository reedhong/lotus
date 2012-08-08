/*
 * ≤‚ ‘ConfigParser
 */

#include <iostream>
using namespace std;
#include "ConfigParser/ConfigParser.h"
using namespace Lotus;

#include "test.h"

void testConfigParser()
{
	ConfigParser* parser = new ConfigParser();
	parser->open("./test.ini");
	
	string url =  parser->get("main", "url");
	int port = parser->getInt("main", "port");
	bool isok = parser->getBool("main", "isok");
	float f = parser->getFloat("main", "arvg");
	delete parser;
}