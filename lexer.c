//
//  lexer.c
//  hvm
//
//  Created by Bernardo Breder on 12/08/17.
//  Copyright © 2017 hvm. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "hvm.h"

#define toy_lexer_add(BEGIN, ALL_TOKENS, CUR_TOKEN, TOKEN) \
    size_t size = ((pc - text) - (BEGIN) + 1); \
    MEMORY_ALLOC_NAMED(TOKEN, struct toy_token_t); \
    TOKEN->word = (char*) MEMORY_ALLOC((size + 1) * sizeof(char)); \
    strncpy(TOKEN->word, (char*) text + (BEGIN), size); \
    TOY_LIST_ADD(ALL_TOKENS, CUR_TOKEN, TOKEN);

struct toy_token_t* toy_lexer(char* text) {
    struct toy_token_t* all_tokens = 0;
    struct toy_token_t* cur_token = 0;
    char* pc = text;
    char c = *pc;
    while (c) {
        if (c <= ' ') {
        } else if (TOY_CHAR_IS_ID_START(c)) {
            size_t begin = pc - text;
            do { c = *(++pc); } while (TOY_CHAR_IS_ID_END(c));
            pc--;
            toy_lexer_add(begin, all_tokens, cur_token, token);
        } else if (TOY_CHAR_IS_NUM(c)) {
            size_t begin = pc - text;
            c = *(++pc);
            while (TOY_CHAR_IS_NUM(c)) { c = *(++pc); }
            pc--;
            toy_lexer_add(begin, all_tokens, cur_token, token);
        } else if (c == '\"') {
            size_t begin = pc - text;
            c = *(++pc);
            while (c != '\"') { c = *(++pc); }
            toy_lexer_add(begin, all_tokens, cur_token, token);
        } else {
            size_t begin = pc - text;
            toy_lexer_add(begin, all_tokens, cur_token, token);
        }
        c = *(++pc);
    }
    return all_tokens;
}
