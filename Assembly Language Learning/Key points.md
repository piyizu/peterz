# Key Points to Review
1. ? The indexed memory locations fail to work in cmov*cc* instructions. E.g. **cmove ar(, 1, 4), %eax** could not be understood.
2. ! Use '**pushal/popal**' instead of 'pushad/popad' when you are lazy and need to keep all the general register values in GNU ASM programs.
3. ! '**pushal/popal**' seemed to fail in certain case. I do not understand why GAS refuses to understand '**pushad/popad**' in AT&T style code.
