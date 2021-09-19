#ifndef INC_2020_RAINBOW_ATTACK_SYNCHRONIZED_WRITER_HPP
#define INC_2020_RAINBOW_ATTACK_SYNCHRONIZED_WRITER_HPP

#include <fstream>
#include <mutex>
#include <string>

/**
 * @see https://stackoverflow.com/questions/33596910/c-how-to-have-multiple-threads-write-to-a-file
 */
class SynchronizedWriter
{
	private:
		std::string hash_path;
		std::ofstream hash_stream;

		std::string password_path;
		std::ofstream password_stream;

		std::mutex mutex;

		unsigned long long int * current_file_size;

	public:
		explicit SynchronizedWriter(
			const std::string & hash_path,
			const std::string & password_path,
			unsigned long long int * current_file_size);

		SynchronizedWriter(const SynchronizedWriter & synchronizedWriter) = delete;

		~SynchronizedWriter();

		SynchronizedWriter operator=(const SynchronizedWriter & other) = delete;

		void write(
			unsigned char * hash_buffer,
			const unsigned long long int & hash_buffer_size,
			unsigned char * password_buffer,
			const unsigned long long int & password_buffer_size);
};

#endif
