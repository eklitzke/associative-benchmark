About
================================

This is a stupid benchmark of C++ `std::map<int, int>` (i.e. a B-tree)
vs. `std::unordered_map<int, int>` (i.e. a C++11 hash table) vs. a
Python dict mapping ints to ints. Run it like this:

```bash
python bench.py           # for 1e6 pairs
python bench.py -n 100    # for 100 pairs

./bench                   # for 1e6 pairs
./bench -n 100            # for 100 pairs
./bench -r -n 1000        # 1000 pairs, and use .reserve()
```

Results
================================

This benchmark is extremely contrived, and you should check it against
your own system C++/Python implementation; but for the curious, on my
Linux GCC
4.7/Python 2.7 system, the results are like this (numbers are
milliseconds taken per task, so lower is better):

Integer Pairs
--------------------------------

```
evan@loonix ~/code/associative-benchmark (master) $ python bench.py
generating list with 1000000 integer pairs...
generated in 3156 ms

dict
---------
create: 458
search: 270
```

```
evan@loonix ~/code/associative-benchmark (master) $ ./bench -r
generating list with 1000000 integer pairs...
generated in 532 ms

sorted list
----------
create: 84
search: 209

map
----------
create: 637
search: 610

hash
----------
create: 341
search: 58

bucket count = 2144977
load factor = 0.466147
max load factor = 1
```

```
evan@loonix ~/code/associative-benchmark (master) $ ./bench
generating list with 1000000 integer pairs...
generated in 532 ms

sorted list
----------
create: 87
search: 210

map
----------
create: 637
search: 610

hash
----------
create: 473
search: 79

bucket count = 1236397
load factor = 0.808722
max load factor = 1
```

String Pairs
--------------------------------

```
evan@loonix ~/code/associative-benchmark (master) $ python bench.py -s
generating list with 1000000 string pairs...
generated in 5420 ms

dict
---------
create: 418
search: 260
```

```
evan@loonix ~/code/associative-benchmark (master) $ ./bench -s -r
generating list with 1000000 string pairs...
generated in 1224 ms

sorted list
----------
create: 902
search: 1023

map
----------
create: 1402
search: 1386

hash
----------
create: 399
search: 104

bucket count = 2144977
load factor = 0.466205
max load factor = 1
```

```
evan@loonix ~/code/associative-benchmark (master) $ ./bench -s
generating list with 1000000 string pairs...
generated in 1132 ms

sorted list
----------
create: 852
search: 1038

map
----------
create: 1337
search: 1332

hash
----------
create: 548
search: 136

bucket count = 1236397
load factor = 0.808802
max load factor = 1
```
