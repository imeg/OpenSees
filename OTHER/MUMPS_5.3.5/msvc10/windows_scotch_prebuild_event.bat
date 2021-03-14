set LIBSCOTCH=%FFTTOP%\external\scotch-esmumps-5.1.12b\src\libscotch

more %LIBSCOTCH%\module.h >  %LIBSCOTCH%\common2.c
more %LIBSCOTCH%\common.c >> %LIBSCOTCH%\common2.c

more %LIBSCOTCH%\module.h      >  %LIBSCOTCH%\common2_file.c
more %LIBSCOTCH%\common_file.c >> %LIBSCOTCH%\common2_file.c


more %LIBSCOTCH%\module.h               >  %LIBSCOTCH%\common2_file_compress.c
more %LIBSCOTCH%\common_file_compress.c >> %LIBSCOTCH%\common2_file_compress.c

more %LIBSCOTCH%\module.h                 >  %LIBSCOTCH%\common2_file_uncompress.c
more %LIBSCOTCH%\common_file_uncompress.c >> %LIBSCOTCH%\common2_file_uncompress.c

more %LIBSCOTCH%\module.h         >  %LIBSCOTCH%\common2_integer.c
more %LIBSCOTCH%\common_integer.c >> %LIBSCOTCH%\common2_integer.c

more %LIBSCOTCH%\module.h        >  %LIBSCOTCH%\common2_memory.c
more %LIBSCOTCH%\common_memory.c >> %LIBSCOTCH%\common2_memory.c

more %LIBSCOTCH%\module.h      >  %LIBSCOTCH%\common2_stub.c
more %LIBSCOTCH%\common_stub.c >> %LIBSCOTCH%\common2_stub.c


REM set bison=%FFTTOP%\external\bison-2.1-win\bin\bison.exe

REM cat ../libscotch/common.h module.h > common.h




