ROOTDIR = .
SRCDIR  = $(ROOTDIR)/src
OBJDIR  = $(ROOTDIR)/obj
INCDIR  = $(ROOTDIR)/include
CC      = g++

OBJ = $(OBJDIR)/main.o $(OBJDIR)/cephes.o $(OBJDIR)/matrix.o $(OBJDIR)/suiteMethod.o $(OBJDIR)/checkFileHead.o $(OBJDIR)/invokeNist.o\
	  $(OBJDIR)/rule.o $(OBJDIR)/dfft.o

m : $(OBJ)
	$(CC) $^ -o $@

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INCDIR)/invokeNist.h $(INCDIR)/checkFileHead.h
	$(CC) -g -c $< -o $@
$(OBJDIR)/rule.o: $(SRCDIR)/rule.cpp $(INCDIR)/rule.h $(INCDIR)/global.h
	$(CC) -g -c $< -o $@
$(OBJDIR)/invokeNist.o: $(SRCDIR)/invokeNist.cpp $(INCDIR)/invokeNist.h $(INCDIR)/global.h $(INCDIR)/suiteMethod.h
	$(CC) -g -c $< -o $@
$(OBJDIR)/checkFileHead.o: $(SRCDIR)/checkFileHead.cpp $(INCDIR)/checkFileHead.h 
	$(CC) -g -c $< -o $@
$(OBJDIR)/cephes.o: $(SRCDIR)/cephes.cpp $(INCDIR)/cephes.h
	$(CC) -g -c $< -o $@
$(OBJDIR)/matrix.o: $(SRCDIR)/matrix.cpp $(INCDIR)/matrix.h $(INCDIR)/global.h
	$(CC) -g -c $< -o $@
$(OBJDIR)/suiteMethod.o: $(SRCDIR)/suiteMethod.cpp $(INCDIR)/cephes.h $(INCDIR)/matrix.h  $(INCDIR)/global.h $(INCDIR)/suiteMethod.h
	$(CC) -g -c $< -o $@
$(OBJDIR)/dfft.o: $(SRCDIR)/dfft.cpp
	$(CC) -g -c $< -o $@

clean:
	rm -r m $(OBJDIR)/*.o

 
