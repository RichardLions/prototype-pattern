# Prototype Pattern

This pattern was inspired by [Game Programming Patterns](https://gameprogrammingpatterns.com/prototype.html) and [
C++ Software Design - Guideline 30](https://www.oreilly.com/library/view/c-software-design/9781098113155/).

## When To Use

This pattern enables an instance of an object to be copied without knowing it's concrete type. 

General:
* Used for an open set of types, no knowledge of the possible types is needed.
* Copies the internal state of the type.

## Example

Create a Prototype:
```cpp
class Type
{
public:
    virtual ~Type() = default;
    virtual std::unique_ptr<Type> Clone() = 0;
};

class TypeA final : public Type
{
public:
    std::unique_ptr<Type> Clone() override { return std::make_unique<TypeA>(*this); }
    State GetState() const;
};

std::unique_ptr<Type> type{std::make_unique<TypeA>()};
std::unique_ptr<Type> clone{type->Clone()};
// Not the same instance
REQUIRE(type != clone);
// clone's state will match type's
REQUIRE(static_cast<TypeA*>(type.get())->GetState() == static_cast<TypeA*>(clone.get())->GetState());
```

## Setup

This repository uses the .sln/.proj files created by Visual Studio 2022 Community Edition.
Using MSVC compiler, Preview version(C++23 Preview). 

### Catch2
The examples for how to use the pattern are written as Unit Tests.

Launching the program in Debug or Release will run the Unit Tests.

Alternative:
Installing the Test Adapter for Catch2 Visual Studio extension enables running the Unit Tests via the Test Explorer Window. Setup the Test Explorer to use the project's .runsettings file.

### vcpkg
This repository uses vcpkg in manifest mode for it's dependencies. To interact with vcpkg, open a Developer PowerShell (View -> Terminal).

To setup vcpkg, install it via the Visual Studio installer. To enable/disable it run these commands from the Developer PowerShell:
```
vcpkg integrate install
vcpkg integrate remove
```

To add additional dependencies run:
```
vcpkg add port [dependency name]
```

To update the version of a dependency modify the overrides section of vcpkg.json. 

To create a clean vcpkg.json and vcpkg-configuration.json file run:
```
vcpkg new --application
```

### TODO
- [x] Implementation
- [x] Unit Tests
