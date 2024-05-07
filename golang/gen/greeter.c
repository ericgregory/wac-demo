// Generated by `wit-bindgen` 0.24.0. DO NOT EDIT!
#include "greeter.h"
#include <stdlib.h>
#include <string.h>

// Imported Functions from `greeter`

__attribute__((__import_module__("$root"), __import_name__("next")))
extern void __wasm_import_greeter_next(uint8_t *);

// Exported Functions from `greeter`

__attribute__((__weak__, __export_name__("cabi_post_greet")))
void __wasm_export_greeter_greet_post_return(uint8_t * arg0) {
  if ((*((size_t*) (arg0 + 4))) > 0) {
    free(*((uint8_t **) (arg0 + 0)));
  }
}

// Canonical ABI intrinsics

__attribute__((__weak__, __export_name__("cabi_realloc")))
void *cabi_realloc(void *ptr, size_t old_size, size_t align, size_t new_size) {
  (void) old_size;
  if (new_size == 0) return (void*) align;
  void *ret = realloc(ptr, new_size);
  if (!ret) abort();
  return ret;
}

// Helper Functions

void greeter_string_set(greeter_string_t *ret, const char*s) {
  ret->ptr = (uint8_t*) s;
  ret->len = strlen(s);
}

void greeter_string_dup(greeter_string_t *ret, const char*s) {
  ret->len = strlen(s);
  ret->ptr = (uint8_t*) cabi_realloc(NULL, 0, 1, ret->len * 1);
  memcpy(ret->ptr, s, ret->len * 1);
}

void greeter_string_free(greeter_string_t *ret) {
  if (ret->len > 0) {
    free(ret->ptr);
  }
  ret->ptr = NULL;
  ret->len = 0;
}

// Component Adapters

__attribute__((__aligned__(4)))
static uint8_t RET_AREA[8];

void greeter_next(greeter_string_t *ret) {
  __attribute__((__aligned__(4)))
  uint8_t ret_area[8];
  uint8_t *ptr = (uint8_t *) &ret_area;
  __wasm_import_greeter_next(ptr);
  *ret = (greeter_string_t) { (uint8_t*)(*((uint8_t **) (ptr + 0))), (*((size_t*) (ptr + 4))) };
}

__attribute__((__export_name__("greet")))
uint8_t * __wasm_export_greeter_greet(void) {
  greeter_string_t ret;
  greeter_greet(&ret);
  uint8_t *ptr = (uint8_t *) &RET_AREA;
  *((size_t*)(ptr + 4)) = (ret).len;
  *((uint8_t **)(ptr + 0)) = (uint8_t *) (ret).ptr;
  return ptr;
}

// Ensure that the *_component_type.o object is linked in

extern void __component_type_object_force_link_greeter(void);
void __component_type_object_force_link_greeter_public_use_in_this_compilation_unit(void) {
  __component_type_object_force_link_greeter();
}