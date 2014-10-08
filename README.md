05_Hashing_Lab
==============

Implement a hash table in C++

Requirements
------------

1. `keyExists`, `find`, `remove`, and `size` should all be O(1)
2. `add` should be reasonably fast. Use linear probing to find an open slot in the hash table. This will be O(1), on average, except when `grow` is called.
3. `grow` should be O(n)
4. Do not leak memory


Reading
=======
"Open Data Structures," Chapter 5, except for 5.2.3. http://opendatastructures.org/ods-cpp/5_Hash_Tables.html

Questions
=========

#### 1. Which of the above requirements work, and which do not? For each requirement, write a brief response.

1. These all take 0(1) time becuase they directly access the elements of the array using the key. Does not matter on numItems.
2. Add uses the key to find where to update the hash record, so without the grow call this function is 0(1).
3. Growth took a lot of work for me but it takes 0(n) time as it iterates through all elements of the old backing array (is dependant on all n items).
4. Backing array is deleted and all object instances of new are deleted in the same functions.

#### 2. I decided to use two function (`keyExists` and `find`) to enable lookup of keys. Another option would have been to have `find` return a `T*`, which would be `NULL` if an item with matching key is not found. Which design do you think would be better? Explain your reasoning. You may notice that the designers of C++ made the same decision I did when they designed http://www.cplusplus.com/reference/unordered_map/unordered_map/

After a bit of thought, I think that the two functions would work functionally better than the find function returning a NULL value for T because that only tells you that there is no data in that location. It does not tell you if there is a key there that had not yet been assigned data, which could be a big problem. With two functions, a user knows for sure that the key does not exist independant of whether or not there is actual data in the location.

#### 3. What is one question that confused you about this exercise, or one piece of advice you would share with students next semester?

One question I had about this excersize is the importance of the keyExists function. I only used it once in the program...did we only include it to adhere to OOP principles in that 
adding it within the find function would be combing two different functions into one?