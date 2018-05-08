// This file is part of XmlPlus package
// 
// Copyright (C)   2010-2013 Satya Prakash Tripathi
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

#ifndef __XMLPLUSOBJECT_H__
#define __XMLPLUSOBJECT_H__

#include <iostream>
#include <sstream>
#include <vector>

namespace XPlus {
  class UString;

struct XPlusObject {
  std::string _objName;
  int _refCnt;
  bool _dontFree;


  inline void dontFree(bool b) {
    _dontFree = b;
  }
  inline bool dontFree() const {
    return _dontFree;
  }

  inline void printRefCnt() {
    std::cout << "@@@@@@@@@@ ptr= " << this  << " name:" <<  _objName << " cnt=" << _refCnt << " : printRefCnt" << std::endl;
  }

  inline virtual void duplicate() {
    ++_refCnt;
  }

  inline virtual void release() {
    --_refCnt;
    if( (_refCnt==0) && !_dontFree) {
      delete this;
    }
  }

  XPlusObject(std::string name=""):
    _objName(name),
    _refCnt(0),
    _dontFree(false)
  {
    std::ostringstream oss;
    oss << this;
  }

  virtual ~XPlusObject();

  // take responsibility for deleting a UString since those aren't really refcounted
  UString* adopt(const UString &str);
  void adopt(UString *ptr) { _adoptedStrings.push_back(ptr); }
 private:
  // keep pointers to the strings instead of strings directly
  // so that they won't be relocated and consumers can store pointers and refs
  std::vector<UString *> _adoptedStrings;
};

} // end namespace XPlus
#endif
