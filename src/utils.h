#ifndef INC_2020_RAINBOW_ATTACK_UTILS_H
#define INC_2020_RAINBOW_ATTACK_UTILS_H

unsigned long long int start_hash_index_f(
	const unsigned long long int * base,
	const unsigned long long int & min_password_length);

unsigned long long int total_hash_count_f(
	const unsigned long long int * base,
	const unsigned long long int & min_password_length,
	const unsigned long long int & max_password_length);

unsigned long long int target_hash_index_f(
	const unsigned long long int * base,
	const unsigned long long int & min_password_length,
	const unsigned long long int & max_password_length);

unsigned long long int * make_boundaries(
	const unsigned long long int & base,
	const unsigned long long int & max_password_length);

unsigned long long int number_length_in_base(
	const unsigned long long int & number,
	const unsigned long long int * boundaries,
	const unsigned long long int & max_password_length);

unsigned char nth_digit_from_number_in_base(
	const unsigned char * alphabet,
	const unsigned long long int * boundaries,
	unsigned long long int number,
	unsigned long long int n,
	unsigned long long int base);

#endif //INC_2020_RAINBOW_ATTACK_UTILS_H
