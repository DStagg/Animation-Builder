#ifndef BINARY_FILE_H
#define BINARY_FILE_H

#include <fstream>

enum FileMode
{
	IO_IN,
	IO_OUT
};

class BinaryFile
{
public:

	BinaryFile();
	BinaryFile( std::string name , int mode = IO_IN , bool overwrite = false );

	void Create( std::string file );
	bool Open( std::string file , int mode = IO_IN , bool overwrite = false );
	void Close();
	void SetFileName( std::string file );
	std::string GetFileName();
	bool IsOpen();

	void SetPosition( int i );
	int GetPosition();
	void Advance( int i );
	int FileSize();

	void SetMode( int mode );
	int GetMode();

	template <class T>
	void Write( T data );	//	generic funtion for writing T into the stream, can be overwritten for non-standard data types
	template <class T>
	T Read();	//	generic function for reading T from the stream, can be overwritten for non-standard data types

private:

	std::fstream _Stream;
	std::string _FileName;
	int _Mode;
};


//	Read and Write	//

template <class T>
void BinaryFile::Write( T data )	//	generic funtion for writing T into the stream, can be overwritten for non-standard data types
{
	if ( GetMode() != IO_OUT )
		SetMode( IO_OUT );

	_Stream.write( (char*)&data , sizeof( data ) );
};

template <class T>	
T BinaryFile::Read()	//	generic function for reading T from the stream, can be overwritten for non-standard data types
{
	if ( GetMode() != IO_IN )
		SetMode( IO_IN );

	T Data;
	_Stream.read( (char*)&Data , sizeof( Data ) );
	
	return Data;
};

#endif