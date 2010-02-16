TEMPLATE = app
TARGET = MindSonde
CONFIG +=qt debug
SOURCES = src/*.cpp
HEADERS = src/*.h
INCLUDEPATH +=../BioAmp/include
MOC_DIR = build/mocFiles
LIBS += -lqwt

