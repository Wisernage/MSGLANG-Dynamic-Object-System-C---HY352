
# MSGlang

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C++](https://img.shields.io/badge/language-C++-blue.svg)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
  - [Basic Concepts](#basic-concepts)
  - [Creating Objects](#creating-objects)
  - [Accessing and Modifying Properties](#accessing-and-modifying-properties)

## Introduction

**MSGlang** is a dynamic object system implemented in C++. It provides a flexible way to create and manipulate objects with properties, methods, and support for various data types. Inspired by scripting languages like JavaScript, MSGlang allows developers to define objects, handle dynamic typing, and perform operations seamlessly within C++.

## Features

- **Dynamic Typing:** Supports multiple data types including integers, doubles, strings, booleans, objects, and functions.
- **Operator Overloading:** Enables intuitive syntax for object manipulation using operators like `[]`, `=`, `+`, `-`, etc.
- **Function Support:** Allows defining and invoking functions (methods) within objects.
- **Chaining and Nesting:** Supports chaining operations and nesting objects for complex data structures.
- **Input Handling:** Provides mechanisms to handle user input dynamically.
- **Extensible:** Easily extendable to support additional features or data types.

## Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/yourusername/MSGlang.git
   cd MSGlang
   ```

2. **Compile the Code:**

   Ensure you have a C++ compiler that supports C++11 or later.

   ```bash
   g++ -std=c++11 -o MSGlang main.cpp
   ```

   Replace `main.cpp` with the name of your source file if different.


## Usage

### Basic Concepts

- **Object:** The primary container that holds properties and methods.
- **`val`:** Represents a value that can be of various types (int, double, string, bool, object, or function).
- **`key`:** Represents a key-value pair within an object.
- **`vals`:** Represents a list of values.

### Creating Objects

Use the `object` keyword along with macros to create objects.

```cpp
let o1 = object[
    key("name") = "John",
    key("age") = 30,
    key("isStudent") = false
];
```

### Accessing and Modifying Properties

Access object properties using the `[]` operator.

```cpp
// Accessing properties
cout << o1["name"] << endl; // Outputs: "John"

// Modifying properties
o1["age"] = 31;
cout << o1["age"] << endl; // Outputs: 31
```

### Defining and Calling Methods

Define methods (functions) within objects using the `lambda` or `func` macros.

```cpp
let o2 = object[
    key("greet") = lambda{ return "Hello, World!"; },
    func("add") {
        return self(1) + self(2);
    }
];

// Calling methods
cout << o2["greet"]() << endl; // Outputs: Hello, World!
cout << o2["add"]() << endl;    // Outputs: 3
```

### Input Handling

Use the `input` class to handle user inputs dynamically.

```cpp
o1["score"] = input("Enter your score: ");
cout << "Your score is: " << o1["score"] << endl;
```

### Example

Here's a comprehensive example demonstrating various features of MSGlang:

```cpp
int main() {
    let o1 = object;
    let o2 = object[values 1, "5", true, false, 3.2, object[values 3, 2]];
    let o3 = object[
        key("a") = 3,
        key("b") = "asd",
        key("c") = lambda{ return none; },
        func("d") { return none; }
    ];

    cout << o1 << nl << o2 << nl << o3 << nl;

    let o4 = object[values 1, 2, ref(o3)];
    cout << o4;

    let printf_impl = object[
        key("4") = "abab",
        key("2") = 4,
        key("3") = 6,
        func("printf") {
            cout << arg("a") + self(2) << nl;
            if (eval_cond("falsefunc")) {
                eval("showme");
                eval("equal");
            }
            return none;
        }
    ];

    let callerobject = object[
        call("printf"),
        func("showme") {
            cout << "this is bab
";
            return none;
        },
        func("falsefunc"){
            return 1==1;
        },
        func("equal") {
            if (self("3") == arg("3")) {
                cout << "same
";
            }
            else {
                cout << "different
";
            }
            return none;
        },
        key("a") = 5,
        key("3") = 8
    ];

    printf_impl << callerobject;

    let printf_implement = object[
        func("printf") {
            for (auto& v : args_list)
                cout << v << nl;
            return none;
        }
    ];

    let callerobjectimplement = object[call("printf"), values 1, "2", true, -3.14];

    printf_implement << callerobjectimplement;

    return 0;
}
```

## Classes and Components

### `val`

Represents a versatile value that can hold different data types. It includes support for integers, doubles, strings, booleans, objects, and functions.

**Key Features:**

- Type Indicators (e.g., `isInt`, `isDouble`, etc.).
- Operator Overloading for assignment and arithmetic operations.
- Function storage using `std::function`.

### `vals`

Manages a collection of `val` instances, allowing the creation of value lists within objects.

**Key Features:**

- Supports comma-separated value insertion.
- Internally uses a `Map` to store values with incremental indices.

### `key`

Represents a key-value pair within an Object. It allows assigning values or functions to specific keys.

**Key Features:**

- Assigns `val` or function to a key.
- Supports chaining of keys.

### `Object`

The core class that holds properties and methods. It uses a `Map` to store key-value pairs and supports dynamic operations.

**Key Features:**

- Overloaded `[]` operator for accessing and assigning properties.
- Supports method calls and object manipulation.
- Overloaded `<<` operator to handle method invocation.

### `MyInput`

Handles user input, dynamically determining the type of input (int, double, bool, or string).

**Key Features:**

- Prompts the user for input.
- Parses input into the appropriate `val` type.

### `MyRef`

Provides reference handling for objects, allowing references to existing objects within new objects.

**Key Features:**

- Overloaded `()` operator to return references.

## Macros and Shortcuts

MSGlang utilizes several macros to simplify object creation and manipulation:

- `let`: Alias for `Object`, used to declare objects.
- `none`: Represents `NULL`.
- `values`: Simplifies adding multiple values to an object.
- `lambda`: Simplifies defining anonymous functions.
- `ref`: Alias for `refa`, used for referencing objects.
- `func(name)`: Simplifies defining named functions within objects.
- `nl`: Represents a newline character (`"\n"`).
- `args_list`: Retrieves the list of arguments passed to functions.

### Example:

```cpp
let obj = object[
    key("name") = "Alice",
    key("age") = 25,
    func("greet") { return "Hello, " + self("name"); },
    values 1, 2, 3
];
```

**Note:** This README provides an overview based on the provided C++ code. For detailed documentation and advanced usage, refer to the inline comments within the source code and explore the classes and their functionalities further.
