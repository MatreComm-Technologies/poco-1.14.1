//
// FileStream_WIN32.h
//
// Library: Foundation
// Package: Streams
// Module:  FileStream
//
// Definition of the FileStreamBuf, FileInputStream and FileOutputStream classes.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_FileStream_WIN32_INCLUDED
#define Foundation_FileStream_WIN32_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/BufferedBidirectionalStreamBuf.h"
#include "Poco/UnWindows.h"


namespace Poco {

class Foundation_API FileStreamBuf: public BufferedBidirectionalStreamBuf
	/// This stream buffer handles Fileio
{
public:
	using NativeHandle = HANDLE;
	
	FileStreamBuf();
		/// Creates a FileStreamBuf.

	~FileStreamBuf();
		/// Destroys the FileStream.

	void open(const std::string& path, std::ios::openmode mode);
		/// Opens the given file in the given mode.

	void openHandle(NativeHandle handle, std::ios::openmode mode);
		/// Take ownership of the given HANDLE.

	bool close();
		/// Closes the File stream buffer. Returns true if successful,
		/// false otherwise.

	bool resizeBuffer(std::streamsize bufferSize) override;
		/// Resizes internal buffer. Minimum size is BUFFER_SIZE.
		/// Minimum is used when requested size is smaller.
		/// Buffer can be resized only when the file is not open.
		/// Returns true if resize succeeded.

	std::streampos seekoff(std::streamoff off, std::ios::seekdir dir, std::ios::openmode mode = std::ios::in | std::ios::out) override;
		/// change position by offset, according to way and mode

	std::streampos seekpos(std::streampos pos, std::ios::openmode mode = std::ios::in | std::ios::out) override;
		/// change to specified position, according to mode

	void flushToDisk();
		/// Forces buffered data to be written to the disk

	NativeHandle nativeHandle() const;
		/// Returns native file descriptor handle

	Poco::UInt64 size() const;
		/// Returns file size

protected:
	enum
	{
		BUFFER_SIZE = 4096
	};

	int readFromDevice(char* buffer, std::streamsize length) override;
	int writeToDevice(const char* buffer, std::streamsize length) override;

private:
	std::string _path;
	NativeHandle _handle;
	UInt64 _pos {0};
};


} // namespace Poco


#endif // Foundation_FileStream_WIN32_INCLUDED