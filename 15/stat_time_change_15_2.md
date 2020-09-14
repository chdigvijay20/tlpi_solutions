`stat()` system call does not change any of the file timestamps.
The three timestamps will be changed in following cases:
1. atime (Access time) - updated when the contents of the file are read
2. mtime (Modified time) - updated when the contents of the file are modified
3. ctime (Change time) - updated when the metadata of the file is modified.

`stat()` system call call does not do any of the above things. It just reads the metadata of the file because of which none of the times will get updated.
