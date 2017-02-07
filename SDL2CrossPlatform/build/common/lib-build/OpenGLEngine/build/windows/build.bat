cl /MT /c ../../src/engine.cpp /link opengl32.lib
lib engine.obj
cl /Foengined.obj /MD /c ../../src/engine.cpp /link opengl32.lib /Fo test.obj
lib engined.obj