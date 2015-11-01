// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef _WIN32
    #include "targetver.h"

#include <Windows.h>
#include <iostream>
#include <sstream>

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}
#endif

#include <stdio.h>


// TODO: reference additional headers your program requires here

//Adding required boost header
#include <boost/test/unit_test.hpp>
#include "easylogging++.h"
#include "SimpleSignal.h"