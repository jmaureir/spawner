AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

bin_PROGRAMS    =	spawner
spawner_SOURCES	=	src/ActionEvent.h \
					src/ActionListener.h \
					src/CommandNotFoundException.h \
					src/Daemon.h \
					src/Daemon.ccc \
					src/Exception.h \
					src/Spawner.h \
					src/Spawner.cc \
					src/Thread.h \
					src/Thread.cc \
					src/main.cc 

spawner_LDFLAGS = @LDFLAGS@ -lpthread -lrt

dist_noinst_SCRIPTS = autogen.sh
