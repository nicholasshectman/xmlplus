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

#ifndef __UTILS_EXCEPTION_H__
#define __UTILS_EXCEPTION_H__

#include <stdexcept>
#include <string>
#include <map>

namespace XPlus
{
  class Exception : public std::exception
  {
    protected:
      std::string                 _msg;
      std::map<std::string, std::string>    _contextMap;

    public:
     Exception(std::string msg="");

    virtual ~Exception() throw();
    
    virtual std::string msg();
    
    void msg(std::string str);
    
    void appendException(const Exception& ex);
    
    void appendMsg(std::string str);
    
    std::string rawMsg() const;

    void setContext(const std::string name, const double value);
    void setContext(const std::string name, const std::string value);
  };

  class NullPointerException : public XPlus::Exception {
    public:
      NullPointerException(std::string msg=""):
      Exception(msg)
    {
    }
  };

  class IndexOutOfBoundsException : public XPlus::Exception {
    public:
      IndexOutOfBoundsException(std::string msg=""):
      Exception(msg)
    {
    }
  };

  class RegularExpressionException: public XPlus::Exception
  {
    public:
      RegularExpressionException(std::string msg=""):
        Exception(msg)
      {
      }
  };
  
  class NotFoundException : public XPlus::Exception {
    public:
      NotFoundException(std::string msg=""):
      Exception(msg)
    {
    }
  };
  
  class DateTimeException : public XPlus::Exception {
    public:
      DateTimeException(std::string msg=""):
      Exception(msg)
    {
    }
  };
  
  class RuntimeException : public XPlus::Exception {
    public:
      RuntimeException(std::string msg=""):
      Exception(msg)
    {
    }
  };

  class StringException : public XPlus::Exception {
    public:
      StringException(std::string msg=""):
      Exception(msg)
    {
    }
  };

} 

#endif // __UTILS_EXCEPTION_H__
