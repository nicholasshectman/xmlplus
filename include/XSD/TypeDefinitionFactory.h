// This file is part of XmlPlus package
// 
// Copyright (C)   2010-2013 Satya Prakash Tripathi
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

#ifndef __XSD_TYPEDEFINITIONFACTORY_H__ 
#define __XSD_TYPEDEFINITIONFACTORY_H__

#include <map>
#include "XSD/UrTypes.h"
#include "XPlus/Exception.h"

namespace XSD
{
  struct StructCreateAttrThroughFsm
  {
    DOM::DOMString*    tagName;
    DOM::DOMString*    nsUri;
    DOM::DOMString*    nsPrefix;
    Element*      ownerElem;
    XMLSchema::TDocument*    ownerDoc;
    FSM::XsdFsmBase*   fsm;
    FSM::FsmCbOptions  options;

    StructCreateAttrThroughFsm(
                              DOM::DOMString*    tagName_,
                              DOM::DOMString*    nsUri_,
                              DOM::DOMString*    nsPrefix_,
                              Element*      ownerElem_,
                              XMLSchema::TDocument*    ownerDoc_,
                              FSM::XsdFsmBase*   fsm_,
                              FSM::FsmCbOptions  options_
                              ):
                        tagName(tagName_),
                        nsUri(nsUri_),
                        nsPrefix(nsPrefix_),
                        ownerElem(ownerElem_),
                        ownerDoc(ownerDoc_),
                        fsm(fsm_),
                        options(options_)
    {
    }
  };



  struct StructCreateElementThroughFsm
  {
    DOM::DOMString* tagName;
    DOM::DOMString* nsUri;
    DOM::DOMString* nsPrefix;
    Node*      parentNode;
    XMLSchema::TDocument* ownerDoc;
    
    bool         abstract;
    bool         nillable;
    bool         fixed;

    FSM::XsdFsmBase*   fsm;
    FSM::FsmCbOptions options;

    // following 2 applicable only when an <element> has 
    // a @type  attribute in xsd
    DOMString actualTypeNsUri;
    DOMString actualTypeName;



    StructCreateElementThroughFsm(DOM::DOMString* tagName_,
                              DOM::DOMString* nsUri_,
                              DOM::DOMString* nsPrefix_,
                              Node*      parentNode_,
                              XMLSchema::TDocument* ownerDoc_,
                              FSM::XsdFsmBase*   fsm_,
                              FSM::FsmCbOptions options_,
                              bool abstract_=false,
                              bool nillable_=false,
                              bool fixed_ = false,
                              DOM::DOMString /* actualTypeNsUri_ */ = "",
                              DOM::DOMString /* actualTypeName_ */ = "<unknown>"
                              ):
                        tagName(tagName_),
                        nsUri(nsUri_),
                        nsPrefix(nsPrefix_),
                        parentNode(parentNode_),
                        ownerDoc(ownerDoc_),
                        abstract(abstract_),
                        nillable(nillable_),
                        fixed(fixed_),
                        fsm(fsm_),
                        options(options_)
      {
      }
  };


  template<typename T> XMLSchema::Types::anyType* createType(XMLSchema::Types::ElementCreateArgs args) 
  { 
    T* pT = NULL;
    try {
      pT = new T(args);
    }
    catch(XPlus::Exception& ex) {
      cerr << "Failed to create type:" << ex.msg() << endl;
    }
    XMLSchema::Types::anyType* pAny = dynamic_cast<XMLSchema::Types::anyType *>(pT);
    //return pT;
    return pAny;
  }

  struct TypeDefinitionFactory 
  {
    typedef std::map<std::string, XMLSchema::Types::anyType*(*)(XMLSchema::Types::ElementCreateArgs args)> map_type;
    
    TypeDefinitionFactory(const std::string& typeName, const std::string& typeNsUri):
      _name(typeName),
      _nsUri(typeNsUri)
    {
    }

    static XMLSchema::Types::anyType* getTypeForQName(const std::string& typeName, const std::string& typeNsUri, XMLSchema::Types::ElementCreateArgs args) 
    {
      std::string key = createKeyForQNameToTypeMap(typeName, typeNsUri);
      map_type::iterator it = getMap()->find(key);
      if(it == getMap()->end()) {
        return NULL;
      }
      // this calls createType
      return it->second(args);
    }

    protected:

    static map_type* getMap() 
    {
      static map_type pQNameToTypeMap;
      return &pQNameToTypeMap;
    }

    static const std::string createKeyForQNameToTypeMap(const std::string& typeName, const std::string& typeNsUri)
    {
      std::ostringstream oss;
      oss << "{" << typeNsUri << "}" << typeName;
      return oss.str();
    }

    inline std::string name() {
      return _name;
    }
    
    inline std::string nsUri() {
      return _nsUri;
    }

    std::string            _name;
    std::string            _nsUri;
  };

  // create a templatized derivation of TypeDefinitionFactory
  template<typename T> struct TypeDefinitionFactoryTmpl : public TypeDefinitionFactory 
  { 
    TypeDefinitionFactoryTmpl(const std::string& typeName, const std::string& typeNsUri):
      TypeDefinitionFactory(typeName, typeNsUri)
    { 
      std::string key = createKeyForQNameToTypeMap(typeName, typeNsUri);
      getMap()->insert(make_pair(key, &createType<T>));
    }
  };

  // E : element class
  // TPtr : pointer to "class of element's type"
  template<typename E, typename TPtr> E* createElementTmpl(StructCreateElementThroughFsm& t)
  {
    if(t.ownerDoc->buildTree() || !t.fsm->fsmCreatedNode())
    {
      DOM::Node* prevSibl = NULL;
      DOM::Node* nextSibl = NULL;
      if( !t.ownerDoc->buildingFromInputStream()) 
      {
        if(t.fsm->prevSiblingNodeRunTime() ) {
          prevSibl = const_cast<Node *>(t.fsm->prevSiblingNodeRunTime());
        }
        if(t.fsm->nextSiblingNodeRunTime() ) {
          nextSibl = const_cast<Node *>(t.fsm->nextSiblingNodeRunTime());
        }
      }
      
      XMLSchema::Types::ElementCreateArgs args(t.tagName, t.nsUri, t.nsPrefix, t.ownerDoc, t.parentNode, prevSibl, nextSibl, t.abstract, t.nillable, t.fixed, false, t.options.isSampleCreate);
      E* node = NULL;

      // if element's type is specified in instance document using xsi:type
      if(t.options.xsiType.length()>0)
      {
        DOM::DOMString instanceTypeNsUri="", instanceTypeName="";
        std::vector<XPlus::UString> tokens;
        t.options.xsiType.tokenize(":", tokens);
        poco_assert(tokens.size()<=2);
        if(tokens.size() == 2) 
        {
          instanceTypeNsUri = t.ownerDoc->getNsUriForNsPrefixExplicit(tokens[0]);
          instanceTypeName = tokens[1];
        }
        else {
          instanceTypeName = tokens[0];
        }
        XMLSchema::Types::anyType* pOverriddenType = TypeDefinitionFactory::getTypeForQName(instanceTypeName, instanceTypeNsUri, args);
        TPtr myTypeCast = dynamic_cast<TPtr>(pOverriddenType);
        if(!myTypeCast || pOverriddenType->typeAbstract()) 
        {
          std::ostringstream oss;
          oss << "  The value of the attribute {"
              << XPlus::Namespaces::s_xsiUri 
              << "}type inside an element, in the instance document should resolve " 
                  "to a valid derivation of it's declared type in Schema document." << endl 
              << "  Type {" << instanceTypeNsUri  << "}" << instanceTypeName 
              << " is not a derivation of Type {" << t.actualTypeNsUri << "}"
              << t.actualTypeName;
          throw XPlus::RuntimeException(oss.str());
        }

        args.suppressTypeAbstract = true;
        node = new E(args);
        node->replaceFsm(pOverriddenType->fsm());
      }
      else
      {
        node = new E(args);
      }
      
      if(t.options.xsiNil == "true")
      {
        if(t.nillable) {
          node->fsm()->contentFsm()->nilled(true);
        }
        else 
        {
          std::ostringstream ossElemNS;
          if(t.nsUri) ossElemNS << "{" << *t.nsUri << "} "; 
          ossElemNS << *t.tagName;

          std::ostringstream oss;
          oss << " The element can not be nilled because it is not declared nillable in the schema";  
          XPlus::RuntimeException ex(oss.str());
          ex.setContext("element", ossElemNS.str());  
          throw ex;        
        }
      }
      
      t.fsm->fsmCreatedNode(node);
      return node;
    }
    else {
      return dynamic_cast<E *>(const_cast<Node*>(t.fsm->fsmCreatedNode()));
    }
  }


  // T :   attribute's class
  template<typename T> T* createAttributeTmpl(StructCreateAttrThroughFsm t)
  {
    if(t.ownerDoc->buildTree() || ! t.fsm->fsmCreatedNode() || t.options.isDefaultCreate)
    {
      XMLSchema::Types::AttributeCreateArgs args(t.tagName, t.nsUri, NULL, t.ownerElem, t.ownerDoc, NULL, t.options.isSampleCreate);
      XPlus::AutoPtr<T> node = new T(args);
      t.fsm->fsmCreatedNode(node);
      return node;
    }
    else {
      return dynamic_cast<T*>(const_cast<Node*>(t.fsm->fsmCreatedNode()));
    }
  }

  
}

#endif
