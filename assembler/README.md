

# nand2tetris assembler

As per chapter 6 of the book *The Elements of Computing Systems*  By Noam Nisan and Shimon Schocken (MIT Press)

[https://www.nand2tetris.org/project06]()

A C based two pass assembler that will take valid Hack specification assembly, and convert it into 16-bit machine code, runnable on the Hack CPU that was previously designed.

Symbolic syntax `dest = comp; jump`

Binary syntax `1 1 1 a c1 c2 c3 c4 c5 c6 d1 d2 d3 j1 j2 j3`


# Criteria

1. When loaded into your assembler, a `Prog.asm` file containing a valid Hack assembly language program should be translated into the correct Hack binary code and stored in a `Prog.hack` file.
1. The output produced by the assembler must be identical to the output produced by the Assembler supplied with the Nand2Tetris Software Suite.
1. The assembler must implement the translation specification given in Chapter 6, Section 2.

