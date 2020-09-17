buildprogram: decode.cpp
	g++ -std=c++11 -o decode decode.cpp
buildprogram: encode.cpp
	g++ -std=c++11 -o encode encode.cpp
buildprogram: troubleshoot.cpp
	g++ -std=c++11 -o troubleshoot troubleshoot.cpp