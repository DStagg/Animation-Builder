#include "BinaryFile.h"

BinaryFile::BinaryFile()
{
	SetFileName( "" );
	SetMode( IO_IN );
};

BinaryFile::BinaryFile( std::string name , int mode , bool overwrite )
{
	if ( mode == IO_IN )
		overwrite = false;
	if( !Open( name , mode , overwrite ) )
		SetFileName( "" );
};

void BinaryFile::Create( std::string file )
{
	Open( file , IO_OUT , true );
	Close();
};

bool BinaryFile::IsOpen()
{
	return _Stream.is_open();
};

void BinaryFile::SetMode( int mode )
{
	if ( GetMode() != mode )
	{	
		_Mode = mode;
		if ( _Stream.is_open() )
		{
			_Stream.close();
			Open( GetFileName() );
		}
	}
};

int BinaryFile::GetMode()
{
	return  _Mode;
};

void BinaryFile::SetPosition( int i )
{
	if ( i < 0 )
		i = 0;
	if ( i >= FileSize() )
		i = FileSize() - 1;

	if ( GetMode() == IO_IN )
		_Stream.seekp( i );
	else
		_Stream.seekg( i );
};

int BinaryFile::GetPosition()
{
	if ( GetMode() == IO_IN )
		return (int)_Stream.tellp();
	else
		return (int)_Stream.tellg();
};

void BinaryFile::Advance( int i )
{
	SetPosition( GetPosition() + i );
};

int BinaryFile::FileSize()
{
	int temp = GetPosition();
	int size;

	if ( GetMode() == IO_IN )
	{
		_Stream.seekp( 0 , std::ios::end );
		size = (int)_Stream.tellp();
		_Stream.seekp( temp );
	}
	else
	{
		_Stream.seekg( 0 , std::ios::end );
		size = (int)_Stream.tellg();
		_Stream.seekg( temp );
	}

	return size;
};

bool BinaryFile::Open( std::string file , int mode , bool overwrite )
{
	SetFileName( file );
	SetMode( mode );

	if ( GetMode() == IO_IN )
		_Stream.open( GetFileName().c_str() , std::ios::binary | std::ios::in );
	else if ( GetMode() == IO_OUT )
	{
		if ( overwrite )
			_Stream.open( GetFileName().c_str() , std::ios::binary | std::ios::out | std::ios::trunc );		
		else
			_Stream.open( GetFileName().c_str() , std::ios::binary | std::ios::out );
	}
	else
		return false;

	return _Stream.is_open();
};

void BinaryFile::Close()
{
	_Stream.close();
};

void BinaryFile::SetFileName( std::string file )
{
	_FileName = file;
};

std::string BinaryFile::GetFileName()
{
	return _FileName;
};