// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <experimental/filesystem>

using namespace std;

template<typename T>
T square(T x) {return x*x;};