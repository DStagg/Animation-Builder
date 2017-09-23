#include "BinarySave.h"

//	Explicit implementations	//

//std::string
template <>
void BinaryFile::Write<std::string>( std::string s )
{
	Write<int>( s.size() );
	for ( int i = 0; i < (int)s.length(); i++ )
		Write<char>( s[i] );
};
template <>
std::string BinaryFile::Read<std::string>()
{
	int Size = Read<int>();
	std::string Temp = "";

	for ( int i = 0; i < Size; i++ )
		Temp += Read<char>();

	return Temp;
};

//bool

template<>
void BinaryFile::Write<bool>( bool b )
{
	if ( b )
		Write<char>( '1' );
	else
		Write<char>( '0' );
};
template<>
bool BinaryFile::Read<bool>()
{
	return ( Read<char>() == '1' );
};