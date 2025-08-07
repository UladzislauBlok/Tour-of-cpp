1. When the pair-of-iterators style becomes tedious, use a range algorithm;
2. When using a range algorithm, remember to explicitly introduce its name;
3. Pipelines of operations on a range can be expressed using views, generators, and filters;
4. To end a range with a predicate, you need to define a sentinel;
5. Using static_assert, we can check that a specific type meets the requirements of a concept;
6. If you want a range algorithm and there isn’t one in the standard, just write your own;
7. The ideal for types is regular;
8. Prefer standard-library concepts where they apply;
9. When requesting parallel execution, be sure to avoid data races and deadlock;
10. A range can be defined by:
    - A {begin,end} pair of iterators
    - A {begin,n} pair, where begin is an iterator and n is the number of elements
    - A {begin,pred} pair, where begin is an iterator and pred is a predicate; 