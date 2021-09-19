#include <cstring>
#include <thread>
#include <vector>
#include <mutex>

#include "synchronized_writer.hpp"
#include "config.h"
#include "help.h"
#include "utils.h"
#include "infos.h"
#include "hashing_thread.h"

std::mutex mutex;

int main(int argc, char ** argv)
{
	const unsigned char alphabet[]{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'
		, 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};
	const unsigned long long int base{sizeof(alphabet) / sizeof(*alphabet)};

	unsigned long long int min_password_length{MIN_PASSWORD_LENGTH};
	unsigned long long int max_password_length{MAX_PASSWORD_LENGTH};

	unsigned long long int max_file_size{MAX_FILE_SIZE};
	unsigned long long int current_file_size{0};

	unsigned long long int hash_count_per_buffer{HASH_COUNT_PER_BUFFER};

	unsigned int long long thread_count{std::thread::hardware_concurrency()};
	if(thread_count <= 0)
	{
		printf("[ERROR] Could not determine how many threads this machine has. Using 4.");
		thread_count = 4;
	}

	std::string hashes_file{"./hashes.txt"};
	std::string passwords_file{"./passwords.txt"};

	if(argc == 1)
	{
		print_help();
	}
	for(int i = 1; i < argc; ++i)
	{
		const std::string delimitor{"="};
		const char * param_name{strtok(argv[i], delimitor.c_str())};
		const char * param_value{strtok(nullptr, delimitor.c_str())};

		if(param_value == nullptr)
		{
			if(strcmp(param_name, "--help") == 0)
			{
				print_help();
				continue;
			}

			printf("Parameter '%s' doesn't have an associated value. Ignoring it.\n", param_name);
			continue;
		}

		if(strcmp(param_name, "--hashes-file") == 0)
		{
			hashes_file = param_value;
			continue;
		}
		if(strcmp(param_name, "--passwords-file") == 0)
		{
			passwords_file = param_value;
			continue;
		}

		unsigned int value;
		try
		{
			value = static_cast<unsigned int>(std::stol(param_value));
			if(value <= 0)
			{
				throw std::runtime_error("Parameter value must be a number greater than 0.");
			}
		}
		catch(int)
		{
			throw std::runtime_error("Parameter value must be a number greater than 0.");
		}

		if(strcmp(param_name, "--min-pass-length") == 0)
		{
			min_password_length = value;
			if(min_password_length > max_password_length)
			{
				max_password_length = min_password_length;
			}
			continue;
		}
		if(strcmp(param_name, "--max-pass-length") == 0)
		{
			max_password_length = value;
			if(max_password_length < min_password_length)
			{
				min_password_length = max_password_length;
			}
			continue;
		}
		if(strcmp(param_name, "--max-file-size") == 0)
		{
			max_file_size = value;
			continue;
		}
		if(strcmp(param_name, "--threads") == 0)
		{
			thread_count = value;
			continue;
		}
		if(strcmp(param_name, "--hashes-per-buffer") == 0)
		{
			hash_count_per_buffer = value;
			continue;
		}
		printf("Unknown parameter '%s'. Ignoring it.\n", param_name);
	}

	const unsigned long long int * const boundaries{make_boundaries(base, max_password_length)};

	SynchronizedWriter * const synchronized_writer{new SynchronizedWriter{"./hashes.txt", "./passwords.txt", &current_file_size}};

	const unsigned long long int start_hash_index{start_hash_index_f(&base, min_password_length)};

	const unsigned long long int total_hash_count_goal{total_hash_count_f(&base, min_password_length, max_password_length)};

	unsigned long long int total_hash_count{0};

	const unsigned long long int target_hash_index{target_hash_index_f(&base, min_password_length, max_password_length)};

	print_infos(
		&min_password_length,
		&max_password_length,
		&max_file_size,
		&hash_count_per_buffer,
		&thread_count,
		&hashes_file,
		&passwords_file,
		&start_hash_index,
		&total_hash_count_goal,
		&target_hash_index);

	std::vector<std::thread *> threads{};

	const std::chrono::time_point<std::chrono::system_clock> start_timestamp{std::chrono::system_clock::now()};

	for(unsigned int i{0}; i < thread_count; ++i)
	{
		threads.push_back(new std::thread(
			hashing_thread,
			&mutex,
			alphabet,
			&base,
			&max_file_size,
			&current_file_size,
			(start_hash_index + (i * hash_count_per_buffer)),
			&hash_count_per_buffer,
			&target_hash_index,
			&total_hash_count,
			thread_count,
			synchronized_writer,
			boundaries,
			&max_password_length));
	}
	for(auto const & thread_pointer : threads)
	{
		thread_pointer->join();
	}

	const std::chrono::time_point<std::chrono::system_clock> end_timestamp{std::chrono::system_clock::now()};

	const std::chrono::duration<double> delta_time{end_timestamp - start_timestamp};

	printf("\n[INFO] Generated %lld hashes in %f sec. (%f hashes / sec)\n",
		   total_hash_count,
		   delta_time.count(),
		   static_cast<double>(total_hash_count) / delta_time.count());

	delete[] boundaries;
	delete synchronized_writer;
	for(auto const & thread_pointer : threads)
	{
		delete thread_pointer;
	}
	threads.clear();

	return 0;

}
