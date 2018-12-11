*False Sharing optimisation problem*

IDE: VS_17, C++

Small report (Russian language): Report\DPrivalov_Optimization_False_sharing.pdf 

*To compile bad case scenario:*
comment out #define CACHE_LINE_ALIGNED

*If test case takes a lot of time:*
change num of iterations here #define ITERATION 30000

(VS adds a lot of optimisational flags, it is better to compile from IDE)
Could be build from VS cmd:
> cl /EHsc Source.cpp
> Source.exe
Or from the regular win command line:
run vcvars32.bat first to set up the environment.
* path for vcvars32.bat can be similar Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build
