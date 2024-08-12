# psswrdgen 0.1

All the implementations have been coded in Windows.


The Java implementation uses SecureRandom.

The javascript implementation uses Math.Random.

The C++ implementation uses std::random_device and std::mt19937.

The C implementation uses the Windows Cryptography API (CryptGenRandom).


We can say that the Java and C implementation are relatively cryptographically safe.

The C++ tends to run faster than the C one because of the use of a less secure random generator.

I have no idea of how safe js Math.Random is

