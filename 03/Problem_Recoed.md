# Questions and Notes

## 1. How can we initialize a custom String object using a string literal like `"abcd"`?

In C++, `"abcd"` is a C-style string literal of type `const char[5]`, including the null terminator `'\0'`.

When passed to a constructor, the array normally decays into a `const char*`.

To initialize our custom `String` object:

1. Define a constructor that accepts `const char*`.
2. Allocate memory using `new char[length + 1]`.
3. Copy the characters, including the null terminator, into the allocated memory.

**Key point:** We do not need to convert the literal into a `char[]` first. The constructor can accept `const char*` directly.

## 2. What is the difference between `malloc`/`free` (C style) and `new`/`delete` (C++ style)?

- **`malloc()`** allocates raw memory without calling constructors.
- **`new`** allocates memory and creates an object. For class types, it invokes the appropriate constructor.
- **`free()`** deallocates memory without calling destructors.
- **`delete`** destroys an object and deallocates its memory.

**Important differences:**

- `malloc()` returns `void*`, while `new` returns a pointer to the specified type.
- `new` supports object initialization, but built-in types are not necessarily initialized to zero.
- Memory allocated by `malloc()` must be released using `free()`.
- Memory allocated by `new` must be released using `delete`.
- Memory allocated by `new[]` must be released using `delete[]`.

**Key point:** Never mix `malloc` with `delete`, or `new` with `free`.

## 3. What is rule of three?

three : Destructor, Copy Constructor, Copy Assignment Operator(=).
When the class we defined involve allocating memory, we need to define the "three" by ourselves to avoid Shallow Copy which may lead to Double Free and Dangling Pointer.

## 4. What is the difference between directly assigning "" and allocating with new char[1]?

Memory Location : `""` is in Constant Data Section(read only) ; Memory allocated by `new` is on the heap(read-write).
Undefined Behavior / Crash: String literals like "" must never be freed using delete[] — doing so results in undefined behavior (usually a runtime crash).

## 5. Why can't begin() and end() return references (e.g., char*&)?

end() returns a computed temporary value (an rvalue, e.g., s + len), which cannot bind to a non-const reference.

Returning a reference (char*&) exposes the internal member pointer, meaning operations like ++it would inadvertently modify the class's original internal data pointer and break encapsulation.

## 6. Why the overloading of operator + can't use & as return type?

The object that the `&` refers to is a Local Object. This Local Object will be destroyed after the `operator+` function exits, which will lead to a Dangling Reference(undefined behavior).
The `operator+` must return by value(Type, not Type&).

## 7. Why overload `operator+` as a non-member function?

- **Key Advantage:** Symmetry & Implicit Type Conversion

### 1. Member Function Approach

- **Requirement:** Requires the left-hand operand to be a class instance (`lhs.operator+(rhs)`).
- **Behavior:**
- `s + "Hello"` works because the right-hand literal can implicitly convert to the class type.
- `"Hello" + s` **fails to compile** because a string literal is a primitive type and cannot invoke a member function.

### 2. Non-member Function Approach

- **Requirement:** Treats both operands symmetrically (`operator+(lhs, rhs)`).
- **Behavior:**
- Both `s + "Hello"` and `"Hello" + s` compile successfully, because implicit type conversion applies to any parameter passed into a global/non-member function.