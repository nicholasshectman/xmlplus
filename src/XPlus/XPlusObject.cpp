// This file is part of XmlPlus package
// 
// Copyright (C)   2018 Akamai Technologies, Inc
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

#include "XPlus/XPlusObject.h"
#include "XPlus/UString.h"

namespace XPlus {

UString* XPlusObject::adopt(const UString &str) {
  _adoptedStrings.push_back(new UString(str));
  return _adoptedStrings.back();
}

XPlusObject::~XPlusObject() {
  for (vector<UString *>::const_iterator it = _adoptedStrings.begin();
       it != _adoptedStrings.end(); ++it)
  {
    delete *it;
  }
}

}
