# C++ Quick Reference Card

## Table of Contents
- [Headers](#headers)
- [Variables & Types](#variables--types)
- [Operators](#operators)
- [Control Flow](#control-flow)
- [Loops](#loops)
- [Functions](#functions)
- [Arrays & Vectors](#arrays--vectors)
- [Strings](#strings)
- [Pointers](#pointers)
- [Classes](#classes)
- [Common Patterns](#common-patterns)
- [STL Containers](#stl-containers)
- [Input/Output](#inputoutput)
- [Debugging](#debugging)

---

## Headers

```cpp
// Most Common
#include <iostream>      // cin, cout
#include <string>        // std::string
#include <vector>        // std::vector
#include <map>           // std::map
#include <fstream>       // File I/O
#include <cmath>         // Math functions
#include <algorithm>     // sort, find, reverse
#include <memory>        // Smart pointers

using namespace std;     // Avoid std:: prefix
```

---

## Variables & Types

```cpp
// Declaration
int x;                  // Uninitialized (don't do this!)
int y = 10;             // Initialized
const int MAX = 100;    // Constant
auto z = 42;            // Type deduction (C++11)

// Data Types
char c = 'A';           // 1 byte, single character
short s = 1000;         // 2 bytes
int i = 100000;         // 4 bytes (most common)
long l = 100000L;       // 4 or 8 bytes
long long ll = 999LL;   // 8 bytes
unsigned int ui = 50;   // Positive only

float f = 3.14f;        // 4 bytes (~7 digits)
double d = 3.14159;     // 8 bytes (~15 digits)

bool flag = true;       // true or false

string str = "Hello";   // C++ string
vector<int> vec = {1,2,3};  // Dynamic array
```

---

## Operators

```cpp
// Arithmetic
+  -  *  /  %

// Comparison
==  !=  <  >  <=  >=

// Logical
&&  (AND)
||  (OR)
!   (NOT)

// Assignment
=  +=  -=  *=  /=  %=

// Increment/Decrement
++x  (pre-increment)
x++  (post-increment)

// Ternary
condition ? true_value : false_value

// Memory
&   (address-of)
*   (dereference)
->  (pointer member access)
.   (direct member access)
```

---

## Control Flow

```cpp
// If / Else If / Else
if (condition) {
    // code
} else if (other_condition) {
    // code
} else {
    // code
}

// Switch
switch (value) {
    case 1:
        // code
        break;
    case 2:
        // code
        break;
    default:
        // code
}

// Ternary (shorthand if)
string result = (x > 5) ? "yes" : "no";
```

---

## Loops

```cpp
// For loop
for (int i = 0; i < n; i++) {
    cout << i << endl;
}

// For-each (range-based, C++11)
for (int val : array) {
    cout << val << endl;
}

for (auto& element : container) {
    element = 10;  // modify element
}

// While
while (condition) {
    // code
}

// Do-While (executes at least once)
do {
    // code
} while (condition);

// Loop Control
continue;   // Skip to next iteration
break;      // Exit loop
```

---

## Functions

```cpp
// Declaration (prototype)
return_type function_name(param1, param2);

// Definition
int add(int a, int b) {
    return a + b;
}

// No return value
void print_message(string msg) {
    cout << msg << endl;
}

// Default parameters
void greet(string name = "Friend") {
    cout << "Hello, " << name << endl;
}

// Pass by reference
void increment(int& x) {
    x++;  // Modifies original
}

// Const parameter (read-only)
void print(const string& text) {
    cout << text << endl;  // Can't modify text
}

// Multiple returns (reference parameters)
void divide(int a, int b, int& quotient, int& remainder) {
    quotient = a / b;
    remainder = a % b;
}
```

---

## Arrays & Vectors

```cpp
// C-style Arrays
int arr[5];                    // Fixed size
int arr2[] = {1, 2, 3};        // Size inferred
int matrix[2][3] = {{1,2,3}, {4,5,6}};

int val = arr[0];              // Access
arr[0] = 10;                   // Modify

// Vector (dynamic array, preferred)
vector<int> v;                 // Empty
vector<int> v2 = {1, 2, 3};    // Initialized
vector<string> names(5);       // 5 empty strings
vector<double> vals(10, 3.14); // 10 values of 3.14

// Methods
v.push_back(4);                // Add to end
v.pop_back();                  // Remove from end
v.size();                      // Number of elements
v.capacity();                  // Allocated space
v.at(0);                       // Safe access (bounds check)
v[0];                          // Direct access
v.clear();                     // Remove all
v.insert(v.begin() + 2, 99);   // Insert at position
v.erase(v.begin() + 1);        // Remove at position

// Iteration
for (int x : v) cout << x << endl;
for (int i = 0; i < v.size(); i++) cout << v[i] << endl;
for (auto it = v.begin(); it != v.end(); ++it) cout << *it << endl;
```

---

## Strings

```cpp
string s = "Hello";
string s2 = "World";

// Concatenation
string combined = s + " " + s2;  // "Hello World"
s += "!";                        // Append

// Properties
s.length();                      // 5
s.size();                        // 5 (same as length)
s[0];                            // 'H' (access character)

// Methods
s.substr(0, 3);                  // "Hel" (position, length)
s.find("ll");                    // 2 (position of substring)
s.replace(0, 5, "Hi");           // Replace "Hello" with "Hi"
s.at(0);                         // Safe character access

// Comparison
s == "Hello";                    // true
s != "hello";                    // true (case-sensitive)
s < "World";                     // true (lexicographic)

// Conversion
string num_str = "123";
int num = stoi(num_str);         // String to int
double d = stod(num_str);        // String to double
string s_from_int = to_string(42);  // Int to string

// Case conversion (need algorithm or manual)
for (char& c : s) c = tolower(c);   // To lowercase
```

---

## Pointers

```cpp
int x = 10;
int* ptr = &x;                  // Pointer to x
                                // & = address-of

cout << x << endl;              // 10
cout << &x << endl;             // Memory address
cout << ptr << endl;            // Memory address
cout << *ptr << endl;           // 10 (* = dereference)

*ptr = 20;                       // Change x through pointer
cout << x << endl;              // 20

// Pointer to pointer
int** ptr2 = &ptr;
cout << **ptr2 << endl;         // 20

// Dynamic memory
int* p = new int;               // Allocate
*p = 42;
delete p;                       // Free memory
p = nullptr;                    // Good practice

int* arr = new int[100];        // Dynamic array
delete[] arr;                   // Note: [] for arrays
arr = nullptr;

// Smart pointers (automatic cleanup, C++11+)
unique_ptr<int> u(new int(42));
shared_ptr<int> s(new int(42));
auto up = make_unique<int>(42);
auto sp = make_shared<int>(42);
```

---

## Classes

```cpp
class MyClass {
private:
    int value;
    
public:
    // Constructor
    MyClass(int v) : value(v) {}
    
    // Destructor
    ~MyClass() {}
    
    // Getter
    int get_value() const {
        return value;
    }
    
    // Setter
    void set_value(int v) {
        if (v > 0) value = v;
    }
    
    // Method
    void print() {
        cout << "Value: " << value << endl;
    }
};

// Usage
MyClass obj(42);
obj.print();
cout << obj.get_value() << endl;

// Pointer
MyClass* ptr = new MyClass(10);
ptr->print();              // -> for pointer access
delete ptr;

// Stack vs Heap
MyClass stack_obj(5);      // Stack (automatic cleanup)
MyClass* heap_obj = new MyClass(10);  // Heap (manual cleanup)
```

---

## Inheritance & Polymorphism

```cpp
class Animal {
public:
    virtual void speak() {
        cout << "Generic sound" << endl;
    }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void speak() override {
        cout << "Woof!" << endl;
    }
};

// Polymorphism
Animal* a = new Dog();
a->speak();                    // "Woof!"
delete a;
```

---

## Common Patterns

### Read Input
```cpp
int x;
cin >> x;

string line;
getline(cin, line);

int a, b;
cin >> a >> b;
```

### Write Output
```cpp
cout << "Hello" << endl;
cout << x << " " << y << endl;

cout << fixed << setprecision(2);  // 2 decimal places
cout << 3.14159 << endl;          // 3.14
```

### File I/O
```cpp
// Write
ofstream out("file.txt");
out << "Hello" << endl;
out.close();

// Read
ifstream in("file.txt");
string line;
while (getline(in, line)) {
    cout << line << endl;
}
in.close();

// Binary
ofstream bin("data.bin", ios::binary);
bin.write((char*)&data, sizeof(data));
```

### Exception Handling
```cpp
try {
    if (x < 0) throw invalid_argument("x must be positive");
} catch (const invalid_argument& e) {
    cout << "Error: " << e.what() << endl;
} catch (const exception& e) {
    cout << "General error: " << e.what() << endl;
} catch (...) {
    cout << "Unknown error" << endl;
}
```

---

## STL Containers

```cpp
// Vector (dynamic array)
vector<int> v = {1, 2, 3};
v.push_back(4);
v.pop_back();
v.size();

// String
string s = "Hello";
s.length();
s.substr(0, 3);
s.find("ll");

// Map (key-value)
map<string, int> ages;
ages["Alice"] = 25;
ages["Bob"] = 30;
ages["Alice"]++;
cout << ages["Alice"] << endl;  // 26
ages.erase("Bob");

// Set (unique values, sorted)
set<int> unique_nums = {3, 1, 2, 1, 3};  // {1, 2, 3}
unique_nums.insert(4);
unique_nums.erase(2);

// Queue (FIFO)
queue<int> q;
q.push(1);
q.push(2);
q.front();   // 1
q.pop();

// Stack (LIFO)
stack<int> s;
s.push(1);
s.push(2);
s.top();     // 2
s.pop();

// List (linked list)
list<int> l = {1, 2, 3};
l.push_back(4);
l.push_front(0);
```

---

## Input/Output

```cpp
#include <iostream>
#include <iomanip>

using namespace std;

// Basic
cout << "Value: " << x << endl;
cin >> x;

// Formatted
cout << fixed << setprecision(2) << 3.14159 << endl;  // 3.14
cout << setw(10) << "Right";  // Right-align in 10 spaces
cout << left << setw(10) << "Left";  // Left-align

// Error output
cerr << "Error: something failed" << endl;
clog << "Log: debug info" << endl;

// String input
string name;
getline(cin, name);  // Read entire line

// Multiple values
int a, b;
cin >> a >> b;
```

---

## Debugging

```cpp
#include <cassert>
#include <iostream>

// Assertions (program stops if false)
assert(x > 0);
assert(ptr != nullptr);

// Debug output
#ifdef DEBUG
    cout << "DEBUG: value = " << x << endl;
#endif

// Log
void log(string msg) {
    cerr << "[LOG] " << msg << endl;
}

// Type information
typeid(variable).name();  // (advanced)

// Print variable address
cout << "Address of x: " << &x << endl;
```

---

## Common Mistakes to Avoid

| Mistake | Fix |
|---------|-----|
| `int arr[10]; arr[10];` | Out of bounds access | Use `.at()` or check bounds |
| `new` without `delete` | Memory leak | Use smart pointers or delete |
| `string x;` uninitialized | Garbage value | Initialize: `string x = "";` |
| `char c = 'ab';` | Wrong type | Use `'a'` for char, `"ab"` for string |
| Comparing strings with `==` on chars | Wrong | Use `str.compare()` or `==` for strings |
| `&` with local variable return | Dangling pointer | Return by value or reference param |
| Forgetting `;` | Syntax error | Add semicolon at end of statements |
| Wrong operator precedence | Logic error | Use parentheses: `(a > 5 && b < 10)` |

---

## Compilation & Execution

```bash
# Compile
g++ -std=c++17 -o program program.cpp

# With optimization
g++ -std=c++17 -O2 -o program program.cpp

# With debugging symbols
g++ -std=c++17 -g -o program program.cpp

# With all warnings
g++ -std=c++17 -Wall -Wextra -o program program.cpp

# Run
./program

# Run with input from file
./program < input.txt

# Run with output to file
./program > output.txt
```

---

## Learning Resources

- **cppreference.com** - Language reference (best!)
- **cplusplus.com** - Tutorials and reference
- **Scott Meyers "Effective C++"** - Best practices
- **Bjarne Stroustrup "C++ Primer"** - Comprehensive guide

---

## Summary Cheat

| Task | Code |
|------|------|
| Print | `cout << x << endl;` |
| Input | `cin >> x;` |
| Declare | `int x = 10;` |
| Array | `vector<int> v = {1,2,3};` |
| String | `string s = "Hello";` |
| Pointer | `int* p = &x; *p = 5;` |
| Class | `class Name { private: int x; public: ... };` |
| Function | `int add(int a, int b) { return a+b; }` |
| Loop | `for(int i=0; i<n; i++) { ... }` |
| If/Else | `if (x > 5) { ... } else { ... }` |
| Try/Catch | `try { ... } catch(exception& e) { ... }` |

---

**Print this page for quick reference while coding!**
