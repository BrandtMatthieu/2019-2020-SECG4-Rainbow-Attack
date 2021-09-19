#ifndef INC_2020_RAINBOW_ATTACK_HASHING_THREAD_H
#define INC_2020_RAINBOW_ATTACK_HASHING_THREAD_H

#include <mutex>
#include "synchronized_writer.hpp"

void hashing_thread(
	std::mutex * mutex,
	const unsigned char * alphabet,
	const unsigned long long int * base,
	const unsigned long long int * max_file_size,
	const unsigned long long int * current_file_size,
	unsigned long long int start,
	const unsigned long long int * hash_count_per_buffer,
	const unsigned long long int * target_hash_count,
	unsigned long long int * total_hash_count,
	const unsigned int & thread_count,
	SynchronizedWriter * synchronized_writer,
	const unsigned long long int * boundaries,
	const unsigned long long int * max_password_length);

#endif //INC_2020_RAINBOW_ATTACK_HASHING_THREAD_H
