//
//  binary.c
//  toy
//
//  Created by Bernardo Breder on 12/08/17.
//  Copyright © 2017 hvm. All rights reserved.
//

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "hvm.h"

struct toy_out_t* toy_out_alloc(bool simulate) {
    MEMORY_ALLOC_NAMED(self, struct toy_out_t);
    self->simulate = simulate;
    if (!simulate) {
        self->bytes_max = 1024;
        self->bytes = MEMORY_ALLOC(self->bytes_max * sizeof(uint8_t));
    }
    return self;
}

void toy_out_realloc(struct toy_out_t* self, size_t count) {
    if (!self->simulate && self->bytes_cur + count > self->bytes_max) {
        self->bytes_max += self->bytes_max / 2;
        self->bytes = realloc(self->bytes, self->bytes_max);
    }
}

void toy_out_write_verbose(struct toy_out_t* self, const char* format, ...) {
    if (!self->simulate) {
        toy_out_verbose_inline("| 0x%04lX | | | ", self->bytes_cur);
        toy_out_verbose_wrapper(format, ...);
        toy_out_verbose_inline("|\n");
    }
}

void toy_out_write_flag(struct toy_out_t* self, uint8_t value, const char* format, ...) {
    if (self->simulate) {
        self->bytes_cur++;
    } else {
        toy_out_verbose_inline("| 0x%04lX | {0x%02X} | %s | ", self->bytes_cur, value, value ? "true" : "false");
        toy_out_verbose_wrapper(format, ...);
        toy_out_verbose_inline("|\n");
        toy_out_realloc(self, 1);
        self->bytes[self->bytes_cur++] = value;
    }
}

void toy_out_write_uint8(struct toy_out_t* self, uint8_t value, const char* format, ...) {
    if (self->simulate) {
        self->bytes_cur++;
    } else {
        toy_out_verbose_inline("| 0x%04lX | {0x%02X} | %d | ", self->bytes_cur, value, value);
        toy_out_verbose_wrapper(format, ...);
        toy_out_verbose_inline("|\n");
        toy_out_realloc(self, 1);
        self->bytes[self->bytes_cur++] = value;
    }
}

void toy_out_write_uint16(struct toy_out_t* self, uint16_t value, const char* format, ...) {
    if (self->simulate) {
        self->bytes_cur += 2;
    } else {
        toy_out_verbose_inline("| 0x%04lX | {0x%02X, 0x%02X} | %d| ", self->bytes_cur, TOY_BYTE_SHIFT_RIGHT(value, 8), TOY_BYTE_SHIFT_RIGHT(value, 0), value);
        toy_out_verbose_wrapper(format, ...);
        toy_out_verbose_inline(" |\n");
        toy_out_realloc(self, 2);
        self->bytes[self->bytes_cur++] = TOY_BYTE_SHIFT_RIGHT(value, 8);
        self->bytes[self->bytes_cur++] = TOY_BYTE_SHIFT_RIGHT(value, 0);
    }
}

void toy_out_write_uint32(struct toy_out_t* self, uint32_t value, const char* format, ...) {
    if (self->simulate) {
        self->bytes_cur += 4;
    } else {
        toy_out_verbose_inline("| 0x%04lX | {0x%02X, 0x%02X, 0x%02X, 0x%02X} | %d | ", self->bytes_cur, TOY_BYTE_SHIFT_RIGHT(value, 24), TOY_BYTE_SHIFT_RIGHT(value, 16), TOY_BYTE_SHIFT_RIGHT(value, 8), TOY_BYTE_SHIFT_RIGHT(value, 0), value);
        toy_out_verbose_wrapper(format, ...);
        toy_out_verbose_inline("|\n");
        toy_out_realloc(self, 4);
        self->bytes[self->bytes_cur++] = TOY_BYTE_SHIFT_RIGHT(value, 24);
        self->bytes[self->bytes_cur++] = TOY_BYTE_SHIFT_RIGHT(value, 16);
        self->bytes[self->bytes_cur++] = TOY_BYTE_SHIFT_RIGHT(value, 8);
        self->bytes[self->bytes_cur++] = TOY_BYTE_SHIFT_RIGHT(value, 0);
    }
}

void toy_out_write_chars(struct toy_out_t* self, char* value, const char* format, ...) {
    size_t n, length = strlen(value);
    if (self->simulate) {
        self->bytes_cur += 2 + length;
    } else {
        toy_out_verbose_inline("| 0x%04lX | {0x%02X, 0x%02X}, {", self->bytes_cur, TOY_BYTE_SHIFT_RIGHT(TOY_CAST(length, uint16_t), 8), TOY_BYTE_SHIFT_RIGHT(TOY_CAST(length, uint16_t), 0));
        for (n = 0 ; n < length ; n++) {
            toy_out_verbose_inline("0x%02X", value[n]);
            if (n != length -1) { toy_out_verbose_inline(", "); }
        }
        toy_out_verbose_inline("} | \"%s\" | ", value);
        toy_out_verbose_wrapper(format, ...);
        toy_out_verbose_inline("|\n");
        toy_out_realloc(self, 2 + length);
        self->bytes[self->bytes_cur++] = TOY_BYTE_SHIFT_RIGHT(length, 8);
        self->bytes[self->bytes_cur++] = TOY_BYTE_SHIFT_RIGHT(length, 0);
        for (n = 0 ; n < length ; n++) {
            self->bytes[self->bytes_cur++] = value[n];
        }
    }
}

struct toy_in_t* toy_in_alloc(uint8_t* bytes, size_t bytes_count) {
    MEMORY_ALLOC_NAMED(self, struct toy_in_t);
    self->bytes = bytes;
    self->bytes_max = bytes_count;
    return self;
}

void toy_in_read_skip(struct toy_in_t* self, size_t count) {
    self->bytes_cur += count;
}

bool toy_in_read_bool(struct toy_in_t* self) {
    return self->bytes[self->bytes_cur++];
}

uint8_t toy_in_read_uint8(struct toy_in_t* self) {
    if (self->bytes_cur >= self->bytes_max) { return 0; }
    return self->bytes[self->bytes_cur++];
}

uint16_t toy_in_read_uint16(struct toy_in_t* self) {
    if (self->bytes_cur >= self->bytes_max) { return 0; }
    uint8_t a = self->bytes[self->bytes_cur++];
    uint8_t b = self->bytes[self->bytes_cur++];
    return TOY_BYTE_SHIFT_LEFT(a, 8) + TOY_BYTE_SHIFT_LEFT(b, 0);
}

uint32_t toy_in_read_uint32(struct toy_in_t* self) {
    if (self->bytes_cur >= self->bytes_max) { return 0; }
    uint8_t a = self->bytes[self->bytes_cur++];
    uint8_t b = self->bytes[self->bytes_cur++];
    uint8_t c = self->bytes[self->bytes_cur++];
    uint8_t d = self->bytes[self->bytes_cur++];
    return TOY_BYTE_SHIFT_LEFT(a, 24) + TOY_BYTE_SHIFT_LEFT(b, 16) + TOY_BYTE_SHIFT_LEFT(c, 8) + TOY_BYTE_SHIFT_LEFT(d, 0);
}

char* toy_in_read_chars(struct toy_in_t* self) {
    if (self->bytes_cur >= self->bytes_max) { return 0; }
    uint8_t a = self->bytes[self->bytes_cur++];
    uint8_t b = self->bytes[self->bytes_cur++];
    size_t length = TOY_BYTE_SHIFT_LEFT(a, 8) + TOY_BYTE_SHIFT_LEFT(b, 0);
    char* chars = MEMORY_ALLOC((length + 1) * sizeof(char));
    size_t n; for (n = 0 ; n < length ; n++) {
        chars[n] = self->bytes[self->bytes_cur++];
    }
    return chars;
}
