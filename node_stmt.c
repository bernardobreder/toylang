//
//  node_stmt.c
//  toy
//
//  Created by Bernardo Breder on 12/08/17.
//  Copyright © 2017 hvm. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "hvm.h"

void toy_node_stmt_head(struct toy_node_stmt_t* self, struct toy_context_t* context) {
    toy_node_head(TOY_CAST(self, struct toy_node_t*), context);
}

void toy_node_stmt_body(struct toy_node_stmt_t* self, struct toy_context_t* context) {
    toy_node_body(TOY_CAST(self, struct toy_node_t*), context);
}

void toy_node_stmt_link(struct toy_node_stmt_t* self, struct toy_context_t* context) {
    toy_node_link(TOY_CAST(self, struct toy_node_t*), context);
}

void toy_node_stmt_write(struct toy_node_stmt_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_write(TOY_CAST(self, struct toy_node_t*), context, out);
}

void toy_node_stmt_return_head(struct toy_node_stmt_return_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->exp, context);
    if (self->next) { toy_node_stmt_head(self->next, context); }
}

void toy_node_stmt_return_body(struct toy_node_stmt_return_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->exp, context);
    if (self->next) { toy_node_stmt_body(self->next, context); }
}

void toy_node_stmt_return_link(struct toy_node_stmt_return_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->exp, context);
    if (self->next) { toy_node_stmt_link(self->next, context); }
}

void toy_node_stmt_return_write(struct toy_node_stmt_return_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->exp, context, out);
    toy_out_write_uint8(out, TOY_OPCODE_RETURN, "Opcode Return");
}

void toy_node_stmt_if_head(struct toy_node_stmt_if_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->exp, context);
    toy_node_stmt_head(self->stmt, context);
    if (self->next) { toy_node_stmt_head(self->next, context); }
}

void toy_node_stmt_if_body(struct toy_node_stmt_if_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->exp, context);
    toy_node_stmt_body(self->stmt, context);
    if (self->next) { toy_node_stmt_body(self->next, context); }
}

void toy_node_stmt_if_link(struct toy_node_stmt_if_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->exp, context);
    toy_node_stmt_link(self->stmt, context);
    if (self->next) { toy_node_stmt_link(self->next, context); }
}

void toy_node_stmt_if_write(struct toy_node_stmt_if_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->exp, context, out);
    
    toy_out_write_uint8(out, TOY_OPCODE_JUMP_FALSE, "Opcode Jump False");
    toy_out_write_uint16(out, self->false_diff_pc, "");
    
    size_t pc = out->bytes_cur;
    toy_node_stmt_write(self->stmt, context, out);
    
    self->false_diff_pc = out->bytes_cur - pc;
}

void toy_node_stmt_while_head(struct toy_node_stmt_while_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->exp, context);
    toy_node_stmt_head(self->stmt, context);
    if (self->next) { toy_node_stmt_head(self->next, context); }
}

void toy_node_stmt_while_body(struct toy_node_stmt_while_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->exp, context);
    toy_node_stmt_body(self->stmt, context);
    if (self->next) { toy_node_stmt_body(self->next, context); }
}

void toy_node_stmt_while_link(struct toy_node_stmt_while_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->exp, context);
    toy_node_stmt_link(self->stmt, context);
    if (self->next) { toy_node_stmt_link(self->next, context); }
}

void toy_node_stmt_while_write(struct toy_node_stmt_while_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    size_t begin_pc = out->bytes_cur;
    toy_node_exp_write(self->exp, context, out);
    
    toy_out_write_uint8(out, TOY_OPCODE_JUMP_FALSE, "Opcode Jump False");
    toy_out_write_uint16(out, self->false_diff_pc, "");
    
    size_t pc = out->bytes_cur;
    toy_node_stmt_write(self->stmt, context, out);
    
    toy_out_write_uint8(out, TOY_OPCODE_JUMP, "Opcode Jump");
    toy_out_write_uint16(out, self->begin_diff_pc, "");
    self->begin_diff_pc = begin_pc - out->bytes_cur;
    
    self->false_diff_pc = out->bytes_cur - pc;
}

void toy_node_stmt_exp_head(struct toy_node_stmt_exp_t* self, struct toy_context_t* context) {
    toy_node_exp_head(self->exp, context);
    if (self->next) { toy_node_stmt_head(self->next, context); }
}

void toy_node_stmt_exp_body(struct toy_node_stmt_exp_t* self, struct toy_context_t* context) {
    toy_node_exp_body(self->exp, context);
    if (self->next) { toy_node_stmt_body(self->next, context); }
}

void toy_node_stmt_exp_link(struct toy_node_stmt_exp_t* self, struct toy_context_t* context) {
    toy_node_exp_link(self->exp, context);
    if (self->next) { toy_node_stmt_link(self->next, context); }
}

void toy_node_stmt_exp_write(struct toy_node_stmt_exp_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_node_exp_write(self->exp, context, out);
    
    toy_out_write_uint8(out, TOY_OPCODE_STACK_DROP, "Opcode Stack Drop");
}
