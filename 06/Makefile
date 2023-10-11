OPT=/opt/LLVM/15.0.0/bin/opt

all:
	clang++ -S -emit-llvm main.cpp
	$(OPT) --dot-cfg main_only.ll
	mv .main.dot main.dot
	dot -Tpng -O main.dot
	$(OPT) -O2 main_only.ll -o main.opt.ll
	$(OPT) --dot-cfg main.opt.ll
	mv .main.dot main.opt.dot
	dot -Tpng -O main.opt.dot