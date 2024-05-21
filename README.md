### 1. Servers
*- Description:*
We have **N** servers and every server it works perfectly when powered by a specific number, if the
servers receive more or less energy than required, their power decreases.
*- Implementation :*
To find the best power i used the **binary search** **O(log n)**, where the left and right are the 
minimum and maximum power from the specific number, when 
we start searching the best output by move to left or right where is the higher output power, until we 
find it.
### 2. Colouring
*- Description:*
We have a picture **N x 2** and need to colouring by giving us **k verticals and horizontals** 
rectangles , we need to find the **number of distinct models** by know we can use only 3 colors.
*- Implementation :*
We have 4 situation when when the last whas **H** and next **V** ,whas **V** and next **H**, both are 
**H** or **V**, so for evrey we use this formules: 

 - If last whas H and now is H too we use : **3^k**
 - If last whas V and now is H too we use : **2 * 3^(k-1)**
 - If last whas V and now is V too we use : **2^k**
 - If last whas H and now is V too we use : **2^(k -1)**
 The complexity is **O(n)** for extra performance i used the **O(log n)** power function
 
 ### 3. Compresion
 *- Description:*
 We have 2 arrays with **A** and **B** lenght of **N** int numbers we need to compres it to so the 
 arrays need to be the same lenght.
 *- Implementation :*
 We iterate over both array and sum elements of array one by one until they match.
 Complexity is **O(max(A, B))**.
 ### 4. Crypting 
 *- Description:*
 We have **N** strings and need to combine it(to generate a password) so one letter 
 appear more whan half  than the other letters.
  *- Implementation :*
  We will using **greedy** to sort the list of string by dominating letter and put the string who 
  respect the condition when we will using d**ynamical programming** to find if we can add another 
  string (from the remainig strings) to the final string wo will respect the conditon. At final we 
  select the longest password. The complexity is **O(n * (log n))** for greedy and **O(m * W)** there 
  **m** is the the how many letter we can add and **W** how many string remaining after selection 
 
 ### 5. Offer
 *- Description:*
 We have **N** products, we cand change the order, we need to find best offer by knowing what if we 
 **select 2 products we have a 50 % disccount** for the cheapest product 
 and if we **select 3 products we got the chepeast for free.**
  *- Implementation :*
  Using **dynamical programing** we create a vector and populate the first 3 elements by making the 
  best offer using the first 3 products, after we iterate until N and using the elements of the vector 
  calculate the best offer possible. The complexity is **O(n)**
