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

#ifndef __XPLUS_NAMESPACES_H__ 
#define __XPLUS_NAMESPACES_H__

#include "DOM/DOMCommonInc.h"

namespace XPlus
{
  class Namespaces
  {
    public:

      //
      //                  'xml' prefix: namespace and attributes 
      //
      static DOM::DOMString   s_xmlStr; 
      static DOM::DOMString   s_xmlUri;
      static DOM::DOMString   s_xmlLangStr; 
      static DOM::DOMString   s_xmlSpaceStr;
      static DOM::DOMString   s_xmlBaseStr;
      static DOM::DOMString   s_xmlIdStr;
      // respective static pointers to the above xml strings
      static DOM::DOMStringPtr   s_xmlStrPtr; 
      static DOM::DOMStringPtr   s_xmlUriPtr;
      static DOM::DOMStringPtr   s_xmlLangStrPtr; 
      static DOM::DOMStringPtr   s_xmlSpaceStrPtr;
      static DOM::DOMStringPtr   s_xmlBaseStrPtr;
      static DOM::DOMStringPtr   s_xmlIdStrPtr;

      //
      //                  'xsi' prefix: namespace and attributes 
      //

      // the string "xsi" and not this prefix's nsUri in the context
      static DOM::DOMString   s_xsiStr; 
      // pointer to DOMString : "http://www.w3.org/2001/XMLSchema-instance"
      static DOM::DOMString   s_xsiUri;
      // the string "type" and not this attribute's value in the context
      static DOM::DOMString   s_xsiTypeStr; 
      // the string "nil" and not this attribute's value in the context
      static DOM::DOMString   s_xsiNilStr;
      // the string "schemaLocation" and not this attribute's value in the context
      static DOM::DOMString   s_xsiSchemaLocationStr;
      // the string "noNamespaceSchemaLocation" and not this attribute's value in the context
      static DOM::DOMString   s_xsiNoNamespaceSchemaLocationStr;

      // respective static pointers to the above xsi strings
      static DOM::DOMStringPtr   s_xsiStrPtr; 
      static DOM::DOMStringPtr   s_xsiUriPtr;
      static DOM::DOMStringPtr   s_xsiTypeStrPtr; 
      static DOM::DOMStringPtr   s_xsiNilStrPtr;
      static DOM::DOMStringPtr   s_xsiSchemaLocationStrPtr;
      static DOM::DOMStringPtr   s_xsiNoNamespaceSchemaLocationStrPtr;
  };
}

#endif
