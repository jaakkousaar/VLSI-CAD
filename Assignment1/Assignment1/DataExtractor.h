#pragma once

// CUSTOM HEADERS
#include "Cube.h"
#include "CubeList.h"

// STL HEADERS
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class DataExtractor
{

public:

	
	// CUSTOM  METHODS

	void extractCubeList( CubeList& cl );	
	// Method for writing cube list to file
	void writeOutList( CubeList& cl );

	// CONSTRUCT/DESTRUCT

	DataExtractor( const std::string& fname );
	~DataExtractor( void );

private:

	// VARIABLES

	unsigned varCount;
	unsigned cubeCount;

	// CONTAINERS

	std::string fileName;

	// MEMBER OBJECTS

	std::ifstream pIn;
	std::ofstream pOut;
	std::exception exFile;

	// CUSTOM  METHODS
	
	// Method for checking if file has correct extension.
	// Returns true if ok, false otherwise
	const bool IsGoodExtension( const std::string& file, 
		const std::string& ext );

	// Method for opening inputstream for file reading
	// Return true if stream is successfully opened, false otherwise
	const bool TryOpenInStream( void );

	// Method for opening outputstream for file reading
	// Return true if stream is successfully opened, false otherwise
	const bool TryOpenOutStream( std::string& out );

	// Method for reading first two line of files to
	// determine dimensions we are dealing with
	void readDimParameters( void );

	// Method for reading data from file, line by line,
	// decoding them and storing coded data to vector.
	// Return true if line is read, false otherwise
	const bool getNextCube( CubeList& cl );

};

