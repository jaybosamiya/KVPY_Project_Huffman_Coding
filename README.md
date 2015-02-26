Huffman Coding
==============

---------------------

Objective
---------

Huffman Coding is an entropy encoding algorithm that, given a set of alphabets and their relative frequencies, encodes each of the alphabets using variable length codes. This leads to lossless compression. The objective is to find the Huffman binary code using binary trees and an optimal ternary code using ternary trees for a set of relative frequencies for alphabets (denoted by 1, 2, 3… without loss of generality).

Solution for Binary Huffman Coding
----------------------------------

Generate the Huffman tree by starting off with a forest of trivial trees (of the alphabets) ordered by relative frequency. Repeatedly combine the two trees with least relative frequencies by making them the children of the root of a new tree which has relative frequency equal to the sum of its children. Continue the above until only one tree remains. This is the optimal Huffman tree. By traversing down to the leaves, assign different symbols to siblings (0 for left sibling, 1 for right sibling). The concatenation of the symbols in the path from root to leaf gives the optimal Huffman code for the alphabet at the leaf.

Naïve Implementation
--------------------
Store the forest in an array and traverse it to obtain the trees with least relative frequency.

+ Time taken per combine – O(N)
+ Number of combines – N
+ Total time for tree creation – O(N^2)    (because ∑(i=1 to N) O(i))

Better Implementation
---------------------

Store the forest in a priority queue and use it to obtain the trees with least relative frequency.

+ Time taken per combine – O(log_2 N)
+ Number of combines – N
+ Total time for tree creation – O(N log N)

Solution for Ternary Huffman Coding
-----------------------------------

Do the same as Binary Huffman Coding except 3 trees must be combined and the symbols assigned should be 0 to left sibling, 1 to middle sibling and 2 to right sibling.


License
-------

[MIT License](http://jay.mit-license.org/2013)
