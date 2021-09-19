#ifndef INC_2020_RAINBOW_ATTACK_SYNCHRONIZED_WRITER_CPP
#define INC_2020_RAINBOW_ATTACK_SYNCHRONIZED_WRITER_CPP

#include <fstream>
#include <string>
#include <thread>
#include <iostream>

#include "synchronized_writer.hpp"

/**
 * Creates a new SynchronizedWriter object
 * @param hash_path a path to a file to write the hashes to
 * @param password_path a path to a file to write the passwords to
 * @param current_file_size a pointer to the current size of the file containing hashes
 */
SynchronizedWriter::SynchronizedWriter(
	const std::string & hash_path,
	const std::string & password_path,
	unsigned long long int * const current_file_size)
	: hash_path{hash_path}
	, hash_stream{this->hash_path, std::ofstream::trunc}
	, password_path{password_path}
	, password_stream{this->password_path, std::ofstream::trunc}
	, mutex{}
	, current_file_size{current_file_size}
{
	if((!hash_stream.is_open()) || (!password_stream.is_open()))
	{
		throw std::runtime_error("Could not open output file.");
	}
}

/**
 * Deletes the SynchronizedWriter object
 */
SynchronizedWriter::~SynchronizedWriter()
{
	this->hash_stream.close();
	this->password_stream.close();
}

/**
 * Writes to the files
 * @param hash_buffer a pointer to a buffer containing the hashes of the passwords
 * @param hash_buffer_size the size of the buffer with the hashes
 * @param password_buffer a pointer to a buffer containing the passwords
 * @param password_buffer_size the size of the buffer with the passwords
 */
void SynchronizedWriter::write(
	unsigned char * const hash_buffer,
	const unsigned long long int & hash_buffer_size,
	unsigned char * const password_buffer,
	const unsigned long long int & password_buffer_size)
{
	this->mutex.lock();

	if(this->hash_stream.is_open())
	{
		this->hash_stream.write(reinterpret_cast<char *>(hash_buffer), static_cast<long int>(hash_buffer_size));
	}
	else
	{
		throw std::runtime_error("Could not write into hash file.");
	}

	if(this->password_stream.is_open())
	{
		this->password_stream.write(reinterpret_cast<char *>(password_buffer), static_cast<long int>(password_buffer_size));
	}
	else
	{
		throw std::runtime_error("Could not write into password file.");
	}

	*(this->current_file_size) += hash_buffer_size;

	this->mutex.unlock();
}

#endif
