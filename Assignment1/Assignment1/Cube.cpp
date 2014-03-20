#include "Cube.h"

using std::vector;


void Cube::addVar( const int pos, unsigned val )
{
	varCube.at( pos ) = val;
}


const bool Cube::isDontCare( void )
{
	// Loop through all variables in cube 
	for( unsigned u = 0; u < size; ++u )
	{
		// If true or comp form found return false
		if( varCube.at( u ) != 11 )
			return false;
	}
	// Else it is Don't care cube
	return true;
}


Cube::Cube( const unsigned u, const unsigned val )
{
	size = u;

	// Create and assigne variable vector
	varCube.assign( size, val);
}


Cube::Cube( const Cube& orig )
{
	size = orig.size;
	varCube = orig.varCube;
}

Cube& Cube::operator= ( const Cube& orig )
{
    if ( this == &orig )
        return *this;
 
	size = orig.size;
	varCube = orig.varCube;

    return *this;
}

Cube::Cube( Cube&& orig )
{
	size = orig.size;
	varCube = orig.varCube;
}

Cube& Cube::operator= ( Cube&& orig )
{
	if( this != &orig )
	{
		size = orig.size;
		varCube = orig.varCube;
	}
	return *this;
}


Cube::~Cube(void)
{
}
