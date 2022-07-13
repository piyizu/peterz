# Rename single code file "main.s" and then make
compiler := as
linker := ld
obj := main.o

main : $(obj)
	$(linker) $(obj) -dynamic-linker /lib/ld-linux.so.2 -lc -m elf_i386 -o ./main

main.o : main.s
	$(compiler) ./main.s --32 -o ./main.o

.PHONY : clean
clean : 
	rm -f ./main
	rm -f $(obj)
