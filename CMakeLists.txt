cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(This InChI)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)


set(Headers
    INCHI-1-SRC/INCHI_BASE/src/bcf_s.h
    INCHI-1-SRC/INCHI_BASE/src/ichi_io.h
    INCHI-1-SRC/INCHI_BASE/src/ichi.h
    INCHI-1-SRC/INCHI_BASE/src/ichi_bns.h
    INCHI-1-SRC/INCHI_BASE/src/extr_ct.h
    INCHI-1-SRC/INCHI_BASE/src/bcf_s.h
    INCHI-1-SRC/INCHI_BASE/src/ichimain.h
    INCHI-1-SRC/INCHI_BASE/src/ichierr.h
    INCHI-1-SRC/INCHI_BASE/src/ichidrp.h
    INCHI-1-SRC/INCHI_BASE/src/ichicomp.h
    INCHI-1-SRC/INCHI_BASE/src/ichicomn.h
    INCHI-1-SRC/INCHI_BASE/src/ichicant.h
    INCHI-1-SRC/INCHI_BASE/src/ichicano.h
    INCHI-1-SRC/INCHI_BASE/src/ichimake.h
    INCHI-1-SRC/INCHI_BASE/src/ichinorm.h
    INCHI-1-SRC/INCHI_BASE/src/ichiring.h
    INCHI-1-SRC/INCHI_BASE/src/ikey_base26.h
    INCHI-1-SRC/INCHI_BASE/src/ichitime.h
    INCHI-1-SRC/INCHI_BASE/src/ichitaut.h
    INCHI-1-SRC/INCHI_BASE/src/ichister.h
    INCHI-1-SRC/INCHI_BASE/src/ichisize.h
    INCHI-1-SRC/INCHI_BASE/src/ichirvrs.h
    INCHI-1-SRC/INCHI_BASE/src/readinch.h
    INCHI-1-SRC/INCHI_BASE/src/mode.h
    INCHI-1-SRC/INCHI_BASE/src/logging.h
    INCHI-1-SRC/INCHI_BASE/src/ixa.h
    INCHI-1-SRC/INCHI_BASE/src/inpdef.h
    INCHI-1-SRC/INCHI_BASE/src/incomdef.h
    INCHI-1-SRC/INCHI_BASE/src/inchi_gui.h
    INCHI-1-SRC/INCHI_BASE/src/inchicmp.h
    INCHI-1-SRC/INCHI_BASE/src/inchi_api.h
    INCHI-1-SRC/INCHI_BASE/src/util.h
    INCHI-1-SRC/INCHI_BASE/src/strutil.h
    INCHI-1-SRC/INCHI_BASE/src/stb_sprintf.h
    INCHI-1-SRC/INCHI_BASE/src/sha2.h
    INCHI-1-SRC/INCHI_BASE/src/mol_fmt.h
)
set(Sources    
    INCHI-1-SRC/INCHI_BASE/src/ichierr.c
    INCHI-1-SRC/INCHI_BASE/src/util.c
    INCHI-1-SRC/INCHI_BASE/src/ichi_io.c
    INCHI-1-SRC/INCHI_BASE/src/strutil.c
    INCHI-1-SRC/INCHI_BASE/src/bcf_s.c
    INCHI-1-SRC/INCHI_BASE/src/ichi_io.c
    INCHI-1-SRC/INCHI_BASE/src/ichi_bns.c
    INCHI-1-SRC/INCHI_BASE/src/ichiisot.c
    INCHI-1-SRC/INCHI_BASE/src/ichierr.c
    INCHI-1-SRC/INCHI_BASE/src/ichicans.c
    INCHI-1-SRC/INCHI_BASE/src/ichicano.c
    INCHI-1-SRC/INCHI_BASE/src/ichican2.c
    INCHI-1-SRC/INCHI_BASE/src/ichimap4.c
    INCHI-1-SRC/INCHI_BASE/src/ichimap2.c
    INCHI-1-SRC/INCHI_BASE/src/ichimap1.c
    INCHI-1-SRC/INCHI_BASE/src/ichimake.c
    INCHI-1-SRC/INCHI_BASE/src/ichimak2.c
    INCHI-1-SRC/INCHI_BASE/src/ichiqueu.c
    INCHI-1-SRC/INCHI_BASE/src/ichiprt3.c
    INCHI-1-SRC/INCHI_BASE/src/ichiprt2.c
    INCHI-1-SRC/INCHI_BASE/src/ichiprt1.c
    INCHI-1-SRC/INCHI_BASE/src/ichiparm.c
    INCHI-1-SRC/INCHI_BASE/src/ichinorm.c
    INCHI-1-SRC/INCHI_BASE/src/ichirvr2.c
    INCHI-1-SRC/INCHI_BASE/src/ichirvr1.c
    INCHI-1-SRC/INCHI_BASE/src/ichiring.c
    INCHI-1-SRC/INCHI_BASE/src/ichiread.c
    INCHI-1-SRC/INCHI_BASE/src/ichirvr6.c
    INCHI-1-SRC/INCHI_BASE/src/ichirvr5.c
    INCHI-1-SRC/INCHI_BASE/src/ichirvr4.c
    INCHI-1-SRC/INCHI_BASE/src/ichirvr3.c
    INCHI-1-SRC/INCHI_BASE/src/ikey_dll.c
    INCHI-1-SRC/INCHI_BASE/src/ikey_base26.c
    INCHI-1-SRC/INCHI_BASE/src/ichitaut.c
    INCHI-1-SRC/INCHI_BASE/src/ichister.c
    INCHI-1-SRC/INCHI_BASE/src/ichisort.c
    INCHI-1-SRC/INCHI_BASE/src/ichirvr7.c
    INCHI-1-SRC/INCHI_BASE/src/runichi.c
    INCHI-1-SRC/INCHI_BASE/src/runichi2.c
    INCHI-1-SRC/INCHI_BASE/src/readinch.c
    INCHI-1-SRC/INCHI_BASE/src/mol_fmt3.c
    INCHI-1-SRC/INCHI_BASE/src/mol2atom.c
    INCHI-1-SRC/INCHI_BASE/src/inchi_gui.c
    INCHI-1-SRC/INCHI_BASE/src/util.c
    INCHI-1-SRC/INCHI_BASE/src/strutil.c
    INCHI-1-SRC/INCHI_BASE/src/sha2.c
    INCHI-1-SRC/INCHI_BASE/src/runichi4.c
    INCHI-1-SRC/INCHI_BASE/src/runichi3.c
    INCHI-1-SRC/INCHI_BASE/src/mol_fmt4.c
    INCHI-1-SRC/INCHI_BASE/src/mol_fmt2.c
    INCHI-1-SRC/INCHI_BASE/src/mol_fmt1.c
)



add_library(${This} STATIC ${Headers} ${Sources})

target_compile_definitions(${This} PUBLIC 
    TARGET_EXE_STANDALONE
)

add_subdirectory(INCHI-1-TEST/)

add_subdirectory(INCHI-1-SRC/INCHI_EXE/inchi-1/src)
add_subdirectory(INCHI-1-SRC/INCHI_API/libinchi/src)
