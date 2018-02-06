# Boolean-Retrieval-Model

###Datasets
You are given two textual dataset for building inverted and positional index on it.
Your dictionary must be written to disk, for each word in the lexicon you must store
a file offset to the corresponding posting list, and finally, you should process the raw
text collection only once (many real-word collections are so big that the cost of
multiple scans is prohibitive).
For the Quran dataset, each verse constitutes a document.
For the Hadeeth dataset, each hadeeth constitutes a document.

###Query Processing
In this assignment, all you need to implement an information retrieval model called
Boolean Information Retrieval Model with some simplified assumptions. You will
be provided with a bunch of overly simplified documents collection (corpus), you
need to implement a simplified Boolean users queries that can only be formed by
joining three terms (t1, t2 and t3) with ( AND, OR and NOT) Boolean operators. For
example a user query may be of the form (t1 AND t2 AND t3). For positional
queries, the query text contains “/” along with a k intended to return all documents
that contains t1 and t2, k words apart. For /0 (zero) means phrase or adjacent terms.

Basic Assumption for Boolean Retrieval Model
1. An index term (word) is either present (1) or absent (0) in the document. A
dictionary contains all index terms.
2. All index terms provide equal evidence with respect to information needs. (
No frequency count necessary, but in next assignment it can be)
3. Queries are Boolean combinations of index terms at max 3.
4. Boolean Operators (AND, OR and NOT) are allowed. For examples:
X AND Y: represents doc that contains both X and Y
X OR Y: represents doc that contains either X or Y
NOT X: represents the doc that do not contain X
5. Queries of the type X AND Y / 3 represents doc that contains both X and Y
and 3 words apart.
We will implement a Boolean Model by creating
a posting list of all the terms present in the documents. You are free to implement a
posting list with your choice of data structures; you are only allowed to preprocess
the text from the documents in term of tokenization in which you can do case folding
and stop-words removal but no-stemming. The stop word list is also provided to you
in assignments files. Your query processing routine must address a query parsing,
evaluation of the cost, and through executing it to fetch the required list of
documents. A command line interface is simply required to demonstrate the working
model. You are also provided by a set of 10 queries, for evaluating your
implementation.
