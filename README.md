## HackAssembler

An assembler for the Hack computer (Nand2Tetris). It parses Hack assembly and produces 16-bit Hack machine code.

### Frontend
The frontend focuses on parsing, symbol handling (predefined symbols, labels, variables), and diagnostics. Its entry is the function:

```c
#include "assembler.h"
AssemblerResult *assemble(char *source, AssemblerConfig config);
```

On success it returns an `AssemblerResult` with:
- instructions: validated A/C instructions ready for emission
- diagnostics: errors/warnings with line numbers and messages
- symbols: resolved symbol table (predefined + labels + variables)
- dests, comps, and jump static table


### Codegen
Codegen takes validated instructions and emits final 16-bit binary string. It assumes the frontend has already validated input and generally minimizes user-facing diagnostics in favor of direct emission.

### License
MIT
