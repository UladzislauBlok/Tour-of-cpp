1. Don’t use the built-in features exclusively. Many fundamental (built-in) features are usually best used indirectly through libraries, such as the ISO C++ standard library.
2. #include or (preferably) import the libraries needed to simplify programming;
3. You don’t have to know every detail of C++ to write good programs.
4. Focus on programming techniques, not on language features.
5. The ISO C++ standard is the final word on language definition issues;
6. ‘Package’ meaningful operations as carefully named functions;
7. A function should perform a single logical operation;
8. Keep functions short;
9. Use overloading when functions perform conceptually the same task on different types;
10. If a function may have to be evaluated at compile time, declare it constexpr;
11. If a function must be evaluated at compile time, declare it consteval;
12. If a function may not have side effects, declare it constexpr or consteval;
13. Understand how language primitives map to hardware;
14. Use digit separators to make large literals readable;
15. Avoid complicated expressions; 
16. Avoid narrowing conversions; 
17. Minimize the scope of a variable;
18. Keep scopes small;
19. Avoid ‘magic constants’; use symbolic constants;
20. Prefer immutable data;
21. Declare one name (only) per declaration;
22. Keep common and local names short; keep uncommon and nonlocal names longer;
23. Avoid similar-looking names;
24. Avoid ALL_CAPS names;
25. Prefer the {}-initializer syntax for declarations with a named type;
26. Use auto to avoid repeating type names;
27. Avoid uninitialized variables;
28. Don’t declare a variable until you have a value to initialize it with;
29. When declaring a variable in the condition of an if-statement, prefer the version with the implicit test against 0 or nullptr;
30. Prefer range-for loops over for-loops with an explicit loop variable;
31. Use unsigned for bit manipulation only;
32. Keep use of pointers simple and straightforward;
33. Use nullptr rather than 0 or NULL;
34. Don’t say in comments what can be clearly stated in code;
35. State intent in comments;
36. Maintain a consistent indentation style;