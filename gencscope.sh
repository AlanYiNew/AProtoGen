#!/bin/sh
find . -name "*.h" -o -name "*.hpp" -o -name "*.cpp" -o -name "*.proto" > cscope.files 
cscope -bR -i cscope.files
rm -rf tags
ctags -R -L ./cscope.files --fields=+iaS --extra=+q
