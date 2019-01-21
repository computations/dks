Dynamic Kernel Selection
===============================================================================

In tree inference with RAxML, it appears that "higher" CPU instruction sets are
not actually faster all the time. I.E. sometimes AVX is faster than AVX2.
Unfortunately, this isn't the case all the time, and appears to depend on the
data. Therefore, this is a toolkit to heuristically determine which of the CPU
options are the best for a given data set.
