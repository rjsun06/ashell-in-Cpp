# ashell-in-Cpp
Implement a simplified command shell supporting redirections and pipes. 

## Test cases:
- Uses read/write (only) for I/O
- Returns shell to normal after command
- Displays 16-character max prompt correctly
- Arrow keys and bell function as expected
- cd command changes directly correctly
- ls command prints listing correctly
- pwd command prints the current working director correctly
- ff command correctly outputs matching files
- exit command exits the shell
- Executes external programs correctly
- Piping between commands works correctly without hangs
- File redirection works correctly for commands
- capable of running external scripts.( Running bash2048 in Ashell be like:)
![6da8ea532fbb80c96cd76a8bed81fd9](https://user-images.githubusercontent.com/92330153/191680352-00a74cdd-a347-411f-80b6-226289ff89ab.png)

## Tips for system calls used in this project:
- open() – Opens a file and potentially creates it if specified. See man page at 
http://man7.org/linux/man-pages/man2/open.2.html
- close() – Closes a file descriptor. See man page at http://man7.org/linux/man-pages/man2/close.2.html
- read() – Reads data from a file descriptor (file, pipe, etc.). See man page at http://man7.org/linux/man-pages/man2/read.2.html
- write() – Writes data to a file descriptor (file, pipe, etc.). See man page at http://man7.org/linux/man-pages/man2/write.2.html
- pipe() – Creates a pipe. See man page at http://man7.org/linux/man-pages/man2/pipe.2.html
- dup2() – Duplicates a file descriptor (note use dup2 instead of dup it is easier). See man page at http://man7.org/linux/man-pages/man2/dup.2.html
- fork() – Makes a copy of a process. See man page at http://man7.org/linux/man-pages/man2/fork.2.html
- execvp() – Replaces the calling process with a new program (note execvp may be the easiest to use but there are many derivatives of exec). See man page at http://man7.org/linux/man-pages/man3/exec.3.html
- wait() – Waits for a child to terminate. See man page at http://man7.org/linux/man-pages/man2/wait.2.html
- getcwd() – Gets the current working directory. See man page at http://man7.org/linux/man-pages/man2/getcwd.2.html
- chdir() – Changes the current working directory. See man page at http://man7.org/linux/man-pages/man2/chdir.2.html
- opendir() – Opens a directory for reading. See man page at http://man7.org/linux/man-pages/man3/opendir.3.html
- readdir() – Reads a directory entry in from a directory opened with opendir. See man page at http://man7.org/linux/man-pages/man3/readdir.3.html
- closedir() – Closes a directory opened with opendir. See man page at http://man7.org/linux/man-pages/man3/opendir.3.html
- stat() – Gets the information about a file. See man page at http://man7.org/linux/man-pages/man2/stat.2.html
- getenv() – Gets an environmental variable, helpful for getting HOME directory. See man page at http://man7.org/linux/man-pages/man3/getenv.3.html
- getpid() – http://man7.org/linux/man-pages/man2/getpid.2.html
