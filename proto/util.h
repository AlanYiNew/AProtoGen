#ifndef _COMM_GAMECORE_UTIL_H_
#define _COMM_GAMECORE_UTIL_H_

#include <string>
#include <iostream>
#include "time.h"
#include "stdio.h"
struct tagJsonPrintOptionsPbc {
    bool always_print_primitive_fields;
    bool preserve_proto_field_names;
    bool url_encode_strings;
};
typedef struct tagJsonPrintOptionsPbc JSONPRINTOPTIONSPBC;
typedef struct tagJsonPrintOptionsPbc *LPJSONPRINTOPTIONSPBC;

struct tagJsonParseOptionsPbc {
    bool url_encode_strings;
};
typedef struct tagJsonParseOptionsPbc JSONPARSEOPTIONSPBC;
typedef struct tagJsonParseOptionsPbc *LPJSONPARSEOPTIONSPBC;



inline unsigned char ToHex(unsigned char x) 
{ 
    return  x > 9 ? x + 55 : x + 48; 
}

inline int FromHex(unsigned char x, unsigned char* y) 
{ 
    //unsigned char y;
    if (x >= 'A' && x <= 'Z') *y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') *y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') *y = x - '0';
    else return -1;

    return 0;
}

inline std::string UrlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) || 
                (str[i] == '-') ||
                (str[i] == '_') || 
                (str[i] == '.') || 
                (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

inline int UrlDecode(const std::string& str, std::string& decStr)
{
    int iRet;
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == '+') decStr += ' ';
        else if (str[i] == '%')
        {
            if (i + 2 >= length)
                return -1;

            unsigned char high;
            iRet = FromHex((unsigned char)str[++i], &high);
            if (iRet != 0)
                return iRet;

            unsigned char low;
            iRet = FromHex((unsigned char)str[++i], &low);
            if (iRet != 0)
                return iRet;

            decStr += high*16 + low;
        }
        else decStr += str[i];
    }
    return 0;
}

// Return a mutable char* pointing to a string's internal buffer,
// which may not be null-terminated. Writing through this pointer will
// modify the string.
inline char* string_as_array(std::string* str) {
  // DO NOT USE const_cast<char*>(str->data())! See the unittest for why.
  return str->empty() ? NULL : &*str->begin();
}

inline bool TimeStampToLocalTimeString(long long int time_int, char* buffer, int buffer_size)
{
    time_t time_stamp = time_int;
    struct tm* pstTm;
    pstTm = localtime(&time_stamp);
    if( !pstTm )
        return false;
    short nYear = (short)(pstTm->tm_year + 1900);
	unsigned char bMonth = (unsigned char)pstTm->tm_mon + 1;
	unsigned char bDay = (unsigned char)pstTm->tm_mday;
	short nHour = (short)pstTm->tm_hour;
	unsigned char bMin = (unsigned char)pstTm->tm_min;
	unsigned char bSec = (unsigned char)pstTm->tm_sec;

    int iWrite = snprintf(buffer, buffer_size, "%4d-%02d-%02d %02d:%02d:%02d", nYear, bMonth, bDay, nHour, bMin, bSec);
	if ((0 > iWrite)||(iWrite >= buffer_size))
	{
		return false;
	}
    return true;
}

#endif //_COMM_GAMECORE_UTIL_H_=======
