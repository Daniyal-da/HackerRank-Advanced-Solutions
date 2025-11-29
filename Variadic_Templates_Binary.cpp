#include <iostream>
using namespace std;
//وقتی فقط یک بیت داریم
template <bool digit>
int reversed_binary_value() {
    return digit;
}

//وقتی بیشتر از یه بیت داریم
template <bool a, bool b, bool... d>
int reversed_binary_value() {
    return (reversed_binary_value<b, d...>() << 1) + a;
    //<<1
    //یعنی یک بیت به چپ شیفت بکن
}


int main() {
    cout << reversed_binary_value<0, 1, 1>() << endl; 
    return 0;
}