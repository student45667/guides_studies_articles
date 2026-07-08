# C++ Comprehensive Study Guide

## Table of Contents
1. [Introduction](#introduction)
2. [Basics & Syntax](#basics--syntax)
3. [Data Types & Variables](#data-types--variables)
4. [Control Structures](#control-structures)
5. [Functions](#functions)
6. [Arrays & Strings](#arrays--strings)
7. [Pointers & Memory Management](#pointers--memory-management)
8. [Object-Oriented Programming](#object-oriented-programming)
9. [Inheritance & Polymorphism](#inheritance--polymorphism)
10. [Standard Library (STL)](#standard-library-stl)
11. [File I/O](#file-io)
12. [Error Handling](#error-handling)
13. [Best Practices](#best-practices)
14. [Quick Reference](#quick-reference)

---

## Introduction

### What is C++?
- **Compiled language**: Code is translated to machine code before running (fast execution)
- **Statically typed**: Variable types declared at compile time
- **Object-oriented**: Supports classes, inheritance, polymorphism
- **Low-level access**: Direct memory manipulation via pointers
- **Backward compatible with C**: Can use C libraries

### Key Differences from Python
| Feature | C++ | Python |
|---------|-----|--------|
| **Compilation** | Compiled | Interpreted |
| **Speed** | Very fast (~100x faster) | Slower (but good for scripts) |
| **Syntax** | Verbose | Concise |
| **Type checking** | Static (compile-time) | Dynamic (runtime) |
| **Memory** | Manual (new/delete) | Automatic (garbage collection) |
| **Use cases** | System software, games, AI | Data science, web, scripting |

### Why Learn C++?
- Control over hardware and performance
- Fundamental CS concepts (memory, pointers, OOP)
- Used in embedded systems, game engines, scientific computing
- Bridge between high-level languages (Python) and low-level (Assembly)

---

## Basics & Syntax

### Hello World

```cpp
#include <iostream>  // Input/output library

using namespace std;  // Avoid typing std:: every time

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

**Compilation & Run:**
```bash
g++ -o hello hello.cpp
./hello
```

### Core Concepts

**Statements & Semicolons:**
- Every statement ends with `;`
- Blocks use `{ }`
- Comments: `//` (single line) or `/* */` (multi-line)

**cout (console output):**
```cpp
cout << "Hello" << endl;      // Print with newline
cout << "Value: " << 42 << " ";  // Can chain multiple outputs
cout.precision(2);             // Set decimal places
cout << 3.14159 << endl;       // Prints: 3.1
```

**cin (console input):**
```cpp
int age;
cout << "Enter age: ";
cin >> age;  // >> = extraction operator (input)

string name;
cin >> name;              // Read single word
getline(cin, name);       // Read entire line
```

---

## Data Types & Variables

### Built-in Data Types

```cpp
// Integer types (sizes may vary by platform)
char c = 'A';              // 1 byte, stores single character (ASCII value)
short s = 1000;            // 2 bytes, range: -32,768 to 32,767
int i = 100000;            // 4 bytes, most common integer type
long l = 100000L;          // 4 or 8 bytes
long long ll = 999999999999LL;  // 8 bytes, very large integers

unsigned int ui = 100;     // No negative values, double positive range
unsigned char uc = 255;    // 0-255

// Floating point (decimal numbers)
float f = 3.14f;           // 4 bytes, ~7 decimal digits precision
double d = 3.141592653589793;  // 8 bytes, ~15 decimal digits (preferred)

// Boolean
bool flag = true;          // true or false
bool condition = (x > 5);  // Result of comparison

// Size of types (system-dependent)
sizeof(int);               // Usually 4 bytes
sizeof(double);            // Usually 8 bytes
```

### Variable Declaration & Initialization

```cpp
int x;              // Declared, uninitialized (contains garbage)
int y = 10;         // Declared and initialized
int z = 5, w = 15;  // Multiple variables in one line
int sum = x + y;    // Can initialize with expression

const int MAX = 100;  // Constant (cannot be changed)
const double PI = 3.14159;

auto result = add(5, 3);  // Type deduced from return type (C++11)
```

### Type Conversion

```cpp
// Implicit conversion (automatic)
int x = 10;
double d = x;  // x automatically converted to double

// Explicit conversion (casting)
int i = (int)3.14;         // C-style cast
int j = static_cast<int>(3.14);  // C++ style (preferred)
int k = int(3.14);         // Function-style cast
```

### Scope

```cpp
int global_var = 10;  // Global scope

int main() {
    int local_var = 20;    // Local to main()
    
    {
        int block_var = 30;  // Local to this block
        // Can access: global_var, local_var, block_var
    }
    
    // Cannot access block_var here
    return 0;
}
```

---

## Control Structures

### If / Else If / Else

```cpp
int score = 85;

if (score >= 90) {
    cout << "A" << endl;
} else if (score >= 80) {
    cout << "B" << endl;
} else if (score >= 70) {
    cout << "C" << endl;
} else {
    cout << "F" << endl;
}

// Ternary operator (shorthand)
string grade = (score >= 80) ? "Pass" : "Fail";
```

### Switch Statement

```cpp
char choice = 'B';

switch (choice) {
    case 'A':
        cout << "Choice A" << endl;
        break;  // Exit switch
    case 'B':
        cout << "Choice B" << endl;
        break;
    default:
        cout << "Invalid" << endl;
}
```

### Loops

```cpp
// FOR loop
for (int i = 0; i < 5; i++) {
    cout << i << endl;
}

// FOR loop with range (C++11+)
vector<int> numbers = {1, 2, 3, 4, 5};
for (int num : numbers) {
    cout << num << endl;
}

// WHILE loop
int i = 0;
while (i < 5) {
    cout << i << endl;
    i++;
}

// DO-WHILE loop (executes at least once)
int j = 0;
do {
    cout << j << endl;
    j++;
} while (j < 5);

// Loop control
for (int i = 0; i < 10; i++) {
    if (i == 3) continue;  // Skip to next iteration
    if (i == 8) break;     // Exit loop
    cout << i << " ";
}
```

---

## Functions

### Function Definition

```cpp
// Syntax: return_type function_name(parameters) { ... }

int add(int a, int b) {
    return a + b;  // Must return value matching return_type
}

void print_message(string msg) {
    cout << msg << endl;  // No return (void)
}

double calculate(double x, double y = 2.0) {
    // y has default value of 2.0 if not provided
    return x * y;
}
```

### Function Prototypes

```cpp
// Declare function before using it
int add(int a, int b);  // Prototype

int main() {
    cout << add(5, 3) << endl;
    return 0;
}

// Implementation can be below main()
int add(int a, int b) {
    return a + b;
}
```

### Passing by Value vs Reference

```cpp
// Pass by value (copy made)
void increment_v(int x) {
    x++;  // Only local copy changed
}

// Pass by reference (original modified)
void increment_r(int &x) {
    x++;  // Original variable changed
}

int main() {
    int num = 5;
    increment_v(num);  // num still 5
    increment_r(num);  // num now 6
}
```

### Return Multiple Values

```cpp
// Option 1: Pass by reference
void divide(int a, int b, int &quotient, int &remainder) {
    quotient = a / b;
    remainder = a % b;
}

// Option 2: Return struct
struct DivResult {
    int quotient;
    int remainder;
};

DivResult divide_v2(int a, int b) {
    return {a / b, a % b};  // C++11 initialization
}

// Usage
int q, r;
divide(17, 5, q, r);  // q = 3, r = 2
```

---

## Arrays & Strings

### C-Style Arrays

```cpp
// Fixed-size arrays (must know size at compile time)
int arr[5] = {10, 20, 30, 40, 50};
int arr2[3] = {1, 2, 3};
int arr3[] = {100, 200};  // Size inferred from initialization

// 2D arrays
int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};

// Access elements
cout << arr[0] << endl;          // 10
cout << matrix[0][1] << endl;    // 2

// Iterate
for (int i = 0; i < 5; i++) {
    cout << arr[i] << endl;
}

// Array name is pointer to first element
int* ptr = arr;
cout << *ptr << endl;            // arr[0]
cout << ptr[1] << endl;          // arr[1]
```

**Problems with C-style arrays:**
- Fixed size at compile time
- No bounds checking
- Decay to pointers (unsafe)

### Vector (Dynamic Array)

```cpp
#include <vector>

vector<int> numbers;              // Empty vector
vector<int> nums = {1, 2, 3};     // Initialized with values
vector<string> names(5);          // 5 empty strings
vector<double> values(10, 3.14);  // 10 values of 3.14

// Add elements
nums.push_back(4);
nums.push_back(5);

// Remove last element
nums.pop_back();

// Access
cout << nums[0] << endl;          // Direct access
cout << nums.at(0) << endl;       // Safe access (bounds checking)

// Size and capacity
cout << nums.size() << endl;      // 4
cout << nums.capacity() << endl;  // May be >= size

// Iterate
for (int num : nums) {
    cout << num << endl;
}

for (int i = 0; i < nums.size(); i++) {
    cout << nums[i] << endl;
}

// Modify
nums[0] = 100;
nums.at(1) = 200;

// Clear all
nums.clear();
```

### C-Style Strings (Character Arrays)

```cpp
char str[] = "Hello";     // Null-terminated array
cout << str << endl;      // Hello
cout << strlen(str) << endl;  // 5 (length)

// Concatenation
char s1[] = "Hello";
char s2[] = "World";
strcat(s1, s2);           // s1 becomes "HelloWorld"

// Problem: Fixed size, no bounds checking, unsafe
```

### C++ Strings (Recommended)

```cpp
#include <string>

string name = "Alice";
string greeting = "Hello " + name;  // Concatenation

// Properties
cout << name.length() << endl;      // 5
cout << name.size() << endl;        // Same as length()
cout << name[0] << endl;            // 'A'

// Methods
cout << name.substr(0, 3) << endl;  // "Ali" (position, length)
cout << name.find("ice") << endl;   // 2 (position)
cout << name.find("xyz") << endl;   // string::npos (not found)

// Comparison
if (name == "Alice") { ... }
if (name != "Bob") { ... }
if (name < "Zoe") { ... }  // Lexicographic comparison

// Modification
name += "!";              // Append
name[0] = 'a';            // Change character
name.replace(0, 1, "A");  // Replace substring

// Conversion
string s = "123";
int num = stoi(s);        // String to int
double d = stod(s);       // String to double
s = to_string(42);        // Int to string
```

---

## Pointers & Memory Management

### Pointers (Advanced!)

```cpp
int x = 10;
int* ptr = &x;    // & = address-of operator
                  // ptr holds the memory address of x

cout << x << endl;       // 10
cout << &x << endl;      // 0x7fff5fbff8ac (address)
cout << ptr << endl;     // 0x7fff5fbff8ac (same address)
cout << *ptr << endl;    // 10 (* = dereference operator)

// Modify through pointer
*ptr = 20;
cout << x << endl;       // 20 (changed!)

// Pointer to pointer
int** ptr_to_ptr = &ptr;
cout << **ptr_to_ptr << endl;  // 20
```

### Dynamic Memory Allocation

```cpp
// Allocate on heap (manual memory management)
int* num = new int;       // Allocate 1 int
*num = 42;
delete num;               // Free memory (must do!)
num = nullptr;            // Good practice

// Dynamic array
int* arr = new int[5];
arr[0] = 100;
arr[1] = 200;
delete[] arr;             // Note: [] for arrays
arr = nullptr;

// What happens if you forget delete?
// Memory leak: memory not freed, unavailable to program
```

### Problems with Raw Pointers
- Easy to forget `delete` → memory leak
- Can have dangling pointers (delete then use)
- No automatic cleanup
- Not exception-safe

### Smart Pointers (C++11+, Recommended)

```cpp
#include <memory>

// unique_ptr: single owner
unique_ptr<int> p1(new int(42));
cout << *p1 << endl;
// Automatically deleted when p1 goes out of scope

// shared_ptr: multiple owners
shared_ptr<int> p2(new int(42));
shared_ptr<int> p3 = p2;  // Both own the same object
// Deleted when last owner goes out of scope

// Use make_unique / make_shared (preferred)
auto p4 = make_unique<int>(42);
auto p5 = make_shared<int>(42);
```

**Memory Layout:**
```
Stack (automatic cleanup)
└─ Local variables
└─ Function parameters
└─ Pointers themselves (not what they point to)

Heap (manual cleanup needed)
└─ Objects created with new
└─ Data structures
└─ Can be large
```

---

## Object-Oriented Programming

### Classes

```cpp
class Person {
private:
    // Private members (only accessible within class)
    string name;
    int age;
    
public:
    // Public members (accessible from outside)
    
    // Constructor (initializes object)
    Person(string n, int a) {
        name = n;
        age = a;
    }
    
    // Method
    void print_info() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    // Getter
    string get_name() const {
        return name;  // const = doesn't modify object
    }
    
    // Setter
    void set_age(int new_age) {
        if (new_age > 0) {
            age = new_age;
        }
    }
};

// Usage
Person p("Alice", 25);
p.print_info();
cout << p.get_name() << endl;
p.set_age(26);
```

### Access Modifiers

```cpp
class Example {
public:
    // Accessible from anywhere
    int public_var;
    
protected:
    // Accessible in derived classes and self
    int protected_var;
    
private:
    // Accessible only within this class
    int private_var;
};
```

### Constructor & Destructor

```cpp
class MyClass {
private:
    int* data;
    
public:
    // Constructor (called when object created)
    MyClass() {
        data = new int[100];
        cout << "Object created" << endl;
    }
    
    // Destructor (called when object destroyed)
    ~MyClass() {
        delete[] data;
        cout << "Object destroyed" << endl;
    }
};

MyClass obj;  // Constructor called
// ...
// Destructor called when obj goes out of scope
```

### Member Initializer List (Preferred)

```cpp
class Rectangle {
private:
    double width, height;
    
public:
    // Member initializer list (more efficient)
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() const {
        return width * height;
    }
};
```

---

## Inheritance & Polymorphism

### Inheritance

```cpp
// Base class
class Animal {
public:
    Animal(string n) : name(n) {}
    
    void eat() {
        cout << name << " is eating" << endl;
    }
    
protected:
    string name;
};

// Derived class (inherits from Animal)
class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}  // Call parent constructor
    
    void bark() {
        cout << name << " barks: Woof!" << endl;
    }
};

// Usage
Dog d("Buddy");
d.eat();   // Inherited method
d.bark();  // Own method
```

### Virtual Functions & Polymorphism

```cpp
class Animal {
public:
    virtual void speak() {  // virtual = can be overridden
        cout << "Generic sound" << endl;
    }
    
    virtual ~Animal() {}  // Virtual destructor (important!)
};

class Dog : public Animal {
public:
    void speak() override {  // override (C++11) is good practice
        cout << "Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "Meow!" << endl;
    }
};

// Polymorphism: same interface, different behavior
void animal_sound(Animal* a) {
    a->speak();  // Calls appropriate version
}

Dog d;
Cat c;
animal_sound(&d);  // "Woof!"
animal_sound(&c);  // "Meow!"
```

---

## Standard Library (STL)

### Vector

```cpp
#include <vector>

vector<int> v = {1, 2, 3};
v.push_back(4);
v.insert(v.begin() + 2, 99);
v.erase(v.begin() + 1);

// Iteration
for (int x : v) cout << x << " ";
```

### String

```cpp
#include <string>

string s = "Hello";
s += " World";
cout << s.length() << endl;
cout << s.substr(0, 5) << endl;
```

### Map (Dictionary)

```cpp
#include <map>

map<string, int> ages;
ages["Alice"] = 25;
ages["Bob"] = 30;

for (auto& p : ages) {
    cout << p.first << ": " << p.second << endl;
}

if (ages.find("Alice") != ages.end()) {
    cout << "Alice found" << endl;
}
```

### Set (Unique Values)

```cpp
#include <set>

set<int> unique_nums = {1, 2, 3, 2, 1};
// {1, 2, 3} - duplicates removed, sorted

for (int n : unique_nums) cout << n << " ";
```

### Queue & Stack

```cpp
#include <queue>
#include <stack>

queue<int> q;
q.push(1);
q.push(2);
cout << q.front() << endl;  // 1
q.pop();

stack<int> s;
s.push(1);
s.push(2);
cout << s.top() << endl;    // 2
s.pop();
```

---

## File I/O

### Reading & Writing Text

```cpp
#include <fstream>

// Writing
ofstream out("file.txt");
out << "Line 1\n";
out << "Line 2\n";
out.close();

// Reading
ifstream in("file.txt");
string line;
while (getline(in, line)) {
    cout << line << endl;
}
in.close();

// Check if file opened
if (!in.is_open()) {
    cerr << "ERROR: Cannot open file" << endl;
}
```

### Reading & Writing Binary

```cpp
// Write binary
ofstream bin("data.bin", ios::binary);
int values[] = {100, 200, 300};
bin.write((char*)values, sizeof(values));
bin.close();

// Read binary
ifstream bin_in("data.bin", ios::binary);
int read_vals[3];
bin_in.read((char*)read_vals, sizeof(read_vals));
bin_in.close();
```

---

## Error Handling

### Assertions (for debugging)

```cpp
#include <cassert>

int x = 10;
assert(x > 0);  // Program terminates if false
assert(x < 20);
```

### Exceptions

```cpp
try {
    int x = 10;
    if (x > 5) {
        throw runtime_error("x is too large");
    }
}
catch (const runtime_error& e) {
    cout << "Error: " << e.what() << endl;
}
catch (const exception& e) {
    cout << "General error: " << e.what() << endl;
}
catch (...) {
    cout << "Unknown error" << endl;
}

// Standard exceptions:
// - logic_error, runtime_error
// - invalid_argument, out_of_range
// - overflow_error, underflow_error
```

---

## Best Practices

### 1. Use const for Read-Only Data
```cpp
const int MAX = 100;
const double PI = 3.14159;

void print_info(const string& name) {
    cout << name << endl;  // Cannot modify name
}
```

### 2. Prefer References Over Pointers
```cpp
void increment(int& x) {  // Reference
    x++;
}

void process(const vector<int>& data) {  // Reference to const
    // Can read but not modify
}
```

### 3. Use Smart Pointers, Not Raw new/delete
```cpp
auto ptr = make_unique<MyClass>();
// Auto cleanup when ptr goes out of scope
```

### 4. Avoid Global Variables
```cpp
// Bad:
int global_count = 0;

// Better: Pass as parameter or use class member
void increment(int& count) {
    count++;
}
```

### 5. Initialize Variables
```cpp
int x = 0;              // Always initialize
string name = "";
bool flag = false;
```

### 6. Use Meaningful Names
```cpp
// Bad:
int x, y, z;

// Good:
int age, salary, count;
```

### 7. Follow RAII Pattern
```cpp
// Resources acquired in constructor, released in destructor
class FileHandler {
private:
    ifstream file;
    
public:
    FileHandler(const string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open");
        }
    }
    
    ~FileHandler() {
        if (file.is_open()) {
            file.close();
        }
    }
};
```

---

## Quick Reference

### Operators

```cpp
// Arithmetic
+, -, *, /, %

// Comparison
==, !=, <, >, <=, >=

// Logical
&&, ||, !

// Assignment
=, +=, -=, *=, /=

// Increment/Decrement
++, --
```

### Common Functions

```cpp
// String
str.length(), str.size(), str.substr(), str.find()

// Vector
v.size(), v.push_back(), v.pop_back(), v.at()

// Math
abs(), sqrt(), pow(), sin(), cos()

// Type conversion
to_string(), stoi(), stod()
```

### Common Headers

```cpp
#include <iostream>      // Input/output
#include <string>        // std::string
#include <vector>        // std::vector
#include <map>           // std::map
#include <fstream>       // File I/O
#include <cmath>         // Math functions
#include <memory>        // Smart pointers
#include <algorithm>     // STL algorithms
```

---

## Learning Path

### Level 1: Foundations (Weeks 1-2)
- [ ] Basics, syntax, variables
- [ ] Data types
- [ ] Control structures
- [ ] Functions
- [ ] Arrays and vectors

### Level 2: Intermediate (Weeks 3-4)
- [ ] Pointers
- [ ] Dynamic memory
- [ ] Classes and objects
- [ ] Constructors/destructors
- [ ] Basic I/O

### Level 3: Advanced (Weeks 5-6)
- [ ] Inheritance
- [ ] Polymorphism
- [ ] STL containers
- [ ] Exception handling
- [ ] Smart pointers

### Level 4: Expert (Weeks 7+)
- [ ] Template programming
- [ ] Advanced STL
- [ ] Design patterns
- [ ] Multi-threading
- [ ] Performance optimization

---

## Resources

- **cppreference.com** - Excellent language reference
- **Cplusplus.com** - Tutorials and reference
- **Scott Meyers "Effective C++"** - Best practices
- **Bjarne Stroustrup's C++ Primer** - Comprehensive guide
- **Compiler**: g++, clang++, MSVC++

---

## Summary

C++ is a powerful language that gives you control and speed. Key takeaways:

✓ Learn pointers thoroughly - they're fundamental  
✓ Use objects to organize code (classes)  
✓ Use STL (vector, string, map) instead of raw arrays/pointers  
✓ Prefer const and references for efficiency  
✓ Use smart pointers for automatic memory management  
✓ Follow RAII pattern for resource safety  
✓ Practice writing small programs to understand concepts  

Start simple, master basics, then gradually explore advanced topics!
