//Exercise13: Sieve of Eratosthenes
int main()
{
	cout << "Gimme the x in 1:x " << endl;
	int max;
	cin >> max;
	vector<int> numbers(max,0);
	vector<int> primes;

	for (int i = 0; i < max; ++i) numbers[i] = i;

	for (int i = 2; i < max; ++i) {

		if (numbers[i] != 0 && i != 0) {

			primes.push_back(i);
			cout << i << " was just added as a prime " << endl;

			for (int j = 2; j*i < max; ++i) {
					primes[i*j] = 0;
					cout << "The multiples of " << i << " have been set to 0. " << endl;

			}
		}
			if (numbers[i] == 0) continue;
	}
