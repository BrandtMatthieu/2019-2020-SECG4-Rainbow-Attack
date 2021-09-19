#ifndef INC_2020_RAINBOW_ATTACK_HELP_CPP
#define INC_2020_RAINBOW_ATTACK_HELP_CPP

#include <thread>

#include "help.h"

/**
 * Prints the help of the program
 */
void print_help()
{
	printf("NAME\n");
	printf("\tgen-passwd\n\n");
	printf("SYNOPSIS\n");
	printf("\tgen-passwd [OPTIONS]\n\n");
	printf("DESCRIPTION\n");
	printf("\tgenerates a list of passwords then all the corresponding hashes, to perform a rainbow attack\n\n");
	printf("OPTIONS\n");
	printf("\t--help\n\t\tDisplays the help.\n");
	printf("\t--hashes-file\n\t\tThe location of the file where the store the hashes.\n\t\tDefault is './hashes.txt'.\n");
	printf("\t--passwords-file\n\t\tThe location of the file where the store the passwords.\n\t\tDefault is './passwords.txt'.\n");
	printf("\t--min-pass-length\n\t\tThe minimum length of passwords to generate.\n\t\tDefault is 6.\n");
	printf("\t--max-pass-length\n\t\tThe maximum length of passwords to generate.\n\t\tDefault is 8.\n");
	printf("\t--max-file-size\n\t\tThe maximum length in bytes of the file containing the hashes.\n\t\tDefault is 12000000 (12 GB).\n");
	printf("\t--threads\n\t\tThe number of threads to use.\n\t\tDefault is how many threads the system has.\n\t\tIn this case %d.\n", std::thread::hardware_concurrency());
	printf("\t--hashes-per-buffer\n\t\tThe number of hashes to write to a buffer.\n\t\tNote this is a per-thread buffer and each hash is 33 bytes long.\n\t\tDefault is 4000000 (4M hashes/buffer = 132MiB).\n");
	exit(0);
}

#endif
