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

#ifndef __SAMPLER_H__
#define __SAMPLER_H__

#include "DOM/DOMAllInc.h"
#include "XPlus/Types.h"

#define CNT_SAMPLES 10

namespace XMLSchema
{
  namespace Sampler
  {
    const extern DOM::DOMString alphaCharSet;
    const extern DOM::DOMString alphaNumCharSet;
    const extern DOM::DOMString hexBinaryCharSet;

    extern DOM::DOMString stringSamples[CNT_SAMPLES];
    extern DOM::DOMString booleanSamples[CNT_SAMPLES];
    extern DOM::DOMString normalizedStringSamples[CNT_SAMPLES];
    extern DOM::DOMString floatSamples[CNT_SAMPLES];
    extern DOM::DOMString intSamples[CNT_SAMPLES];
    extern DOM::DOMString longSamples[CNT_SAMPLES];
    extern DOM::DOMString doubleSamples[CNT_SAMPLES];
    extern DOM::DOMString unsignedIntSamples[CNT_SAMPLES];
    extern DOM::DOMString unsignedLongSamples[CNT_SAMPLES];
    extern DOM::DOMString unsignedShortSamples[CNT_SAMPLES];
    extern DOM::DOMString unsignedByteSamples[CNT_SAMPLES];
    extern DOM::DOMString byteSamples[CNT_SAMPLES];
    extern DOM::DOMString NameSamples[CNT_SAMPLES];
    extern DOM::DOMString NCNameSamples[CNT_SAMPLES];
    extern DOM::DOMString NOTATIONSamples[CNT_SAMPLES];
    extern DOM::DOMString QNameSamples[CNT_SAMPLES];
    extern DOM::DOMString anyURISamples[CNT_SAMPLES];
    extern DOM::DOMString base64BinarySamples[CNT_SAMPLES];
    extern DOM::DOMString hexBinarySamples[CNT_SAMPLES];
    extern DOM::DOMString gMonthSamples[CNT_SAMPLES];
    extern DOM::DOMString gDaySamples[CNT_SAMPLES];
    extern DOM::DOMString gMonthDaySamples[CNT_SAMPLES];
    extern DOM::DOMString gYearSamples[CNT_SAMPLES];
    extern DOM::DOMString gYearMonthSamples[CNT_SAMPLES];
    extern DOM::DOMString dateSamples[CNT_SAMPLES];
    extern DOM::DOMString timeSamples[CNT_SAMPLES];
    extern DOM::DOMString dateTimeSamples[CNT_SAMPLES];
    extern DOM::DOMString durationSamples[CNT_SAMPLES];
    extern DOM::DOMString decimalSamples[CNT_SAMPLES];
    extern DOM::DOMString positiveIntegerSamples[CNT_SAMPLES];
    extern DOM::DOMString nonNegativeIntegerSamples[CNT_SAMPLES];
    extern DOM::DOMString shortSamples[CNT_SAMPLES];
    extern DOM::DOMString negativeIntegerSamples[CNT_SAMPLES];
    extern DOM::DOMString nonPositiveIntegerSamples[CNT_SAMPLES];
    extern DOM::DOMString integerSamples[CNT_SAMPLES];
    extern DOM::DOMString IDSamples[CNT_SAMPLES];
    extern DOM::DOMString NMTOKENSamples[CNT_SAMPLES];
    extern DOM::DOMString NMTOKENSSamples[CNT_SAMPLES];
    extern DOM::DOMString ENTITYSamples[CNT_SAMPLES];
    extern DOM::DOMString ENTITIESSamples[CNT_SAMPLES];
    extern DOM::DOMString IDREFSamples[CNT_SAMPLES];
    extern DOM::DOMString IDREFSSamples[CNT_SAMPLES];
    extern DOM::DOMString languageSamples[CNT_SAMPLES];
    extern DOM::DOMString tokenSamples[CNT_SAMPLES];

    DOM::DOMString getRandomSampleStringOfLengthRange(int minLength, int maxLength, DOM::DOMString charSet=alphaCharSet);
    DOM::DOMString getRandomSampleStringOfMinLength(int minLength, DOM::DOMString charSet=alphaCharSet);
    DOM::DOMString getRandomSampleStringOfMaxLength(int maxLength, DOM::DOMString charSet=alphaCharSet);
    DOM::DOMString getRandomSampleStringOfLength(int length, DOM::DOMString charSet=alphaCharSet);

    DOM::DOMString getRandomSampleBase64StringOfLength(int length);
    DOM::DOMString getRandomSampleBase64StringOfLengthRange(int minLength, int maxLength);
    DOM::DOMString getRandomSampleBase64StringOfMinLength(int minLength);
    DOM::DOMString getRandomSampleBase64StringOfMaxLength(int maxLength);
    
    DOM::DOMString getUrlSchemeSample(int len);
    DOM::DOMString getUrnSchemeSample(int len);
    DOM::DOMString getRandomSampleAnyURIOfLength(int len);
    DOM::DOMString getRandomSampleAnyURIOfLengthRange(int minLen, int maxLen);
    DOM::DOMString getRandomSampleAnyURIOfMinLength(int minLen);
    DOM::DOMString getRandomSampleAnyURIOfMaxLength(int maxLen);

    DOM::DOMString getRandomSampleLong(XPlus::Int64 minIncl, XPlus::Int64 maxIncl);
    DOM::DOMString getRandomSampleLongOfLength(int len);
    
    DOM::DOMString getRandomSampleDouble(double minIncl, double maxIncl);
    // -1 in totalDigits/fractionDigits digits means those are unset
    DOM::DOMString getRandomSampleDoubleOfDigits(int totalDigits=-1, int fractionDigits=-1);

    DOM::DOMString getRandomSample(std::vector<DOM::DOMString> samples);
    DOM::DOMString getRandomSample(DOM::DOMString *arrSamples, int lenSamples=CNT_SAMPLES);

    XPlus::UInt64 nonnegativeIntegerRandom(XPlus::UInt64 maxExcl);
    XPlus::Int64 integerRandomInRange(XPlus::Int64 minIncl, XPlus::Int64 maxExcl);
  }
}

#endif
