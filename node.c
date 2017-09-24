//
//  node.c
//  toy
//
//  Created by Bernardo Breder on 12/08/17.
//  Copyright © 2017 hvm. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "hvm.h"

void toy_node_head(struct toy_node_t* self, struct toy_context_t* context) {
    if (!self) { return; }
    switch (self->type) {
        case TOY_NODE_CLASS_TYPE: toy_node_class_head(TOY_CAST(self, struct toy_node_class_t*), context); break;
        case TOY_NODE_FIELD_TYPE: toy_node_field_head(TOY_CAST(self, struct toy_node_field_t*), context); break;
        case TOY_NODE_FUNC_TYPE: toy_node_func_head(TOY_CAST(self, struct toy_node_func_t*), context); break;
        case TOY_NODE_ARG_TYPE: toy_node_arg_head(TOY_CAST(self, struct toy_node_arg_t*), context); break;
        case TOY_NODE_STMT_IF_TYPE: toy_node_stmt_if_head(TOY_CAST(self, struct toy_node_stmt_if_t*), context); break;
        case TOY_NODE_STMT_WHILE_TYPE: toy_node_stmt_while_head(TOY_CAST(self, struct toy_node_stmt_while_t*), context); break;
        case TOY_NODE_STMT_RETURN_TYPE: toy_node_stmt_return_head(TOY_CAST(self, struct toy_node_stmt_return_t*), context); break;
        case TOY_NODE_STMT_EXP_TYPE: toy_node_stmt_exp_head(TOY_CAST(self, struct toy_node_stmt_exp_t*), context); break;
        case TOY_NODE_EXP_TERNARY_TYPE: toy_node_exp_ternary_head(TOY_CAST(self, struct toy_node_exp_ternary_t*), context); break;
        case TOY_NODE_EXP_OR_TYPE: toy_node_exp_or_head(TOY_CAST(self, struct toy_node_exp_or_t*), context); break;
        case TOY_NODE_EXP_AND_TYPE: toy_node_exp_and_head(TOY_CAST(self, struct toy_node_exp_and_t*), context); break;
        case TOY_NODE_EXP_EQ_TYPE: toy_node_exp_eq_head(TOY_CAST(self, struct toy_node_exp_eq_t*), context); break;
        case TOY_NODE_EXP_NEQ_TYPE: toy_node_exp_neq_head(TOY_CAST(self, struct toy_node_exp_neq_t*), context); break;
        case TOY_NODE_EXP_GT_TYPE: toy_node_exp_gt_head(TOY_CAST(self, struct toy_node_exp_gt_t*), context); break;
        case TOY_NODE_EXP_GE_TYPE: toy_node_exp_ge_head(TOY_CAST(self, struct toy_node_exp_ge_t*), context); break;
        case TOY_NODE_EXP_LT_TYPE: toy_node_exp_lt_head(TOY_CAST(self, struct toy_node_exp_lt_t*), context); break;
        case TOY_NODE_EXP_LE_TYPE: toy_node_exp_le_head(TOY_CAST(self, struct toy_node_exp_le_t*), context); break;
        case TOY_NODE_EXP_SUM_TYPE: toy_node_exp_sum_head(TOY_CAST(self, struct toy_node_exp_sum_t*), context); break;
        case TOY_NODE_EXP_SUB_TYPE: toy_node_exp_sub_head(TOY_CAST(self, struct toy_node_exp_sub_t*), context); break;
        case TOY_NODE_EXP_MUL_TYPE: toy_node_exp_mul_head(TOY_CAST(self, struct toy_node_exp_mul_t*), context); break;
        case TOY_NODE_EXP_DIV_TYPE: toy_node_exp_div_head(TOY_CAST(self, struct toy_node_exp_div_t*), context); break;
        case TOY_NODE_EXP_NEG_TYPE: toy_node_exp_neg_head(TOY_CAST(self, struct toy_node_exp_neg_t*), context); break;
        case TOY_NODE_EXP_NOT_TYPE: toy_node_exp_not_head(TOY_CAST(self, struct toy_node_exp_not_t*), context); break;
        case TOY_NODE_EXP_ID_TYPE: toy_node_exp_id_head(TOY_CAST(self, struct toy_node_exp_id_t*), context); break;
        case TOY_NODE_EXP_STR_TYPE: toy_node_exp_str_head(TOY_CAST(self, struct toy_node_exp_str_t*), context); break;
        case TOY_NODE_EXP_NUM_TYPE: toy_node_exp_num_head(TOY_CAST(self, struct toy_node_exp_num_t*), context); break;
        default: printf("unexpected node type %d not in bound from %d to %d\n", self->type, TOY_NODE_MIN_TYPE, TOY_NODE_MAX_TYPE); exit(1);
    }
}

void toy_node_body(struct toy_node_t* self, struct toy_context_t* context) {
    if (!self) { return; }
    switch (self->type) {
        case TOY_NODE_CLASS_TYPE: toy_node_class_body(TOY_CAST(self, struct toy_node_class_t*), context); break;
        case TOY_NODE_FIELD_TYPE: toy_node_field_body(TOY_CAST(self, struct toy_node_field_t*), context); break;
        case TOY_NODE_FUNC_TYPE: toy_node_func_body(TOY_CAST(self, struct toy_node_func_t*), context); break;
        case TOY_NODE_ARG_TYPE: toy_node_arg_body(TOY_CAST(self, struct toy_node_arg_t*), context); break;
        case TOY_NODE_STMT_IF_TYPE: toy_node_stmt_if_body(TOY_CAST(self, struct toy_node_stmt_if_t*), context); break;
        case TOY_NODE_STMT_WHILE_TYPE: toy_node_stmt_while_body(TOY_CAST(self, struct toy_node_stmt_while_t*), context); break;
        case TOY_NODE_STMT_RETURN_TYPE: toy_node_stmt_return_body(TOY_CAST(self, struct toy_node_stmt_return_t*), context); break;
        case TOY_NODE_STMT_EXP_TYPE: toy_node_stmt_exp_body(TOY_CAST(self, struct toy_node_stmt_exp_t*), context); break;
        case TOY_NODE_EXP_TERNARY_TYPE: toy_node_exp_ternary_body(TOY_CAST(self, struct toy_node_exp_ternary_t*), context); break;
        case TOY_NODE_EXP_OR_TYPE: toy_node_exp_or_body(TOY_CAST(self, struct toy_node_exp_or_t*), context); break;
        case TOY_NODE_EXP_AND_TYPE: toy_node_exp_and_body(TOY_CAST(self, struct toy_node_exp_and_t*), context); break;
        case TOY_NODE_EXP_EQ_TYPE: toy_node_exp_eq_body(TOY_CAST(self, struct toy_node_exp_eq_t*), context); break;
        case TOY_NODE_EXP_NEQ_TYPE: toy_node_exp_neq_body(TOY_CAST(self, struct toy_node_exp_neq_t*), context); break;
        case TOY_NODE_EXP_GT_TYPE: toy_node_exp_gt_body(TOY_CAST(self, struct toy_node_exp_gt_t*), context); break;
        case TOY_NODE_EXP_GE_TYPE: toy_node_exp_ge_body(TOY_CAST(self, struct toy_node_exp_ge_t*), context); break;
        case TOY_NODE_EXP_LT_TYPE: toy_node_exp_lt_body(TOY_CAST(self, struct toy_node_exp_lt_t*), context); break;
        case TOY_NODE_EXP_LE_TYPE: toy_node_exp_le_body(TOY_CAST(self, struct toy_node_exp_le_t*), context); break;
        case TOY_NODE_EXP_SUM_TYPE: toy_node_exp_sum_body(TOY_CAST(self, struct toy_node_exp_sum_t*), context); break;
        case TOY_NODE_EXP_SUB_TYPE: toy_node_exp_sub_body(TOY_CAST(self, struct toy_node_exp_sub_t*), context); break;
        case TOY_NODE_EXP_MUL_TYPE: toy_node_exp_mul_body(TOY_CAST(self, struct toy_node_exp_mul_t*), context); break;
        case TOY_NODE_EXP_DIV_TYPE: toy_node_exp_div_body(TOY_CAST(self, struct toy_node_exp_div_t*), context); break;
        case TOY_NODE_EXP_NEG_TYPE: toy_node_exp_neg_body(TOY_CAST(self, struct toy_node_exp_neg_t*), context); break;
        case TOY_NODE_EXP_NOT_TYPE: toy_node_exp_not_body(TOY_CAST(self, struct toy_node_exp_not_t*), context); break;
        case TOY_NODE_EXP_ID_TYPE: toy_node_exp_id_body(TOY_CAST(self, struct toy_node_exp_id_t*), context); break;
        case TOY_NODE_EXP_STR_TYPE: toy_node_exp_str_body(TOY_CAST(self, struct toy_node_exp_str_t*), context); break;
        case TOY_NODE_EXP_NUM_TYPE: toy_node_exp_num_body(TOY_CAST(self, struct toy_node_exp_num_t*), context); break;
        default: printf("unexpected node type %d not in bound from %d to %d\n", self->type, TOY_NODE_MIN_TYPE, TOY_NODE_MAX_TYPE); exit(1);
    }
}

void toy_node_link(struct toy_node_t* self, struct toy_context_t* context) {
    if (!self) { return; }
    switch (self->type) {
        case TOY_NODE_CLASS_TYPE: toy_node_class_link(TOY_CAST(self, struct toy_node_class_t*), context); break;
        case TOY_NODE_FIELD_TYPE: toy_node_field_link(TOY_CAST(self, struct toy_node_field_t*), context); break;
        case TOY_NODE_FUNC_TYPE: toy_node_func_link(TOY_CAST(self, struct toy_node_func_t*), context); break;
        case TOY_NODE_ARG_TYPE: toy_node_arg_link(TOY_CAST(self, struct toy_node_arg_t*), context); break;
        case TOY_NODE_STMT_IF_TYPE: toy_node_stmt_if_link(TOY_CAST(self, struct toy_node_stmt_if_t*), context); break;
        case TOY_NODE_STMT_WHILE_TYPE: toy_node_stmt_while_link(TOY_CAST(self, struct toy_node_stmt_while_t*), context); break;
        case TOY_NODE_STMT_RETURN_TYPE: toy_node_stmt_return_link(TOY_CAST(self, struct toy_node_stmt_return_t*), context); break;
        case TOY_NODE_STMT_EXP_TYPE: toy_node_stmt_exp_link(TOY_CAST(self, struct toy_node_stmt_exp_t*), context); break;
        case TOY_NODE_EXP_TERNARY_TYPE: toy_node_exp_ternary_link(TOY_CAST(self, struct toy_node_exp_ternary_t*), context); break;
        case TOY_NODE_EXP_OR_TYPE: toy_node_exp_or_link(TOY_CAST(self, struct toy_node_exp_or_t*), context); break;
        case TOY_NODE_EXP_AND_TYPE: toy_node_exp_and_link(TOY_CAST(self, struct toy_node_exp_and_t*), context); break;
        case TOY_NODE_EXP_EQ_TYPE: toy_node_exp_eq_link(TOY_CAST(self, struct toy_node_exp_eq_t*), context); break;
        case TOY_NODE_EXP_NEQ_TYPE: toy_node_exp_neq_link(TOY_CAST(self, struct toy_node_exp_neq_t*), context); break;
        case TOY_NODE_EXP_GT_TYPE: toy_node_exp_gt_link(TOY_CAST(self, struct toy_node_exp_gt_t*), context); break;
        case TOY_NODE_EXP_GE_TYPE: toy_node_exp_ge_link(TOY_CAST(self, struct toy_node_exp_ge_t*), context); break;
        case TOY_NODE_EXP_LT_TYPE: toy_node_exp_lt_link(TOY_CAST(self, struct toy_node_exp_lt_t*), context); break;
        case TOY_NODE_EXP_LE_TYPE: toy_node_exp_le_link(TOY_CAST(self, struct toy_node_exp_le_t*), context); break;
        case TOY_NODE_EXP_SUM_TYPE: toy_node_exp_sum_link(TOY_CAST(self, struct toy_node_exp_sum_t*), context); break;
        case TOY_NODE_EXP_SUB_TYPE: toy_node_exp_sub_link(TOY_CAST(self, struct toy_node_exp_sub_t*), context); break;
        case TOY_NODE_EXP_MUL_TYPE: toy_node_exp_mul_link(TOY_CAST(self, struct toy_node_exp_mul_t*), context); break;
        case TOY_NODE_EXP_DIV_TYPE: toy_node_exp_div_link(TOY_CAST(self, struct toy_node_exp_div_t*), context); break;
        case TOY_NODE_EXP_NEG_TYPE: toy_node_exp_neg_link(TOY_CAST(self, struct toy_node_exp_neg_t*), context); break;
        case TOY_NODE_EXP_NOT_TYPE: toy_node_exp_not_link(TOY_CAST(self, struct toy_node_exp_not_t*), context); break;
        case TOY_NODE_EXP_ID_TYPE: toy_node_exp_id_link(TOY_CAST(self, struct toy_node_exp_id_t*), context); break;
        case TOY_NODE_EXP_STR_TYPE: toy_node_exp_str_link(TOY_CAST(self, struct toy_node_exp_str_t*), context); break;
        case TOY_NODE_EXP_NUM_TYPE: toy_node_exp_num_link(TOY_CAST(self, struct toy_node_exp_num_t*), context); break;
        default: printf("unexpected node type %d not in bound from %d to %d\n", self->type, TOY_NODE_MIN_TYPE, TOY_NODE_MAX_TYPE); exit(1);
    }
}

void toy_node_write(struct toy_node_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    if (!self) { return; }
    switch (self->type) {
        case TOY_NODE_CLASS_TYPE: toy_node_class_write(TOY_CAST(self, struct toy_node_class_t*), context, out); break;
        case TOY_NODE_FIELD_TYPE: toy_node_field_write(TOY_CAST(self, struct toy_node_field_t*), context, out); break;
        case TOY_NODE_FUNC_TYPE: toy_node_func_write(TOY_CAST(self, struct toy_node_func_t*), context, out); break;
        case TOY_NODE_ARG_TYPE: toy_node_arg_write(TOY_CAST(self, struct toy_node_arg_t*), context, out); break;
        case TOY_NODE_STMT_IF_TYPE: toy_node_stmt_if_write(TOY_CAST(self, struct toy_node_stmt_if_t*), context, out); break;
        case TOY_NODE_STMT_WHILE_TYPE: toy_node_stmt_while_write(TOY_CAST(self, struct toy_node_stmt_while_t*), context, out); break;
        case TOY_NODE_STMT_RETURN_TYPE: toy_node_stmt_return_write(TOY_CAST(self, struct toy_node_stmt_return_t*), context, out); break;
        case TOY_NODE_STMT_EXP_TYPE: toy_node_stmt_exp_write(TOY_CAST(self, struct toy_node_stmt_exp_t*), context, out); break;
        case TOY_NODE_EXP_TERNARY_TYPE: toy_node_exp_ternary_write(TOY_CAST(self, struct toy_node_exp_ternary_t*), context, out); break;
        case TOY_NODE_EXP_OR_TYPE: toy_node_exp_or_write(TOY_CAST(self, struct toy_node_exp_or_t*), context, out); break;
        case TOY_NODE_EXP_AND_TYPE: toy_node_exp_and_write(TOY_CAST(self, struct toy_node_exp_and_t*), context, out); break;
        case TOY_NODE_EXP_EQ_TYPE: toy_node_exp_eq_write(TOY_CAST(self, struct toy_node_exp_eq_t*), context, out); break;
        case TOY_NODE_EXP_NEQ_TYPE: toy_node_exp_neq_write(TOY_CAST(self, struct toy_node_exp_neq_t*), context, out); break;
        case TOY_NODE_EXP_GT_TYPE: toy_node_exp_gt_write(TOY_CAST(self, struct toy_node_exp_gt_t*), context, out); break;
        case TOY_NODE_EXP_GE_TYPE: toy_node_exp_ge_write(TOY_CAST(self, struct toy_node_exp_ge_t*), context, out); break;
        case TOY_NODE_EXP_LT_TYPE: toy_node_exp_lt_write(TOY_CAST(self, struct toy_node_exp_lt_t*), context, out); break;
        case TOY_NODE_EXP_LE_TYPE: toy_node_exp_le_write(TOY_CAST(self, struct toy_node_exp_le_t*), context, out); break;
        case TOY_NODE_EXP_SUM_TYPE: toy_node_exp_sum_write(TOY_CAST(self, struct toy_node_exp_sum_t*), context, out); break;
        case TOY_NODE_EXP_SUB_TYPE: toy_node_exp_sub_write(TOY_CAST(self, struct toy_node_exp_sub_t*), context, out); break;
        case TOY_NODE_EXP_MUL_TYPE: toy_node_exp_mul_write(TOY_CAST(self, struct toy_node_exp_mul_t*), context, out); break;
        case TOY_NODE_EXP_DIV_TYPE: toy_node_exp_div_write(TOY_CAST(self, struct toy_node_exp_div_t*), context, out); break;
        case TOY_NODE_EXP_NEG_TYPE: toy_node_exp_neg_write(TOY_CAST(self, struct toy_node_exp_neg_t*), context, out); break;
        case TOY_NODE_EXP_NOT_TYPE: toy_node_exp_not_write(TOY_CAST(self, struct toy_node_exp_not_t*), context, out); break;
        case TOY_NODE_EXP_ID_TYPE: toy_node_exp_id_write(TOY_CAST(self, struct toy_node_exp_id_t*), context, out); break;
        case TOY_NODE_EXP_STR_TYPE: toy_node_exp_str_write(TOY_CAST(self, struct toy_node_exp_str_t*), context, out); break;
        case TOY_NODE_EXP_NUM_TYPE: toy_node_exp_num_write(TOY_CAST(self, struct toy_node_exp_num_t*), context, out); break;
        default: printf("unexpected node type %d not in bound from %d to %d\n", self->type, TOY_NODE_MIN_TYPE, TOY_NODE_MAX_TYPE); exit(1);
    }
}

size_t toy_node_next_count(struct toy_node_next_t* self) {
    size_t count = 0;
    struct toy_node_next_t* aux = self;
    while (aux) {
        count++;
        aux = TOY_CAST(aux->next, struct toy_node_next_t*);
    }
    return count;
}
