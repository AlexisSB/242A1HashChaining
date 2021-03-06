Overview

Asgn processes two groups of words. The first compulsory argument should
specify a file to read in the first group of words. The second group of
words is read from stdin. If a word that is read in from stdin is not in
the first group of words, then the word will be printed to stdout.
For example:
    ./asgn dictionary.txt < document.txt
should print out words in document.txt that do not occur in the dictionary.
Words from the first group are stored in a chaining hash table for later search
by the second group of words.The default chaining uses a linked list.

Options

-r
This tells the hash table to use red-black binary search trees(rbt)
for chaining. A rbt offers improvements in search speed when many
values are chained in the same container.

-s table-size
Changes the size of the hash table to the specified size. Default size is 3877.

-p
Prints out the contents of the hash table to stdout.
Prints one line per non-empty container.
Doesn't read any more words in from stdin.

-i
Prints extra information to stderr. This includes the time to fill the
hash table with words from the first group of words, how long it took to search
the hashtable for the words in the second group, and how many unknown words
were found this way
     e.g.  
     	   Fill time : 1.390000
	   Search time : 0.450000
	   Unknown words : 8690

-h
Prints this message.

