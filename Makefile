# ──────────────────────────────────────────────────────────────
#  Makefile — Student Database Management System
#  Course: CSE 124 - Data Structure Lab
#  Institution: Daffodil International University
# ──────────────────────────────────────────────────────────────

CC       = gcc
CFLAGS   = -Wall -Wextra -pedantic -std=c99 -Iinclude
SOURCES  = src/main.c src/student.c src/database.c src/utils.c ui/menu.c
TARGET   = student_db

# ── Default target ──
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
	@echo.
	@echo [BUILD] student_db compiled successfully.
	@echo [RUN]   Execute with: ./student_db

# ── Clean build artifacts ──
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(TARGET).exe 2>nul
else
	rm -f $(TARGET)
endif
	@echo [CLEAN] Build artifacts removed.

# ── Run the program ──
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
