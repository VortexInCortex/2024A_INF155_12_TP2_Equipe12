# Description
This little program answers questions by finding keywords present in both the question and the dictionnary. If it cannot answer the question, it prompts the user to add the entry in its dictionnary.

# Technical Challenges
This program used both dynamic arrays and linked lists, the latter was most challenging to implement. This linked list system was created to massively speed up keyword searches through the dictionnary. We also had to implement some proper input safety, ensuring the user couldn't enter invalid values into the program and crash it. We also had to properly use the free() function and unit tests to ensure the stability of the program. Finally, understanding of tokens and how to subdivide a sentence in its tokens using a delimiter was used to store and read entries from the dictionary.
<br>
To provide a clearer explanation, we used a linked list which only stored the first keyword for the stored entries. For instance, Hash map and hash both share the same struct which only stores the word "hash" and then the words "hash" and "hash map" were stored in a dynamic array which were only compared against the keywords in the question if the word "hash" first matched a keyword in the question.

# Example
What is a hash map?

-> This would start a search through our sorted dictionnary for the word "hash" since both "hash map" and "hash" are stored in the same struct in the linked list. After matching the word "hash" it would further search within the entries that match this keyword. Between "hash map" and "hash" the program would match the longer entry as the correct match and would answer with the definition of a hash map.
