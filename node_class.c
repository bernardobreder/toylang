//
//  node_class.c
//  toy
//
//  Created by Bernardo Breder on 12/08/17.
//  Copyright © 2017 hvm. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "hvm.h"

void toy_node_unit_head(struct toy_node_unit_t* self, struct toy_context_t* context) {
    toy_out_verbose_inline("# Unit Compilation\n-----\n");
    toy_node_head_typed(self->classes, context);
}

void toy_node_unit_body(struct toy_node_unit_t* self, struct toy_context_t* context) {
    toy_node_body_typed(self->classes, context);
}

void toy_node_unit_link(struct toy_node_unit_t* self, struct toy_context_t* context) {
    toy_node_link_typed(self->classes, context);
}

void toy_node_unit_write(struct toy_node_unit_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    if (out->simulate) {
        toy_node_class_write(self->classes, context, out);
    } else {
        toy_out_verbose_inline("# Bytes Structured\n\n");
        toy_out_verbose_inline("| Address | Bytes | Value | Description |\n");
        toy_out_verbose_inline("| :-----: | :---- | :---: | :---------- |\n");
        toy_node_class_write(self->classes, context, out);
        
        toy_out_verbose_inline("# Bytes as Array\n\n");
        toy_out_verbose_inline("| Address | 0x0 | 0x1 | 0x2 | 0x3 | 0x4 | 0x5 | 0x6 | 0x7 | 0x8 | 0x9 | 0xA | 0xB | 0xC | 0xD | 0xE | 0xF |\n");
        toy_out_verbose_inline("| ------: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |\n");
        size_t n; for (n = 0 ; n < out->bytes_cur ;) {
            toy_out_verbose_inline("| **0x%04X** ", TOY_CAST(n, uint16_t));
            int m; for (m = 0 ; m < 16 ; m++, n++) {
                if (n < out->bytes_cur) {
                    toy_out_verbose_inline("| 0x%02X ", out->bytes[n]);
                } else {
                    toy_out_verbose_inline("| - ");
                }
            }
            toy_out_verbose_inline("|\n");
        }
        toy_out_verbose_inline("\n");
    }
}

void toy_node_class_head(struct toy_node_class_t* self, struct toy_context_t* context) {
    toy_out_verbose_inline("## Class: %s\n\n", self->name);
    toy_out_verbose_inline("* **Field Count**: %d\n", self->field_count);
    toy_out_verbose_inline("* **Method Count**: %d\n", self->func_count);
    self->class_index = context->class_count++;
    toy_node_head_typed(self->fields, context);
    toy_node_head_typed(self->funcs, context);
    if (self->next) { toy_node_class_head(self->next, context); }
}

void toy_node_class_body(struct toy_node_class_t* self, struct toy_context_t* context) {
    self->field_count = TOY_CAST(toy_node_next_count(TOY_CAST(self->fields, struct toy_node_next_t*)), uint16_t);
    self->func_count = TOY_CAST(toy_node_next_count(TOY_CAST(self->funcs, struct toy_node_next_t*)), uint16_t);
    toy_node_body_typed(self->fields, context);
    toy_node_body_typed(self->funcs, context);
    if (self->next) { toy_node_class_body(self->next, context); }
}

void toy_node_class_link(struct toy_node_class_t* self, struct toy_context_t* context) {
    toy_node_link_typed(self->fields, context);
    toy_node_link_typed(self->funcs, context);
    if (self->next) { toy_node_class_link(self->next, context); }
}

void toy_node_class_write(struct toy_node_class_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_out_write_flag(out, TRUE, "There are more Class to be read");
    toy_out_write_chars(out, self->name, "Name of Class");
    toy_out_write_uint16(out, self->field_count, "Number of Fields");
    toy_node_field_write(self->fields, context, out);
    toy_out_write_uint16(out, self->func_count, "Number of Func");
    toy_node_func_write(self->funcs, context, out);
    if (self->next) { toy_node_class_write(self->next, context, out); }
    else { toy_out_write_flag(out, FALSE, "There aren't more Class to read"); }
}

void toy_node_field_head(struct toy_node_field_t* self, struct toy_context_t* context) {
    toy_out_verbose_inline("### Field: %s\n\n", self->name);
    if (self->next) { toy_node_field_head(self->next, context); }
}

void toy_node_field_body(struct toy_node_field_t* self, struct toy_context_t* context) {
    if (self->next) { toy_node_field_body(self->next, context); }
}

void toy_node_field_link(struct toy_node_field_t* self, struct toy_context_t* context) {
    if (self->next) { toy_node_field_link(self->next, context); }
}

void toy_node_field_write(struct toy_node_field_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    
}

void toy_node_func_head(struct toy_node_func_t* self, struct toy_context_t* context) {
    toy_out_verbose_inline("### Method: %s\n\n", self->name);
    toy_out_verbose_inline("* **Number of Arguments**: %d\n\n", self->arg_count);
    toy_node_head_typed(self->args, context);
    toy_node_head_typed(self->stmt, context);
    if (self->next) { toy_node_func_head(self->next, context); }
}

void toy_node_func_body(struct toy_node_func_t* self, struct toy_context_t* context) {
    self->arg_count = TOY_CAST(toy_node_next_count(TOY_CAST(self->args, struct toy_node_next_t*)), uint16_t);
    toy_node_body_typed(self->args, context);
    toy_node_body_typed(self->stmt, context);
    if (self->next) { toy_node_func_body(self->next, context); }
}

void toy_node_func_link(struct toy_node_func_t* self, struct toy_context_t* context) {
    toy_node_link_typed(self->args, context);
    toy_node_link_typed(self->stmt, context);
    if (self->next) { toy_node_func_link(self->next, context); }
}

void toy_node_func_write(struct toy_node_func_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    toy_out_write_flag(out, TRUE, "There are more Func to be read");
    toy_out_write_chars(out, self->name, "Name of Func");
    
    toy_out_write_uint16(out, self->arg_count, "Number of Arguments");
    toy_node_arg_write(self->args, context, out);
    
    toy_out_write_uint16(out, self->opcode_count, "Number of Opcodes bytes");
    
    self->pc = out->bytes_cur;
    toy_out_write_verbose(out, "Start Func Code");
    toy_node_stmt_write(self->stmt, context, out);
    toy_out_write_verbose(out, "End Func Code");
    self->opcode_count = out->bytes_cur - self->pc;
    
    if (self->next) { toy_node_func_write(self->next, context, out); }
    else { toy_out_write_flag(out, FALSE, "There aren't more Func to read"); }
}

void toy_node_arg_head(struct toy_node_arg_t* self, struct toy_context_t* context) {
    if (self->next) { toy_node_arg_head(self->next, context); }
}

void toy_node_arg_body(struct toy_node_arg_t* self, struct toy_context_t* context) {
    if (self->next) { toy_node_arg_body(self->next, context); }
}

void toy_node_arg_link(struct toy_node_arg_t* self, struct toy_context_t* context) {
    if (self->next) { toy_node_arg_link(self->next, context); }
}

void toy_node_arg_write(struct toy_node_arg_t* self, struct toy_context_t* context, struct toy_out_t* out) {
    
}
