// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// i = R1
// while (i > 0)
//   R2 = R2 + R0
//   i = i - 1

@R1
D=M
@i
M=D

@R2
M=0

@R0
D=M
@COOKED
D;JEQ

@R1
D=M
@COOKED
D;JEQ

(LOOP)
  @R0
  D=M
  @R2
  M=D+M // R2=R2+R0

  @i
  M=M-1 // i=i-1
  D=M
  @COOKED
  D;JEQ // while (i > 0)

  @LOOP
  0;JMP

(COOKED)
  @COOKED
  0;JMP