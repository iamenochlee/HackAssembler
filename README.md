## HackAssembler

An assembler for the Hack computer (Nand2Tetris). It parses Hack assembly language and produces 16-bit Hack machine code.

### Hack Assembly Language Rules

1. **A-Instructions**: `@value` where value is a number or symbol
2. **C-Instructions**: `dest=comp;jump`
   - `comp` is always required
   - If `dest` is empty, `jump` must be present (e.g., `0;JMP`)
   - If `jump` is empty, `dest` can be present (e.g., `D=M`)
3. **Labels**: `(LABEL_NAME)` - may be defined before use
4. **Comments**: `//` inline or whole line
5. **Whitespace**: Ignored

### Project Structure

```
frontend/
├── core/           # Main assembler logic
│   ├── assembler.c # the orchestrator
│   ├── parser.c    # Line parsing (A-instructions, C-instructions, labels)
│   └── analyzer.c  # Instruction validation and symbol resolution
├── helpers/        # Symbol and instruction management
│   ├── init.c      # Initialize symbol tables (dest, comp, jump)
│   ├── mutation.c  # Add symbols, instructions, diagnostics
│   └── query.c     # Validate dest/comp/jump, get symbol values
├── structures/     # Data structures
│   ├── map.c       # Symbol table implementation
│   └── vector.c    # Dynamic array for instructions/diagnostics
└── utils/          # Utilities
    ├── check.c     # Line type detection
    ├── get.c       # Parse C-instructions into components
    └── lines.c     # Line reading and sanitization

codegen/            # Binary code generation (future work)
test/asm/           # Test assembly files
```

### API

```c
#include "assembler.h"

AssemblerConfig config = {
    .generate_instructions = 1,  // 1 to generate, 0 for analysis only (useful for LSP)
    .debug = 0
};

AssemblerResult result = assemble(source_code, config);

// Access results:
// - result.instructions: Vector of validated instructions or NULL if AssemblerConfig.generate_instructions is 0
// - result.diagnostics: Vector of error messages
// - result.symbols: Resolved symbol table
// - dests, comps, and jump table

// free after use
AssemblerResult__free(result);
```

### Testing

Test files are provided in `test/asm/`:
- `Add.asm` - Simple addition program
- `Max.asm` - Computes max of two numbers
- `Pong.asm` - Full Pong game (large test file)

### Implementation Notes

- **Memory Management**: The assembler uses malloc/free throughout. All allocated memory is properly freed via `AssemblerResult__free()`
- **Error Handling**: Invalid instructions are caught during parsing/validation and reported with line numbers, when `AssemblerResult.diagnostics->size > 1` new instructions are longer added

### License

MIT
