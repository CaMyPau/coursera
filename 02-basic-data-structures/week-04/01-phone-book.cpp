#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    unordered_map< int64_t, string > phoneBook;
    string op;
    string name;
    int64_t phone;
    for( size_t i = 0; i < n; i ++ )
    {
        cin >> op;
        if( op == "add" )
        {
            cin >> phone >> name;
            phoneBook[ phone ] = name;
        }
        else if( op == "find")
        {
            cin >> phone;
            auto it = phoneBook.find( phone );
            if( it != phoneBook.cend() )
            {
                cout << it->second << endl;
            }
            else
            {
                cout << "not found" << endl;
            }
        }
        else if( op == "del")
        {
            cin >> phone;
            phoneBook.erase( phone );
        }
    }
}
