#include "CubeList.h"


using std::vector;
using std::string;
using std::unique_ptr;
using std::to_string;
using std::move;


void CubeList::createComplementPCN( vector< unique_ptr< Cube > >& lst )
{
	unsigned size = list.size();
	// Check for 3 rules of simple PCN.If this is simple enough, 
	// complement it and return from recursion
	if( !size )
	{
		unique_ptr< Cube > cube( new Cube( cSize, 11 ) );
		// Clear list and set its size to zero
		vector< unique_ptr< Cube > >().swap( list );
		list.push_back( move( cube ) );
		return;
	}
	else if( size == 1 )
	{
		getComplement( 0 );
		return;
	}
	else if( containsDontCare( lst ) )
	{
		vector< unique_ptr< Cube > >().swap( list );
		return;
	}
	// Else create recursion for Shannon cofactoring the cube list
	else
	{
		unsigned temp = getMostBinate();
		getPosCofactor( temp );
		getNegCofactor( temp );
		createComplementPCN( pos );
		createComplementPCN( neg );
		joinCoFactors();
	}
}


const bool CubeList::containsDontCare( vector< unique_ptr< Cube > >& lst )
{
	// Loop through all cubes
	for( auto it = lst.begin(); it != lst.end(); ++it )
	{
		// If don't care cube is found, return true
		if( it->get()->isDontCare() )
			return true;
	}
	// Else signal that list doesn't contain any don't care cube
	return false;
}


void CubeList::getComplement( const unsigned num )
{
	// Create temp, copy existing cube there and clear original
	unique_ptr< Cube > cube( new Cube( cSize, 11 ) );
	cube = move( list.at( num ) );
	vector< unique_ptr< Cube > >().swap( list );	
	// Get all vars from cube 
	for( unsigned u = 0; u < cSize; ++u )
	{
		unsigned t = list.at( num )->getVar( u );
		unique_ptr< Cube > temp( new Cube( cSize, 11 ) );
		// Complement current
		if( t == 1 )
			temp->setVar( u, 10 );
		else if( t == 10 )
			temp->setVar( u, 1 );
		addNew( move( temp ) );
	}
}


void CubeList::getPosCofactor( const unsigned binate )
{
	// Clear current Pos cofactor list and set it's size to zero
	vector< unique_ptr< Cube > >().swap( pos );
	// Loop through current list 
	for( auto it = list.begin(); it != list.end(); ++it )
	{
		// If current value is positive, it gets don't care
		if( it->get()->getVar( binate ) == 1 )
			it->get()->setVar( binate, 11 );
		// If value is negtive, delete this cube from list
		else if( it->get()->getVar( binate ) == 10 )
		{
			swap( *it, list.back() );
			list.pop_back();
		}
	}
}


void CubeList::getNegCofactor( const unsigned binate )
{
	// Clear current Pos cofactor list and set it's size to zero
	vector< unique_ptr< Cube > >().swap( pos );
	// Loop through current list 
	for( auto it = list.begin(); it != list.end(); ++it )
	{
		// If current value is negative, it gets don't care
		if( it->get()->getVar( binate ) == 10 )
			it->get()->setVar( binate, 11 );
		// If value is positive, delete this cube from list
		else if( it->get()->getVar( binate ) == 1 )
		{
			swap( *it, list.back() );
			list.pop_back();
		}
	}
}


void CubeList::joinCoFactors( void )
{
	// Clear existing list and set size to zero
	vector< unique_ptr< Cube > >().swap( list );
	// Include positive cofactor
	unsigned temp = pos.size();
	for( unsigned u = 0; u < temp; ++u )
		addNew( getCubeRef( u, pos ) );
	// Include negative cofactor
	temp = neg.size();
	for( unsigned u = 0; u < temp; ++u )
		addNew( getCubeRef( u, neg ) );
}


const unsigned CubeList::getMostBinate( void )
{
	unsigned cubeSize = list.at( 0 )->getSize();
	// Assign vectors
	T.assign( cubeSize, 0 );
	C.assign( cubeSize, 0 );
	max.assign( cubeSize, 0 );
	// Get binated level for all variables
	// If there is no binate get unate
	if( getBinatedLevels() )
	{
		// If there is 1 max, then we have answer
		if( max.size() == 1 )
			return max.at( 0 );
		else
			return getMaxFromEquals();
	}
	else
		return getUnatedLevels();
}


const bool CubeList::getBinatedLevels( void )
{
	curMax = 0;
	max.clear();
	bool comp = false, tru = false, both = false;
	unsigned cubeSize = list.at( 0 )->getSize();
	// Loop through all vars to get most binated
	for( unsigned u = 0; u < cubeSize; ++u )
	{
		for( auto it = list.begin(); it != list.end(); ++it )
		{
			// If according var is on true form
			if( it->get()->getVar( u ) == 1 )
			{
				++T.at( u );
				tru = true;
			}
			// If is in complemented form
			if( it->get()->getVar( u ) == 10 )
			{
				++C.at( u );
				comp = true;
			}
		}
		// Check if there has been binate?
		if( !u )
		{
			curMax = T.at( u ) + C.at( u );
			max.push_back( 0 );
		}
		if( !both ) 
			both = comp && tru;
		else
		{
			// Compare with max values
			if( T.at( u ) + C.at( u ) == curMax )
				max.push_back( u );
			else if( T.at( u ) + C.at( u ) > curMax )
			{
				max.clear();
				curMax = T.at( u ) + C.at( u );
				max.push_back( u );
			}
		}
	}
	if( both ) return true;
	else return false;
}


const unsigned CubeList::getUnatedLevels( void )
{
	curMax = 0;
	max.clear();
	T.clear();
	unsigned cubeSize = list.at( 0 )->getSize();
	// Loop through all vars to get most binated
	for( unsigned u = 0; u < cubeSize; ++u )
	{
		for( auto it = list.begin(); it != list.end(); ++it )
		{
			// If according var is not "don't care"
			if( it->get()->getVar( u ) == 1 || 
				it->get()->getVar( u ) == 10 )
				++T.at( u );
		}
		// Compare with max values
		if( T.at( u ) == curMax )
			max.push_back( u );
		else if( T.at( u ) > curMax )
		{
			max.clear();
			curMax = T.at( u );
			max.push_back( u );
		}
	}
	return max.at( 0 );
}


const unsigned CubeList::getMaxFromEquals( void )
{
	int val = -1;
	unsigned count = max.size();
	// Loop through max values and get |T-C| dif
	for( unsigned u = 0; u < count; ++u )
	{
		double min = 0.0, temp;
		temp = fabs( double( T.at( max.at( u ) ) - C.at( max.at( u ) ) ) );

		if( !u || min > temp )
		{
			min = temp;
			val = u;
		}
	}
	return unsigned( val );
}


const string CubeList::printCube( const unsigned num )
{
	string cubeData = "";
	unsigned counter = 0;
	// Loop through cube data
	for( unsigned u = 0; u < cSize; ++u )
	{
		// If positive, increment counter and put value into string
		if( list.at( num )->getVar( u ) == 1 )
		{
			cubeData = cubeData + " " + to_string( u + 1 );
			++counter;
		}
		else if( list.at( num )->getVar( u ) == 10 )
		{
			cubeData = cubeData + " " + "-" + to_string( u + 1 );
			++counter;
		}
	}
	// Form final string of cube representation
	return to_string( counter ) + cubeData;
}


CubeList::CubeList(void)
{
}


CubeList::~CubeList(void)
{
}
