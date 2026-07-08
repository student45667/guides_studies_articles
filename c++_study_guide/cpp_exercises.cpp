// ============================================================================
// C++ PRACTICAL EXERCISES - Learn by Doing
// ============================================================================
// Difficulty levels: Beginner (B), Intermediate (I), Advanced (A)
// Try solving each exercise before looking at the solution!
// ============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

// ============================================================================
// SECTION 1: BASICS & VARIABLES (Beginner)
// ============================================================================

/*
EXERCISE 1.1 [B]: Temperature Conversion
Write a program that converts Fahrenheit to Celsius using the formula: C = (F - 32) * 5/9
- Input: temperature in Fahrenheit
- Output: temperature in Celsius with 2 decimal places
*/

void exercise_1_1() {
    cout << "\n--- EXERCISE 1.1: Temperature Conversion ---" << endl;
    
    double fahrenheit = 98.6;
    double celsius = (fahrenheit - 32) * 5.0 / 9.0;
    
    cout << "F: " << fahrenheit << " = C: " << celsius << endl;
}

/*
EXERCISE 1.2 [B]: Circle Area Calculator
Given a radius, calculate the area of a circle (area = π * r²)
*/

void exercise_1_2() {
    cout << "\n--- EXERCISE 1.2: Circle Area ---" << endl;
    
    const double PI = 3.14159265;
    double radius = 5.0;
    double area = PI * radius * radius;
    
    cout << "Radius: " << radius << endl;
    cout << "Area: " << area << endl;
}

/*
EXERCISE 1.3 [B]: Swap Two Variables
Write a program that swaps the values of two variables without using a temporary variable
Hint: Use x = x + y; y = x - y; x = x - y;
*/

void exercise_1_3() {
    cout << "\n--- EXERCISE 1.3: Swap Variables ---" << endl;
    
    int x = 5, y = 10;
    cout << "Before: x = " << x << ", y = " << y << endl;
    
    x = x + y;
    y = x - y;
    x = x - y;
    
    cout << "After: x = " << x << ", y = " << y << endl;
}

// ============================================================================
// SECTION 2: CONTROL STRUCTURES (Beginner/Intermediate)
// ============================================================================

/*
EXERCISE 2.1 [B]: Check Odd/Even
Given a number, determine if it's odd or even
*/

void exercise_2_1() {
    cout << "\n--- EXERCISE 2.1: Odd/Even Check ---" << endl;
    
    int num = 17;
    
    if (num % 2 == 0) {
        cout << num << " is even" << endl;
    } else {
        cout << num << " is odd" << endl;
    }
}

/*
EXERCISE 2.2 [B]: Grade Classifier
Convert a numeric score (0-100) to a letter grade (A-F)
- 90-100: A
- 80-89: B
- 70-79: C
- 60-69: D
- Below 60: F
*/

void exercise_2_2() {
    cout << "\n--- EXERCISE 2.2: Grade Classifier ---" << endl;
    
    int score = 85;
    char grade;
    
    if (score >= 90) grade = 'A';
    else if (score >= 80) grade = 'B';
    else if (score >= 70) grade = 'C';
    else if (score >= 60) grade = 'D';
    else grade = 'F';
    
    cout << "Score: " << score << " -> Grade: " << grade << endl;
}

/*
EXERCISE 2.3 [I]: FizzBuzz
Print numbers 1-100, but:
- Print "Fizz" if divisible by 3
- Print "Buzz" if divisible by 5
- Print "FizzBuzz" if divisible by both
- Otherwise print the number
*/

void exercise_2_3() {
    cout << "\n--- EXERCISE 2.3: FizzBuzz (first 30) ---" << endl;
    
    for (int i = 1; i <= 30; i++) {
        if (i % 15 == 0) {
            cout << "FizzBuzz ";
        } else if (i % 3 == 0) {
            cout << "Fizz ";
        } else if (i % 5 == 0) {
            cout << "Buzz ";
        } else {
            cout << i << " ";
        }
    }
    cout << endl;
}

/*
EXERCISE 2.4 [I]: Prime Number Checker
Determine if a given number is prime
A prime number is only divisible by 1 and itself
*/

void exercise_2_4() {
    cout << "\n--- EXERCISE 2.4: Prime Number Checker ---" << endl;
    
    int num = 17;
    bool is_prime = true;
    
    if (num < 2) {
        is_prime = false;
    } else {
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = false;
                break;
            }
        }
    }
    
    cout << num << " is " << (is_prime ? "prime" : "not prime") << endl;
}

// ============================================================================
// SECTION 3: ARRAYS & VECTORS (Intermediate)
// ============================================================================

/*
EXERCISE 3.1 [I]: Find Maximum in Array
Given an array of numbers, find the maximum value
*/

void exercise_3_1() {
    cout << "\n--- EXERCISE 3.1: Find Maximum ---" << endl;
    
    vector<int> numbers = {45, 23, 78, 12, 89, 34};
    
    int max_val = numbers[0];
    for (int num : numbers) {
        if (num > max_val) {
            max_val = num;
        }
    }
    
    cout << "Numbers: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    cout << "Maximum: " << max_val << endl;
}

/*
EXERCISE 3.2 [I]: Sum and Average
Calculate the sum and average of array elements
*/

void exercise_3_2() {
    cout << "\n--- EXERCISE 3.2: Sum and Average ---" << endl;
    
    vector<int> numbers = {10, 20, 30, 40, 50};
    
    int sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    
    double average = (double)sum / numbers.size();
    
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
}

/*
EXERCISE 3.3 [I]: Reverse an Array
Reverse the order of elements in an array
*/

void exercise_3_3() {
    cout << "\n--- EXERCISE 3.3: Reverse Array ---" << endl;
    
    vector<int> arr = {1, 2, 3, 4, 5};
    
    cout << "Original: ";
    for (int n : arr) cout << n << " ";
    cout << endl;
    
    reverse(arr.begin(), arr.end());
    
    cout << "Reversed: ";
    for (int n : arr) cout << n << " ";
    cout << endl;
}

/*
EXERCISE 3.4 [I]: Count Occurrences
Count how many times a specific value appears in an array
*/

void exercise_3_4() {
    cout << "\n--- EXERCISE 3.4: Count Occurrences ---" << endl;
    
    vector<int> numbers = {1, 2, 3, 2, 4, 2, 5};
    int target = 2;
    int count = 0;
    
    for (int num : numbers) {
        if (num == target) {
            count++;
        }
    }
    
    cout << "Value " << target << " appears " << count << " times" << endl;
}

// ============================================================================
// SECTION 4: STRINGS (Intermediate)
// ============================================================================

/*
EXERCISE 4.1 [I]: Palindrome Checker
Determine if a string is a palindrome (reads same forwards and backwards)
Example: "racecar" is a palindrome
*/

void exercise_4_1() {
    cout << "\n--- EXERCISE 4.1: Palindrome Checker ---" << endl;
    
    string word = "racecar";
    string reversed = word;
    reverse(reversed.begin(), reversed.end());
    
    bool is_palindrome = (word == reversed);
    cout << word << " is " << (is_palindrome ? "a palindrome" : "not a palindrome") << endl;
}

/*
EXERCISE 4.2 [I]: String Length Without Using .length()
Implement your own function to count string characters
*/

void exercise_4_2() {
    cout << "\n--- EXERCISE 4.2: String Length (Manual) ---" << endl;
    
    string text = "Hello";
    int length = 0;
    
    for (char c : text) {
        length++;
    }
    
    cout << "Text: " << text << endl;
    cout << "Length: " << length << endl;
}

/*
EXERCISE 4.3 [I]: Count Vowels
Count the number of vowels (a, e, i, o, u) in a string
*/

void exercise_4_3() {
    cout << "\n--- EXERCISE 4.3: Count Vowels ---" << endl;
    
    string text = "Hello World";
    int vowel_count = 0;
    
    for (char c : text) {
        char lower = tolower(c);
        if (lower == 'a' || lower == 'e' || lower == 'i' || 
            lower == 'o' || lower == 'u') {
            vowel_count++;
        }
    }
    
    cout << "Text: " << text << endl;
    cout << "Vowel count: " << vowel_count << endl;
}

// ============================================================================
// SECTION 5: FUNCTIONS (Intermediate)
// ============================================================================

/*
EXERCISE 5.1 [I]: Factorial Function
Write a function to calculate factorial of n
Factorial(n) = n * (n-1) * (n-2) * ... * 1
Example: 5! = 120
*/

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

void exercise_5_1() {
    cout << "\n--- EXERCISE 5.1: Factorial ---" << endl;
    
    for (int i = 1; i <= 5; i++) {
        cout << i << "! = " << factorial(i) << endl;
    }
}

/*
EXERCISE 5.2 [I]: Power Function
Write a function to calculate x raised to power n
*/

int power(int x, int n) {
    int result = 1;
    for (int i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}

void exercise_5_2() {
    cout << "\n--- EXERCISE 5.2: Power Function ---" << endl;
    
    cout << "2^5 = " << power(2, 5) << endl;
    cout << "3^3 = " << power(3, 3) << endl;
}

/*
EXERCISE 5.3 [I]: GCD (Greatest Common Divisor)
Write a function to find GCD of two numbers
Hint: Use Euclidean algorithm
*/

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void exercise_5_3() {
    cout << "\n--- EXERCISE 5.3: GCD ---" << endl;
    
    cout << "GCD(48, 18) = " << gcd(48, 18) << endl;
    cout << "GCD(100, 50) = " << gcd(100, 50) << endl;
}

// ============================================================================
// SECTION 6: CLASSES (Intermediate/Advanced)
// ============================================================================

/*
EXERCISE 6.1 [I]: Circle Class
Create a Circle class with:
- Constructor to set radius
- Method to calculate area
- Method to calculate circumference
*/

class Circle {
private:
    double radius;
    const double PI = 3.14159265;
    
public:
    Circle(double r) : radius(r) {}
    
    double area() {
        return PI * radius * radius;
    }
    
    double circumference() {
        return 2 * PI * radius;
    }
};

void exercise_6_1() {
    cout << "\n--- EXERCISE 6.1: Circle Class ---" << endl;
    
    Circle c(5.0);
    cout << "Radius: 5.0" << endl;
    cout << "Area: " << c.area() << endl;
    cout << "Circumference: " << c.circumference() << endl;
}

/*
EXERCISE 6.2 [I]: Counter Class
Create a Counter class that:
- Increments a count
- Decrements a count
- Resets to zero
- Gets current value
*/

class Counter {
private:
    int count;
    
public:
    Counter() : count(0) {}
    
    void increment() { count++; }
    void decrement() { count--; }
    void reset() { count = 0; }
    int get_count() const { return count; }
};

void exercise_6_2() {
    cout << "\n--- EXERCISE 6.2: Counter Class ---" << endl;
    
    Counter c;
    cout << "Initial: " << c.get_count() << endl;
    
    c.increment();
    c.increment();
    c.increment();
    cout << "After 3 increments: " << c.get_count() << endl;
    
    c.decrement();
    cout << "After 1 decrement: " << c.get_count() << endl;
    
    c.reset();
    cout << "After reset: " << c.get_count() << endl;
}

/*
EXERCISE 6.3 [A]: Student Class
Create a Student class with:
- Name, ID, grades
- Method to add grade
- Method to calculate average
- Method to display info
*/

class Student {
private:
    string name;
    int id;
    vector<double> grades;
    
public:
    Student(string n, int i) : name(n), id(i) {}
    
    void add_grade(double grade) {
        grades.push_back(grade);
    }
    
    double get_average() {
        if (grades.empty()) return 0.0;
        double sum = 0;
        for (double g : grades) sum += g;
        return sum / grades.size();
    }
    
    void display_info() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Average: " << get_average() << endl;
    }
};

void exercise_6_3() {
    cout << "\n--- EXERCISE 6.3: Student Class ---" << endl;
    
    Student s("Alice", 101);
    s.add_grade(85);
    s.add_grade(90);
    s.add_grade(78);
    s.display_info();
}

// ============================================================================
// SECTION 7: ADVANCED (Advanced)
// ============================================================================

/*
EXERCISE 7.1 [A]: Fibonacci Sequence
Generate Fibonacci sequence up to n numbers
Fibonacci: 0, 1, 1, 2, 3, 5, 8, 13...
*/

void exercise_7_1() {
    cout << "\n--- EXERCISE 7.1: Fibonacci Sequence ---" << endl;
    
    int n = 10;
    vector<int> fib(n);
    
    fib[0] = 0;
    fib[1] = 1;
    
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    cout << "First " << n << " Fibonacci numbers: ";
    for (int f : fib) cout << f << " ";
    cout << endl;
}

/*
EXERCISE 7.2 [A]: Sorting Algorithm (Bubble Sort)
Implement bubble sort to sort an array in ascending order
*/

void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void exercise_7_2() {
    cout << "\n--- EXERCISE 7.2: Bubble Sort ---" << endl;
    
    vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Original: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    bubble_sort(numbers);
    
    cout << "Sorted: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
}

/*
EXERCISE 7.3 [A]: Frequency Map
Create a map of word frequencies in a string
*/

void exercise_7_3() {
    cout << "\n--- EXERCISE 7.3: Word Frequency ---" << endl;
    
    string text = "hello world hello cpp hello";
    map<string, int> freq;
    
    stringstream ss(text);
    string word;
    while (ss >> word) {
        freq[word]++;
    }
    
    cout << "Word frequencies:" << endl;
    for (auto& p : freq) {
        cout << "  " << p.first << ": " << p.second << endl;
    }
}

// ============================================================================
// MAIN: RUN ALL EXERCISES
// ============================================================================

int main() {
    cout << "========================================" << endl;
    cout << "C++ PRACTICAL EXERCISES" << endl;
    cout << "========================================" << endl;
    
    // BEGINNER EXERCISES
    exercise_1_1();
    exercise_1_2();
    exercise_1_3();
    
    // CONTROL STRUCTURES
    exercise_2_1();
    exercise_2_2();
    exercise_2_3();
    exercise_2_4();
    
    // ARRAYS & VECTORS
    exercise_3_1();
    exercise_3_2();
    exercise_3_3();
    exercise_3_4();
    
    // STRINGS
    exercise_4_1();
    exercise_4_2();
    exercise_4_3();
    
    // FUNCTIONS
    exercise_5_1();
    exercise_5_2();
    exercise_5_3();
    
    // CLASSES
    exercise_6_1();
    exercise_6_2();
    exercise_6_3();
    
    // ADVANCED
    exercise_7_1();
    exercise_7_2();
    exercise_7_3();
    
    cout << "\n========================================" << endl;
    cout << "All exercises completed!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}

// ============================================================================
// COMPILATION & EXECUTION
// ============================================================================

/*

COMPILE:
  g++ -std=c++17 -o exercises cpp_exercises.cpp

RUN:
  ./exercises

============================================================================

CHALLENGE EXERCISES (Try these on your own!)

1. [I] Write a function to check if a string is a pangram
   (contains all 26 letters of the alphabet)

2. [I] Implement a function to convert decimal to binary

3. [A] Create a Matrix class with methods for:
   - Addition
   - Multiplication
   - Transpose
   - Determinant

4. [A] Implement a simple calculator using classes for each operation

5. [A] Create a Linked List class with insert, delete, search methods

6. [A] Write a file I/O program that:
   - Reads a text file
   - Counts words, lines, characters
   - Writes statistics to output file

============================================================================

TIPS FOR SUCCESS

1. Start with simple exercises
2. Don't look at solution until you try!
3. Test your code with different inputs
4. Use cout to debug: print intermediate values
5. Read error messages carefully
6. Try to optimize after getting working solution
7. Challenge yourself with bonus problems

============================================================================
*/
