// Generate list of prime numbers using Sieve of Eratosthenes.
ll _sieve_size;
bitset<10000010> bs; // [b]it [s]et 10^7 should be enough for most cases
vi primes;    // compact list of primes

void sieve(ll upperbound)    // create list of primes in [0..upperbound]
{
    _sieve_size = upperbound + 1; // add 1 to include upperbound
    bs.set();                     // set all bits to 1
    bs[0] = bs[1] = 0;            // exception index 0 and 1
    for (ll i = 2; i <= _sieve_size; ++i)
        if (bs[i])
        {   // cross out multiples of i starting from i * i!
            for (ll j = i * i; j <= _sieve_size; j += i) bs[j] = 0;
            primes.push_back( (int)i );
        }
}

bool isPrime(ll N)    // a good enough deterministic prime tester
{
    if (N <= _sieve_size) return bs[N];    // O(1) for small primes
    for (int i = 0; i < (int)primes.size(); ++i)
        if (N % primes[i] == 0) return false;
    return true;    // it takes longer if N is a large prime!
}                   // note: only work for N <= (last prime in vi 'primes')^2

// inside int main()
    sieve(10000000);    // can go up to 10^7 (need few seconds)
    printf("%d\n", isPrime(2147483647));     // 10-digit prime
    printf("%d\n", isPrime(136117223861LL)); // not a prime, 104729 * 1299709