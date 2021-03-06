extern crate libc;
extern crate regex;

mod note;

use note::{Note,Interval};
use std::ffi::{CStr, CString};

/// Given a string describing a note in scientific pitch (e.g. "C#5", "Dbb4",
/// "E0"), returns an integer representing the note as an unbounded MIDI note
/// number.
#[no_mangle]
pub unsafe extern fn musictheory_note_number(note: *mut libc::c_char) -> isize {
    let s = CStr::from_ptr(note).to_str().unwrap_or("");
    match Note::from_string(s) {
        Err(msg) => panic!(msg),
        Ok(note) => note.number()
    }
}

/// Given a note number (e.g. 61 is one semitone above middle C) and a letter
/// (as a character, e.g. 'D'), returns the correct enharmonic spelling of the
/// note built on that letter.
///
/// e.g.
/// musictheory_spell_note(61, 'C') => "C#4"
/// musictheory_spell_note(61, 'D') => "Db4"
#[no_mangle]
pub unsafe extern fn musictheory_spell_note(note_number: isize,
                                            letter: char) -> *mut libc::c_char {
    match Note::spell(note_number, letter) {
        Err(msg) => panic!(msg),
        Ok(note) => CString::new(note.to_string()).unwrap().into_raw()
    }
}

/// Given a note number and an interval (provided as a string like "m3" for
/// minor third, "M3" for major third, etc.), returns the number of the note
/// that interval above that note.
#[no_mangle]
pub unsafe extern fn musictheory_note_number_plus_interval(
    note_number: isize, interval: *mut libc::c_char) -> isize {
    let s = CStr::from_ptr(interval).to_str().unwrap_or("");
    match Interval::from_string(s) {
        Err(msg) => panic!(msg),
        Ok(interval) => Note::number_plus_interval(note_number, interval)
    }
}
