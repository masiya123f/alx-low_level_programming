#include "main.h"
/**
 * read_textfile - reads a text file and print it
 *
 * @filename: const char type pointer to the file
 *
 * @letters: size_t type
 *
 * Return: 0
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int ptr;
	ssize_t fpRead, fpWrite, fpClose;
	char *buffer;

	if (filename == NULL)
		return (0);

	buffer = malloc(sizeof(char) * letters);

	if (buffer == NULL)
		return (-1);

	ptr = open(filename, O_RDONLY);

	if (ptr == -1)
		return (-1);

	fpRead = read(ptr, buffer, letters);

	if (fpRead == -1)
		return (-1);

	fpWrite = write(STDOUT_FILENO, buffer, fpRead);

	if (fpWrite == -1)
		return (-1);
	fpClose = close(ptr);

	if (fpClose == -1)
		return (-1);

	return (fpRead);
}
