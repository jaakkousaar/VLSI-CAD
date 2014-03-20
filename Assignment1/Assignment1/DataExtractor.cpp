#include "DataExtractor.h"


using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::exception;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::istringstream;
using std::stoi;
using std::unique_ptr;
using std::move;
using std::to_string;


void DataExtractor::extractCubeList( CubeList& cl )
{
	// Check file extension
	if( !IsGoodExtension( fileName, "pcn" ) ) 
	{
		cout << "Wrong extension in source file" << endl;
		exit( -1 );
	}
	// If extension is good try open files
	if( !TryOpenInStream() )
	{
		cout << "Error opening files" << endl;
		exit( -1 );
	}
	readDimParameters();
	cl.setSize( varCount );
	// Create cube and fill it with data from file
	for( unsigned u = 0; u < cubeCount; ++u )
	{
		if( !getNextCube( cl ) )
		{
			cout << "Exiting..."<< endl;
			exit( -1 );
		}
	}
}


void DataExtractor::readDimParameters( void )
{
	string line;
	// Read first line of file...
	getline( pIn, line );
	istringstream iss1( line );
	// ...and get variable count
	string token;
	iss1 >> token;
	varCount = stoi( token );
	// Read second line of file...
	getline( pIn, line );
	istringstream iss2( line );
	// ...and get cube count
	iss2 >> token;
	cubeCount = stoi( token );
}


const bool DataExtractor::getNextCube( CubeList& cl )
{
	unique_ptr< Cube > ptr( new Cube( varCount, 11 ) );
	string line;
	// If there is another line to read
	if( getline( pIn, line ) )
	{
		string token;
		istringstream iss( line );
		// Get first number for count
		iss >> token;
		unsigned count = stoi( token );
		// For every numbers in line, add it to vector
		for( unsigned u = 0; u < count; ++u )
		{
			iss >> token;
			// Decode
			int i = stoi( token );
			if( i < 0 )
			{
				i = -i;
				ptr->addVar( i - 1, 10 );
			}
			else 
				ptr->addVar( i - 1, 1 );
			
		}
		cl.addNew( move( ptr ) );
		return true;
	}
	else
	{
		cout << "File does not have enough rows... " <<  endl;
		return false;
	}
}


const bool DataExtractor::IsGoodExtension( const string& file, const string& ext )
{
	string s = file.substr( file.find_last_of( "." ) + 1 );
	unsigned sz = s.size();
	// Check extension length
	if( ext.size() != sz )
	{
		cout << "Wrong file extension length!" << endl;
		return false;
	}
	// Check extension equality
	for( size_t i = 0; i < sz; ++i )
	{
		if ( tolower( s[ i ] ) != tolower( ext[ i ] ) )
		{
			cout << "Wrong file extension!" << endl;
			return false;
		}
	}
	return true;
};


const bool DataExtractor::TryOpenInStream( void )
{
	try
	{
		pIn.open( fileName.c_str(), ios::in );
		pIn.exceptions( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
		if( !pIn && !pIn.is_open() )
		{
			cout << "File Is NOT Open!" << endl;
			return false;
		}
	}
	catch( exception const& e )
	{
		string strFormatted = "The file " + fileName + " could not be opened due to this error: ";
		strFormatted += e.what();
		cout << strFormatted << endl;
		pIn.close();
		return false;
	}
	return true;
}


const bool DataExtractor::TryOpenOutStream( string& out )
{
	try
	{
		pOut.open( out.c_str(), ios::out );
		pOut.exceptions( ofstream::eofbit | ofstream::failbit | ofstream::badbit );
		if( !pOut && !pOut.is_open() )
		{
			cout << "File Is NOT Open!" << endl;
			return false;
		}
	}
	catch( exception const& e )
	{
		string strFormatted = "The file " + out + " could not be opened due to this error: ";
		strFormatted += e.what();
		cout << strFormatted << endl;
		pOut.close();
		return false;
	}
	return true;
}


void DataExtractor::writeOutList( CubeList& cl )
{
	string outFile = "";
	outFile = "o_" + fileName;
	if( !TryOpenOutStream( outFile ) )
		exit( -1 );

	const unsigned lSize = cl.getSize();
	pOut << lSize << endl;
	const unsigned cSize = cl.getCubeSize();
	pOut << cSize << endl;

	for( unsigned u = 0; u < lSize; ++u )
		pOut << cl.printCube( u );

	pOut.close();
}


DataExtractor::DataExtractor( const std::string& fname )
{
	fileName = fname;
}


DataExtractor::~DataExtractor(void)
{
}
