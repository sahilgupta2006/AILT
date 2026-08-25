#include <bits/stdc++.h>
using namespace std;

int main() {
    int a = 0, b = 0;

    cout << "(" << a << ", " << b << ")\n";

    a = 4;
    cout << "(" << a << ", " << b << ")\n";

    int pour = min(a, 3 - b);
    a -= pour;
    b += pour;
    cout << "(" << a << ", " << b << ")\n";

    b = 0;
    cout << "(" << a << ", " << b << ")\n";

    pour = min(a, 3 - b);
    a -= pour;
    b += pour;
    cout << "(" << a << ", " << b << ")\n";

    a = 4;
    cout << "(" << a << ", " << b << ")\n";

    pour = min(a, 3 - b);
    a -= pour;
    b += pour;
    cout << "(" << a << ", " << b << ")\n";

    return 0;
}