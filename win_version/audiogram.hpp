#ifndef audiogramH
#define audiogramH
#endif

#include <System.Classes.hpp>
#include "common.hpp"

#include "Unit1.h"

bool __fastcall load_audiogram(TForm1 *main_frm);
void __fastcall unload_audiogram(TForm1 *main_frm);

void __fastcall validate_audiogram(TForm1 *main_frm);
void __fastcall edit_audiogram(TForm1 *main_frm);
void __fastcall delete_audiogram(TForm1 *main_frm);
void __fastcall cancel_audiogram(TForm1 *main_frm);

void __fastcall load_audiogram_grph_type(TForm1 *main_frm);
void __fastcall add_audiogram_grph_type(TForm1 *main_frm);

void __fastcall preview_audiogram_grph(TForm1 *main_frm);

