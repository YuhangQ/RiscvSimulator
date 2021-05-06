#pragma once

void jumpTo(std::string&);
void jumpTo(int);

// JAL
bool jal();

// JALR
bool jalr();

// BRANCH
bool beq();
bool bne();
bool blt();
bool bge();
bool bltu();
bool bgeu();

// pseudo
bool j();
bool jr();
bool ret();
bool call();
bool tail();

// pseudo branch
bool beqz();
bool bnez();
bool blez();
bool bgez();
bool bltz();
bool bgtz();
bool bgt();
bool ble();
bool bgtu();
bool bleu();
