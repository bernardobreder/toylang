//
//  node_exp.c
//  toy
//
//  Created by Bernardo Breder on 12/08/17.
//  Copyright © 2017 hvm. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "hvm.h"

void toy_node_exp_head(struct toy_node_exp_t* self, struct toy_context_t* context) {
    toy_node_head(TOY_CAST(self, struct toy_node_t*), context);
}

void toy_node_exp_body(struct toy_node_exp_t* self, struct toy_context_t* context) {
    toy_node_body(TOY_CAST(self, struct toy_node_t*), context);
}

void toy_node_exp_link(struct toy_node_exp_t* self, struct toy_context_t* context) {
    toy_node_link(TOY_CAST(self, struct toy_node_t*), context);
}

void toy_node_exp_write(struct toy_node_exp_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_write(TOY_CAST(self, struct toy_node_t*), context, out);
}

void toy_node_exp_ternary_head(struct toy_node_exp_ternary_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->exp, context);
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_ternary_body(struct toy_node_exp_ternary_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->exp, context);
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_ternary_link(struct toy_node_exp_ternary_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->exp, context);
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_ternary_write(struct toy_node_exp_ternary_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->exp, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_JUMP_FALSE, "Opcode Jump False");
    toy_out_write_uint16(out, self->false_diff_pc, "Number of bytes to Jump");
    toy_node_exp_write(self->left, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_JUMP, "Opcode Jump");
    toy_out_write_uint16(out, self->true_diff_pc, "Number of bytes to Jump");
    self->false_diff_pc = out->bytes_cur;
    toy_node_exp_write(self->right, context, out);
    self->true_diff_pc = out->bytes_cur;
    toy_out_write_uint8(out, TOY_OPCODE_BOOL_AND, "Opcode Boolean And");
}

void toy_node_exp_or_head(struct toy_node_exp_or_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_or_body(struct toy_node_exp_or_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_or_link(struct toy_node_exp_or_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_or_write(struct toy_node_exp_or_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_JUMP_TRUE, "Opcode Jump True");
    toy_out_write_uint16(out, self->true_diff_pc, "Address: 0x%04X", out->bytes_cur + 1 + self->true_diff_pc);
    size_t true_pc = out->bytes_cur;
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_BOOL_OR, "Opcode Boolean Or");
    self->true_diff_pc = out->bytes_cur - true_pc;
}

void toy_node_exp_and_head(struct toy_node_exp_and_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_and_body(struct toy_node_exp_and_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_and_link(struct toy_node_exp_and_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_and_write(struct toy_node_exp_and_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_JUMP_FALSE, "Opcode Jump False");
    toy_out_write_uint16(out, self->false_diff_pc, "Address: 0x%04X", out->bytes_cur + 1 + self->false_diff_pc);
    size_t false_pc = out->bytes_cur;
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_BOOL_AND, "Opcode Boolean And");
    self->false_diff_pc = out->bytes_cur - false_pc;
}

void toy_node_exp_eq_head(struct toy_node_exp_eq_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_eq_body(struct toy_node_exp_eq_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_eq_link(struct toy_node_exp_eq_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_eq_write(struct toy_node_exp_eq_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_EQ, "Opcode Number Equal");
}

void toy_node_exp_neq_head(struct toy_node_exp_neq_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_neq_body(struct toy_node_exp_neq_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_neq_link(struct toy_node_exp_neq_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_neq_write(struct toy_node_exp_neq_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_NEQ, "Opcode Number Not Equal");
}

void toy_node_exp_gt_head(struct toy_node_exp_gt_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_gt_body(struct toy_node_exp_gt_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_gt_link(struct toy_node_exp_gt_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_gt_write(struct toy_node_exp_gt_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_GT, "Opcode Number Grater Than");
}

void toy_node_exp_ge_head(struct toy_node_exp_ge_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_ge_body(struct toy_node_exp_ge_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_ge_link(struct toy_node_exp_ge_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_ge_write(struct toy_node_exp_ge_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_GE, "Opcode Number Greater Equal");
}

void toy_node_exp_lt_head(struct toy_node_exp_lt_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_lt_body(struct toy_node_exp_lt_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_lt_link(struct toy_node_exp_lt_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_lt_write(struct toy_node_exp_lt_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_LT, "Opcode Number Lower Than");
}

void toy_node_exp_le_head(struct toy_node_exp_le_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_le_body(struct toy_node_exp_le_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_le_link(struct toy_node_exp_le_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_le_write(struct toy_node_exp_le_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_LE, "Opcode Number Lower Equal");
}

void toy_node_exp_sum_head(struct toy_node_exp_sum_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_sum_body(struct toy_node_exp_sum_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_sum_link(struct toy_node_exp_sum_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_sum_write(struct toy_node_exp_sum_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_SUM, "Opcode Number Sum");
}

void toy_node_exp_sub_head(struct toy_node_exp_sub_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_sub_body(struct toy_node_exp_sub_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_sub_link(struct toy_node_exp_sub_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_sub_write(struct toy_node_exp_sub_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_SUB, "Opcode Number Sub");
}

void toy_node_exp_mul_head(struct toy_node_exp_mul_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_mul_body(struct toy_node_exp_mul_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_mul_link(struct toy_node_exp_mul_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_mul_write(struct toy_node_exp_mul_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_MUL, "Opcode Number Mul");
}

void toy_node_exp_div_head(struct toy_node_exp_div_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->left, context);
    toy_node_exp_head(self->right, context);
}

void toy_node_exp_div_body(struct toy_node_exp_div_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->left, context);
    toy_node_exp_body(self->right, context);
}

void toy_node_exp_div_link(struct toy_node_exp_div_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->left, context);
    toy_node_exp_link(self->right, context);
}

void toy_node_exp_div_write(struct toy_node_exp_div_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->left, context, out);
    toy_node_exp_write(self->right, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_DIV, "Opcode Number Div");
}

void toy_node_exp_neg_head(struct toy_node_exp_neg_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->exp, context);
}

void toy_node_exp_neg_body(struct toy_node_exp_neg_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->exp, context);
}

void toy_node_exp_neg_link(struct toy_node_exp_neg_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->exp, context);
}

void toy_node_exp_neg_write(struct toy_node_exp_neg_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->exp, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_NUM_NEG, "Opcode Number Negative");
}

void toy_node_exp_not_head(struct toy_node_exp_not_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->exp, context);
}

void toy_node_exp_not_body(struct toy_node_exp_not_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->exp, context);
}

void toy_node_exp_not_link(struct toy_node_exp_not_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->exp, context);
}

void toy_node_exp_not_write(struct toy_node_exp_not_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->exp, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_BOOL_NOT, "Opcode Boolean Not");
}

void toy_node_exp_id_head(struct toy_node_exp_id_t* self, struct toy_context_t* context) {

}

void toy_node_exp_id_body(struct toy_node_exp_id_t* self, struct toy_context_t* context) {

}

void toy_node_exp_id_link(struct toy_node_exp_id_t* self, struct toy_context_t* context) {

}

void toy_node_exp_id_write(struct toy_node_exp_id_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    
}

void toy_node_exp_str_head(struct toy_node_exp_str_t* self, struct toy_context_t* context) {

}

void toy_node_exp_str_body(struct toy_node_exp_str_t* self, struct toy_context_t* context) {

}

void toy_node_exp_str_link(struct toy_node_exp_str_t* self, struct toy_context_t* context) {

}

void toy_node_exp_str_write(struct toy_node_exp_str_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_out_write_uint8(out, TOY_OPCODE_CONST_STR, "Opcode Const Number");
    toy_out_write_chars(out, self->token->word, "Value: \"%s\"", self->token->word);
}

void toy_node_exp_num_head(struct toy_node_exp_num_t* self, struct toy_context_t* context) {

}

void toy_node_exp_num_body(struct toy_node_exp_num_t* self, struct toy_context_t* context) {
    sscanf(self->token->word, "%d", &self->value);
}

void toy_node_exp_num_link(struct toy_node_exp_num_t* self, struct toy_context_t* context) {

}

void toy_node_exp_num_write(struct toy_node_exp_num_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_out_write_uint8(out, TOY_OPCODE_CONST_NUM, "Opcode Const Number");
    toy_out_write_uint32(out, self->value, "Value: %d", self->value);
}
