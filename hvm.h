//
//  lexer.h
//  hvm
//
//  Created by Bernardo Breder on 12/08/17.
//  Copyright © 2017 hvm. All rights reserved.
//

#ifndef lexer_h
#define lexer_h

#include <stddef.h>

#ifndef bool
typedef uint8_t bool;
#endif

struct toy_token_t {
    char* word;
    struct toy_token_t* next;
};

struct toy_out_t {
    bool simulate;
    uint8_t* bytes;
    size_t bytes_max, bytes_cur;
};

struct toy_in_t {
    uint8_t* bytes;
    size_t bytes_max, bytes_cur;
};

struct toy_context_t {
    uint32_t class_count;
};

struct toy_node_t {
    uint8_t type;
};

struct toy_node_next_t {
    uint8_t type;
    struct toy_node_field_t* next;
};

struct toy_node_unit_t {
    uint8_t type;
    struct toy_node_class_t* classes;
};

struct toy_node_class_t {
    uint8_t type;
    struct toy_node_class_t* next;
    char* name;
    struct toy_node_field_t* fields;
    struct toy_node_func_t* funcs;
    uint16_t class_index;
    uint16_t field_count;
    uint16_t func_count;
};

struct toy_node_field_t {
    uint8_t type;
    struct toy_node_field_t* next;
    char* name;
};

struct toy_node_func_t {
    uint8_t type;
    struct toy_node_func_t* next;
    char* name;
    struct toy_node_arg_t* args;
    struct toy_node_stmt_t* stmt;
    uint16_t arg_count;
    uint16_t opcode_count;
    size_t pc;
};

struct toy_node_arg_t {
    uint8_t type;
    struct toy_node_arg_t* next;
    char* name;
};

struct toy_node_stmt_t {
    uint8_t type;
    struct toy_node_stmt_t* next;
};

struct toy_node_stmt_exp_t {
    uint8_t type;
    struct toy_node_stmt_t* next;
    struct toy_node_exp_t* exp;
};

struct toy_node_stmt_return_t {
    uint8_t type;
    struct toy_node_stmt_t* next;
    struct toy_node_exp_t* exp;
};

struct toy_node_stmt_while_t {
    uint8_t type;
    struct toy_node_stmt_t* next;
    struct toy_node_exp_t* exp;
    struct toy_node_stmt_t* stmt;
    uint16_t begin_diff_pc;
    uint16_t false_diff_pc;
};

struct toy_node_stmt_if_t {
    uint8_t type;
    struct toy_node_stmt_t* next;
    struct toy_node_exp_t* exp;
    struct toy_node_stmt_t* stmt;
    uint16_t false_diff_pc;
};

struct toy_node_exp_t {
    uint8_t type;
};

struct toy_node_exp_ternary_t {
    uint8_t type;
    struct toy_node_exp_t* exp;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
    uint16_t true_diff_pc;
    uint16_t false_diff_pc;
};

struct toy_node_exp_or_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
    uint16_t true_diff_pc;
};

struct toy_node_exp_and_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
    uint16_t false_diff_pc;
};

struct toy_node_exp_eq_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
};

struct toy_node_exp_neq_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
};

struct toy_node_exp_gt_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
};

struct toy_node_exp_ge_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
};

struct toy_node_exp_lt_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
};

struct toy_node_exp_le_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
};

struct toy_node_exp_sum_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
};

struct toy_node_exp_sub_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
};

struct toy_node_exp_mul_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
};

struct toy_node_exp_div_t {
    uint8_t type;
    struct toy_node_exp_t* left;
    struct toy_node_exp_t* right;
};

struct toy_node_exp_neg_t {
    uint8_t type;
    struct toy_node_exp_t* exp;
};

struct toy_node_exp_not_t {
    uint8_t type;
    struct toy_node_exp_t* exp;
};

struct toy_node_exp_id_t {
    uint8_t type;
    struct toy_token_t* token;
};

struct toy_node_exp_str_t {
    uint8_t type;
    struct toy_token_t* token;
};

struct toy_node_exp_num_t {
    uint8_t type;
    struct toy_token_t* token;
    int32_t value;
};

struct toy_vm_func_t {
    char* name;
    uint16_t arg_count;
    uint16_t opcode_count;
    uint8_t* opcodes;
    struct toy_vm_func_t* next;
};

struct toy_vm_class_t {
    char* name;
    uint16_t field_count;
    uint16_t func_count;
    struct toy_vm_func_t* funcs;
    struct toy_vm_class_t* next;
};

struct toy_vm_stack_t {
    union {
        uint32_t number;
    } data;
};

struct toy_vm_t {
    struct toy_vm_class_t* classes;
    struct toy_vm_func_t* main_func;
    uint8_t* bytes_start;
};

#define NIL 0

#define TRUE 1

#define FALSE 0

#define TOY_CAST(OBJ, STRUCT) \
    ((STRUCT) OBJ)

#define MEMORY_ALLOC(SIZE) \
    calloc(1, SIZE)

#define MEMORY_ALLOC_NAMED(NAME, STRUCT) \
    STRUCT* NAME = (STRUCT*) MEMORY_ALLOC(sizeof(STRUCT));

#define TOY_CHAR_IS_ID_START(C) \
    (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z') || C == '_'

#define TOY_CHAR_IS_ID_END(C) \
    (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z') || (C >= '0' && C <= '9') || C == '_'

#define TOY_CHAR_IS_NUM(C) \
    (C >= '0' && C <= '9')

#define TOY_CHAR_IS_STR(C) \
    C == '\"'

#define TOY_TOKEN_GET(TOKENS) \
    (*(TOKENS))

#define TOY_TOKEN_GET_NEXT(TOKENS) \
    (TOY_TOKEN_GET(TOKENS)->next)

#define TOY_TOKEN_IS_ID(TOKENS) \
    TOY_CHAR_IS_ID_START(TOY_TOKEN_GET(TOKENS)->word[0])

#define TOY_TOKEN_IS_NUM(TOKENS) \
    TOY_CHAR_IS_NUM(TOY_TOKEN_GET(TOKENS)->word[0])

#define TOY_TOKEN_IS_STR(TOKENS) \
    TOY_CHAR_IS_STR(TOY_TOKEN_GET(TOKENS)->word[0])

#define TOY_TOKEN_WORD(TOKENS) \
    (TOY_TOKEN_GET(TOKENS) ? TOY_TOKEN_GET(TOKENS)->word : "<EOF>")

#define TOY_TOKEN_WORD_NEXT(TOKENS) \
    (TOY_TOKEN_GET_NEXT(TOKENS) ? TOY_TOKEN_GET_NEXT(TOKENS)->word : "<EOF>")

#define TOY_TOKEN_NEXT(TOKENS) \
    TOY_TOKEN_GET(TOKENS) = TOY_TOKEN_GET(TOKENS) ? TOY_TOKEN_GET(TOKENS)->next : 0

#define TOY_TOKEN_EQUAL(WORD1, WORD2) \
    (WORD1[0] == WORD2[0] && !strcmp(WORD1, WORD2))

#define TOY_NODE_ALLOC(STRUCT, NAME, TYPE) \
    MEMORY_ALLOC_NAMED(NAME, STRUCT) \
    NAME->type = TYPE;

#define TOY_LIST_ADD(ALL, CUR, VALUE) \
    if (ALL) { \
        CUR->next = VALUE; \
        CUR = VALUE; \
    } else { \
        ALL = CUR = VALUE; \
    }

#define TOY_NODE_MIN_TYPE 1
#define TOY_NODE_MAX_TYPE 27

#define TOY_NODE_UNIT_TYPE 1
#define TOY_NODE_CLASS_TYPE 2
#define TOY_NODE_FIELD_TYPE 3
#define TOY_NODE_FUNC_TYPE 4
#define TOY_NODE_ARG_TYPE 5
#define TOY_NODE_STMT_IF_TYPE 6
#define TOY_NODE_STMT_WHILE_TYPE 7
#define TOY_NODE_STMT_RETURN_TYPE 8
#define TOY_NODE_STMT_EXP_TYPE 9
#define TOY_NODE_EXP_TERNARY_TYPE 10
#define TOY_NODE_EXP_OR_TYPE 11
#define TOY_NODE_EXP_AND_TYPE 12
#define TOY_NODE_EXP_EQ_TYPE 13
#define TOY_NODE_EXP_NEQ_TYPE 14
#define TOY_NODE_EXP_GT_TYPE 15
#define TOY_NODE_EXP_GE_TYPE 16
#define TOY_NODE_EXP_LT_TYPE 17
#define TOY_NODE_EXP_LE_TYPE 18
#define TOY_NODE_EXP_SUM_TYPE 19
#define TOY_NODE_EXP_SUB_TYPE 20
#define TOY_NODE_EXP_MUL_TYPE 21
#define TOY_NODE_EXP_DIV_TYPE 22
#define TOY_NODE_EXP_NEG_TYPE 23
#define TOY_NODE_EXP_NOT_TYPE 24
#define TOY_NODE_EXP_ID_TYPE 25
#define TOY_NODE_EXP_STR_TYPE 26
#define TOY_NODE_EXP_NUM_TYPE 27

#define TOY_OPCODE_MIN_TYPE 1
#define TOY_OPCODE_MAX_TYPE 27

//#define TOY_OPCODE_CONST_NIL 1
#define TOY_OPCODE_CONST_STR 2
#define TOY_OPCODE_CONST_NUM 3
#define TOY_OPCODE_RETURN 4
#define TOY_OPCODE_JUMP 5
#define TOY_OPCODE_JUMP_TRUE 6
#define TOY_OPCODE_JUMP_FALSE 7
#define TOY_OPCODE_STACK_INC 8
#define TOY_OPCODE_STACK_DEC 9
#define TOY_OPCODE_STACK_DROP 10
#define TOY_OPCODE_NUM_EQ 11
#define TOY_OPCODE_NUM_NEQ 12
#define TOY_OPCODE_NUM_GT 13
#define TOY_OPCODE_NUM_GE 14
#define TOY_OPCODE_NUM_LT 15
#define TOY_OPCODE_NUM_LE 16
#define TOY_OPCODE_NUM_SUM 17
#define TOY_OPCODE_NUM_SUB 18
#define TOY_OPCODE_NUM_MUL 19
#define TOY_OPCODE_NUM_DIV 20
#define TOY_OPCODE_NUM_NEG 21
#define TOY_OPCODE_BOOL_OR 22
#define TOY_OPCODE_BOOL_AND 23
#define TOY_OPCODE_BOOL_NOT 24

#define toy_error(FORMAT, ARGS...) printf(FORMAT, ARGS); exit(1);

#ifdef DEBUG
#define toy_out_verbose_wrapper(FORMAT, ARGS...) \
    va_list args; \
    va_start(args, FORMAT); \
    vprintf(FORMAT, args); \
    va_end(args);
#else
#define toy_out_verbose_wrapper(FORMAT, ARGS...)
#endif

#ifdef DEBUG
#define toy_out_verbose_inline(...) printf(__VA_ARGS__);
#else
#define toy_out_verbose_inline(...)
#endif

#define TOY_BYTE_SHIFT_RIGHT(VALUE, SHIFT) (((VALUE) >> SHIFT) & 0xFF)
#define TOY_BYTE_SHIFT_LEFT(VALUE, SHIFT) (((VALUE) & 0xFF) << SHIFT)

struct toy_token_t* toy_lexer(char* text);

struct toy_node_unit_t* toy_parser(struct toy_token_t* tokens);

struct toy_vm_t* toy_vm_alloc(struct toy_in_t* in);
int toy_vm(struct toy_vm_t* self);
void toy_vm_class_add_func(struct toy_vm_class_t* class, struct toy_vm_func_t* func);
void toy_vm_add_class(struct toy_vm_t* self, struct toy_vm_class_t* class);

size_t toy_node_next_count(struct toy_node_next_t* self);

struct toy_out_t* toy_out_alloc(bool simulate);
void toy_out_write_verbose(struct toy_out_t* self, const char* format, ...);
void toy_out_write_flag(struct toy_out_t* self, uint8_t value, const char* format, ...);
void toy_out_write_uint8(struct toy_out_t* self, uint8_t value, const char* format, ...);
void toy_out_write_uint16(struct toy_out_t* self, uint16_t value, const char* format, ...);
void toy_out_write_uint32(struct toy_out_t* self, uint32_t value, const char* format, ...);
void toy_out_write_chars(struct toy_out_t* self, char* value, const char* format, ...);


struct toy_in_t* toy_in_alloc(uint8_t* bytes, size_t bytes_count);
void toy_in_read_skip(struct toy_in_t* self, size_t count);
bool toy_in_read_bool(struct toy_in_t* self);
uint8_t toy_in_read_uint8(struct toy_in_t* self);
uint16_t toy_in_read_uint16(struct toy_in_t* self);
uint32_t toy_in_read_uint32(struct toy_in_t* self);
char* toy_in_read_chars(struct toy_in_t* self);

#define toy_node_head_typed(SELF, CONTEXT) toy_node_head(TOY_CAST(SELF, struct toy_node_t*), CONTEXT)
#define toy_node_body_typed(SELF, CONTEXT) toy_node_body(TOY_CAST(SELF, struct toy_node_t*), CONTEXT)
#define toy_node_link_typed(SELF, CONTEXT) toy_node_link(TOY_CAST(SELF, struct toy_node_t*), CONTEXT)
#define toy_node_write_typed(SELF, CONTEXT, OUTPUT) toy_node_write(TOY_CAST(SELF, struct toy_node_t*), CONTEXT, OUTPUT)

void toy_node_head(struct toy_node_t* self, struct toy_context_t* context);
void toy_node_body(struct toy_node_t* self, struct toy_context_t* context);
void toy_node_link(struct toy_node_t* self, struct toy_context_t* context);
void toy_node_write(struct toy_node_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_head(struct toy_node_t* self, struct toy_context_t* context);
void toy_node_body(struct toy_node_t* self, struct toy_context_t* context);
void toy_node_link(struct toy_node_t* self, struct toy_context_t* context);
void toy_node_write(struct toy_node_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_unit_head(struct toy_node_unit_t* self, struct toy_context_t* context);
void toy_node_unit_body(struct toy_node_unit_t* self, struct toy_context_t* context);
void toy_node_unit_link(struct toy_node_unit_t* self, struct toy_context_t* context);
void toy_node_unit_write(struct toy_node_unit_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_class_head(struct toy_node_class_t* self, struct toy_context_t* context);
void toy_node_class_body(struct toy_node_class_t* self, struct toy_context_t* context);
void toy_node_class_link(struct toy_node_class_t* self, struct toy_context_t* context);
void toy_node_class_write(struct toy_node_class_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_field_head(struct toy_node_field_t* self, struct toy_context_t* context);
void toy_node_field_body(struct toy_node_field_t* self, struct toy_context_t* context);
void toy_node_field_link(struct toy_node_field_t* self, struct toy_context_t* context);
void toy_node_field_write(struct toy_node_field_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_func_head(struct toy_node_func_t* self, struct toy_context_t* context);
void toy_node_func_body(struct toy_node_func_t* self, struct toy_context_t* context);
void toy_node_func_link(struct toy_node_func_t* self, struct toy_context_t* context);
void toy_node_func_write(struct toy_node_func_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_arg_head(struct toy_node_arg_t* self, struct toy_context_t* context);
void toy_node_arg_body(struct toy_node_arg_t* self, struct toy_context_t* context);
void toy_node_arg_link(struct toy_node_arg_t* self, struct toy_context_t* context);
void toy_node_arg_write(struct toy_node_arg_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_stmt_head(struct toy_node_stmt_t* self, struct toy_context_t* context);
void toy_node_stmt_body(struct toy_node_stmt_t* self, struct toy_context_t* context);
void toy_node_stmt_link(struct toy_node_stmt_t* self, struct toy_context_t* context);
void toy_node_stmt_write(struct toy_node_stmt_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_stmt_return_head(struct toy_node_stmt_return_t* self, struct toy_context_t* context);
void toy_node_stmt_return_body(struct toy_node_stmt_return_t* self, struct toy_context_t* context);
void toy_node_stmt_return_link(struct toy_node_stmt_return_t* self, struct toy_context_t* context);
void toy_node_stmt_return_write(struct toy_node_stmt_return_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_stmt_if_head(struct toy_node_stmt_if_t* self, struct toy_context_t* context);
void toy_node_stmt_if_body(struct toy_node_stmt_if_t* self, struct toy_context_t* context);
void toy_node_stmt_if_link(struct toy_node_stmt_if_t* self, struct toy_context_t* context);
void toy_node_stmt_if_write(struct toy_node_stmt_if_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_stmt_while_head(struct toy_node_stmt_while_t* self, struct toy_context_t* context);
void toy_node_stmt_while_body(struct toy_node_stmt_while_t* self, struct toy_context_t* context);
void toy_node_stmt_while_link(struct toy_node_stmt_while_t* self, struct toy_context_t* context);
void toy_node_stmt_while_write(struct toy_node_stmt_while_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_stmt_exp_head(struct toy_node_stmt_exp_t* self, struct toy_context_t* context);
void toy_node_stmt_exp_body(struct toy_node_stmt_exp_t* self, struct toy_context_t* context);
void toy_node_stmt_exp_link(struct toy_node_stmt_exp_t* self, struct toy_context_t* context);
void toy_node_stmt_exp_write(struct toy_node_stmt_exp_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_head(struct toy_node_exp_t* self, struct toy_context_t* context);
void toy_node_exp_body(struct toy_node_exp_t* self, struct toy_context_t* context);
void toy_node_exp_link(struct toy_node_exp_t* self, struct toy_context_t* context);
void toy_node_exp_write(struct toy_node_exp_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_ternary_head(struct toy_node_exp_ternary_t* self, struct toy_context_t* context);
void toy_node_exp_ternary_body(struct toy_node_exp_ternary_t* self, struct toy_context_t* context);
void toy_node_exp_ternary_link(struct toy_node_exp_ternary_t* self, struct toy_context_t* context);
void toy_node_exp_ternary_write(struct toy_node_exp_ternary_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_or_head(struct toy_node_exp_or_t* self, struct toy_context_t* context);
void toy_node_exp_or_body(struct toy_node_exp_or_t* self, struct toy_context_t* context);
void toy_node_exp_or_link(struct toy_node_exp_or_t* self, struct toy_context_t* context);
void toy_node_exp_or_write(struct toy_node_exp_or_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_and_head(struct toy_node_exp_and_t* self, struct toy_context_t* context);
void toy_node_exp_and_body(struct toy_node_exp_and_t* self, struct toy_context_t* context);
void toy_node_exp_and_link(struct toy_node_exp_and_t* self, struct toy_context_t* context);
void toy_node_exp_and_write(struct toy_node_exp_and_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_eq_head(struct toy_node_exp_eq_t* self, struct toy_context_t* context);
void toy_node_exp_eq_body(struct toy_node_exp_eq_t* self, struct toy_context_t* context);
void toy_node_exp_eq_link(struct toy_node_exp_eq_t* self, struct toy_context_t* context);
void toy_node_exp_eq_write(struct toy_node_exp_eq_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_neq_head(struct toy_node_exp_neq_t* self, struct toy_context_t* context);
void toy_node_exp_neq_body(struct toy_node_exp_neq_t* self, struct toy_context_t* context);
void toy_node_exp_neq_link(struct toy_node_exp_neq_t* self, struct toy_context_t* context);
void toy_node_exp_neq_write(struct toy_node_exp_neq_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_gt_head(struct toy_node_exp_gt_t* self, struct toy_context_t* context);
void toy_node_exp_gt_body(struct toy_node_exp_gt_t* self, struct toy_context_t* context);
void toy_node_exp_gt_link(struct toy_node_exp_gt_t* self, struct toy_context_t* context);
void toy_node_exp_gt_write(struct toy_node_exp_gt_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_ge_head(struct toy_node_exp_ge_t* self, struct toy_context_t* context);
void toy_node_exp_ge_body(struct toy_node_exp_ge_t* self, struct toy_context_t* context);
void toy_node_exp_ge_link(struct toy_node_exp_ge_t* self, struct toy_context_t* context);
void toy_node_exp_ge_write(struct toy_node_exp_ge_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_lt_head(struct toy_node_exp_lt_t* self, struct toy_context_t* context);
void toy_node_exp_lt_body(struct toy_node_exp_lt_t* self, struct toy_context_t* context);
void toy_node_exp_lt_link(struct toy_node_exp_lt_t* self, struct toy_context_t* context);
void toy_node_exp_lt_write(struct toy_node_exp_lt_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_le_head(struct toy_node_exp_le_t* self, struct toy_context_t* context);
void toy_node_exp_le_body(struct toy_node_exp_le_t* self, struct toy_context_t* context);
void toy_node_exp_le_link(struct toy_node_exp_le_t* self, struct toy_context_t* context);
void toy_node_exp_le_write(struct toy_node_exp_le_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_sum_head(struct toy_node_exp_sum_t* self, struct toy_context_t* context);
void toy_node_exp_sum_body(struct toy_node_exp_sum_t* self, struct toy_context_t* context);
void toy_node_exp_sum_link(struct toy_node_exp_sum_t* self, struct toy_context_t* context);
void toy_node_exp_sum_write(struct toy_node_exp_sum_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_sub_head(struct toy_node_exp_sub_t* self, struct toy_context_t* context);
void toy_node_exp_sub_body(struct toy_node_exp_sub_t* self, struct toy_context_t* context);
void toy_node_exp_sub_link(struct toy_node_exp_sub_t* self, struct toy_context_t* context);
void toy_node_exp_sub_write(struct toy_node_exp_sub_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_mul_head(struct toy_node_exp_mul_t* self, struct toy_context_t* context);
void toy_node_exp_mul_body(struct toy_node_exp_mul_t* self, struct toy_context_t* context);
void toy_node_exp_mul_link(struct toy_node_exp_mul_t* self, struct toy_context_t* context);
void toy_node_exp_mul_write(struct toy_node_exp_mul_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_div_head(struct toy_node_exp_div_t* self, struct toy_context_t* context);
void toy_node_exp_div_body(struct toy_node_exp_div_t* self, struct toy_context_t* context);
void toy_node_exp_div_link(struct toy_node_exp_div_t* self, struct toy_context_t* context);
void toy_node_exp_div_write(struct toy_node_exp_div_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_neg_head(struct toy_node_exp_neg_t* self, struct toy_context_t* context);
void toy_node_exp_neg_body(struct toy_node_exp_neg_t* self, struct toy_context_t* context);
void toy_node_exp_neg_link(struct toy_node_exp_neg_t* self, struct toy_context_t* context);
void toy_node_exp_neg_write(struct toy_node_exp_neg_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_not_head(struct toy_node_exp_not_t* self, struct toy_context_t* context);
void toy_node_exp_not_body(struct toy_node_exp_not_t* self, struct toy_context_t* context);
void toy_node_exp_not_link(struct toy_node_exp_not_t* self, struct toy_context_t* context);
void toy_node_exp_not_write(struct toy_node_exp_not_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_id_head(struct toy_node_exp_id_t* self, struct toy_context_t* context);
void toy_node_exp_id_body(struct toy_node_exp_id_t* self, struct toy_context_t* context);
void toy_node_exp_id_link(struct toy_node_exp_id_t* self, struct toy_context_t* context);
void toy_node_exp_id_write(struct toy_node_exp_id_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_str_head(struct toy_node_exp_str_t* self, struct toy_context_t* context);
void toy_node_exp_str_body(struct toy_node_exp_str_t* self, struct toy_context_t* context);
void toy_node_exp_str_link(struct toy_node_exp_str_t* self, struct toy_context_t* context);
void toy_node_exp_str_write(struct toy_node_exp_str_t* self, struct toy_context_t* context, struct toy_out_t* out);

void toy_node_exp_num_head(struct toy_node_exp_num_t* self, struct toy_context_t* context);
void toy_node_exp_num_body(struct toy_node_exp_num_t* self, struct toy_context_t* context);
void toy_node_exp_num_link(struct toy_node_exp_num_t* self, struct toy_context_t* context);
void toy_node_exp_num_write(struct toy_node_exp_num_t* self, struct toy_context_t* context, struct toy_out_t* out);

#endif /* lexer_h */
