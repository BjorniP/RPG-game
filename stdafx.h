#pragma once
/*These directories are pre-compiled so the compile time will be faster*/
#include<cstdlib>
#include<ctime>
#include<time.h>
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<list>
#include<utility>
#include<thread>
#include<set>
#include<memory>
#include<deque>
#include<algorithm>
#include<cmath>


//SFML libraries
#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

//Custom
#include"VectorMath.h"


//Pre-compiled means that these directories are compiled once, before anything else that
// is needed to be compiled and every other time we compile the program "knows" what these 
// directories include and skips these and compile other code blocks.This way the compile
//run-time will be much shorter.
