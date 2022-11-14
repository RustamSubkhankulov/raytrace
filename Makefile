#==========================================================
#CONFIG
#==========================================================

# compilers
CXX  = g++
CC   = gcc

# object files output directory
OBJ_DIR = obj

# source files input directory
SRC_DIR = src

# header files directory
INC_DIR = include

# bool flag (0 or 1) - shows whether use flags ot not
USE_DEBUG_FLAGS = 0

#==========================================================
# FLAGS
#==========================================================

# flags for c++ 
CXXFLAGS = -O3

# flags for c
CFLAGS   = -O3

#----------------------------------------------------------

# flags needed to use with sfml
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#----------------------------------------------------------

ifeq ($(USE_DEBUG_FLAGS), 1)

	DEBUG_FLAGS = 												\
	-lubsan -D NDEBUG -g -std=c++20 -fmax-errors=1 				\
	-Wall -Wextra -Weffc++ -Waggressive-loop-optimizations  	\
	-Wc++0x-compat -Wc++11-compat -Wc++14-compat  				\
	-Wcast-qual -Wchar-subscripts -Wconditionally-supported 	\
	-Wconversion  -Wctor-dtor-privacy -Wempty-body 				\
	-Wfloat-equal -Wformat-nonliteral -Wformat-security 		\
	-Wformat-signedness -Wformat=2 -Winline  -Wlogical-op 		\
	-Wmissing-declarations  -Wnon-virtual-dtor -Wopenmp-simd	\
	-Woverloaded-virtual -Wpacked -Wpointer-arith 				\
	-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo	\
	-Wstack-usage=8192  -Wstrict-null-sentinel 					\
	-Wstrict-overflow=2 -Wsuggest-attribute=noreturn 			\
	-Wsuggest-final-methods -Wsuggest-final-types  				\
	-Wsuggest-override -Wswitch-default -Wswitch-enum 			\
	-Wsync-nand -Wundef  -Wunreachable-code -Wunused 			\
	-Wuseless-cast -Wvariadic-macros -Wno-literal-suffix 		\
	-Wno-missing-field-initializers -Wno-narrowing				\
	-Wno-old-style-cast -Wno-varargs -fcheck-new 				\
	-fsized-deallocation  -fstack-protector 					\
	-fstrict-overflow   -flto-odr-type-merging 					\
	-fno-omit-frame-pointer -fPIE -fsanitize=address  			\
	-fsanitize=bool -fsanitize=bounds -fsanitize=enum  			\
	-fsanitize=float-cast-overflow 								\
	-fsanitize=float-divide-by-zero 							\
	-fsanitize=integer-divide-by-zero -fsanitize=leak 			\
	-fsanitize=nonnull-attribute -fsanitize=null 				\
	-fsanitize=object-size -fsanitize=return 					\
	-fsanitize=returns-nonnull-attribute -fsanitize=shift 		\
	-fsanitize=signed-integer-overflow -fsanitize=undefined 	\
	-fsanitize=unreachable -fsanitize=vla-bound 				\
	-fsanitize=vptr -lm -pie

else

	FLAGS =

endif

#==========================================================
# OBJECT FILES LIST
#==========================================================

RTRACE_OBJ =  $(OBJ_DIR)/vector.o        		\
	  		  $(OBJ_DIR)/logs.o          		\
	  		  $(OBJ_DIR)/coordsys.o      		\
	  		  $(OBJ_DIR)/graphics.o	  	 		\
	  		  $(OBJ_DIR)/general.o		 		\
	  		  $(OBJ_DIR)/colour.o		 		\
	  		  $(OBJ_DIR)/raytrace.o				\
	  		  $(OBJ_DIR)/raytrace_test.o		\
			  $(OBJ_DIR)/objects.o				\
			  $(OBJ_DIR)/quadratic_equation.o	\
	  		  $(OBJ_DIR)/exception.o	

#==========================================================
# FUNCTIONS
#==========================================================

MINIMAL_DEP = $(SRC_DIR)/$(1)/$(1).cpp $(INC_DIR)/$(1)/$(1).hpp

#==========================================================
# TARGETS
#==========================================================

all: say_hello

#----------------------------------------------------------

rtrace: $(RTRACE_OBJ)
	$(CXX) $(RTRACE_OBJ) $(SFML_FLAGS) -o $(@)

#----------------------------------------------------------

$(OBJ_DIR)/objects.o:				$(SRC_DIR)/raytrace/objects.cpp							\
									$(INC_DIR)/raytrace/objects.hpp							\
									$(INC_DIR)/raytrace/raytrace.hpp
	$(CXX) 							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS)

#----------------------------------------------------------

$(OBJ_DIR)/raytrace.o:				$(SRC_DIR)/raytrace/raytrace.cpp						\
									$(INC_DIR)/raytrace/raytrace.hpp 						\
									$(INC_DIR)/raytrace/raytrace_conf.hpp 					\
									$(INC_DIR)/raytrace/objects.hpp 						
	$(CXX) 							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS)
									

#----------------------------------------------------------

$(OBJ_DIR)/raytrace_test.o:			$(SRC_DIR)/raytrace/raytrace_test.cpp					\
									$(INC_DIR)/raytrace/raytrace.hpp						\
									$(INC_DIR)/raytrace/objects.hpp							
	$(CXX) 							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS)

#----------------------------------------------------------

$(OBJ_DIR)/exception.o:				$(SRC_DIR)/mystd/exception/exception.cpp				\
									$(INC_DIR)/mystd/exception/exception.hpp
	$(CXX) 							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS)

#----------------------------------------------------------

$(OBJ_DIR)/vector.o:				$(call MINIMAL_DEP,vector)
	$(CXX) 							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS)

#----------------------------------------------------------

$(OBJ_DIR)/graphics.o: 				$(call MINIMAL_DEP,graphics)							\
									$(INC_DIR)/vector/vector.hpp 							\
									$(INC_DIR)/colour/colour.hpp 							\
									$(INC_DIR)/graphics/keys.hpp 							\
									$(INC_DIR)/coordsys/coordsys.hpp
	$(CXX)							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS)

#----------------------------------------------------------

$(OBJ_DIR)/logs.o:     				$(call MINIMAL_DEP,logs)								\
									$(INC_DIR)/logs/errors.h 								\
									codegen/err_descr.txt
	$(CXX) 							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS)

#----------------------------------------------------------

$(OBJ_DIR)/coordsys.o: 				$(call MINIMAL_DEP,coordsys)							\
									$(INC_DIR)/vector/vector.hpp 							
	$(CXX) 							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS) 

#----------------------------------------------------------

$(OBJ_DIR)/general.o:  				$(call MINIMAL_DEP,general)								\
									$(INC_DIR)/general/general_conf.hpp 
	$(CXX)							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS)

#----------------------------------------------------------

$(OBJ_DIR)/colour.o: 				$(call MINIMAL_DEP,colour)								\
									$(INC_DIR)/vector/vector.hpp 							
	$(CXX) 							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS) 

#----------------------------------------------------------

$(OBJ_DIR)/quadratic_equation.o: 	$(call MINIMAL_DEP,quadratic_equation)
	$(CXX) 							$(<) -c -o $(@) $(DEBUG_FLAGS) $(CXXFLAGS) 

#==========================================================
# .PHONY TARGETS
#==========================================================

.PHONY: dir clean say_hello

say_hello:
	@ echo "Please, specify make target"

dir:
	@ mkdir -p obj

clean:
	- rm $(OBJ_DIR)/*.o 
	- rm rtrace

#==========================================================
