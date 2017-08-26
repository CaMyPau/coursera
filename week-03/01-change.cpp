#include <array>
#include <iostream>

using namespace std;

int main()
{
    int64_t total;
    cin >> total;

    constexpr array< int64_t, 3 > coins = { 10, 5, 1 };

    int64_t result = 0;
    for( const auto & coin : coins )
    {
        result += total / coin;
        total %= coin;
        if( ! total )
        {
            break;
        }
    }

    cout << result << endl;
}
