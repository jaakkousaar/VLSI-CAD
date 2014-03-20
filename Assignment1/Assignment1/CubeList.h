#pragma once

// CUSTOM HEADERS
#include "Cube.h"

// STL HEADERS
#include <vector>
#include <memory>
#include <string>
#include <array>
#include <cmath>

class CubeList
{

public:

	// GETTERS/SETTERS

	// Get main list size
	inline const unsigned getSize( void )const { return list.size(); };

	// Get cube size
	inline const unsigned getCubeSize( void )const { return cSize; };

	// Set cube size variable
	inline void setSize( const unsigned u ){ cSize = u; };

	// Get pointer to cube in list(
	inline std::unique_ptr< Cube > getCubeRef( const unsigned num,
		std::vector< std::unique_ptr< Cube > >& lst )
		{ return move( lst.at( num ) ); };

	// Getter for getting reference to main cube list
	inline std::vector< std::unique_ptr< Cube > >& getMainList( void )
		{ return list; };

	// CUSTOM METHODS

	// Method for converting cube data to human readable string
	const std::string printCube( const unsigned num );

	// Add pointer of a new cube to the list
	inline void addNew( std::unique_ptr< Cube > c ) 
		{ list.push_back( std::move( c ) ); };

	// Method for creating complements from PCN
	void createComplementPCN( std::vector< std::unique_ptr< Cube > >& lst );

	// CONSTRUCT/DESTRUCT

	CubeList(void);
	~CubeList(void);

private:

	// VARIABLES

	unsigned cSize;
	unsigned mostBinate;
	unsigned curMax;

	//CONTAINERS

	// Main data structure holding cubes
	std::vector< std::unique_ptr< Cube > > list;
	// Additional structure for holding temporary pos cofactor
	std::vector< std::unique_ptr< Cube > > pos;
	// Additional structure for holding temporary neg cofactor
	std::vector< std::unique_ptr< Cube > > neg;
	// Temp vectors for holding binated level for each vars
	std::vector< unsigned > T; // True form level
	std::vector< unsigned > C; // Complement form level
	// Temp vector for max binated variable(s)
	std::vector< unsigned > max;

	

	// CUSTOM METHODS

	// Method for finding most binate variable
	const unsigned getMostBinate( void );

	// Helper method for looping all cubes and 
	// filling vectors with according binated levels
	const bool getBinatedLevels( void );

	// Helper method for looping all cubes and 
	// filling vectors with according unated levels.
	// Used if no binated values are found
	const unsigned getUnatedLevels( void );

	// Helper methor for getting best var from equal
	// binate values 
	const unsigned getMaxFromEquals( void );

	// Helper method for detecting if PCN is simple
	// enough to complement (according to 3 rules)
	const bool containsDontCare( std::vector< std::unique_ptr< Cube > >& lst );

	// Method for calculating complement PCN
	void getComplement( const unsigned num );

	// Method for creating true form Shannon Cofactor
	void getPosCofactor( const unsigned binate );

	// Method for creating complemented form Shannon Cofactor
	void getNegCofactor( const unsigned binate );

	// Method for joining two cofactors to a new list of cubes
	void joinCoFactors( void );

};

