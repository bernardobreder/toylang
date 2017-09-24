//
//  main.c
//  hvm
//
//  Created by Bernardo Breder on 12/08/17.
//  Copyright © 2017 hvm. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "hvm.h"

int main(int argc, const char * argv[]) {
    char* code = "class a { a func main () { return (1+2)/3==4 and 5!=6 and 1==1 } func b (a, b, c) { return a + b } }";
//    char* code = "class a { a func main () { return 0 and 1 and 2 and 3 } }";
    struct toy_token_t* tokens = toy_lexer(code);
    struct toy_node_unit_t* node = toy_parser(tokens);
    
    MEMORY_ALLOC_NAMED(context, struct toy_context_t);
    toy_node_unit_head(node, context);
    toy_node_unit_body(node, context);
    toy_node_unit_link(node, context);
    
    struct toy_out_t* out_sim = toy_out_alloc(TRUE);
    toy_node_unit_write(node, context, out_sim);
    
    struct toy_out_t* out = toy_out_alloc(FALSE);
    toy_node_unit_write(node, context, out);
    
    struct toy_in_t* in = toy_in_alloc(out->bytes, out->bytes_cur);
    
    struct toy_vm_t* vm = toy_vm_alloc(in);
    if (vm->main_func) {
        toy_vm(vm);
    } else {
        toy_out_verbose_inline("> Not found main function in any class\n\n");
    }
    
    return 0;
}
