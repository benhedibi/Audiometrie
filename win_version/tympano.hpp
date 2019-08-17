#ifndef tympanogramH
#define tympanogramH
#endif

#include <System.Classes.hpp>
#include "common.hpp"

#include "Unit1.h"

bool __fastcall load_tympanogram(TForm1 *main_frm);
void __fastcall unload_tympanogram(TForm1 *main_frm);

void __fastcall validate_tympanogram(TForm1 *main_frm);
void __fastcall edit_tympanogram(TForm1 *main_frm);
void __fastcall delete_tympanogram(TForm1 *main_frm);
void __fastcall cancel_tympanogram(TForm1 *main_frm);

void __fastcall load_tympanogram_grph_type(TForm1 *main_frm);
void __fastcall add_tympanogram_grph_type(TForm1 *main_frm);

void __fastcall preview_tympanogram_grph(TForm1 *main_frm);

