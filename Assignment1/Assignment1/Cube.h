#pragma once

// STL HEADERS
#include <vector>

class Cube
{

public:

	// GETTERS/SETTERS

	inline const unsigned getSize( void )const { return size; };
	inline const unsigned getVar( const unsigned u )const 
		{ return u < varCube.size() ? varCube.at( u ) : 2; };
	inline void setVar( const unsigned u, const unsigned val ) 
		{ varCube.at( u ) =  val; }; 

	// CUSTOM METHODS

	// Method for adding new value to varCube vector
	void addVar( const int pos, unsigned val );

	// Method for checking if cube contains only 
	// don't care values (11)
	const bool isDontCare( void );

	// CONSTRUCT/DESTRUCT

	// Constructor for creating cube with specific values
	Cube( const unsigned u, const unsigned val );
	// Copy constructor and copy assignment operator
	Cube( const Cube& orig );
	Cube& operator= ( const Cube& orig );
	// Move constructor and move assignment operator
	Cube( Cube&& orig );
	Cube& operator= ( Cube&& orig );
	// Destructor
	~Cube( void );

private:

	// VARIABLES

	unsigned size;

	// CONTAINERS

	std::vector< unsigned > varCube;


};

