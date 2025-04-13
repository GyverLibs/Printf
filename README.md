# Printf
Лёгкая форматированная печать для Arduino Print
- Вывод чисел с указанием ширины и выравнивания, целые - с основанием, float - с кол-вом десятичных
- Вывод строк с выравниванием
- Вывод variadic списка любых типов

## Документация
```cpp
// constructor
PF(Print&);

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

PF(Serial)("hello", 10)()("hello", 10, false)();

PF(Serial)(f)();
PF(Serial)(i)();
PF(Serial)(f, 3, 7, true)(',')(f, 3, 7, false)();
PF(Serial)(i, 10, 7, true, ' ')(',')(-i, 10, 7, false)();
PF(Serial).dprintln(f, i, 1234, 3.14, "abc", F("def"));
```
```
hello     
     hello
12.35
123
12.3450,012.345
123    ,-000123
12.35,123,1234,3.14,abc,def,
```