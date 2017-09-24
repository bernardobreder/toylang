//
//  parser.c
//  hvm
//
//  Created by Bernardo Breder on 12/08/17.
//  Copyright © 2017 hvm. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hvm.h"

struct toy_node_stmt_t* toy_parser_stmt(struct toy_token_t** tokens);

struct toy_node_exp_t* toy_parser_exp(struct toy_token_t** tokens);

bool toy_parser_eof(struct toy_token_t** tokens) {
    return !TOY_TOKEN_GET(tokens);
}

void toy_parser_token(struct toy_token_t** tokens, const char* name) {
    if (!TOY_TOKEN_EQUAL(name, TOY_TOKEN_WORD(tokens))) {
        printf("expected '%s' but was '%s'\n", name, TOY_TOKEN_WORD(tokens)); exit(1);
    }
    TOY_TOKEN_NEXT(tokens);
}

bool toy_parser_has(struct toy_token_t** tokens, const char* name) {
    return TOY_TOKEN_EQUAL(name, TOY_TOKEN_WORD(tokens));
}

bool toy_parser_has_next(struct toy_token_t** tokens, const char* name) {
    return TOY_TOKEN_EQUAL(name, TOY_TOKEN_WORD_NEXT(tokens));
}

bool toy_parser_try(struct toy_token_t** tokens, const char* name) {
    if (toy_parser_has(tokens, name)) {
        TOY_TOKEN_NEXT(tokens);
        return TRUE;
    }
    return FALSE;
}

char* toy_parser_id(struct toy_token_t** tokens) {
    if (!TOY_TOKEN_IS_ID(tokens)) {
        printf("expected <ID> but was '%s'\n", TOY_TOKEN_WORD(tokens)); exit(1);
    }
    char* word = TOY_TOKEN_WORD(tokens);
    TOY_TOKEN_NEXT(tokens);
    return word;
}

struct toy_node_exp_t* toy_parser_exp_num(struct toy_token_t** tokens) {
    TOY_NODE_ALLOC(struct toy_node_exp_num_t, node, TOY_NODE_EXP_NUM_TYPE);
    node->token = TOY_TOKEN_GET(tokens);
    TOY_TOKEN_NEXT(tokens);
    return TOY_CAST(node, struct toy_node_exp_t*);
}

struct toy_node_exp_t* toy_parser_exp_str(struct toy_token_t** tokens) {
    TOY_NODE_ALLOC(struct toy_node_exp_str_t, node, TOY_NODE_EXP_STR_TYPE);
    node->token = TOY_TOKEN_GET(tokens);
    TOY_TOKEN_NEXT(tokens);
    return TOY_CAST(node, struct toy_node_exp_t*);
}

struct toy_node_exp_t* toy_parser_exp_id(struct toy_token_t** tokens) {
    TOY_NODE_ALLOC(struct toy_node_exp_id_t, node, TOY_NODE_EXP_ID_TYPE);
    node->token = TOY_TOKEN_GET(tokens);
    TOY_TOKEN_NEXT(tokens);
    return TOY_CAST(node, struct toy_node_exp_t*);
}

struct toy_node_exp_t* toy_parser_exp_param(struct toy_token_t** tokens) {
    toy_parser_token(tokens, "(");
    struct toy_node_exp_t* exp = toy_parser_exp(tokens);
    toy_parser_token(tokens, ")");
    return exp;
}

struct toy_node_exp_t* toy_parser_exp_literal(struct toy_token_t** tokens) {
    if (toy_parser_has(tokens, "(")) {
        return toy_parser_exp_param(tokens);
    } else if (TOY_TOKEN_IS_ID(tokens)) {
        return toy_parser_exp_id(tokens);
    } else if (TOY_TOKEN_IS_STR(tokens)) {
        return toy_parser_exp_str(tokens);
    } else if (TOY_TOKEN_IS_NUM(tokens)) {
        return toy_parser_exp_num(tokens);
    }
    return 0;
}

struct toy_node_exp_t* toy_parser_exp_unary(struct toy_token_t** tokens) {
    if (toy_parser_try(tokens, "-")) {
        TOY_NODE_ALLOC(struct toy_node_exp_neg_t, node, TOY_NODE_EXP_NEG_TYPE);
        node->exp = toy_parser_exp_literal(tokens);
        return TOY_CAST(node, struct toy_node_exp_t*);
    } else if (toy_parser_try(tokens, "!")) {
        TOY_NODE_ALLOC(struct toy_node_exp_not_t, node, TOY_NODE_EXP_NOT_TYPE);
        node->exp = toy_parser_exp_literal(tokens);
        return TOY_CAST(node, struct toy_node_exp_t*);
    } else {
        return toy_parser_exp_literal(tokens);
    }
}

struct toy_node_exp_t* toy_parser_exp_mul(struct toy_token_t** tokens) {
    struct toy_node_exp_t* left = toy_parser_exp_unary(tokens);
    while (toy_parser_has(tokens, "*") || toy_parser_has(tokens, "/")) {
        if (toy_parser_try(tokens, "*")) {
            TOY_NODE_ALLOC(struct toy_node_exp_mul_t, node, TOY_NODE_EXP_MUL_TYPE);
            node->left = left;
            node->right = toy_parser_exp_mul(tokens);
            left = TOY_CAST(node, struct toy_node_exp_t*);
        } else if (toy_parser_try(tokens, "/")) {
            TOY_NODE_ALLOC(struct toy_node_exp_div_t, node, TOY_NODE_EXP_DIV_TYPE);
            node->left = left;
            node->right = toy_parser_exp_mul(tokens);
            left = TOY_CAST(node, struct toy_node_exp_t*);
        }
    }
    return left;
}

struct toy_node_exp_t* toy_parser_exp_sum(struct toy_token_t** tokens) {
    struct toy_node_exp_t* left = toy_parser_exp_mul(tokens);
    while (toy_parser_has(tokens, "+") || toy_parser_has(tokens, "-")) {
        if (toy_parser_try(tokens, "+")) {
            TOY_NODE_ALLOC(struct toy_node_exp_sum_t, node, TOY_NODE_EXP_SUM_TYPE);
            node->left = left;
            node->right = toy_parser_exp_sum(tokens);
            left = TOY_CAST(node, struct toy_node_exp_t*);
        } else if (toy_parser_try(tokens, "-")) {
            TOY_NODE_ALLOC(struct toy_node_exp_sub_t, node, TOY_NODE_EXP_SUB_TYPE);
            node->left = left;
            node->right = toy_parser_exp_sum(tokens);
            left = TOY_CAST(node, struct toy_node_exp_t*);
        }
    }
    return left;
}

struct toy_node_exp_t* toy_parser_exp_compare(struct toy_token_t** tokens) {
    struct toy_node_exp_t* left = toy_parser_exp_sum(tokens);
    while ((toy_parser_has(tokens, "=") && toy_parser_has_next(tokens, "=")) || (toy_parser_has(tokens, "!") && toy_parser_has_next(tokens, "=")) || toy_parser_has(tokens, ">") || toy_parser_has(tokens, "<")) {
        if (toy_parser_has(tokens, "=") && toy_parser_has_next(tokens, "=")) {
            TOY_TOKEN_NEXT(tokens); TOY_TOKEN_NEXT(tokens);
            TOY_NODE_ALLOC(struct toy_node_exp_eq_t, node, TOY_NODE_EXP_EQ_TYPE);
            node->left = left;
            node->right = toy_parser_exp_sum(tokens);
            left = TOY_CAST(node, struct toy_node_exp_t*);
        } else if (toy_parser_has(tokens, "!") && toy_parser_has_next(tokens, "=")) {
            TOY_TOKEN_NEXT(tokens); TOY_TOKEN_NEXT(tokens);
            TOY_NODE_ALLOC(struct toy_node_exp_neq_t, node, TOY_NODE_EXP_NEQ_TYPE);
            node->left = left;
            node->right = toy_parser_exp_sum(tokens);
            left = TOY_CAST(node, struct toy_node_exp_t*);
        } else if (toy_parser_has(tokens, ">") && toy_parser_has_next(tokens, "=")) {
            TOY_TOKEN_NEXT(tokens); TOY_TOKEN_NEXT(tokens);
            TOY_NODE_ALLOC(struct toy_node_exp_ge_t, node, TOY_NODE_EXP_GE_TYPE);
            node->left = left;
            node->right = toy_parser_exp_sum(tokens);
            left = TOY_CAST(node, struct toy_node_exp_t*);
        } else if (toy_parser_has(tokens, "<") && toy_parser_has_next(tokens, "=")) {
            TOY_TOKEN_NEXT(tokens); TOY_TOKEN_NEXT(tokens);
            TOY_NODE_ALLOC(struct toy_node_exp_le_t, node, TOY_NODE_EXP_LE_TYPE);
            node->left = left;
            node->right = toy_parser_exp_sum(tokens);
            left = TOY_CAST(node, struct toy_node_exp_t*);
        } else if (toy_parser_try(tokens, ">")) {
            TOY_NODE_ALLOC(struct toy_node_exp_gt_t, node, TOY_NODE_EXP_GT_TYPE);
            node->left = left;
            node->right = toy_parser_exp_sum(tokens);
            left = TOY_CAST(node, struct toy_node_exp_t*);
        } else if (toy_parser_try(tokens, "<")) {
            TOY_NODE_ALLOC(struct toy_node_exp_lt_t, node, TOY_NODE_EXP_LT_TYPE);
            node->left = left;
            node->right = toy_parser_exp_sum(tokens);
            left = TOY_CAST(node, struct toy_node_exp_t*);
        }
    }
    return left;
}

struct toy_node_exp_t* toy_parser_exp_and(struct toy_token_t** tokens) {
    struct toy_node_exp_t* left = toy_parser_exp_compare(tokens);
    if (toy_parser_try(tokens, "and")) {
        TOY_NODE_ALLOC(struct toy_node_exp_and_t, node, TOY_NODE_EXP_AND_TYPE);
        node->left = left;
        node->right = toy_parser_exp_and(tokens);
        left = TOY_CAST(node, struct toy_node_exp_t*);
    }
    return left;
}

struct toy_node_exp_t* toy_parser_exp_or(struct toy_token_t** tokens) {
    struct toy_node_exp_t* left = toy_parser_exp_and(tokens);
    if (toy_parser_try(tokens, "or")) {
        TOY_NODE_ALLOC(struct toy_node_exp_or_t, node, TOY_NODE_EXP_OR_TYPE);
        node->left = left;
        node->right = toy_parser_exp_or(tokens);
        left = TOY_CAST(node, struct toy_node_exp_t*);
    }
    return left;
}

struct toy_node_exp_t* toy_parser_exp_ternary(struct toy_token_t** tokens) {
    struct toy_node_exp_t* exp = toy_parser_exp_or(tokens);
    if (toy_parser_try(tokens, "?")) {
        TOY_NODE_ALLOC(struct toy_node_exp_ternary_t, node, TOY_NODE_EXP_TERNARY_TYPE);
        node->exp = exp;
        node->left = toy_parser_exp_ternary(tokens);
        toy_parser_token(tokens, ":");
        node->right = toy_parser_exp_ternary(tokens);
        exp = TOY_CAST(node, struct toy_node_exp_t*);
    }
    return exp;
}

struct toy_node_exp_t* toy_parser_exp(struct toy_token_t** tokens) {
    return toy_parser_exp_ternary(tokens);
}

struct toy_node_stmt_t* toy_parser_stmt_exp(struct toy_token_t** tokens) {
    TOY_NODE_ALLOC(struct toy_node_stmt_exp_t, node, TOY_NODE_STMT_EXP_TYPE);
    node->exp = toy_parser_exp(tokens);
    return TOY_CAST(node, struct toy_node_stmt_t*);
}

struct toy_node_stmt_t* toy_parser_stmt_if(struct toy_token_t** tokens) {
    toy_parser_token(tokens, "if");
    TOY_NODE_ALLOC(struct toy_node_stmt_if_t, node, TOY_NODE_STMT_IF_TYPE);
    node->exp = toy_parser_exp(tokens);
    node->stmt = toy_parser_stmt(tokens);
    return TOY_CAST(node, struct toy_node_stmt_t*);
}

struct toy_node_stmt_t* toy_parser_stmt_while(struct toy_token_t** tokens) {
    TOY_NODE_ALLOC(struct toy_node_stmt_while_t, node, TOY_NODE_STMT_WHILE_TYPE);
    toy_parser_token(tokens, "while");
    node->exp = toy_parser_exp(tokens);
    node->stmt = toy_parser_stmt(tokens);
    return TOY_CAST(node, struct toy_node_stmt_t*);
}

struct toy_node_stmt_t* toy_parser_stmt_return(struct toy_token_t** tokens) {
    TOY_NODE_ALLOC(struct toy_node_stmt_return_t, node, TOY_NODE_STMT_RETURN_TYPE);
    toy_parser_token(tokens, "return");
    node->exp = toy_parser_exp(tokens);
    return TOY_CAST(node, struct toy_node_stmt_t*);
}

struct toy_node_stmt_t* toy_parser_stmt_block(struct toy_token_t** tokens) {
    struct toy_node_stmt_t *stmts = NIL, *stmt = NIL;
    toy_parser_token(tokens, "{");
    while (!toy_parser_try(tokens, "}")) {
        struct toy_node_stmt_t* stmt_node = toy_parser_stmt(tokens);
        TOY_LIST_ADD(stmts, stmt, stmt_node);
    }
    return stmts;
}

struct toy_node_stmt_t* toy_parser_stmt(struct toy_token_t** tokens) {
    if (toy_parser_has(tokens, "{")) {
        return toy_parser_stmt_block(tokens);
    } else if (toy_parser_has(tokens, "if")) {
        return toy_parser_stmt_if(tokens);
    } else if (toy_parser_has(tokens, "while")) {
        return toy_parser_stmt_while(tokens);
    } else if (toy_parser_has(tokens, "return")) {
        return toy_parser_stmt_return(tokens);
    } else {
        return toy_parser_stmt_exp(tokens);
    }
}

struct toy_node_field_t* toy_parser_field(struct toy_token_t** tokens) {
    TOY_NODE_ALLOC(struct toy_node_field_t, node, TOY_NODE_FIELD_TYPE);
    node->name = strdup(toy_parser_id(tokens));
    return node;
}

struct toy_node_arg_t* toy_parser_arg(struct toy_token_t** tokens) {
    TOY_NODE_ALLOC(struct toy_node_arg_t, node, TOY_NODE_ARG_TYPE);
    node->name = strdup(toy_parser_id(tokens));
    return node;
}

struct toy_node_arg_t* toy_parser_args(struct toy_token_t** tokens) {
    struct toy_node_arg_t *args = NIL, *arg = NIL;
    toy_parser_token(tokens, "(");
    if (!toy_parser_try(tokens, ")")) {
        struct toy_node_arg_t* arg_node = toy_parser_arg(tokens);
        TOY_LIST_ADD(args, arg, arg_node);
        while (toy_parser_try(tokens, ",")) {
            struct toy_node_arg_t* arg_node = toy_parser_arg(tokens);
            TOY_LIST_ADD(args, arg, arg_node);
        }
        toy_parser_token(tokens, ")");
    }
    return args;
}

struct toy_node_func_t* toy_parser_func(struct toy_token_t** tokens) {
    TOY_NODE_ALLOC(struct toy_node_func_t, node, TOY_NODE_FUNC_TYPE);
    toy_parser_token(tokens, "func");
    node->name = strdup(toy_parser_id(tokens));
    node->args = toy_parser_args(tokens);
    node->stmt = toy_parser_stmt(tokens);
    return node;
}

struct toy_node_class_t* toy_parser_class(struct toy_token_t** tokens) {
    TOY_NODE_ALLOC(struct toy_node_class_t, node, TOY_NODE_CLASS_TYPE);
    toy_parser_token(tokens, "class");
    node->name = strdup(toy_parser_id(tokens));
    toy_parser_token(tokens, "{");
    struct toy_node_field_t* field = NIL;
    struct toy_node_func_t* func = NIL;
    while (!toy_parser_try(tokens, "}")) {
        if (toy_parser_has(tokens, "func")) {
            struct toy_node_func_t* func_node = toy_parser_func(tokens);
            TOY_LIST_ADD(node->funcs, func, func_node);
        } else {
            struct toy_node_field_t* field_node = toy_parser_field(tokens);
            TOY_LIST_ADD(node->fields, field, field_node);
        }
    }
    return node;
}

struct toy_node_class_t* toy_parser_classes(struct toy_token_t** tokens) {
    struct toy_node_class_t *list = NIL, *cur = NIL;
    while (!toy_parser_eof(tokens)) {
        struct toy_node_class_t* node = toy_parser_class(tokens);
        TOY_LIST_ADD(list, cur, node);
    }
    return list;
}

struct toy_node_unit_t* toy_parser(struct toy_token_t* tokens) {
    TOY_NODE_ALLOC(struct toy_node_unit_t, node, TOY_NODE_CLASS_TYPE);
    node->classes = toy_parser_classes(&tokens);
    return node;
}
