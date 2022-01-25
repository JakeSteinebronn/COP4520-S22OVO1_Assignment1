This program was written in c++17.
To compile and run:
g++ -std=c++17 -O3 -pthread assignment1.cpp && ./a.out

I am running 8 threads, each thread is responsible for looping up to sqrt(bound) (i.e. 1e4) 
and using the miller-rabin test to check if each number the thread is responsible for is prime.
If it is, then it will loop over all its multiples and turn them off in an array called isprime. 
Afterward, the main thread will simply collect the prime numbers from this isprime array. 
This will be correct (as long as the primality check is correct) because to determine if a number x 
is prime, you simply have to show that every prime number less than sqrt(x) does not divide x. 
I verified the correctness of this by checking the prime-count via third-party (wolfram alpha).
The miller-rabin test is technically probalistic, but it can be shown that with sufficient iterations,
it will be guaranteed to be correct within a certain bound (based on the number of iterations). These
required iterations are performed, so this is guaranteed to be correct.