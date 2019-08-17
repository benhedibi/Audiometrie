#ifndef gainpH
#define gainpH
#endif

#include <System.Classes.hpp>
#include "common.hpp"

#include "Unit1.h"

bool __fastcall load_gainp(TForm1 *main_frm);
void __fastcall unload_gainp(TForm1 *main_frm);

void __fastcall validate_gainp(TForm1 *main_frm);
void __fastcall edit_gainp(TForm1 *main_frm);
void __fastcall delete_gainp(TForm1 *main_frm);
void __fastcall cancel_gainp(TForm1 *main_frm);

void __fastcall load_gainp_grph_type(TForm1 *main_frm);
void __fastcall add_gainp_grph_type(TForm1 *main_frm);

void __fastcall preview_gainp_grph(TForm1 *main_frm);
