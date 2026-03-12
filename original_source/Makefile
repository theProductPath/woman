HEADER = woman.h

OBJ = main.o highlt.o get_comm.o get_topics.o pick_topic.o pr_array.o\
	get_string.o pr_heading.o end_prog.o

woeman: $(OBJ)
	@echo "Compiling woeman..."
	@mcc -o woeman $(OBJ) -lcurses -ltermcap -g

$(OBJ): $(HEADER)
	@mcc -c $*.c -g
