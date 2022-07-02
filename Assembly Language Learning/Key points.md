# Key Points to Review
1. ? The indexed memory locations fail to work in cmov*cc* instructions. E.g. **cmove ar(, 1, 4), %eax** could not be understood.
2. ! Use '**pushal/popal**' instead of 'pushad/popad' when you are lazy and need to keep all the general register values in GNU ASM programs.
3. ~~! '**pushal/popal**' seemed to fail in certain case. I do not understand why GAS refuses to understand '**pushad/popad**' in AT&T style code.~~ ( It was my fault. It is important to use 'pushal' and 'popal' at the right position and the right moment!) **USE 'PUSHAL/POPAL CAREFULLY! YOU SHOULD KNOW WHAT YOU ARE DOWING WHEN YOU TYPE 'PUSHAL/POPAL'. DO NOT USE IT JUST BEFORE THE 'CALL' INSTRUCTION! THE CALLEE MAY NEED THE STACK'S ON-TOP VALUES.**
4. ! It seems that indexed memory positions are not supported in many instructions such as 'cmov*cc*' and 'pushl'. Use other memory indexing methods like indirect memory positions, e.g. 4(%esp) .
5. ! OF and CF: OF(the overflow flag) is for signed values and CF(the carry flag) is for unsigned values. Be careful when manipulating both signed and unsigned values simultaneously.
