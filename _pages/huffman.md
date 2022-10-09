---
title: "Huffman Compression Algorithm"
permalink: /projects/huffman/
layout: single
classes: wide
excerpt: "An incredible compression algorithm"
header:
 overlay_image: /images/projects/huff.png
 caption: "Huffman Coding"
date: 2022-09-11
comments: true
sidebar:
 nav: "docs2"
 
feature_row_left1:
 - url: "https://github.com/Simonlee711/CSE-13S/tree/master/asgn6"
   btn_label: "Code"
   btn_class: "btn--primary"
---
 
 
# Keywords:
 
Data Compression, David Huffman, Information theory, entropy, Huffman coding
 
---
 
# History
 
When David Huffman was a graduate student in a class at MIT, the professor gave the class an unsolved problem: **How to construct an optimal static encoding of information**. The young Huffman came back a few days later with his solution, and that solution changed the world. Data compression is now used in all aspects of communication. David Huffman joined the faculty of MIT in 1953, and in 1967 he joined the faculty of University of California, Santa Cruz as one of its earliest members and helped to found its Computer Science Department, where he served as chairman from 1970 to 1973. He retired in 1994, and passed away in 1999.
 
---
 
# Algorithm
**The Huffman Compression algorithm** or **huffman coding** is a lossless algorithm. The idea is to assign variable-length bit codes to input characters; lengths of the assigned codes are based on the frequencies of corresponding characters. The most frequent character gets the smallest code and the least frequent character gets the largest code. And since we are working with bits (1 byte of memory is 8 bits), it results in a smaller data size. But let's look further into how the underlying mathematics works.
 
The key idea is called **entropy**, originally defined by Claude Shannon in 1948. Entropy is a measure of the amount of information in a set of symbols. If we define \\( I(x) = log_{2} Pr[ x] \\) to be the information content of a symbol, then the entropy of the set  X = x1,x2,..., xn is
 
\\[ H( \chi ) = \sum_{i=1}^{n} Pr[x_{i} I(x_{i})] = \sum_{i=1}^{n} Pr[ x_{i}] \log_{2} Pr[ x_i]\\]
 
We can see that the optimal static encoding will assign the least number of bits to the most common symbol, and the greatest number of bits to the least common symbol.
 
The variable-length codes assigned to input characters are Prefix Codes, meaning the codes (bit sequences) are assigned in such a way that the code assigned to one character is not the prefix of code assigned to any other character and is therefore unique. This is how Huffman Coding makes sure that there is no ambiguity during the decoding from the generated bitstream. So in totality the algorithm is to encode all unique characters to form a huffman tree, and decode the information using the codes established during the encoding phase.
 
---
 
## Encode
 
The first step in building the huffman tree is to create leaf nodes for all unique characters. We then take a data structure called the **min heap** and build the tree. The min heap acts as a priority queue where the leaf nodes are all sorted by ascending order. This is because we want to take the two least frequency leaf nodes and combine them to build out the tree. We repeat these steps of combining lead nodes of the two smallest frequencies until we have only one node remaining. Our tree is complete. Next in order to establish the codes, we run a post traversal order tree traversal where if we go left we encode a 0 and if we go right we encode a 1. Once we hit a terminal node we know exactly what the code will be. We save these codes for the decoder and we can now feed the input characters into the tree to compress our data. We are left with strictly zeros and ones.
 
{% highlight C linenos %}
 
#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"
 
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
 
#define OPTIONS "hi:o:v"
 
uint64_t bytes_read;
uint64_t bytes_written;
static uint8_t bytes = 0;
static uint64_t hist[ALPHABET];
 
void LIpt(Node *root, Stack **s) { //Leaf and Internal Post Traversal
   if (root == NULL) { //->left == NULL && root->right == NULL){
       return;
   }
   LIpt(root->left, s);
   LIpt(root->right, s);
   if (root->left == NULL && root->right == NULL) {
       Node *L = node_create('L', 0);
       stack_push(*s, L);
       stack_push(*s, root);
   }
   if (root->left != NULL && root->right != NULL) {
       Node *I = node_create('I', 0);
       stack_push(*s, I);
   }
}
 
int main(int argc, char **argv) {
   int opt = 0;
   int in = STDIN_FILENO, out = STDOUT_FILENO;
   int verbose = 0;
 
   //make histogram
   //SOURCE: Professor Long's example from class to construct histogram
   int length = 0;
   uint8_t buffer[BLOCK];
   while ((length = read(in, buffer, sizeof(BLOCK)) > 0)) {
       bytes += length;
       for (int i = 0; i < length + 1; i++) {
           hist[buffer[i]] += 1;
       }
   }
   hist[0] += 1;
   hist[255] += 1;
 
   //build tree
   Node *huffman_tree = build_tree(hist);
 
   //construct codes
   Code table[ALPHABET];
   for (int i = 0; i < ALPHABET; i++) {
       table[i] = code_init();
   }
   build_codes(huffman_tree, table);
 
   //counter for leaf's
   int leaf_counter = 0;
   for (int k = 0; k < ALPHABET; k++) {
       if (hist[k] != 0) {
           leaf_counter += 1;
       }
   }
 
   //header
   struct stat statbuf;
   fstat(in, &statbuf);
   fchmod(out, statbuf.st_mode);
 
   Header h;
   h.magic = MAGIC; //change to -> if dot notation doesn't work
   h.permissions = statbuf.st_mode;
   h.tree_size = ((3 * leaf_counter) - 1);
   h.file_size = statbuf.st_size;
   write_bytes(out, (uint8_t *) &h, sizeof(h));
 
   //build the Leaf and internal post traversal array
   Stack *s = stack_create(h.tree_size);
   uint8_t arr[h.tree_size];
   LIpt(huffman_tree, &s);
   Node *temp;
   for (int i = h.tree_size - 1; i >= 0; i--) {
       stack_pop(s, &temp);
       arr[i] = temp->symbol;
       node_delete(&temp);
   }
   write_bytes(out, arr, sizeof(arr));
 
   //write out to outfile
   lseek(in, 0, SEEK_SET);
   uint8_t bit;
   uint64_t byte_counter = 0;
   uint64_t bit_counter = 0;
   for (uint64_t sym = 0; sym < h.file_size; sym++) {
       read_bytes(in, &bit, 1);
       if (table[bit].top != 0) {
           write_code(out, &table[bit]);
       }
       bit_counter += code_size(&table[bit]);
   }
   flush_codes(out);
 
   //calculating bytes compressed
   if (bit_counter <= 8) {
       byte_counter = 1;
   } else {
       if ((bit_counter % 8) == 0) {
           byte_counter = bit_counter / 8;
       } else {
           byte_counter = (bit_counter / 8) + 1;
       }
   }
 
   //verbose printing
   if (verbose) {
       printf("uncompressed file size: %lu\n", h.file_size);
       double total = sizeof(h) + sizeof(arr) + byte_counter;
       printf("compressed file size: %0.0f\n", total);
       double all_bytes = h.file_size;
       printf("Space saving: %0.2f%%\n", (1.0 - (total / all_bytes)) * 100.0);
   }
 
   //close files
   close(in);
   close(out);
}
 
{% endhighlight %}
 
---
 
## Decode
 
In order to decode we first must feed the huffman tree as well as the list of codes for every unique character. We then take our file containing binary files and walk the tree. The tree walking process takes in a single bit at a time and it is basically an instructions manual on whether to go left or right in the tree. If the bit is a 0 we go left and if the bit is a 1 we go right until we hit a terminal node. Once we hit the terminal node we can translate the sequence of bits to be the character saved in the codes table. We repeat this process until we are left with the original data. Congratulations you have performed the Huffman Compression Algorithm.
 
{% highlight C linenos %}
 
#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
 
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
 
#define OPTIONS "hi:o:v"
 
uint64_t bytes_read;
uint64_t bytes_written;
 
int main(int argc, char **argv) {
   int opt = 0;
   int in = STDIN_FILENO, out = STDOUT_FILENO;
   int verbose = 0;
 
   //read in header
   Header h = { 0 };
   read_bytes(in, (uint8_t *) &h, sizeof(Header));
 
   //header check
   if (h.magic != 0xDEADBEEF) {
       fprintf(stderr, "*** Invalid Magic Number ***\n");
       return 0;
   }
 
   //file permission
   struct stat statbuf;
   fstat(in, &statbuf);
   fchmod(out, statbuf.st_mode);
 
   //rebuild tree;
   uint8_t dump[h.tree_size];
   read(in, dump, h.tree_size);
   Node *root = rebuild_tree(h.tree_size, dump);
 
   //decompress the message
   uint8_t bit; // = 0;
   uint64_t pos = 0;
   Node *curr = root;
   uint32_t bits = 0;
   double byte_counter;
   while ((bits = read_bit(in, &bit)) > 0) {
       if (pos == h.file_size + 1) {
           break;
       }
       if (bit == 0) {
           if (curr->left == NULL) {
               write_bytes(out, &(curr->symbol), 1);
               curr = root;
           } else {
               curr = curr->left;
           }
       }
       if (bit == 1) {
           if (curr->right == NULL) {
               write_bytes(out, &(curr->symbol), 1);
               curr = root;
           } else {
               curr = curr->right;
           }
       }
       pos += 1;
   }
   //calculating bytes to decompress
   if ((pos) <= 8) {
       byte_counter = 1;
   } else {
       if (((pos) % 8) == 0) {
           byte_counter = (pos) / 8;
       } else {
           byte_counter = ((pos) / 8) + 1;
       }
   }
 
   //verbose printing
   if (verbose) {
       printf("compressed file size: %0.0f\n", byte_counter);
       printf("uncompressed file size %lu: \n", h.file_size);
       double all_bytes = h.file_size;
       printf("Space saving: %0.2f%%\n", (1.0 - (byte_counter / all_bytes)) * 100);
   }
 
   close(in);
   close(out);
}
 
{% endhighlight %}
 
---
 
# Example
 
Let us insert the Delta Corona Virus Genome within the file ```delta_variant.fa``` into our Huffman encoder. The file content looks like this:
 
{% highlight txt linenos %}
 
\>FJ376619.2 Bulbul coronavirus HKU11-934, complete genome
GACAAAGCTCAAAATCAATACGTTATACGTATTGTATTTTGTAGCCCTCTAGCTTCGCTAGCTCGATTCC
GACACCAATCCAGGTGCGTTGTGCTGGACAGTGCCTGCCCGGTTTAGTGACTTACAGATTTGATCACGCC
TAACCACAGTTCATTGTGGAGTTTCGGCTGTTGATTGTCTGTTTGTTGCAACGGGGTCTTACTGTGTTCT
...
 
{% endhighlight %}
 
Once we run the compression, we are left with a binary file that is illegible in plaintext.
 
{% highlight txt linenos %}
 
^C^EB<96>^S<80>pO^EÁpÀ@^E^@aá  0<90>^_!^XH<2^V^D^V^H^[^E<80>^@<82>0xx
^F^D^PÀ\`&<84>^@8^Y^F<83>Ã!`à $^\^U^N^O^F^C<81>^BÁÁ f¢íV×'îOyïóÅ]âú^.<9b>ÔLËZÄå>räÌr¹T<9f>ã<99>ù<8d>ù¶J<8f>K1öó<93>^_Ò\ù¼î^?>ZI'~s<9f>qó^S<¼OL³{^\<9c><9f>õx<97>_¾$²Æaò±<9f>òÏ{ÕoñõÞ<96>æ^|¹<8b>ìq-ó<9e>$ýy<¤îYJ§b<93>G=Ç1f,<8e>¾YLW<8f>$ÝRªy$æuè©õ½)ÉÆ%¾;<Nz9·íÙMlþRÑå©[<89>^X¥5kÞå<8b><95>ÍçâßÆì<9f>£IÎÕ%^X«Þråf®ie×u<8b><9f>î,|¹bæ<88>Ñ;kTeú=ù'¯ºÜ<9d><97>MG¯\<9c>â±?õ*ÕvÏÎcù<8b>^W?<93>^Vis<9f><93><89>o)é|ùóR¥¬¹NMdºÑboòåa¢íG~_ç6Éÿ1%¬ÛWyWR<9c>þ<8e>YòÛù.çþc^sUÆÊÔmüæÏ<95>^[Íç+y<89>òÜÇ'£9¦<
 
{% endhighlight %}
 
However during the encoding, a list of codes were successfully generated to help us decode our encoded file as long as we feed it both the huffman tree as well as this list of codes in the decoding process. A list of our codes are printed here:
 
{% highlight txt linenos %}
 
Char | Huffman code
'G'  |          00
'o'  |    01000000
's'  |   010000010
'h'  | 01000001100
','  | 01000001101
'g'  | 01000001110
'>'  | 01000001111
'y'  |  0100001000
'v'  |  0100001001
'n'  |   010000101
'.'  | 01000011000
'd'  | 01000011001
'p'  |  0100001101
'-'  |   010000111
'N'  |      010001
'7'  | 01001000000
'3'  | 01001000001
'O'  | 01001000010
'V'  | 01001000011
'S'  |   010010001
'8'  | 01001001000
'6'  | 01001001001
'R'  | 01001001010
'H'  |0100100101100
'P'  |0100100101101
'B'  |010010010111000
'I'  |010010010111001
'F'  |01001001011101
'Y'  |01001001011110
'X'  |01001001011111
'4'  |  0100100110
'1'  |  0100100111
' '  |    01001010
'a'  |   010010110
'5'  | 01001011100
'9'  | 01001011101
'0'  |  0100101111
'e'  |    01001100
'U'  | 01001101000
'M'  | 01001101001
'u'  |  0100110101
'i'  |  0100110110
'c'  |  0100110111
'2'  |   010011100
'r'  |   010011101
'L'  |0100111100000
'K'  |010011110000100
'Q'  |010011110000101
'E'  |010011110000110
'b'  |0100111100001110000
'_'  |0100111100001110001
'Z'  |010011110000111001
'J'  |01001111000011101
'W'  |0100111100001111
'D'  |010011110001
'l'  | 01001111001
'/'  |  0100111101
'm'  |  0100111110
't'  |  0100111111
'\n' |        0101
'C'  |         011
'A'  |          10
'T'  |          11
 
{% endhighlight %}
 
We can also see a clear compression that occurs when we observe our output. Our file went from \\(4.72mb\\) to \\( 1.33mb\\) which is a compression rate of \\( 71.89% \\) percent. Finally in order to retrieve our original file we feed our binary file ```delta_variant.bin```, our list of codes and feed it back along with the huffman tree construction to get our original file.
 
{% highlight txt linenos %}
 
\>FJ376619.2 Bulbul coronavirus HKU11-934, complete genome
GACAAAGCTCAAAATCAATACGTTATACGTATTGTATTTTGTAGCCCTCTAGCTTCGCTAGCTCGATTCC
GACACCAATCCAGGTGCGTTGTGCTGGACAGTGCCTGCCCGGTTTAGTGACTTACAGATTTGATCACGCC
TAACCACAGTTCATTGTGGAGTTTCGGCTGTTGATTGTCTGTTTGTTGCAACGGGGTCTTACTGTGTTCT
...
 
{% endhighlight %}
 
---
 
# Code
 
This project was done in CSE13-S at UC Santa Cruz taught by Professor Darrell Long. Below I will list the source files that were made in this assignment as well as the code linked below it.
 
```Makefile```: a make file to easily run the program by prompting make into the Linux terminal on our
Ubuntu virtual machine.
 
```README.md```: describes how the program works and runs in addition to how to use the makefile
 
```Encode.c```:this file contains the encoded huffman codes
 
```Decode.c```:this file contains the decoded huffman codes
 
```Entropy.c```: like last assignment entropy.c will be used to test our codes level of entropy
 
```defines.h```: This file will contain the macro definitions used throughout the assignment.
 
```header.h```: This will contain thestruct definition for a file header.
 
```node.h```: This file will contain the node ADT interface. This file will be provided.
 
```node.c```: This file will contain your implementation of the node ADT.
 
```pq.h```: This file will contain the priority queue ADT interface. This file will be provided.
 
```pq.c```: This file will contain your implementation of the priority queue ADT. You Must Define your priority
queue struct in this file.
 
```code.h```: This file will contain the code ADT interface. This file will be provided.
 
```code.c```: This file will contain your implementation of the code ADT.
 
```io.h```: This file will contain the I/O module interface. This file will be provided.
 
```io.c```: This file will contain your implementation of the I/O module.
 
```stack.h```: This file will contain the stack ADT interface. This file will be provided.
 
```stack.c```: This file will contain your implementation of the stack ADT. You must define your stack struct in
this file.
 
```huffman.h```: This file will contain the Huffman coding module interface. This file will be provided.
 
```huffman.c``` : This file will contain your implementation of the Huffman coding module interface.
 
 
{% include feature_row id="feature_row_left1" type="left" %}
 
---
 
# Tutorial on how to run code
 
Step 1. Run the makefile.
```
make
```
 
Step 2. Run the encoder executable file while also passing in the system arguments. You will receive a compressed version of your data.
```
//to run encoder
./encode [-h] [-v] [-i infile] [-o outfile]
```
 
Step 3. Run the decoder executable file while passing in the proper system arguments. You should get your original file back
```
//to run decoder
./decode [-h] [-v] [-i infile] [-o outfile]
```
 
 
 
 

