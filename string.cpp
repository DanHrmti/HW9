#include <stddef.h>
#include <iostream>
#include <cstring>

#include "string.h"

/**
 * @brief Initiates an empty string
 */
String::String() {
    data = new char[1];
    data[0] = '\0';
    length = 0;
}

/**
 * @brief Initiates string from other string
 */
String::String(const String &str) {
    length = str.length;
    data = new char[length+1];
    strcpy(data, str.data);
}

/**
 * @brief Initiates a string from char array
 */
String::String(const char *str) {
    length = strlen(str);
    data = new char[length+1];
    strcpy(data, str);
}


String::~String() {
    delete[] data;
}

/**
 * @brief Changes this from String
 */
String& String::operator=(const String &rhs) {
    if (this == &rhs) {
        return *this;
    }

    delete[] data;
    length = rhs.length;
    data = new char[length+1];
    strcpy(data, rhs.data);
    return *this;
}

/**
 * @brief Changes this from char array
 */
String& String::operator=(const char *str) {
    delete[] data;
    length = strlen(str);
    data = new char[length+1];
    strcpy(data, str);
    return *this;
}

/**
 * @brief Returns true iff the contents of this equals to the
 * contents of rhs
 */
bool String::equals(const String &rhs) const {
    if (length == rhs.length) {
        if (!strcmp(data, rhs.data)) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/**
 * @brief Returns true iff the contents of this equals to rhs
 */
bool String::equals(const char *rhs) const {
    if (!strcmp(data, rhs)) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
void String::split(const char *delimiters, String **output, size_t *size) const {

    String this_clone_1(*this); /* for counting number of substrings */
    String this_clone_2(*this); /* for extracting substrings */
    *size = 0;
    char *cur_sub_str;

    /* determine size */
    cur_sub_str = strtok(this_clone_1.data, delimiters);
    while (cur_sub_str != NULL) {
       *size+=1;
       cur_sub_str = strtok(NULL, delimiters);
    }

    if (*size == 0) {
        *output = NULL;
        return;
    }

    if (output == NULL) {
        return;
    }

    /* allocate memory for substrings */
    *output = new String[*size];

    int i = 0;

    /* get the first substring */
    cur_sub_str = strtok(this_clone_2.data, delimiters);
   
    /* walk through substrings and add to output */
    while (cur_sub_str != NULL) {
        (*output)[i] = cur_sub_str;
        i++;
        cur_sub_str = strtok(NULL, delimiters);        
    }

    return;
}

/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const {
    return atoi(this->data);
}

/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const {

    String trimed_this;
    String this_clone(*this);
    int start_index = 0, end_index = length-1;

    while (this_clone.data[start_index] == ' ') {
        start_index++;
    }

    if (start_index == (int)length) {
        return trimed_this;
    }

    while (this_clone.data[end_index] == ' ') {
        end_index--;
    }
    this_clone.data[end_index+1] = '\0';

    trimed_this = &(this_clone.data[start_index]);
    return trimed_this;
}