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

#include "XPlus/Namespaces.h"

using namespace DOM;

namespace XPlus
{
  // namespace and attributes with 'xml' prefix
  DOMString     Namespaces::s_xmlStr                             = "xml"; 
  DOMString     Namespaces::s_xmlUri                             = "http://www.w3.org/XML/1998/namespace";
  DOMString     Namespaces::s_xmlLangStr                         = "lang";
  DOMString     Namespaces::s_xmlSpaceStr                        = "space";
  DOMString     Namespaces::s_xmlBaseStr                         = "base";
  DOMString     Namespaces::s_xmlIdStr                           = "id";

  DOMStringPtr  Namespaces::s_xmlStrPtr                          = &s_xmlStr; 
  DOMStringPtr  Namespaces::s_xmlUriPtr                          = &s_xmlUri;
  DOMStringPtr  Namespaces::s_xmlLangStrPtr                      = &s_xmlLangStr; 
  DOMStringPtr  Namespaces::s_xmlSpaceStrPtr                     = &s_xmlSpaceStr; 
  DOMStringPtr  Namespaces::s_xmlBaseStrPtr                      = &s_xmlBaseStr; 
  DOMStringPtr  Namespaces::s_xmlIdStrPtr                        = &s_xmlIdStr; 


  // namespace and attributes with 'xsi' prefix
  DOMString     Namespaces::s_xsiStr                             = "xsi"; 
  DOMString     Namespaces::s_xsiUri                             = "http://www.w3.org/2001/XMLSchema-instance";
  DOMString     Namespaces::s_xsiTypeStr                         = "type"; 
  DOMString     Namespaces::s_xsiNilStr                          = "nil";
  DOMString     Namespaces::s_xsiSchemaLocationStr               = "schemaLocation";
  DOMString     Namespaces::s_xsiNoNamespaceSchemaLocationStr    = "noNamespaceSchemaLocation";

  DOMStringPtr  Namespaces::s_xsiStrPtr                          = &s_xsiStr; 
  DOMStringPtr  Namespaces::s_xsiUriPtr                          = &s_xsiUri;
  DOMStringPtr  Namespaces::s_xsiTypeStrPtr                      = &s_xsiTypeStr; 
  DOMStringPtr  Namespaces::s_xsiNilStrPtr                       = &s_xsiNilStr;
  DOMStringPtr  Namespaces::s_xsiSchemaLocationStrPtr            = &s_xsiSchemaLocationStr;
  DOMStringPtr  Namespaces::s_xsiNoNamespaceSchemaLocationStrPtr = &s_xsiNoNamespaceSchemaLocationStr;

}

