//
//  vm.c
//  toy
//
//  Created by Bernardo Breder on 13/08/17.
//  Copyright © 2017 hvm. All rights reserved.
//

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "hvm.h"

struct toy_vm_t* toy_vm_alloc(struct toy_in_t* in) {
    struct toy_vm_class_t* cur_class = NIL;
    struct toy_vm_func_t* cur_func = NIL;
    MEMORY_ALLOC_NAMED(self, struct toy_vm_t);
    self->bytes_start = in->bytes;
    while (toy_in_read_uint8(in)) {
        MEMORY_ALLOC_NAMED(class, struct toy_vm_class_t);
        class->name = toy_in_read_chars(in);
        class->field_count = toy_in_read_uint16(in);
        class->func_count = toy_in_read_uint16(in);
        while (toy_in_read_uint8(in)) {
            MEMORY_ALLOC_NAMED(func, struct toy_vm_func_t);
            func->name = toy_in_read_chars(in);
            func->arg_count = toy_in_read_uint16(in);
            func->opcode_count = toy_in_read_uint16(in);
            func->opcodes = &in->bytes[in->bytes_cur];
            toy_in_read_skip(in, func->opcode_count);
            TOY_LIST_ADD(class->funcs, cur_func, func);
            if (!strcmp("main", func->name)) {
                self->main_func = func;
            }
        }
        TOY_LIST_ADD(self->classes, cur_class, class);
    }
    return self;
}

#define TOY_VM_READ_INT16(PC) (PC[0] << 8) + PC[1]; PC += 2;
#define TOY_VM_READ_INT32(PC) (PC[0] << 24) + (PC[1] << 16) + (PC[2] << 8) + PC[3]; PC += 4;

int toy_vm(struct toy_vm_t* self) {
    toy_out_verbose_inline("# Virtual Machine\n\n");
    uint16_t stack_count = 1024;
    struct toy_vm_stack_t stack[stack_count];
    struct toy_vm_stack_t* stack_cur = stack - 1;
    uint8_t* pc = self->main_func->opcodes;
    for (;;) {
        toy_out_verbose_inline("--- \n");
        toy_out_verbose_inline("#### State \n\n");
        toy_out_verbose_inline("| Address | Instruction | Argument | \n");
        toy_out_verbose_inline("| ------: | :---------- | :------: | \n");
        toy_out_verbose_inline("| 0x%04lX | ", pc - self->bytes_start);
        switch (*(pc++)) {
            case TOY_OPCODE_CONST_STR: {
                toy_out_verbose_inline("Const String | \n");
                break;
            }
            case TOY_OPCODE_CONST_NUM: {
                uint32_t value = TOY_VM_READ_INT32(pc);
                toy_out_verbose_inline("Const Number | %d | \n", value);
                stack_cur++;
                stack_cur->data.number = value;
                break;
            }
            case TOY_OPCODE_RETURN: {
                toy_out_verbose_inline("Return | \n");
                return 0;
            }
            case TOY_OPCODE_JUMP: {
                uint16_t value = TOY_VM_READ_INT16(pc);
                toy_out_verbose_inline("Jump | 0x%04lX | \n", (pc + value) - self->bytes_start);
                pc += value;
                break;
            }
            case TOY_OPCODE_JUMP_TRUE: {
                uint16_t value = TOY_VM_READ_INT16(pc);
                toy_out_verbose_inline("Jump True | 0x%04lX | \n", (pc + value) - self->bytes_start);
                if (stack_cur->data.number) {
                    pc += value;
                }
                break;
            }
            case TOY_OPCODE_JUMP_FALSE: {
                uint16_t value = TOY_VM_READ_INT16(pc);
                toy_out_verbose_inline("Jump False | 0x%04lX | \n", (pc + value) - self->bytes_start);
                if (!stack_cur->data.number) {
                    pc += value;
                }
                break;
            }
            case TOY_OPCODE_STACK_INC: {
                break;
            }
            case TOY_OPCODE_STACK_DEC: {
                break;
            }
            case TOY_OPCODE_STACK_DROP: {
                break;
            }
            case TOY_OPCODE_NUM_EQ: {
                toy_out_verbose_inline("Number Equal | \n");
                stack_cur--;
                stack_cur->data.number = stack_cur->data.number == (stack_cur+1)->data.number;
                break;
            }
            case TOY_OPCODE_NUM_NEQ: {
                toy_out_verbose_inline("Number Not Equal | \n");
                stack_cur--;
                stack_cur->data.number = stack_cur->data.number != (stack_cur+1)->data.number;
                break;
            }
            case TOY_OPCODE_NUM_GT: {
                toy_out_verbose_inline("Number Greater Than | \n");
                break;
            }
            case TOY_OPCODE_NUM_GE: {
                toy_out_verbose_inline("Number Greater Equal | \n");
                break;
            }
            case TOY_OPCODE_NUM_LT: {
                toy_out_verbose_inline("Number Lower Than | \n");
                break;
            }
            case TOY_OPCODE_NUM_LE: {
                toy_out_verbose_inline("Number Lower Equal | \n");
                break;
            }
            case TOY_OPCODE_NUM_SUM: {
                toy_out_verbose_inline("Number Sum | \n");
                stack_cur--;
                stack_cur->data.number = stack_cur->data.number + (stack_cur+1)->data.number;
                break;
            }
            case TOY_OPCODE_NUM_SUB: {
                toy_out_verbose_inline("Number Sub | \n");
                stack_cur--;
                stack_cur->data.number = stack_cur->data.number / (stack_cur+1)->data.number;
                break;
            }
            case TOY_OPCODE_NUM_MUL: {
                toy_out_verbose_inline("Number Mul | \n");
                stack_cur--;
                stack_cur->data.number = stack_cur->data.number * (stack_cur+1)->data.number;
                break;
            }
            case TOY_OPCODE_NUM_DIV: {
                toy_out_verbose_inline("Number Div | \n");
                stack_cur--;
                stack_cur->data.number = stack_cur->data.number / (stack_cur+1)->data.number;
                break;
            }
            case TOY_OPCODE_NUM_NEG: {
                toy_out_verbose_inline("Number Negative | \n");
                stack_cur->data.number = -stack_cur->data.number;
                break;
            }
            case TOY_OPCODE_BOOL_OR: {
                toy_out_verbose_inline("Boolean Or | \n");
                stack_cur--;
                stack_cur->data.number = stack_cur->data.number || (stack_cur+1)->data.number;
                break;
            }
            case TOY_OPCODE_BOOL_AND: {
                toy_out_verbose_inline("Boolean And | \n");
                stack_cur--;
                stack_cur->data.number = stack_cur->data.number && (stack_cur+1)->data.number;
                break;
            }
            case TOY_OPCODE_BOOL_NOT: {
                toy_out_verbose_inline("Boolean Not | \n");
                stack_cur->data.number = !stack_cur->data.number;
                break;
            }
        }
        toy_out_verbose_inline("\n");
        toy_out_verbose_inline("## Stack \n\n");
        {
            toy_out_verbose_inline("| Stack | \n");
            toy_out_verbose_inline("| :---: | \n");
            struct toy_vm_stack_t* stack_aux = stack_cur;
            while (stack_aux >= stack) {
                toy_out_verbose_inline("| %d | \n", stack_aux->data.number);
                stack_aux--;
            }
        }
    }
    return 0;
}

//void toy_vm_class_add_func(struct toy_vm_class_t* class, struct toy_vm_func_t* func) {
//    list_add
//}
//
//void toy_vm_add_class(struct toy_vm_t* self, struct toy_vm_class_t* class) {
//    
//}
