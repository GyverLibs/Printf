# Printf
## Документация
```cpp
// constructor
Printf(Print&);

// new line
();

// integer
(T val, uint8_t radix = 10, uint8_t width = 0, bool right = true, char fill = '0');

// float
(float val, uint8_t dec = 2, uint8_t width = 0, bool right = true, char fill = '0');

// string
(const char* str);
(const char* str, uint8_t width, bool right = true);
(const String& str, uint8_t width = 0, bool right = true);
(const __FlashStringHelper* fstr);

// variadic
print(Args... args);
println(Args... args);

// variadic + ','
dprint(Args... args);
dprintln(Args... args);
```

## Пример
```cpp
float f = 12.345;
int i = 123;

Printf(Serial)("hello", 10)()("hello", 10, false)();
Printf(Serial)(f)();
Printf(Serial)(i)();
Printf(Serial)(f, 3, 7, true)(',')(f, 3, 7, false)();
Printf(Serial)(i, 10, 7, true, ' ')(',')(-i, 10, 7, false)();
```
```
hello     
     hello
12.35
123
12.3450,012.345
123    ,-000123
```