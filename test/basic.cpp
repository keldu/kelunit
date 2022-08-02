#include "../source/kelunit/distance/meter.h"
#include "../source/kelunit/time/second.h"

#include "../source/kelunit/unit_print.h"

#include <iostream>

int main(){
	/**
	* The definition is a bit convoluted, so I leave it in the hands of the headers themselves and define a convenience alias for the user.
	* meter e.g. is defined by
	*
	* namespace unit_type {
	*   struct meter {};
	* }
	* template<typename S>
	* using meter = unit<S, unit_base<unit_type::meter, 1>>;
	*
	* which then can be used as follows
	*/
	using scalar = kelun::scalar<float>;
	using meter = kelun::meter<float>;
	using square_meter = kelun::square_meter<float>;
	using second = kelun::second<float>;

	meter a = 6.f;

	meter b = 3.f;

	second s = 10.f;

	// Since it is not compileable I cannot show it, but c + s would throw a compilation error.
	meter c = a+b;
	meter d = a-b;

	// Auto deduced type. Based on the template parameters automatically stitches together a valid unit
	auto mps = b / s;

	// Technically auto deduced, but predefined for convenience.
	square_meter e = a*b;
	// 
	scalar f = a/b;

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
