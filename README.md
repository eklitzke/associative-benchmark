This is a stupid benchmark of C++ `std::map<int, int>` (i.e. a B-tree)
vs. `std::unordered_map<int, int>` vs. a Python dict mapping ints to
ints. Run it like this:

```bash
python bench.py           # for 1e6 pairs
python bench.py -n 100    # for 100 pairs

./bench                   # for 1e6 pairs
./bench -n 100            # for 100 pairs
./bench -r -n 1000        # 1000 pairs, and use .reserve()
```

