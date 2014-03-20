#include "CubeList.h"
#include "DataExtractor.h"

#include <vector>
#include <iostream>
#include <string>

int main( int argc, char* argv[] )
{
	//std::cout << argv[ 0 ] << std::endl;
	//std::cout << argv[ 1 ] << std::endl;
	std::string s( argv[ 1 ] );
	DataExtractor dc( s );

	CubeList cl;

	dc.extractCubeList( cl );

	cl.createComplementPCN( cl.getMainList() );

	dc.writeOutList( cl );



	return 0;
}