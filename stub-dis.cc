/* Stub functions to interface to the GNU disassembler library
    (libopcodes).
   Copyright 2001, 2003 Brian R. Gaeke.

This file is part of VMIPS.

VMIPS is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

VMIPS is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with VMIPS; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#include "sysinclude.h"
#include "vmips.h"
#include "stub-dis.h"

extern "C" { 

#include "bfd.h"
#include "dis-asm.h"

}

static struct disassemble_info disasm_info;

bool
setup_disassembler (FILE *stream)
{
	/* Set up for libopcodes. */
	INIT_DISASSEMBLE_INFO(disasm_info, stream, fprintf);
	disasm_info.buffer_length = 4;
	return true; /* success */
}

void
call_disassembler(uint32 pc, uint32 instr)
{
	/* Point libopcodes at the instruction... */
	disasm_info.buffer_vma = pc;
	disasm_info.buffer = (bfd_byte *) &instr;

	/* Disassemble the instruction, which is in *host* byte order. */
	if (machine->host_bigendian) {
		print_insn_big_mips(pc, &disasm_info);
	} else {
		print_insn_little_mips(pc, &disasm_info);
	}
	putc('\n', (FILE *)disasm_info.stream);   /* End the line. */
}
