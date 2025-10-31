## HackAssembler

An assembler for the Hack computer (Nand2Tetris). It parses Hack assembly and produces 16-bit Hack machine code.

### Frontend
The frontend focuses on parsing, symbol handling (predefined symbols, labels, variables), and diagnostics. Its entry is the function:

```c
AssemblerResult *assemble(char *source);
```

On success it returns an `AssemblerResult` with:
- instructions: validated A/C instructions ready for emission
- diagnostics: errors/warnings with line numbers and messages
- symbols: resolved symbol table (predefined + labels + variables)

Example shape of the result (conceptual):

```text
AssemblerResult {
  instructions: Vector<Instruction>,
  diagnostics:  Vector<Diagnostic>, // colored when printed (red/yellow)
  symbols:      Map,
}
```

### Codegen
Codegen takes validated instructions and emits final 16-bit binary strings (sets a-bit, packs comp/dest/jump, etc.). It assumes the frontend has already validated input and generally minimizes user-facing diagnostics in favor of direct emission.

### License
MIT
