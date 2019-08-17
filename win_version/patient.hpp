#ifndef patientH
#define patientH
#endif

#include <System.Classes.hpp>
#include "common.hpp"

#include "Unit1.h"

bool __fastcall load_patient(TForm1 *main_frm);
void __fastcall unload_patient(TForm1 *main_frm);

void __fastcall validate_patient(TForm1 *main_frm);
void __fastcall edit_patient(TForm1 *main_frm);
void __fastcall delete_patient(TForm1 *main_frm);
void __fastcall cancel_patient(TForm1 *main_frm);

