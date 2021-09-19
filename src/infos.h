#ifndef INC_2020_RAINBOW_ATTACK_INFOS_H
#define INC_2020_RAINBOW_ATTACK_INFOS_H

void print_infos(
	const unsigned long long int * min_password_length,
	const unsigned long long int * max_password_length,
	const unsigned long long int * max_file_size,
	const unsigned long long int * hash_count_per_buffer,
	const unsigned int long long * thread_count,
	const std::string * hash_file,
	const std::string * password_file,
	const unsigned long long int * start_hash_index,
	const unsigned long long int * total_hash_count_goal,
	const unsigned long long int * target_hash_index);

#endif //INC_2020_RAINBOW_ATTACK_INFOS_H
