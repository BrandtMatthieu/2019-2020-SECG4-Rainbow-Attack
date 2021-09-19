#ifndef INC_2020_RAINBOW_ATTACK_HASHING_THREAD_CPP
#define INC_2020_RAINBOW_ATTACK_HASHING_THREAD_CPP

#include <thread>
#include <algorithm>
#include <cstring>

#include "hashing_thread.h"
#include "config.h"
#include "utils.h"
#include "sha256.hpp"

/**
 * A hashing thread hashing passwords
 *
 * @param mutex a pointer to a mutex used for managing multithreading
 * @param alphabet a pointer to a custom alphabet to use
 * @param base a pointer to the base the alphabet is in
 * @param max_file_size a pointer to the max size of the file containing hashes
 * @param current_file_size a pointer to the current size of the file containing hashes
 * @param start the start index of this thread
 * @param hash_count_per_buffer a pointer to the number of hashes stored in a single ram buffer
 * @param target_hash_count a pointer to the target number of hashes
 * @param total_hash_count a pointer to the number of hashes done
 * @param thread_count a reference to the number of threads running
 * @param synchronized_writer a pointer to the file writer
 * @param boundaries a pointer to an array with the boundaries of the password lengths
 * @param max_password_length a pointer the maximum length of the passwords
 */
void hashing_thread(
	std::mutex * const mutex,
	const unsigned char * const alphabet,
	const unsigned long long int * const base,
	const unsigned long long int * const max_file_size,
	const unsigned long long int * const current_file_size,
	unsigned long long int start,
	const unsigned long long int * const hash_count_per_buffer,
	const unsigned long long int * const target_hash_count,
	unsigned long long int * const total_hash_count,
	const unsigned int & thread_count,
	SynchronizedWriter * const synchronized_writer,
	const unsigned long long int * const boundaries,
	const unsigned long long int * const max_password_length)
{
	mutex->lock();
	printf("[THREAD] Starting thread %d.\n", std::this_thread::get_id());
	mutex->unlock();

	constexpr unsigned long long int hash_length{HASH_RESULT_SIZE + LINE_FEED_CHAR_SIZE};

	while(start < *target_hash_count)
	{
		const unsigned long long int hash_count{std::min({*hash_count_per_buffer, // full buffer
															 *target_hash_count + 1 - start, // only remaining hashes (< full buffer)
															 (*max_file_size - *current_file_size) / hash_length})}; // not to exceed the file size

		const unsigned long long int hash_buffer_size{hash_length * hash_count};

		auto * const hash_buffer = new(std::nothrow) unsigned char[hash_buffer_size];

		auto * const length_buffer = new(std::nothrow) unsigned long long int[hash_count];
		if(hash_buffer == nullptr || length_buffer == nullptr)
		{
			throw std::runtime_error("Could not allocate memory. There might not be enough memory available. Try reducing the buffer size and try again.");
		}

		unsigned long long int password_buffer_size{0};
		for(unsigned long long int i{0}; i < hash_count; ++i) // add the size of every password + line break to know the total size of the buffer
		{
			const unsigned long long int length{number_length_in_base(start + i, boundaries, *max_password_length)};
			length_buffer[i] = length;
			password_buffer_size += length + 1; // last + 1 is for '\n'
		}

		auto * const password_buffer = new(std::nothrow) unsigned char[password_buffer_size];
		if(password_buffer == nullptr)
		{
			throw std::runtime_error("Could not allocate memory. There might not be enough memory available. Try reducing the buffer size and try again.");
		}

		for(unsigned long long int i{0}, hash_buffer_displacement{0}, password_buffer_displacement{0};
			i < hash_count;
			++i) // for all passwords in the current buffer
		{
			const unsigned long long int password_size{length_buffer[i]};

			for(unsigned long long int nth_digit{0}; nth_digit < password_size; ++nth_digit) // for all characters of the current password
			{

				unsigned char * const p{password_buffer + password_buffer_displacement + (password_size - nth_digit - 1)};
				const unsigned char c{nth_digit_from_number_in_base(alphabet, boundaries, start + i, nth_digit, *base)};
				*p = c;

				//password_buffer[password_buffer_displacement + ((password_size) - 1 - nth_digit)] = nth_digit_from_number_in_base(alphabet, boundaries,(start + i), nth_digit, *base);
			}
			password_buffer[password_buffer_displacement + password_size] = '\0';

			const std::string hash{sha256(std::string{reinterpret_cast<char *>(password_buffer + password_buffer_displacement)})};
			const unsigned long long int hash_size{HASH_RESULT_SIZE};

			password_buffer[password_buffer_displacement + password_size] = '\n';

			memcpy(hash_buffer + hash_buffer_displacement, hash.c_str(), hash_size);
			hash_buffer[hash_buffer_displacement + hash_size] = '\n';

			hash_buffer_displacement += hash_size + 1;
			password_buffer_displacement += password_size + 1;
		}

		synchronized_writer->write(hash_buffer, hash_buffer_size, password_buffer, password_buffer_size);

		mutex->lock();

		*total_hash_count += hash_count;
		start += *hash_count_per_buffer * thread_count;

		printf("[THREAD] Thread %d hashed another %llu hashes. (%f%% completed)\n",
			   std::this_thread::get_id(),
			   hash_count,
			   std::min({static_cast<double>(*total_hash_count) * 100.0 / static_cast<double>(*target_hash_count), 100.0}));

		mutex->unlock();

		delete[] hash_buffer;
		delete[] length_buffer;
		delete[] password_buffer;
	}

	mutex->lock();
	printf("[THREAD] Thread %d just finished.\n", std::this_thread::get_id());
	mutex->unlock();

}

#endif
