# Overview
This program implements a cache with support for three eviction policies: 
First-In-First-Out (FIFO), Least-Recently-Used (LRU), and Clock. The cache 
continuously takes items from stdin until stdin is closed. After each lookup, 
the program prints to stdout, indicating whether the item accessed is a HIT or 
MISS. If it is a MISS, the cache adds the item and evicts another item based 
on the specified eviction policy. Upon program exit, and after stdin is closed, 
a summary line is printed, specifying the total number of compulsory and capacity
misses.

# Usage
Run the cacher using the following command:

  ./cacher [-N size] <policy>

size: Size of the cache.
policy: Eviction policy flag, which can be one of the following:
-F for First-In-First-Out
-L for Least Recently Used
-C for Clock
If no policy is given, the cacher will use First-In-First-Out by default.
