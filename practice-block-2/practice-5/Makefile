TASK_1 = ./task_1.c
TASK_RESULT_1 = ./build/task_1

TASK_2 = ./task_2.c
TASK_RESULT_2 = ./build/task_2

TASK_3 = ./task_3.c
TASK_RESULT_3 = ./build/task_3

.PHONY: all build_dir task_1 task_2 clean

clean:
	@rm -rf ./build

build_dir:
	@mkdir -p ./build

task_1: build_dir
	gcc $(TASK_1) -o $(TASK_RESULT_1)
	@echo ""
	$(TASK_RESULT_1)

task_2: build_dir
	gcc $(TASK_2) -o $(TASK_RESULT_2)
	@echo ""
	$(TASK_RESULT_2)

task_3: build_dir
	gcc $(TASK_3) -o $(TASK_RESULT_3)
	@echo ""
	$(TASK_RESULT_3)

