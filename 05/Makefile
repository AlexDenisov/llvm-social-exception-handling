OPT=/opt/LLVM/15.0.0/bin/opt

all:
	clang main.c lock.c exceptions.c personality.c some_stuff_locked.ll
	$(OPT) --dot-cfg some_stuff_locked.ll
	mv .some_stuff_locked.dot some_stuff_locked.dot
	dot -Tpng -O some_stuff_locked.dot