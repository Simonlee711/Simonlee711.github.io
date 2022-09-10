---
title: "Huffman Compression Algorithm"
permalink: /huffman/
layout: splash 
classes: wide
excerpt: "An incredible compression algorithm"
header:
  overlay_image: /images/huff.png
  caption: "Huffman Coding"
date: 2022-09-10
---

# Introduction

When David Huffman was a graduate student in a class at MIT, the professor gave the class an unsolved problem: How to construct an optimal static encoding of information. The young Huffman came back a few days later with his solution, and that solution changed the world. Data compression is now used in all aspects of communication. David Huffman joined the faculty of MIT in 1953, and in 1967 he joined the faculty of University of California, Santa Cruz as one of its earliest members and helped to found its Computer Science Department, where he served as chairman from 1970 to 1973. He retired in 1994, and passed away in 1999.

The key idea is called entropy, originally defined by Claude Shannon in 1948. Entropy is a measure of the amount of information in a, say, set of symbols. If we define \\( I(x) = log_{2} Pr[x] \\) to be the information content of a symbol, then the entropy of the set \\( X = {x_{1},..., x_{n} \\) is 

{% include figure image_path="images/eq.png" alt="this is a placeholder image" caption="" %}

It should be easy to see that the optimal static encoding will assign the least number of bits to the most
common symbol, and the greatest number of bits to the least common symbol. 