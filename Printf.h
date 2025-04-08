#pragma once
#include <Arduino.h>

class PrintfClass {
   public:
    PrintfClass(Print& p) : _p(p) {}

    // int
    PrintfClass& operator()(signed char i, uint8_t radix = 10, uint8_t width = 0, bool right = true, char fill = '0') {
        return (*this)((long)i, radix, width, right, fill);
    }
    PrintfClass& operator()(short i, uint8_t radix = 10, uint8_t width = 0, bool right = true, char fill = '0') {
        return (*this)((long)i, radix, width, right, fill);
    }
    PrintfClass& operator()(int i, uint8_t radix = 10, uint8_t width = 0, bool right = true, char fill = '0') {
        return (*this)((long)i, radix, width, right, fill);
    }
    PrintfClass& operator()(long i, uint8_t radix = 10, uint8_t width = 0, bool right = true, char fill = '0') {
        if (i < 0) {
            _write('-');
            i = -i;
            if (width) --width;
        }
        return (*this)((unsigned long)i, radix, width, right, fill);
    }

    // uint
    PrintfClass& operator()(unsigned char i, uint8_t radix = 10, uint8_t width = 0, bool right = true, char fill = '0') {
        return (*this)((unsigned long)i, radix, width, right, fill);
    }
    PrintfClass& operator()(unsigned short i, uint8_t radix = 10, uint8_t width = 0, bool right = true, char fill = '0') {
        return (*this)((unsigned long)i, radix, width, right, fill);
    }
    PrintfClass& operator()(unsigned int i, uint8_t radix = 10, uint8_t width = 0, bool right = true, char fill = '0') {
        return (*this)((unsigned long)i, radix, width, right, fill);
    }
    PrintfClass& operator()(unsigned long i, uint8_t radix = 10, uint8_t width = 0, bool right = true, char fill = '0') {
        char buf[33];
        ultoa(i, buf, radix);
        return _printAligned(buf, width, right, fill);
    }

    // float
    PrintfClass& operator()(float f, uint8_t dec = 2, uint8_t width = 0, bool right = true, char fill = '0') {
        char buf[21];
        dtostrf(f, dec + 2, dec, buf);
        return _printAligned(buf, width, right, fill);
    }
    PrintfClass& operator()(double d, uint8_t dec = 2, uint8_t width = 0, bool right = true, char fill = '0') {
        return (*this)((float)d, dec, width, right, fill);
    }

    // bool
    PrintfClass& operator()(bool b) {
        _write(b ? '0' : '1');
        return *this;
    }

    // string
    PrintfClass& operator()(char c) {
        _write(c);
        return *this;
    }
    PrintfClass& operator()(const char* str) {
        while (*str) _write(*str++);
        return *this;
    }
    PrintfClass& operator()(const char* str, uint8_t width, bool right = true) {
        return _printAligned(str, width, right, ' ');
    }
    PrintfClass& operator()(const String& str, uint8_t width = 0, bool right = true) {
        return (*this)(str.c_str(), width, right);
    }
    PrintfClass& operator()(const __FlashStringHelper* fstr) {
        PGM_P str = (PGM_P)fstr;
        while (true) {
            char c = pgm_read_byte(str++);
            if (!c) break;
            _write(c);
        }
        return *this;
    }

    // new line
    PrintfClass& operator()() {
        _write('\r');
        _write('\n');
        return *this;
    }

#ifdef PF_USE_FOLD
    template <typename... Args>
    PrintfClass& print(Args... args) {
        ((*this)(args), ...);
        return *this;
    }
    template <typename... Args>
    PrintfClass& println(Args... args) {
        return print(args...)();
    }
#endif

   private:
    Print& _p;

    inline void _write(char c) {
        _p.write(c);
    }
    PrintfClass& _printAligned(const char* buf, uint16_t width, bool right, char s) {
        int16_t fill = width ? width - strlen(buf) : 0;
        while (!right && fill > 0) _write(s), --fill;
        (*this)(buf);
        while (right && fill > 0) _write(s), --fill;
        return *this;
    }
};

inline PrintfClass PF(Print& p) {
    return p;
}