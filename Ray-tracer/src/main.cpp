#include <iostream>
#include <cmath>
#include "Tracing/Tracer.hpp"

int main()
{
	Tracer* tracer = new Tracer();
	tracer->Run();
	delete tracer;
	return 0;
}