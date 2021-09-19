#ifndef INC_2020_RAINBOW_ATTACK_INFOS_CPP
#define INC_2020_RAINBOW_ATTACK_INFOS_CPP

#include <string>

#include "infos.h"

/**
 * Prints the program infos
 * @param min_password_length a pointer to the minimum password length
 * @param max_password_length a pointer to the maximum password length
 * @param max_file_size a pointer to the maximum size of the file containing the hashes
 * @param hash_count_per_buffer a pointer to the number of hashes in a single RAM buffer
 * @param thread_count a pointer to the number of threads used
 * @param hash_file a pointer to the path to the file containing the hashes
 * @param password_file a pointer to the path to the file containing the passwords
 * @param start_hash_index a pointer to the stating index of the hashes
 * @param total_hash_count_goal a pointer to the number of hash to generate
 * @param target_hash_index a pointer to the target index of the hashes
 */
void print_infos(
	const unsigned long long int * const min_password_length,
	const unsigned long long int * const max_password_length,
	const unsigned long long int * const max_file_size,
	const unsigned long long int * const hash_count_per_buffer,
	const unsigned int long long * const thread_count,
	const std::string * const hash_file,
	const std::string * const password_file,
	const unsigned long long int * const start_hash_index,
	const unsigned long long int * const total_hash_count_goal,
	const unsigned long long int * const target_hash_index)
{
	printf("[INFO] Hashing passwords with length from %llu to %llu.\n",
		   *min_password_length, *max_password_length);
	printf("[INFO] Hashes stored in '%s' (max %lld bytes).\n",
		   hash_file->c_str(),
		   *max_file_size);
	printf("[INFO] Passwords stored in '%s' (no max size).\n",
		   password_file->c_str());
	printf("[INFO] %llu hashing threads (%lld hashes per buffer).\n",
		   *thread_count,
		   *hash_count_per_buffer);
	printf("[INFO] Staring at %llu to %llu (%llu hashes total).\n",
		   *start_hash_index,
		   *target_hash_index,
		   *total_hash_count_goal);
	printf("[INFO] %llu buffers needed = %llu buffers per thread.\n\n",
		   1 + ((*total_hash_count_goal - 1) / *hash_count_per_buffer),
		   (1 + ((*total_hash_count_goal - 1) / *hash_count_per_buffer)) / *thread_count);
}

#endif
