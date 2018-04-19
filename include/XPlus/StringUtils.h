// This file is part of XmlPlus package
// 
// Copyright (C)   2010-2013 Satya Prakash Tripathi
// Copyright (C)   2017-2018 Akamai Technologies
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

#ifndef __XPLUS_STRINGUTILS_H__ 
#define __XPLUS_STRINGUTILS_H__

#include <sstream>
#include <string>
#include <iostream>

#include "XPlus/Exception.h"
#include "XPlus/UString.h"

using namespace std;

namespace XPlus
{
  template <class T> string toString (const T & t)
  {
    string result;
    ostringstream oss;
    oss << t;
    if (!oss) {
      throw StringException("toString failed");
    }
    return oss.str();
  }

  template <> string toString (const bool& b);
  template <> string toString (const string& b);
  template <> string toString (const UString& b);

  template <class T> T fromString(const string& s)
  {
    T result;
    istringstream iss (s);
    iss >> result;
    return result;
  }

  template <> bool fromString<bool>(const string& s);
  template <> string fromString<string>(const string& s);
  template <> UString fromString<UString>(const string& s);
}
#endif
