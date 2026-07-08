// ============================================================================
// C++ COMPREHENSIVE STUDY GUIDE
// ============================================================================
// A practical guide from basics to advanced concepts
// Perfect for engineers transitioning from C or Python
//
// Topics:
//   1. Basics & Syntax
//   2. Data Types & Variables
//   3. Control Structures
//   4. Functions
//   5. Arrays & Strings
//   6. Pointers & Memory Management
//   7. Object-Oriented Programming (Classes)
//   8. Inheritance & Polymorphism
//   9. Standard Library (STL)
//  10. File I/O
//  11. Error Handling & Debugging
// ============================================================================

#include <iostream>      // Standard input/output
#include <fstream>       // File input/output
#include <string>        // std::string
#include <vector>        // std::vector (dynamic array)
#include <map>           // std::map (dictionary-like)
#include <cmath>         // Math functions
#include <iomanip>       // Output formatting
#include <cassert>       // Assertions for debugging

using namespace std;

// ============================================================================
// SECTION 1: BASICS & SYNTAX
// ============================================================================

/*
 * C++ is a compiled, statically-typed language that builds on C.
 * Key differences from Python:
 * - Must declare variable types
 * - No automatic memory management (you manage with new/delete or smart pointers)
 * - Faster execution (compiled, not interpreted)
 * - More control over hardware
 */

void example_1_basics() {
    cout << "\n=== 1. BASICS & SYNTAX ===" << endl;
    
    // Comment: single line (like Python #)
    /* Multi-line comment
       (like Python triple quotes) */
    
    // Variables must be declared with type
    int age = 25;
    float salary = 50000.50f;  // f = float literal
    double price = 99.99;       // double = 64-bit float (default)
    bool is_active = true;
    char grade = 'A';
    
    cout << "Age: " << age << endl;
    cout << "Salary: " << salary << endl;
    cout << "Is Active: " << is_active << endl;  // Prints "1" (true)
    cout << "Grade: " << grade << endl;
    
    // Type conversion (casting)
    int x = 10;
    double y = (double)x;  // C-style cast
    double z = static_cast<double>(x);  // C++ style (preferred)
    
    cout << "x = " << x << ", y (converted) = " << y << endl;
}

// ============================================================================
// SECTION 2: DATA TYPES & VARIABLES
// ============================================================================

void example_2_data_types() {
    cout << "\n=== 2. DATA TYPES & VARIABLES ===" << endl;
    
    // Integer types (size varies by platform)
    char c = 65;              // 8-bit: stores 'A' (ASCII value)
    short s = 1000;           // 16-bit signed
    int i = 100000;           // 32-bit signed (most common)
    long l = 100000L;         // 32 or 64-bit signed
    long long ll = 9223372036854775807LL;  // 64-bit signed
    
    unsigned int ui = 100000; // No negative values (0 to ~4.2B)
    
    // Floating point types
    float f = 3.14f;          // 32-bit, ~7 decimal digits precision
    double d = 3.141592653589793;  // 64-bit, ~15 decimal digits (preferred)
    
    // Boolean
    bool flag = true;
    
    // Size of types (varies by system)
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of double: " << sizeof(double) << " bytes" << endl;
    cout << "Size of bool: " << sizeof(bool) << " byte" << endl;
    
    // Constants (cannot be changed)
    const int MAX_USERS = 100;
    const double PI = 3.14159265;
    
    cout << "MAX_USERS = " << MAX_USERS << endl;
    cout << "PI = " << PI << endl;
    
    // Scope: variables exist only in their block
    {
        int local_var = 50;  // Only exists in this block
        cout << "Local var: " << local_var << endl;
    }
    // cout << local_var << endl;  // ERROR: local_var not defined
}

// ============================================================================
// SECTION 3: CONTROL STRUCTURES
// ============================================================================

void example_3_control() {
    cout << "\n=== 3. CONTROL STRUCTURES ===" << endl;
    
    // ================================================================
    // IF / ELSE IF / ELSE (same as C/Python)
    // ================================================================
    
    int score = 85;
    
    if (score >= 90) {
        cout << "Grade: A" << endl;
    } else if (score >= 80) {
        cout << "Grade: B" << endl;
    } else if (score >= 70) {
        cout << "Grade: C" << endl;
    } else {
        cout << "Grade: F" << endl;
    }
    
    // Ternary operator (shorthand if/else)
    string status = (score >= 80) ? "Pass" : "Fail";
    cout << "Status: " << status << endl;
    
    // ================================================================
    // SWITCH (for multiple specific values)
    // ================================================================
    
    char choice = 'B';
    
    switch (choice) {
        case 'A':
            cout << "You chose A" << endl;
            break;  // Jump out of switch
        case 'B':
            cout << "You chose B" << endl;
            break;
        case 'C':
            cout << "You chose C" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
    }
    
    // ================================================================
    // LOOPS
    // ================================================================
    
    // FOR loop (traditional)
    cout << "\nFor loop (0-4):" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    // WHILE loop
    cout << "While loop:" << endl;
    int count = 0;
    while (count < 3) {
        cout << "Count: " << count << endl;
        count++;
    }
    
    // DO-WHILE loop (runs at least once)
    cout << "Do-while loop:" << endl;
    int n = 0;
    do {
        cout << "n = " << n << endl;
        n++;
    } while (n < 2);
    
    // FOR loop with range (C++11 and later)
    vector<int> nums = {10, 20, 30, 40};
    cout << "Range-based for loop:" << endl;
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    
    // BREAK and CONTINUE
    cout << "Loop with break/continue:" << endl;
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;  // Skip iteration
        if (i == 4) break;     // Exit loop
        cout << i << " ";
    }
    cout << endl;
}

// ============================================================================
// SECTION 4: FUNCTIONS
// ============================================================================

// Function declaration (prototype) - optional if defined before use
int add(int a, int b);

void example_4_functions() {
    cout << "\n=== 4. FUNCTIONS ===" << endl;
    
    // Calling functions
    int result = add(5, 3);
    cout << "5 + 3 = " << result << endl;
    
    // Function with no return value
    print_line();
    
    // Function with default parameters
    greet("Alice", "Hello");
    greet("Bob");  // Uses default message
    
    // Function with multiple return values (using reference or struct)
    int quotient, remainder;
    divide_with_remainder(17, 5, quotient, remainder);
    cout << "17 / 5 = " << quotient << " remainder " << remainder << endl;
}

// Function implementations
int add(int a, int b) {
    return a + b;
}

void print_line() {
    cout << "---" << endl;
}

void greet(string name, string message = "Hi") {
    cout << message << " " << name << endl;
}

void divide_with_remainder(int a, int b, int &q, int &r) {
    // & means pass by reference (changes affect original variable)
    q = a / b;
    r = a % b;
}

// ============================================================================
// SECTION 5: ARRAYS & STRINGS
// ============================================================================

void example_5_arrays_strings() {
    cout << "\n=== 5. ARRAYS & STRINGS ===" << endl;
    
    // ================================================================
    // C-STYLE ARRAYS (fixed size, unsafe)
    // ================================================================
    
    int arr[5] = {10, 20, 30, 40, 50};  // Fixed size at compile time
    
    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 2D array
    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    cout << "Matrix[0][1] = " << matrix[0][1] << endl;
    
    // ================================================================
    // C++ VECTOR (dynamic array, safe, preferred)
    // ================================================================
    
    vector<int> vec = {100, 200, 300};
    vec.push_back(400);  // Add element
    vec.pop_back();      // Remove last element
    
    cout << "Vector size: " << vec.size() << endl;
    cout << "Vector: ";
    for (int v : vec) {
        cout << v << " ";
    }
    cout << endl;
    
    // ================================================================
    // C-STYLE STRINGS (character arrays, unsafe)
    // ================================================================
    
    char cstring[] = "Hello";  // String stored as char array
    cout << "C-string: " << cstring << endl;
    cout << "Length: " << strlen(cstring) << endl;
    
    // ================================================================
    // C++ STRINGS (safe, recommended)
    // ================================================================
    
    string name = "Alice";
    string full_name = name + " Smith";  // Concatenation
    
    cout << "Name: " << name << endl;
    cout << "Full name: " << full_name << endl;
    cout << "Length: " << full_name.length() << endl;
    cout << "First char: " << full_name[0] << endl;
    
    // String methods
    string text = "hello world";
    cout << "Uppercase: " << (text[0] = 'H', text) << endl;
    cout << "Substring: " << text.substr(0, 5) << endl;  // "hello"
    cout << "Find 'world': " << text.find("world") << endl;  // Position 6
    
    // String comparison
    if (name == "Alice") {
        cout << "Name is Alice" << endl;
    }
}

// ============================================================================
// SECTION 6: POINTERS & MEMORY MANAGEMENT
// ============================================================================

void example_6_pointers() {
    cout << "\n=== 6. POINTERS & MEMORY MANAGEMENT ===" << endl;
    
    // ================================================================
    // POINTERS (advanced concept)
    // ================================================================
    
    int x = 10;
    int* ptr = &x;  // & = address-of operator
                    // ptr points to x
    
    cout << "x = " << x << endl;
    cout << "Address of x: " << &x << endl;
    cout << "Pointer value: " << ptr << endl;
    cout << "Dereference pointer: " << *ptr << endl;  // * = dereference
    
    // Modify through pointer
    *ptr = 20;
    cout << "x after pointer change: " << x << endl;
    
    // ================================================================
    // DYNAMIC MEMORY ALLOCATION (new/delete)
    // ================================================================
    
    // Allocate memory on heap (must manually delete)
    int* num = new int;
    *num = 42;
    cout << "Dynamic int: " << *num << endl;
    delete num;  // Free memory
    num = nullptr;  // Good practice: set to nullptr after delete
    
    // Dynamic array
    int* arr = new int[5];
    arr[0] = 100;
    arr[1] = 200;
    cout << "Dynamic array: " << arr[0] << ", " << arr[1] << endl;
    delete[] arr;  // Note: [] for arrays
    arr = nullptr;
    
    // ================================================================
    // SMART POINTERS (automatic cleanup, C++11+)
    // Recommended over raw new/delete
    // ================================================================
    
    // unique_ptr: single owner
    // shared_ptr: multiple owners
    // See Section 11 for details
    
    cout << "Pointer examples completed" << endl;
}

// ============================================================================
// SECTION 7: OBJECT-ORIENTED PROGRAMMING - CLASSES
// ============================================================================

// Class definition
class BankAccount {
private:
    // Private members (only accessible within class)
    double balance;
    string account_number;
    
public:
    // Constructor (initializes object)
    BankAccount(string acct_num, double initial_balance) {
        account_number = acct_num;
        balance = initial_balance;
        cout << "Account created: " << account_number << endl;
    }
    
    // Destructor (cleanup when object deleted)
    ~BankAccount() {
        cout << "Account destroyed: " << account_number << endl;
    }
    
    // Methods (functions in a class)
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        }
    }
    
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
        } else {
            cout << "Insufficient funds" << endl;
        }
    }
    
    // Getter method (const = doesn't modify object)
    double get_balance() const {
        return balance;
    }
    
    // Const method that returns string reference
    const string& get_account_number() const {
        return account_number;
    }
};

void example_7_classes() {
    cout << "\n=== 7. CLASSES & OBJECTS ===" << endl;
    
    // Create object on stack
    BankAccount account("ACC001", 1000.0);
    
    account.deposit(500);
    account.withdraw(200);
    cout << "Balance: $" << account.get_balance() << endl;
    
    // Create object on heap (must delete manually)
    BankAccount* acct2 = new BankAccount("ACC002", 500.0);
    acct2->deposit(100);  // -> for pointer member access
    cout << "Balance: $" << acct2->get_balance() << endl;
    delete acct2;  // Don't forget!
}

// ============================================================================
// SECTION 8: INHERITANCE & POLYMORPHISM
// ============================================================================

// Base class
class Animal {
protected:  // Protected: accessible in derived classes
    string name;
    
public:
    Animal(string n) : name(n) {}
    
    // Virtual function (can be overridden in derived classes)
    virtual void speak() {
        cout << name << " makes a sound" << endl;
    }
    
    virtual ~Animal() {}  // Virtual destructor (best practice)
};

// Derived class (inherits from Animal)
class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}  // Call parent constructor
    
    // Override parent method
    void speak() override {
        cout << name << " barks: Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    Cat(string n) : Animal(n) {}
    
    void speak() override {
        cout << name << " meows: Meow!" << endl;
    }
};

void example_8_inheritance() {
    cout << "\n=== 8. INHERITANCE & POLYMORPHISM ===" << endl;
    
    // Polymorphism: same interface, different behavior
    vector<Animal*> animals;
    
    animals.push_back(new Dog("Buddy"));
    animals.push_back(new Cat("Whiskers"));
    animals.push_back(new Animal("Generic"));
    
    cout << "Making animals speak:" << endl;
    for (Animal* animal : animals) {
        animal->speak();
    }
    
    // Clean up
    for (Animal* animal : animals) {
        delete animal;
    }
    animals.clear();
}

// ============================================================================
// SECTION 9: STANDARD LIBRARY (STL)
// ============================================================================

void example_9_stl() {
    cout << "\n=== 9. STANDARD LIBRARY (STL) ===" << endl;
    
    // ================================================================
    // VECTOR (dynamic array)
    // ================================================================
    
    vector<int> numbers = {1, 2, 3};
    numbers.push_back(4);
    numbers.insert(numbers.begin() + 2, 99);  // Insert at position 2
    
    cout << "Vector: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // ================================================================
    // STRING
    // ================================================================
    
    string str = "Hello";
    str += " World";
    cout << "String: " << str << endl;
    
    // ================================================================
    // MAP (key-value pairs, like Python dict)
    // ================================================================
    
    map<string, int> ages;
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;
    
    cout << "Ages map:" << endl;
    for (auto& pair : ages) {
        cout << "  " << pair.first << ": " << pair.second << endl;
    }
    
    cout << "Alice's age: " << ages["Alice"] << endl;
    
    // ================================================================
    // Other useful containers
    // ================================================================
    
    // List (linked list)
    // Deque (double-ended queue)
    // Set (unique values)
    // Stack, Queue
}

// ============================================================================
// SECTION 10: FILE I/O
// ============================================================================

void example_10_file_io() {
    cout << "\n=== 10. FILE I/O ===" << endl;
    
    // ================================================================
    // WRITING TO FILE
    // ================================================================
    
    ofstream outfile("example.txt");  // Open for writing
    
    if (!outfile.is_open()) {
        cerr << "ERROR: Could not open file for writing" << endl;
        return;
    }
    
    outfile << "First line\n";
    outfile << "Second line\n";
    outfile << "Number: " << 42 << "\n";
    outfile.close();
    
    cout << "File written: example.txt" << endl;
    
    // ================================================================
    // READING FROM FILE
    // ================================================================
    
    ifstream infile("example.txt");  // Open for reading
    
    if (!infile.is_open()) {
        cerr << "ERROR: Could not open file for reading" << endl;
        return;
    }
    
    string line;
    cout << "File contents:" << endl;
    while (getline(infile, line)) {
        cout << "  " << line << endl;
    }
    infile.close();
    
    // ================================================================
    // READING/WRITING BINARY
    // ================================================================
    
    // Writing binary data
    ofstream binfile("data.bin", ios::binary);
    int values[] = {100, 200, 300};
    binfile.write((char*)values, sizeof(values));
    binfile.close();
    
    // Reading binary data
    ifstream binread("data.bin", ios::binary);
    int read_values[3];
    binread.read((char*)read_values, sizeof(read_values));
    binread.close();
    
    cout << "Binary read: " << read_values[0] << ", " << read_values[1] << endl;
}

// ============================================================================
// SECTION 11: ERROR HANDLING & DEBUGGING
// ============================================================================

void example_11_error_handling() {
    cout << "\n=== 11. ERROR HANDLING & DEBUGGING ===" << endl;
    
    // ================================================================
    // ASSERTIONS (for debugging)
    // ================================================================
    
    int x = 10;
    assert(x > 0);  // Program terminates if false
    
    // ================================================================
    // EXCEPTIONS (try/catch)
    // ================================================================
    
    try {
        int result = 100 / 1;  // Normal division
        cout << "100 / 1 = " << result << endl;
        
        // Simulate error
        if (result == 100) {
            throw runtime_error("An error occurred!");  // Throw exception
        }
    }
    catch (const runtime_error& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown exception caught" << endl;
    }
    
    cout << "Program continues after exception" << endl;
    
    // ================================================================
    // DEBUGGING OUTPUTS
    // ================================================================
    
    #ifdef DEBUG
        cout << "DEBUG: This only prints if DEBUG is defined" << endl;
    #endif
    
    // Formatted output for debugging
    cout << "Debugging info:" << endl;
    cout << "  int size: " << sizeof(int) << " bytes" << endl;
    cout << "  pointer: " << &x << endl;
}

// ============================================================================
// SECTION 12: BEST PRACTICES & PATTERNS
// ============================================================================

// RAII Pattern (Resource Acquisition Is Initialization)
// Constructor acquires resource, destructor releases it

class FileWrapper {
private:
    ifstream file;
    
public:
    FileWrapper(const string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file: " + filename);
        }
    }
    
    ~FileWrapper() {
        if (file.is_open()) {
            file.close();
        }
    }
    
    string read_line() {
        string line;
        getline(file, line);
        return line;
    }
};

void example_12_best_practices() {
    cout << "\n=== 12. BEST PRACTICES ===" << endl;
    
    // Avoid raw pointers when possible
    // Use smart pointers: unique_ptr, shared_ptr
    
    // Avoid global variables
    // Use const for things that shouldn't change
    // Use references (&) instead of pointers when possible
    // Always initialize variables
    // Use meaningful variable names
    
    cout << "Best practices:" << endl;
    cout << "  - Use vector instead of raw arrays" << endl;
    cout << "  - Use string instead of char arrays" << endl;
    cout << "  - Use const for immutable data" << endl;
    cout << "  - Use references (&) for efficiency" << endl;
    cout << "  - Use exceptions for error handling" << endl;
    cout << "  - Follow RAII pattern" << endl;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    cout << "============================================" << endl;
    cout << "C++ COMPREHENSIVE STUDY GUIDE" << endl;
    cout << "============================================" << endl;
    
    // Run examples in order
    example_1_basics();
    example_2_data_types();
    example_3_control();
    example_4_functions();
    example_5_arrays_strings();
    example_6_pointers();
    example_7_classes();
    example_8_inheritance();
    example_9_stl();
    example_10_file_io();
    example_11_error_handling();
    example_12_best_practices();
    
    cout << "\n============================================" << endl;
    cout << "Study guide completed!" << endl;
    cout << "============================================" << endl;
    
    return 0;
}

// ============================================================================
// COMPILATION & EXECUTION
// ============================================================================

/*

COMPILE:
  g++ -std=c++17 -o cpp_guide cpp_study_guide.cpp

RUN:
  ./cpp_guide

COMPILATION FLAGS:
  -std=c++17       : Use C++17 standard (supports modern features)
  -Wall            : Enable all compiler warnings
  -Wextra          : Extra warnings
  -g               : Include debug symbols (for debugging with gdb)
  -O2              : Optimization level 2 (make code faster)

EXAMPLE:
  g++ -std=c++17 -Wall -g -o cpp_guide cpp_study_guide.cpp

============================================================================

QUICK REFERENCE TABLE

Category             | C++                    | Python
-------------------- |---------------------- |----------------------------
Variable declaration | int x = 10;           | x = 10
Type checking        | Static (compile time) | Dynamic (runtime)
Pointers             | int* ptr = &x;        | (reference system different)
Memory management    | new/delete or smart   | Automatic (garbage collection)
Classes              | class MyClass { ... } | class MyClass: ...
String type          | std::string           | str
Array type           | vector<int>           | list
Dictionary           | map<key, value>       | dict
Loop                 | for, while, do-while  | for, while
Function             | returnType func() {}  | def func():
Exception handling   | try/catch             | try/except

============================================================================

COMMON PATTERNS

1. Read input:
   int x;
   cin >> x;

2. Write output:
   cout << "Hello " << name << endl;

3. Create dynamic object:
   MyClass* obj = new MyClass();
   delete obj;

4. Iterate through vector:
   for (int v : vec) { ... }

5. Check if map has key:
   if (map.find(key) != map.end()) { ... }

6. Try-catch:
   try { ... }
   catch (const exception& e) { cout << e.what(); }

============================================================================

NEXT STEPS FOR LEARNING

1. Practice pointer manipulation
2. Learn about smart pointers (unique_ptr, shared_ptr)
3. Study template programming (generic classes)
4. Learn about STL algorithms (sort, find, etc.)
5. Understand move semantics and perfect forwarding
6. Study multi-threading
7. Explore design patterns (Singleton, Factory, etc.)
8. Learn about performance optimization

============================================================================
*/
