#ifndef audiovocH
#define audiovocH
#endif

#include <System.Classes.hpp>
#include "common.hpp"

#include "Unit1.h"

bool __fastcall load_audiovoc(TForm1 *main_frm);
void __fastcall unload_audiovoc(TForm1 *main_frm);

void __fastcall validate_audiovoc(TForm1 *main_frm);
void __fastcall edit_audiovoc(TForm1 *main_frm);
void __fastcall delete_audiovoc(TForm1 *main_frm);
void __fastcall cancel_audiovoc(TForm1 *main_frm);

void __fastcall load_audiovoc_grph_type(TForm1 *main_frm);
void __fastcall add_audiovoc_grph_type(TForm1 *main_frm);

void __fastcall preview_audiovoc_grph(TForm1 *main_frm);

