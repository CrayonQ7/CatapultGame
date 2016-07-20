#include "XMLParser.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

// 空格
const static int SPACE = 32;
// 换行
const static int NEXTLINE = 10;
// tab 横向制表符
const static int TAB = 9;

XMLParser * XMLParser::parseWithFile(const char * xmlFileName)
{
	XMLParser *pXMLParser = new XMLParser();
	if (pXMLParser->initWithFile(xmlFileName))
	{
		pXMLParser->autorelease();
		return pXMLParser;
	}
	CC_SAFE_DELETE(pXMLParser);
	return NULL;
}

XMLParser * XMLParser::parseWithString(const char * content)
{
	dictionary = new Dictionary();
	CCSAXParser _parser;
	_parser.setDelegator(this);
	const char *fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(xmlFileName);
	return _parser.parse(fullPath);
}

XMLParser::XMLParser()
{
}

XMLParser::~XMLParser()
{
	CC_SAFE_DELETE(this->dictionary);
}

bool XMLParser::initWithFile(const char * xmlFileName)
{
	return false;
}

bool XMLParser::initWithString(const char * content)
{
	return false;
}

void XMLParser::startElement(void * ctx, char * name, const char ** atts)
{
}

void XMLParser::endElement(void * ctx, const char * name)
{
}

void XMLParser::textHandler(void * ctx, const char * s, int len)
{
}

cocos2d::CCString * XMLParser::getString(const char * key)
{
	return nullptr;
}
