#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

#include "../src/utils.h"

BOOST_AUTO_TEST_SUITE(all_tests)

	const unsigned char alphabet[]{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'
		, 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};
	const unsigned long long int base{sizeof(alphabet) / sizeof(alphabet[0])};
	const unsigned long long int max_password_length{8};

	unsigned long long int * boundaries{make_boundaries(base, max_password_length)};


	BOOST_AUTO_TEST_SUITE(start_hash_index)
		BOOST_AUTO_TEST_CASE(normal_cases)
		{
			BOOST_CHECK_EQUAL(start_hash_index_f(&base, 1), 0);
			BOOST_CHECK_EQUAL(start_hash_index_f(&base, 2), base);
			BOOST_CHECK_EQUAL(start_hash_index_f(&base, 3), base + (base * base));
			BOOST_CHECK_EQUAL(start_hash_index_f(&base, 4), base + (base * base) + (base * base * base));
			BOOST_CHECK_EQUAL(start_hash_index_f(&base, 5), base + (base * base) + (base * base * base) + (base * base * base * base));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(total_hash_count)
		BOOST_AUTO_TEST_CASE(min_length_1)
		{
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 1, 1), base);
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 1, 2), base + (base * base));
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 1, 3), base + (base * base) + (base * base * base));
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 1, 4), base + (base * base) + (base * base * base) + (base * base * base * base));
		}

		BOOST_AUTO_TEST_CASE(min_length_2)
		{
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 2, 2), (base * base));
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 2, 3), (base * base) + (base * base * base));
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 2, 4), (base * base) + (base * base * base) + (base * base * base * base));
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 2, 5), (base * base) + (base * base * base) + (base * base * base * base) + (base * base * base * base * base));
		}

		BOOST_AUTO_TEST_CASE(min_length_3)
		{
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 3, 3), (base * base * base));
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 3, 4), (base * base * base) + (base * base * base * base));
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 3, 5), (base * base * base) + (base * base * base * base) + (base * base * base * base * base));
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 3, 6), (base * base * base) + (base * base * base * base) + (base * base * base * base * base) + (base * base * base * base * base * base));
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 3, 7), (base * base * base) + (base * base * base * base) + (base * base * base * base * base) + (base * base * base * base * base * base) + (base * base * base * base * base * base * base));
			BOOST_CHECK_EQUAL(total_hash_count_f(&base, 3, 8), (base * base * base) + (base * base * base * base) + (base * base * base * base * base) + (base * base * base * base * base * base) + (base * base * base * base * base * base * base) + (base * base * base * base * base * base * base * base));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(target_hash_index)
		BOOST_AUTO_TEST_CASE(min_length_1)
		{
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 1, 1), base - 1);
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 1, 2), base + (base * base) - 1);
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 1, 3), base + (base * base) + (base * base * base) - 1);
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 1, 4), base + (base * base) + (base * base * base) + (base * base * base * base) - 1);
		}

		BOOST_AUTO_TEST_CASE(min_length_2)
		{
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 2, 2), base + (base * base) - 1);
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 2, 3), base + (base * base) + (base * base * base) - 1);
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 2, 4), base + (base * base) + (base * base * base) + (base * base * base * base) - 1);
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 2, 5), base + (base * base) + (base * base * base) + (base * base * base * base) + (base * base * base * base * base) - 1);
		}

		BOOST_AUTO_TEST_CASE(min_length_3)
		{
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 3, 3), base + (base * base) + (base * base * base) - 1);
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 3, 4), base + (base * base) + (base * base * base) + (base * base * base * base) - 1);
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 3, 5), base + (base * base) + (base * base * base) + (base * base * base * base) + (base * base * base * base * base) - 1);
			BOOST_CHECK_EQUAL(target_hash_index_f(&base, 3, 6), base + (base * base) + (base * base * base) + (base * base * base * base) + (base * base * base * base * base) + (base * base * base * base * base * base) - 1);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(boundaries_test)
		BOOST_AUTO_TEST_CASE(boundaries_manual_test)
		{
			unsigned long long int * b{make_boundaries(base, 5)};
			BOOST_CHECK_EQUAL(b[0], 0);
			BOOST_CHECK_EQUAL(b[1], base);
			BOOST_CHECK_EQUAL(b[2], base + base * base);
			BOOST_CHECK_EQUAL(b[3], base + base * base + base * base * base);
			BOOST_CHECK_EQUAL(b[4], base + base * base + base * base * base + base * base * base * base);
			delete [] b;
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(length_test)
		BOOST_AUTO_TEST_CASE(length_test)
		{
			BOOST_CHECK_EQUAL(number_length_in_base(0, boundaries, max_password_length), 1);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + 1, boundaries, max_password_length), 1);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base - 1, boundaries, max_password_length), 1);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base, boundaries, max_password_length), 2);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base + 1, boundaries, max_password_length), 2);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base + (base * base) - 1, boundaries, max_password_length), 2);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base + (base * base), boundaries, max_password_length), 3);
			BOOST_CHECK_EQUAL(number_length_in_base(3906, boundaries, max_password_length), 3);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base + (base * base) + 1, boundaries, max_password_length), 3);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base + (base * base) + (base * base * base) - 1, boundaries, max_password_length), 3);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base + (base * base) + (base * base * base), boundaries, max_password_length), 4);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base + (base * base) + (base * base * base) + 1, boundaries, max_password_length), 4);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base + (base * base) + (base * base * base) + (base * base * base * base) - 1, boundaries, max_password_length), 4);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base + (base * base) + (base * base * base) + (base * base * base * base), boundaries, max_password_length), 5);
			BOOST_CHECK_EQUAL(number_length_in_base(0 + base + (base * base) + (base * base * base) + (base * base * base * base) + 1, boundaries, max_password_length), 5);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(digit_test)
		BOOST_AUTO_TEST_CASE(length_1)
		{
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, 0, 0, base), '0');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, 1, 0, base), '1');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, 9, 0, base), '9');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, 10, 0, base), 'a');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base - 1, 0, base), 'Z');
		}

		BOOST_AUTO_TEST_CASE(length_2)
		{

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + 0, 0, base), '0');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + 0, 1, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + 1, 0, base), '1');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + 1, 1, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + 9, 0, base), '9');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + 9, 1, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + 10, 0, base), 'a');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + 10, 1, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base - 1, 0, base), 'Z');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base - 1, 1, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base + 0, 0, base), '0');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base + 0, 1, base), '1');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base + 1, 0, base), '1');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base + 1, 1, base), '1');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base + 9, 0, base), '9');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base + 9, 1, base), '1');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base + 10, 0, base), 'a');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base + 10, 1, base), '1');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base + base - 1, 0, base), 'Z');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + base + base - 1, 1, base), '1');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) - 1, 0, base), 'Z');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) - 1, 1, base), 'Z');
		}

		BOOST_AUTO_TEST_CASE(length_3)
		{

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 0, 0, base), '0');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 0, 1, base), '0');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 0, 2, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 1, 0, base), '1');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 1, 1, base), '0');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 1, 2, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 9, 0, base), '9');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 9, 1, base), '0');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 9, 2, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 10, 0, base), 'a');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 10, 1, base), '0');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + 10, 2, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base - 1, 0, base), 'Z');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base - 1, 1, base), '0');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base - 1, 2, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 0, 0, base), '0');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 0, 1, base), '1');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 0, 2, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 1, 0, base), '1');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 1, 1, base), '1');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 1, 2, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 9, 0, base), '9');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 9, 1, base), '1');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 9, 2, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 10, 0, base), 'a');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 10, 1, base), '1');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + 10, 2, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + base - 1, 0, base), 'Z');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + base - 1, 1, base), '1');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + base + base - 1, 2, base), '0');

			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + (base * base * base) - 1, 0, base), 'Z');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + (base * base * base) - 1, 1, base), 'Z');
			BOOST_CHECK_EQUAL(nth_digit_from_number_in_base(alphabet, boundaries, base + (base * base) + (base * base * base) - 1, 2, base), 'Z');
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
