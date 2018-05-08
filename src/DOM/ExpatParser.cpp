// This file is part of XmlPlus package
// 
// Copyright (C)   2010-2013   Satya Prakash Tripathi
//
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE VERSION 3 as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU LESSER GENERAL PUBLIC LICENSE VERSION 3 for more details.
//
// You should have received a copy of the GNU LESSER GENERAL PUBLIC LICENSE VERSION 3
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <iostream>
#include <fstream>
#include <vector>

#include "DOM/ExpatParser.h"
#include "DOM/DOMCommonInc.h"
#include "DOM/DOMException.h"
#include "DOM/DOMCommonInc.h"

#define NSSEP XML_Char('|')

using namespace std;

namespace ExpatCB
{

  void onXmlDecl(void            *userData,
                 const XML_Char  *version,
                 const XML_Char  *encoding,
                 int             standalone)
  {
    if(!userData) {
      return;
    }
    DOM::DOMString *versionStr=NULL;
    DOM::DOMString *encodingStr=NULL;
    if(version)
      versionStr = new DOM::DOMString(version);
    if(encoding)
      encodingStr = new DOM::DOMString(encoding);

    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    
    // the callback inside DOMParser finally uses the value of the two
    // DOMString pointers inside XmlDecl, and doesn't store the pointers 
    // themselves(as AutoPtr or plain pointer). So we should free them here
    // after callback. Found from valgrind. 
    parser->onXmlDecl(userData, versionStr, encodingStr, standalone); 
    delete(versionStr);
    delete(encodingStr);
    cout << endl;  
  }


  //tripletStr: [nsUri|] localName [|nsPrefix]
  DOM::NodeNSTriplet getNSTriplet(ExpatParser *parser, DOM::DOMString tripletStr)
  {
    DOM::DOMStringP nsUri = NULL;
    DOM::DOMStringP nsPrefix = NULL;
    DOM::DOMStringP localName = NULL;
    vector<DOM::DOMString> tokens;
    tripletStr.tokenize(string(1, NSSEP), tokens);
    if( (tokens.size() > 3) || (tokens.size() ==0) ) {
      cerr << "incorrect element info for "
        << tripletStr.str() << endl;
      exit(1);
      //TODO: throw exception
    }
    if(tokens.size() == 3 ) {
      nsUri = parser->adopt(tokens[0]);
      localName = parser->adopt(tokens[1]);
      nsPrefix = parser->adopt(tokens[2]);
    }
    else if(tokens.size() == 2 ) {
      nsUri = parser->adopt(tokens[0]);
      localName = parser->adopt(tokens[1]);
    }
    else {
      localName = parser->adopt(tokens[0]);
    }
    return DOM::NodeNSTriplet(nsUri, nsPrefix, localName);
  }

  void onElementStart(void *userData, 
                      const XML_Char *name, 
                      const XML_Char **atts)
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    
    DOM::NodeNSTriplet nsTriplet = getNSTriplet(parser, DOM::DOMString(name));

    /*
    parser->onElementStart(parserUserData->userData, nsTriplet); 

    for (int i = 0; atts[i]; i += 2) 
    {
      DOM::NodeNSTriplet nsTripletAttr = getNSTriplet(parser, DOM::DOMString(atts[i]));
      parser->onAttribute(parserUserData->userData, 
                          nsTripletAttr,
                          new DOM::DOMString(atts[i+1])
                          );
    }
    */

    vector<DOM::AttributeInfo> attrVec;
    for (int i = 0; atts[i]; i += 2) 
    {
      DOM::NodeNSTriplet nsTripletAttr = getNSTriplet(parser, DOM::DOMString(atts[i]));
      DOM::AttributeInfo attrInfo(  const_cast<DOM::DOMString *>(nsTripletAttr.nsUri()), 
                                    const_cast<DOM::DOMString *>(nsTripletAttr.nsPrefix()), 
                                    const_cast<DOM::DOMString *>(nsTripletAttr.localName()), 
                                    parser->adopt(atts[i+1]));
      attrVec.push_back(attrInfo);
    }

    parser->onElementStart(parserUserData->userData, nsTriplet, attrVec); 

  }

  void onElementEnd(
                    void *userData, 
                    const XML_Char *name)
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;

    DOM::NodeNSTriplet nsTriplet = getNSTriplet(parser, name);
    parser->onElementEnd(parserUserData->userData, nsTriplet); 
  }

  void onNamespaceStart(void *userData, 
                        const XML_Char *prefix,
                        const XML_Char *uri)
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    DOM::DOMStringPtr nsUri = ((uri) ? parser->adopt(uri): NULL);
    DOM::DOMStringPtr nsPrefix = ((prefix) ? parser->adopt(prefix): NULL);
    parser->onNamespaceStart(parserUserData->userData, nsPrefix, nsUri);
  }

  void onNamespaceEnd(void *userData, 
                      const XML_Char *prefix)
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    DOM::DOMStringPtr nsPrefix = ((prefix) ? parser->adopt(prefix): NULL);
    parser->onNamespaceEnd(parserUserData->userData, nsPrefix); 
  }

  void onDocTypeStart( void  *userData,
                       const XML_Char *doctypeName,
                       const XML_Char *sysid,
                       const XML_Char *pubid,
                       int has_internal_subset)
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    DOM::DOMStringPtr doctypeNamePtr = ((doctypeName) ? parser->adopt(doctypeName): NULL);
    DOM::DOMStringPtr sysidPtr = ((sysid) ? parser->adopt(sysid): NULL);
    DOM::DOMStringPtr pubidPtr = ((pubid) ? parser->adopt(pubid): NULL);
    parser->onDocTypeStart(parserUserData->userData,doctypeNamePtr, sysidPtr, pubidPtr, has_internal_subset); 
  }

  void onDocTypeEnd(void *userData)
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    parser->onDocTypeEnd(parserUserData->userData);
  }

  void onCDATAStart(void *userData) 
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    parser->onCDATAStart(parserUserData->userData);
  }

  void onCDATAEnd(void *userData)
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    parser->onCDATAEnd(parserUserData->userData);
  }

  void onPI( void *userData,
             const XML_Char *target,
             const XML_Char *data)
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    DOM::DOMStringPtr targetStr = ((target) ? parser->adopt(target): NULL);
    DOM::DOMStringPtr dataStr = ((data) ? parser->adopt(data): NULL);
    parser->onPI(parserUserData->userData, targetStr, dataStr); 
  }

  void onCharacterData(void *userData, const XML_Char *charBuff,  int len)
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    DOM::DOMStringPtr charBuffStr = ((charBuff) ? parser->adopt(DOM::DOMString(charBuff, len)): NULL);
    parser->onCharacterData(parserUserData->userData, charBuffStr);
  }

  void onComment(void *userData, const XML_Char *data)
  {
    if(!userData) {
      return;
    }
    ParserUserData *parserUserData = (ParserUserData *)userData;
    ExpatParser *parser = parserUserData->parser;
    DOM::DOMStringPtr dataStr = ((data) ? parser->adopt(DOM::DOMString(data)): NULL);
    parser->onComment(parserUserData->userData, dataStr);
  }
}

int ExpatParser::getCurentLineNum()
{
  return XML_GetCurrentLineNumber(_expatParser);
}

int ExpatParser::getCurentColumnNum()
{
  return XML_GetCurrentColumnNumber(_expatParser);
}

ExpatParser::ExpatParser()
{
  //create expat parser
  //_expatParser = XML_ParserCreate(NULL);
#ifdef XML_UNICODE
  _expatParser = XML_ParserCreateNS(NULL, NSSEP);
  //_expatParser = XML_ParserCreateNS(asciiToUTF16String("UTF-16"), '|');
#else
  _expatParser = XML_ParserCreateNS(NULL, NSSEP);
#endif
  XML_SetXmlDeclHandler(_expatParser, ExpatCB::onXmlDecl);
  XML_SetElementHandler(_expatParser, ExpatCB::onElementStart, ExpatCB::onElementEnd);
  XML_SetNamespaceDeclHandler(_expatParser, ExpatCB::onNamespaceStart, ExpatCB::onNamespaceEnd);
  XML_SetDoctypeDeclHandler(_expatParser, ExpatCB::onDocTypeStart, ExpatCB::onDocTypeEnd);
  XML_SetProcessingInstructionHandler(_expatParser, ExpatCB::onPI);
  XML_SetCommentHandler( _expatParser, ExpatCB::onComment);
  XML_SetCharacterDataHandler(_expatParser, ExpatCB::onCharacterData);
  XML_SetCdataSectionHandler(_expatParser, ExpatCB::onCDATAStart, ExpatCB::onCDATAEnd);
  XML_SetReturnNSTriplet(_expatParser, 1);

typedef void
(XMLCALL *XML_XmlDeclHandler)(void            *userData,
                              const XML_Char  *version,
                              const XML_Char  *encoding,
                              int             standalone);
  /*
  _parserUserData = new ParserUserData();
  _parserUserData->parser = this;
  XML_SetUserData(_expatParser, _parserUserData);
  */
}

ExpatParser::~ExpatParser()
{
  //XML_ParserFree(_expatParser);
  delete _parserUserData;
}

void ExpatParser::setUserData(void *userData) {
  
  _parserUserData = new ParserUserData();
  _parserUserData->parser = this;
  _parserUserData->userData = userData;  
  XML_SetUserData(_expatParser, _parserUserData);
}

bool ExpatParser::parseXmlFile(string xmlFile)
{
  ifstream is;
  is.open(xmlFile.c_str(), ios::binary);
  if(is.fail()) {
    cerr << "Failed to open: [ " << xmlFile << " ]" << endl;
    return false;
  }
  return parseInputStream(is);
}

// this is one function that any other wrapper finction like parseXmlFile
// or others will call, to parse the inputstream
bool ExpatParser::parseInputStream(istream& is)
{
  char buf[BUFFSIZE];
  bool ret=false;

  void *userData = ((_parserUserData)? _parserUserData->userData : NULL);
  this->onDocumentStart(userData);
  while(1)
  {
    is.read(buf, sizeof(buf));  
    unsigned long nread = is.gcount();
    int done = (nread < sizeof(buf));
    if (XML_Parse(_expatParser, buf, nread, done) == XML_STATUS_ERROR)
    {
      DOM::XmlParseException ex(XML_ErrorString(XML_GetErrorCode(_expatParser)));
      //ex.setContext("line", XML_GetCurrentLineNumber(_expatParser));
      //ex.setContext("column", XML_GetCurrentColumnNumber(_expatParser));
      ex.setContext("byte", XML_GetCurrentByteIndex(_expatParser));
      throw ex;
    }
    if(nread < BUFFSIZE) {
      break;
    }
  }
  this->onDocumentEnd(userData);

  XML_ParserFree(_expatParser);
  return true;
}
