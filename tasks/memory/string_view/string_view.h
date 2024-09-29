#pragma once

#include <string>

class StringView {
public:
    const char* str_ptr;  // Указатель на исходную строку (C-строку или строку)
    size_t start_pos;  // Начальная позиция подстроки
    size_t length;     // Длина подстроки

    // Конструктор, принимающий const std::string&
    StringView(const std::string& str, size_t start_pos = 0, size_t length = std::string::npos)
        : str_ptr(str.c_str()), start_pos(start_pos), length(length) {
        if (start_pos + length > str.length() || length == std::string::npos) {
            this->length = str.length() - start_pos;
        }
    }

    // Конструктор, принимающий С-строку и длину подстроки
    StringView(const char* cstr, size_t length) : str_ptr(cstr), start_pos(0), length(length) {
        size_t cstr_len = std::char_traits<char>::length(cstr);  // Определяем длину C-строки
        if (length > cstr_len) {
            this->length = cstr_len;
        }
    }

    // Конструктор, принимающий С-строку
    StringView(const char* cstr) : str_ptr(cstr), start_pos(0), length(std::string::npos) {
        size_t cstr_len = std::char_traits<char>::length(cstr);  // Определяем длину C-строки
        this->length = cstr_len;
    }

    // Оператор для получения символа по индексу
    char operator[](size_t index) const {
        return str_ptr[start_pos + index];
    }

    // Метод для получения длины подстроки
    size_t Size() const {
        return length;
    }
};
