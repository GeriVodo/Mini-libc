// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source) {
	/* TODO: Implement strcpy(). */
	int len = strlen(source);

	for(int i = 0; i < len ; i++) {
		destination[i] = source [i];
	}

	destination[len] = '\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len) {
	/* TODO: Implement strncpy(). */
	size_t i = 0;

    for (; i < len && source[i] != '\0'; i++) {
        destination[i] = source[i];
    }

    for (; i < len; i++) {
        destination[i] = '\0';
    }

    return destination;
}

char *strcat(char *destination, const char *source) {
	/* TODO: Implement strcat(). */
	size_t lenD = strlen(destination);
	size_t lenS = strlen(source);

	for(size_t i = 0 ; i < lenS ; i++) {
		destination[lenD + i] = source[i];
	}

	destination[lenD + lenS] = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len) {
	/* TODO: Implement strncat(). */
	size_t i;
	int lenD = strlen(destination);

	for (i = 0; i < len; i++) {
    destination[lenD + i] = source[i];
  	}

	destination[lenD + i] = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2) {
	/* TODO: Implement strcmp(). */
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }

    return (int)((unsigned char)*str1 - (unsigned char)*str2);
}

int strncmp(const char *str1, const char *str2, size_t len) {
	/* TODO: Implement strncmp(). */
	while (len > 0) {
        if (*str1 != *str2) {
            return (int)*str1 - (int)*str2;
        } else if (*str1 == '\0') {
            return 0;
        }
        str1++;
        str2++;
        len--;
    }

    return 0;
}

size_t strlen(const char *str) {
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c) {
	/* TODO: Implement strchr(). */
	// strchr - finds first instance of a char in a string
	int len = strlen(str);

	for(int i = 0 ; i < len ; i++){
		if(str[i] == c){
			const char *first = &str[i];
			return (char *)first;
		}
	}
	return NULL;
}

char *strrchr(const char *str, int c) {
	/* TODO: Implement strrchr(). */
	//strchr - finds the last instance of a char in a string
	int len = strlen(str);
	const char *last = '\0';

	for(int i = 0 ; i < len ; i++){
		if(str[i] == c){
			last = &str[i];
		}
	}

	return (char *)last;
}

char *strstr(const char *haystack, const char *needle) {
	/* TODO: Implement strstr(). */
	//strstr - locates a substring in a string
	// returns a pointer to the beginning of the first occurrence of str2 in str1
	// if str2 does not appear in str1 returns NULL
	// if str2 points to a str with lenght zero the strstr() returns string1
	int haystack_len = strlen(haystack);
	int needle_len = strlen(needle);

	for (int i = 0; i < haystack_len; i++) {
		if (haystack[i] == needle[0]) {
			int chars = 0;

			for (int j = 0; j < needle_len; j++) {
				if (haystack[i + j] == needle [j]) {
					chars++;
				}
			}

			if (chars == needle_len) {
				return (char *)&haystack[i];
			}
		}
	}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle) {
	/* TODO: Implement strrstr(). */
	int haystack_len = strlen(haystack);
    int needle_len = strlen(needle);
    int i = haystack_len - needle_len;

    for (; i >= 0; i--) {
        int j;
        for (j = 0; j < needle_len; j++) {
            if (haystack[i + j] != needle[j]) {
                break;
            }
        }
        if (j == needle_len) {
            return (char *)&haystack[i];
        }
    }
    return NULL;
}

void *memcpy(void *destination, const void *source, size_t num) {
	/* TODO: Implement memcpy(). */
	// memcpy copies blocks of memory from one place to another

	char *d = destination;
    const char *s = source;
    while (num--) *d++ = *s++;
	return destination;
}

void *memmove(void *destination, const void *source, size_t num) {
	/* TODO: Implement memmove(). */
	char temp;
	for (size_t i = 0; i < num; i++) {
		temp = ((char *) source)[i];
		((char *)destination)[i] = temp;
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num) {
	/* TODO: Implement memcmp(). */
	char *p1 = (char *)ptr1;
    char *p2 = (char *)ptr2;

    for (size_t i = 0; i < num; i++) {
        if (p1[i] < p2[i]) {
            return -1;
        } else if (p1[i] > p2[i]) {
            return 1;
        }
    }
    return 0;
}

void *memset(void *source, int value, size_t num) {
	/* TODO: Implement memset(). */
	char *src = (char *)source;

	for (size_t i = 0; i < num; i++) {
		src[i] = value;
	}
	return source;
}
