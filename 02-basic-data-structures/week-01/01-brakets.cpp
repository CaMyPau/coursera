#include <iostream>
#include <stack>
#include <string>

using namespace std;

char pairBracket( char c )
{
    switch( c )
    {
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    default:
        return '\0';
    }
}

int isBalanced( const string & str )
{
    stack< pair< char, size_t > > s;

    for( size_t i = 0; i < str.size(); i ++ )
    {
        auto c = str[ i ];
        switch( c )
        {
        case '(':
        case '[':
        case '{':
        {
            s.emplace( c, i );
            break;
        }
        case ')':
        case ']':
        case '}':
        {
            if( s.size() && s.top().first == pairBracket( c ) )
            {
                s.pop();
            }
            else
            {
                return i;
            }
        }
        default:
            ;
        }
    }

    if( s.empty() )
    {
        return -1;
    }
    else
    {
        while( s.size() != 1 )
        {
            s.pop();
        }
        return s.top().second;
    }
}

int main()
{
    string input;
    cin >> input;

    auto result = isBalanced( input );
    if ( result == -1 )
        cout << "Success" << endl;
    else
        cout << result + 1 << endl;

    return 0;
}
