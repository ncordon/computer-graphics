########################################################################
##
## archivo 'include.make'
##
## definiciones comunes para todos los binarios
## requiere definir:
##
##   - target_name
##   - units_loc (unidades locales, en el mismo directorio donde se crea el binario)
##   - units     (otras unidades, en los directorios de fuentes, objs....)



## *********************************************************************
##
## invalidar definiciones de pattern rules predefinidias, definir targets

.SUFFIXES:
.PHONY: x, all, compile_all



## *********************************************************************
## objs

objs_no_loc   := $(addprefix $(objs_dir)/, $(addsuffix .o, $(notdir $(units))))
objs_loc      := $(addsuffix .o, $(notdir $(units_loc)))
objs          := $(objs_loc) $(objs_no_loc)  $(objs_jpg)

## *********************************************************************
## librerías para el enlazador (puede depender del S.O. y de la GPU)

uname:=$(shell uname -s)

ifeq ($(uname),Darwin)
    os          := OSX
    lib_gl      := -framework OpenGL
    lib_glut    := -framework GLUT
    lib_glu     := /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGLU.dylib
    lib_aux     := $(lib_glu)
    depr        := -Wdeprecated-declarations
else
    os          := LINUX
    lib_gl_std  := -lGL
    lib_gl_nv1  := /usr/lib/nvidia-340-updates/libGL.so
    lib_gl_nv2  := /usr/lib/nvidia-304/libGL.so
    ifeq ($(wildcard $(lib_gl_nv1)),$(lib_gl_nv1))
   	    lib_gl  := $(lib_gl_nv1)
    else ifeq ($(wildcard $(lib_gl_nv2)),$(lib_gl_nv2))
            lib_gl  := $(lib_gl_nv2)
    else
   	    lib_gl  := $(lib_gl_std)   
    endif
    lib_glut    := -lglut
    lib_glu     := -lGLU
    lib_aux     := -lGLEW $(lib_glu)
endif

lib_jpg         := -L/opt/local/lib -ljpeg

## flags enlazador
ld_flags  := $(lib_dir_loc) $(lib_aux) $(lib_glut) $(lib_gl) $(lib_jpg)


## flags compilador:
os_flag  := -D$(os)
c_flags  := -I$(include_dir) -I$(extra_inc_dir) $(os_flag) $(opt_dbg_flag) $(exit_first) $(warn_all) 


## *********************************************************************
## auxiliares:

raya:=---------------------------------------------------------------

##
## funcion para compilar
## llamar con:
##     $(call compilar, $<, $@)

compilar =\
   echo `tput bold`$(raya);\
   echo Compilando: $(notdir $(1));\
   tput sgr0 ;\
   echo g++ $(c_flags) -c $(1) -o $(2) ;\
   g++ $(c_flags) -c $(1) -o $(2)

## *********************************************************************
## targets

x: $(target_name)
	@echo "S.O.       :" $(os)
	@echo "Ejecutando :" $(target_name) " ...."
	./$(target_name)
 
all:
	make clean
	make compile_all

compile_all: $(target_name) 

## *********************************************************************
## enlazar

$(target_name) : $(objs)
	@echo `tput bold`$(raya)
	@echo "S.O.    : " $(os)
	@echo Enlazando: $(target_name) ....
	@tput sgr0
	g++ -o $(target_name) $(objs) $(ld_flags)
	@echo $(raya)

## *********************************************************************
## compilar una unidad

## localmente (fuente y obj en el directorio de trabajo)

%.o: %.cpp
	@$(call compilar,$<,$@)

## ---------------------------------------------------------------------
## no localmente (fuente en $(srcs_dir), obj en $(objs_dir)

$(objs_dir)/%.o: $(srcs_dir)/%.cpp
	@$(call compilar,$<,$@)
   
$(objs_dir)/%.o: $(srcs_dir)/%.cc
	@$(call compilar,$<,$@)
   
$(objs_dir)/%.o: $(srcs_dir)/%.c
	@$(call compilar,$<,$@)

## ---------------------------------------------------------------------
## en el directorio 'srcs'
   
$(objs_dir)/%.o: $(jpg_srcs_dir)/%.c
	@$(call compilar,$<,$@)
      
$(objs_dir)/%.o: $(jpg_srcs_dir)/%.cpp
	@$(call compilar,$<,$@)
   
## *********************************************************************
## limpiar

clean:
	rm -f $(objs_dir)/*.o *.o $(target_name)
	



