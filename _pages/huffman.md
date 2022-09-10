---
title: "Huffman Compression Algorithm"
permalink: /huffman/
layout: splash 
classes: wide
excerpt: "An incredible compression algorithm"
header:
  overlay_image: /images/huff.png
  caption: "Huffman Coding" 
date: 2022-09-11

feature_row_left1:
  - url: "https://github.com/Simonlee711/CSE-13S/tree/master/asgn6"
    btn_label: "Code"
    btn_class: "btn--primary"
---
# Keywords: 

Data Compression, David Huffman, Information theory, entropy, Huffman coding

# History

When David Huffman was a graduate student in a class at MIT, the professor gave the class an unsolved problem: **How to construct an optimal static encoding of information**. The young Huffman came back a few days later with his solution, and that solution changed the world. Data compression is now used in all aspects of communication. David Huffman joined the faculty of MIT in 1953, and in 1967 he joined the faculty of University of California, Santa Cruz as one of its earliest members and helped to found its Computer Science Department, where he served as chairman from 1970 to 1973. He retired in 1994, and passed away in 1999.

---

# Algorithm
**The Huffman Compression algorithm** or **huffman coding** is a lossless algorithm. The idea is to assign variable-length bit codes to input characters, lengths of the assigned codes are based on the frequencies of corresponding characters. The most frequent character gets the smallest code and the least frequent character gets the largest code. And since we are working with bits (1 byte of memory is 8 bits), it results in a smaller data size. But lets look further into how the underlying mathematics works.

The key idea is called **entropy**, originally defined by Claude Shannon in 1948. Entropy is a measure of the amount of information in a say, set of symbols. If we define \\( I(x) = log_{2} Pr[x] \\) to be the information content of a symbol, then the entropy of the set \\( X = {x_{1},..., x_{n} \\) is 

\\[ H( \chi ) = \sum_{i=1}^{n} Pr[x_{i} I(x_{i})] = \sum_{i=1}^{n} Pr[ x_{i}] \log_{2} Pr[ x_i]\\]

We can see that the optimal static encoding will assign the least number of bits to the most common symbol, and the greatest number of bits to the least common symbol. 

The variable-length codes assigned to input characters are Prefix Codes, meaning the codes (bit sequences) are assigned in such a way that the code assigned to one character is not the prefix of code assigned to any other character and is therefore unique. This is how Huffman Coding makes sure that there is no ambiguity during the decoding from the generated bitstream. So in totality the algorithm is to encode all unique characters to form a huffman tree, and decode the information using the codes established during the encoding phase.

---

## Encode

The first step in building the huffman tree is to create leaf nodes for all unique characters. We then take a data structure called the **min heap** and build the tree. The min heap acts as a priority queue where the leaf nodes are all sorted by ascending order. This is because we want to take the two least frequency leaf nodes and combine them to build out the tree. We repeat these steps of combining lead nodes of the two smallest frequencies until we have only one node remaining. Our tree is complete. Next in order to establish the codes, we run a post traversal order tree traversal where if we go left we encode a 0 and if we go right we encode a 1. Once we hit a terminal node we know exactly what the code will be. We save these codes for the decoder and we can now feed the input characters into the tree to compress our data. We are left with a containing strictly zeros and ones.

---

## Decode

In order to decode we first must feed the huffman tree as well as the list of codes for every unique character. We then take our file containing binary files and walk the tree. The tree walking process takes in a single bit at a time and it is basically an instructions manual on whether to go left or right in the tree. If the bit is a 0 we go left and if the bit is a 1 we go right until we hit a terminal node. Once we hit the terminal node we can translate the sequence of bits to be the character saved in the codes table. We repeat this process until we are left with the original data. Congratulations you have performed the Huffman Compression Algorithm

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

Step 1. Run the make file.
```
make
```

Step 2. Run the encoder exacutable file while also passing in the system arguments. You will recieve a compressed version of your data.
```
//to run encoder
./encode [-h] [-v] [-i infile] [-o outfile]
```

Step 3. Run the decoder exectuable file while passing in the proper system arguments. You should get your original file back
```
//to run decoder
./decode [-h] [-v] [-i infile] [-o outfile]
```


