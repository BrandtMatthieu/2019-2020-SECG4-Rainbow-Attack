#ifndef INC_2020_RAINBOW_ATTACK_UTILS_CPP
#define INC_2020_RAINBOW_ATTACK_UTILS_CPP

#include <cmath>
#include <new>
#include <stdexcept>

#include "utils.h"

/**
 * Returns the start index of the generated passwords.
 * @param base a pointer to the base the passwords are in.
 * @param min_password_length a pointer to the minimum size of the password.
 * @return the start index of the generated passwords.
 */
unsigned long long int start_hash_index_f(
	const unsigned long long int * const base,
	const unsigned long long int & min_password_length)
{
	unsigned long long int start{0};

	for(unsigned long long int i{1}; i < min_password_length; ++i)
	{
		start += static_cast<unsigned long long int>(pow(*base, i));
	}

	return start;
}

/**
 * Returns how many passwords will be generated.
 * @param base a pointer to the base the passwords are in.
 * @param min_password_length the minimum size of the password.
 * @param max_password_length the maximum size of the password.
 * @return how many passwords will be generated.
 */
unsigned long long int total_hash_count_f(
	const unsigned long long int * const base,
	const unsigned long long int & min_password_length,
	const unsigned long long int & max_password_length)
{
	unsigned long long int target_hash_count{0};
	for(unsigned long long int i{min_password_length}; i <= max_password_length; ++i)
	{
		target_hash_count += static_cast<unsigned long long int>(pow(*base, i));
	}
	return target_hash_count;
}

/**
 * Returns the end index of the generated passwords.
 * @param base a pointer to the base the passwords are in.
 * @param min_password_length the minimum size of the password.
 * @param max_password_length the maximum size of the password.
 * @return the end index of the generated passwords.
 */
unsigned long long int target_hash_index_f(
	const unsigned long long int * const base,
	const unsigned long long int & min_password_length,
	const unsigned long long int & max_password_length)
{
	return start_hash_index_f(base, min_password_length) - 1 + total_hash_count_f(base, min_password_length, max_password_length);
}

/**
 * Returns a pointer to an array with the boundaries/index/password length
 * @param base the base the array is in
 * @param max_password_length the max length of the password
 * @return a pointer to an array with the boundaries to
 */
unsigned long long int * make_boundaries(
	const unsigned long long int & base,
	const unsigned long long int & max_password_length)
{
	auto * boundaries = new(std::nothrow) unsigned long long int[max_password_length];
	if(boundaries == nullptr)
	{
		throw std::runtime_error("Could not  allocate boundaries array");
	}

	unsigned long long int b{0};
	for(unsigned long long int i = 0; i <= max_password_length; ++i)
	{
		b += static_cast<unsigned long long int>(pow(base, i));
		boundaries[i] = b - 1;
	}
	return boundaries;
}

/**
 * Returns the number of digits of a number in a certain base
 *
 * i.e.
 * number(10) = 9, base = 2
 * number(2) = 1001
 * longueur(1001) = 4
 *
 * @see https://www.geeksforgeeks.org/given-number-n-decimal-base-find-number-digits-base-base-b/
 * @param number the input number in base 10
 * @param boundaries a pointer to the array with the boundaries
 * @param max_password_length the maximum length of the passwords
 * @return the number of digits of a number in a certain base
 */
unsigned long long int number_length_in_base(
	const unsigned long long int & number,
	const unsigned long long int * const boundaries,
	const unsigned long long int & max_password_length)
{
	unsigned long long int i = 1;
	while(number >= boundaries[i] && i < max_password_length)
	{
		i++;
	}
	return i;
}

/**
 * Returns the nth digit from the right of a number in a certain base
 *
 * i.e.
 * number(10) = 100, base = 4, n = 3
 * number(4) = 1210
 * nth(1210) = 2
 *
 * https://www.geeksforgeeks.org/find-the-nth-digit-from-right-in-base-b-of-the-given-number-in-decimal-base/?ref=rp
 * @param alphabet a custom alphabet to use
 * @param number the input number in base 10
 * @param n the nth digit to get (0 based)
 * @param base the custom base
 * @return the nth digit from the right of a number in a certain base
 */
unsigned char nth_digit_from_number_in_base(
	const unsigned char * const alphabet,
	const unsigned long long int * const boundaries,
	unsigned long long int number,
	unsigned long long int n,
	unsigned long long int base)
{
	unsigned long long int i{0};
	while(boundaries[i] <= number)
	{
		++i;
	}
	number = number - boundaries[i - 1];

	for(unsigned long long int j{0}; j < n; ++j)
	{
		number = number / base;
	}

	return alphabet[number % base];
}

#endif
