#include "../source/kelunit/distance/meter.h"
#include "../source/kelunit/time/second.h"

#include "../source/kelunit/unit_print.h"

#include <iostream>

int main(){
	using scalar = kelun::scalar<float>;
	using meter = kelun::meter<float>;
	using square_meter = kelun::square_meter<float>;
	using second = kelun::second<float>;

	meter a = 6.f;

	meter b = 3.f;

	second s = 10.f;

	meter c = a+b;
	meter d = a-b;

	square_meter e = a*b;
	// 
	scalar f = a/b;

	auto mps = b / s;

	std::cout<<"Values:\n";
	std::cout<<"a: "<<a<<"\n";
	std::cout<<"b: "<<b<<"\n";
	std::cout<<"c: "<<c<<"\n";
	std::cout<<"d: "<<d<<"\n";
	std::cout<<"e: "<<e<<"\n";
	std::cout<<"f: "<<f<<"\n";
	std::cout<<"mps: "<<mps<<"\n";
	std::cout<<std::endl;

	return 0;
}
