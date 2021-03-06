
#ifndef cheddar_generated_musictheory_h
#define cheddar_generated_musictheory_h


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>



/// Given a string describing a note in scientific pitch (e.g. "C#5", "Dbb4",
/// "E0"), returns an integer representing the note as an unbounded MIDI note
/// number.
intptr_t musictheory_note_number(char* note);

/// Given a note number (e.g. 61 is one semitone above middle C) and a letter
/// (as a character, e.g. 'D'), returns the correct enharmonic spelling of the
/// note built on that letter.
///
/// e.g.
/// musictheory_spell_note(61, 'C') => "C#4"
/// musictheory_spell_note(61, 'D') => "Db4"
char* musictheory_spell_note(intptr_t note_number, char letter);

/// Given a note number and an interval (provided as a string like "m3" for
/// minor third, "M3" for major third, etc.), returns the number of the note
/// that interval above that note.
intptr_t musictheory_note_number_plus_interval(intptr_t note_number, char* interval);



#ifdef __cplusplus
}
#endif


#endif
