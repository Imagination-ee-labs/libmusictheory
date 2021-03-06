#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musictheory.h"

void run_test(bool (test)(), const char* name, bool* passed) {
  if (test()) {
    fprintf(stderr, "PASSED: %s\n\n", name);
  } else {
    *passed = false;
    fprintf(stderr, "FAILED: %s\n\n", name);
  }
}

char* test_name;
bool passed;

void testing(char* name) {
  test_name = name;
  passed = true;
}

void test_int_equal_impl(int expected, int actual, int lineno) {
  if (actual != expected) {
    fprintf(stderr, "[%s (%s:%d)] Expected %d, got %d.\n",
            test_name, __FILE__, lineno, expected, actual);
    passed = false;
  }
}

void test_str_equal_impl(void* expected, void* actual, int lineno) {
  if (strcmp(expected, actual) != 0) {
    fprintf(stderr, "[%s (%s:%d)] Expected %s, got %s.\n",
            test_name, __FILE__, lineno, expected, actual);
    passed = false;
  }
}

#define test_int_equal(e, a) test_int_equal_impl(e, a, __LINE__)
#define test_str_equal(e, a) test_str_equal_impl(e, a, __LINE__)

bool test_note_number() {
  testing("note_number");

  test_int_equal(-3, musictheory_note_number("A-2"));
  test_int_equal(-2, musictheory_note_number("Bb-2"));
  test_int_equal(-1, musictheory_note_number("B-2"));
  test_int_equal(0, musictheory_note_number("B#-2"));
  test_int_equal(0, musictheory_note_number("C-1"));
  test_int_equal(12, musictheory_note_number("C0"));
  test_int_equal(21, musictheory_note_number("A0"));
  test_int_equal(24, musictheory_note_number("C1"));
  test_int_equal(27, musictheory_note_number("Eb1"));
  test_int_equal(36, musictheory_note_number("C2"));
  test_int_equal(48, musictheory_note_number("C3"));
  test_int_equal(60, musictheory_note_number("B#3"));
  test_int_equal(60, musictheory_note_number("C4"));
  test_int_equal(60, musictheory_note_number("Dbb4"));
  test_int_equal(61, musictheory_note_number("C#4"));
  test_int_equal(61, musictheory_note_number("Db4"));
  test_int_equal(62, musictheory_note_number("C##4"));
  test_int_equal(62, musictheory_note_number("D4"));
  test_int_equal(62, musictheory_note_number("Ebb4"));
  test_int_equal(63, musictheory_note_number("Eb4"));
  test_int_equal(64, musictheory_note_number("D##4"));
  test_int_equal(64, musictheory_note_number("E4"));
  test_int_equal(69, musictheory_note_number("A4"));
  test_int_equal(72, musictheory_note_number("C5"));
  test_int_equal(127, musictheory_note_number("G9"));
  test_int_equal(128, musictheory_note_number("G#9"));
  test_int_equal(129, musictheory_note_number("A9"));

  return passed;
}

bool test_spell_note() {
  testing("spell_note");

  test_str_equal("C-1", musictheory_spell_note(0, 'C'));
  test_str_equal("C0", musictheory_spell_note(12, 'C'));
  test_str_equal("C1", musictheory_spell_note(24, 'C'));
  test_str_equal("C2", musictheory_spell_note(36, 'C'));
  test_str_equal("C3", musictheory_spell_note(48, 'C'));
  test_str_equal("B#3", musictheory_spell_note(60, 'B'));
  test_str_equal("C4", musictheory_spell_note(60, 'C'));
  test_str_equal("C#4", musictheory_spell_note(61, 'C'));
  test_str_equal("Db4", musictheory_spell_note(61, 'D'));
  test_str_equal("C##4", musictheory_spell_note(62, 'C'));
  test_str_equal("D4", musictheory_spell_note(62, 'D'));
  test_str_equal("Ebb4", musictheory_spell_note(62, 'E'));
  test_str_equal("Eb4", musictheory_spell_note(63, 'E'));
  test_str_equal("E4", musictheory_spell_note(64, 'E'));
  test_str_equal("C5", musictheory_spell_note(72, 'C'));

  return passed;
}

bool test_note_number_plus_interval() {
  testing("note_number_plus_interval");

  test_int_equal(65, musictheory_note_number_plus_interval(60, "P4"));
  test_int_equal(63, musictheory_note_number_plus_interval(60, "m3"));
  test_int_equal(72, musictheory_note_number_plus_interval(60, "P8"));
  test_int_equal(69, musictheory_note_number_plus_interval(60, "M6"));

  return passed;
}

int main() {
  bool passed = true;

  printf("\n%s\n\n", "-----");

  run_test(test_note_number, "test_note_number", &passed);
  run_test(test_spell_note, "test_spell_note", &passed);
  run_test(test_note_number_plus_interval, "test_note_number_plus_interval", &passed);

  printf("%s\n\n", "-----");

  return passed ? 0 : 1;
}
