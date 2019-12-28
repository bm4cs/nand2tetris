// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.



@pixel_state_past //0xFFFF=black, 0x0000=white
M=-1
D=0
@PREPARE
0;JMP

(MAIN)
  @KBD
  D=M

  @PREPARE
  D;JEQ // if no key, leave D=0
  D=-1 // else -1


(PREPARE)
// Determine what to set pixels to (i.e. on [-1]  or off [0])
// Keep a record of previous, to save on repainting.
// Uses the D register to represent desired state.

  @pixel_state
  M=D
  @pixel_state_old
  D=D-M

  @MAIN
  D;JEQ // dont repaint if equal

  @pixel_state
  D=M
  @pixel_state_old
  M=D

  @SCREEN
  D=A
  @8192
  D=D+A
  @pixel_pointer
  M=D // setup pointer


(RENDER)
  @pixel_pointer
  D=M-1
  M=D

  @MAIN
  D;JLT // if (pixel_pointer<0) return

  @pixel_state
  D=M //what pixel value

  @pixel_pointer
  A=M //where to write pixel
  M=D //write it

  @RENDER
  0;JMP //rinse and repeat
