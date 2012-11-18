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

This benchmark is extremely contrived (e.g. it only checks integers,
and not strings), and you should check it against your own system
C++/Python implementation; but for the curious, on my Linux GCC
4.7/Python 2.7 system, the results are like this (numbers are
milliseconds taken per task, so lower is better):

```
evan@loonix ~/code/associative-benchmark (master) $ python bench.py
generating number list with 1000000 integer pairs...
generated in 3156 ms

dict
---------
create: 458
search: 270
```

```
evan@loonix ~/code/associative-benchmark (master) $ ./bench
generating number list with 1000000 integer pairs...
generated in 534 ms

map
----------
create: 640
search: 621

hash
----------
create: 470
search: 77

bucket count = 1236397
load factor = 0.808713
max load factor = 1
```

```
evan@loonix ~/code/associative-benchmark (master) $ ./bench -r
generating number list with 1000000 integer pairs...
generated in 534 ms

map
----------
create: 629
search: 637

hash
----------
create: 341
search: 58

bucket count = 2144977
load factor = 0.466144
max load factor = 1
```
