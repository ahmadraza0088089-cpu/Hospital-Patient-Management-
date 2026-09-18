# ============================================================
#  Makefile — Hospital Patient Management System
#  Usage:  make          → compiles all files
#          make run      → compiles and runs
#          make clean    → removes compiled files
# ============================================================

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET   = hospital

SOURCES = main.cpp \
          Person.cpp \
          Patient.cpp \
          Doctor.cpp \
          Staff.cpp \
          MedicalRecord.cpp \
          Appointment.cpp \
          Bill.cpp \
          Hospital.cpp

HEADERS = Person.h Patient.h Doctor.h Staff.h \
          MedicalRecord.h Appointment.h Bill.h \
          Hospital.h Interfaces.h Exceptions.h \
          Procedure.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)
	@echo "Build successful! Run with: ./hospital"

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) *.csv records.txt
	@echo "Cleaned."
