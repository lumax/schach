PROJECT_NAME=schach
DEFS+=-D_GNU_SOURCE=1 -D_REENTRANT
INCLUDES+=-I/usr/include/SDL
LIBS+=


CFLAGS+=-g -c -Wall 
LDFLAGS+=-lSDL -lSDL_ttf -lSDL_image


OBJS = schach.o

include $(MAKE_DIR)/global.mak

armpub:
	cp -f $(PROJECT_NAME) $(ELDK_FS)/usr/$(PROJECT_NAME)
	cp -f $(PROJECT_NAME) /mnt/hgfs/ecad/RUPPERT/temp/$(PROJECT_NAME)	