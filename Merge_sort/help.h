/*
 * help.h
 *
 *  Created on: 12-Sep-2017
 *      Author: sree
 */

#ifndef HELP_H_
#define HELP_H_

void printHelp(char* program) {

	std::cout << "usage: " << program << " [-xyzXYZv]\n" << '\n'
			<< "-x, -y, -z are numbers of threads in each dimension. On my machine\n"
			<< "  the correct number is x*y*z = 32\n" << '\n'
			<< "-X, -Y, -Z are numbers of blocks to use in each dimension. Each block\n"
			<< "  holds x*y*z threads, so the total number of threads is:\n"
			<< "  x*y*z*X*Y*Z\n" << '\n' << "-v prints out extra info\n" << '\n'
			<< "? prints this message and exits\n" << '\n'
			<< "example: ./mergesort -x 8 -Y 10 -v\n" << '\n'
			<< "Reads in a list of integer numbers from stdin, and performs\n"
			<< "a bottom-up merge sort:\n" << '\n'
			<< "Input:          8 3 1 9 1 2 7 5 9 3 6 4 2 0 2 5\n"
			<< "Threads: |    t1    |    t2    |    t3    |    t4    |\n"
			<< "         | 8 3 1 9  | 1 2 7 5  | 9 3 6 4  | 2 0 2 5  |\n"
			<< "         |  38 19   |  12 57   |  39 46   |  02 25   |\n"
			<< "         |   1398   |   1257   |   3469   |   0225   |\n"
			<< "         +----------+----------+----------+----------+\n"
			<< "         |          t1         |          t2         |\n"
			<< "         |       11235789      |       02234569      |\n"
			<< "         +---------------------+---------------------+\n"
			<< "         |                     t1                    |\n"
			<< "         |      0 1 1 2 2 2 3 3 4 5 5 6 7 8 9 9      |\n"
			<< '\n' << '\n';
}


#endif /* HELP_H_ */
