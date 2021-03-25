Wraps a file to specified width by user and outputs result on either the terminal or a new file with a prefix "wrap." , 
whichever is specified by the user. Compatible with Linux and Windows machines. 

Example:

Input:

./ww 80 manifesto.txt

-- If input file is a text file, ww will wrap the contents of the file to a maximum of 80 width
and print the result to the terminal. 

./ww 80 foo
-- If the file name is a directory, ww will open each regular file in the directory and write to a new
file created in the same directory. The name for each output file will be the name of the input file
prefixed with “wrap.”, so that a file “bar” will become “wrap.bar”. If a file by that name already
exists, overwrite it.


Error Conditions:

If the file does not exist or cannot be opened use perror to report a message to the user and
terminate with exit status EXIT_FAILURE.
If the input contains a word that is longer than the page width, print it on a single line by itself
that will exceed the page width. Do not truncate or divide the word. If your program needs to exceed
the page width, continue printing the input file and then finish with exit status EXIT_FAILURE.
