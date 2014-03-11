/*

KVPY Summer Project 2013

Copyright 2013 Jay H. Bosamiya

*/

/*

Miniproject 1 - Huffman Coding

Suppose we have messages consisting of sequences of characters.
In each message, the characters are independent and appear with
a known probability in any given position; the probabilities
are the same for all positions. We wish to encode each character
into a sequence of 0s and 1s so that no code for a character is
the prefix of the code for any other character. This prefix
property allows us to decode a string of 0s and 1s by repeatedly
deleting prefixes of the string that are codes for characters.
Given a set of characters and their probabilities, the Huffman
algorithm finds a code with the prefix property such that the
average length of a code for a character is a minimum.

The objective is to code an implementation for Huffman coding for
binary and ternary encoding.

*/

/*

Solution
Use heaps to easily obtain the top K trees to merge.

*/

/*

Notes:
(1) STL has been used for making a dynamic array for the heap used in the implementation.
(2) I have used templates so as to make the code reusable. These can be removed to make
	different codes for binary and ternary.

*/

#include <iostream>
#include <iomanip>

#include "HuffmanCoder.h"

int main() {
	HuffmanCoder<2> hc2;
	HuffmanCoder<3> hc3;
	int N;
	float val[1000];
	std::cin >> N;
	for ( int i = 0 ; i < N ; i++ ) {
		std::cin >> val[i];
	}
	hc2.makeTree(N,val);
	hc3.makeTree(N,val);
	std::cout << "\n\n";
	std::cout << "+--------------+----------------------+----------------------+\n"
	          << "| Character    | Binary Encoding      | Ternary Encoding     |\n"
	          << "+--------------+----------------------+----------------------+\n";
	for ( int i = 0 ; i < N ; i++ ) {
		std::string s2,s3;
		hc2.getCode(i,s2);
		hc3.getCode(i,s3);

		std::cout << "| " << std::setw(12) << i << " | " << std::setw(20)
		          << s2 << " | " << std::setw(20) << s3 << " |\n";
	}
	std::cout << "+--------------+----------------------+----------------------+\n"
	          << "\n\nAverage length of encoding: \n\t" << hc2.averageLength()
			  << " for binary\n\t" << hc3.averageLength() << " for ternary\n";
	return 0;
}
