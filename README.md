## Table of content

- [Description](#my_get_next_line)
- [How it works](#how-it-works)
- [Utility/Helper functions](#utility-functions)
- [Memory-Management](#memory-management)

# My_**get_next_line**
The **get_next_line** function is a function designed to read and return *lines* via repeated calls to read the text file pointed to by the file descriptor (**fd**), **ONE LINE AT A TIME** including the terminating *\n* character except at the end of the file which does not end with *\n* character. If theres nothing to be read,
it should return **NULL**.

# error-controls
```C
if (**fd** < 0 || BUFFER_SIZE <= 0 || read(**fd**, NULL, 0) < 0
```

The conditions above are Error handling controls; File descriptors (**fd**) are never in the negtive, only positives - they must have a content. Buffers must be greater than 0. The **read** function is greater than 0 if the file can be opened and read and returns -1 if the file cannot be opened. So, checking if the file can be opened.

## How it works: 
The function parameter receives the file descriptor (**fd**) passed as
an argument as shown in the prototype below.

```C
char	*get_next_line(int fd)
```

In a typical manner, we need a place we can dump the output result. So, for this function we declare a char pointer to a Static variable called *lines*. Why static variable? 

[Static variables](https://www.geeksforgeeks.org/static-variables-in-c/)  are variables that have the property of preserving their 
value even after they are out of their scope. They are commonly denoted with the suffix type of "static" like shown below;

```C
static char	*lines;
```

In addition,  we need a char pointer variable called *buffer* with a predetermined size - 10 bytes of char (This value can be modified or desired) of *BUFFER_SIZE* defined in the header file. The purpose of this variable is to receive the text read from the **fd** for further processing. 

Finally, an INT variable, *bytes_read* is declared to keep track of the amount of bytes read from the **fd**. This *bytes_read* is an index of sort that we use for the char,*buffer*.

In order to fulfil the condition necessary for reading the **fd**, *bytes_read* is initialised to 1. Meaning, if there are no *bytes_read*, then the program moves on to the next execution. 
 
Also, a  function, **nl_found** (new line found) is called in this condition. This function is needed to search through the static variable - *lines* for the *\n* character everytime the loop is entered. If *\n* is found, the loop is broken. Then the program moves to the next executable operation. However, it should be noted that the whole string of characters read and stored which may include the *\n* character is contained and null terminated within the *buffer* variable which is ultimately stored up in *lines*. The condition fails if *\n* is found among the *lines* string.

Otherwise, if the condition above holds true, the loop performs a helping 
function *ft_strjoin* from the Utils file **get_next_line_utils.c**. This aims to join accordingly the content of *buffer* to the static variable, *lines*. In the first call, the static variable *lines* is empty. Next, within *ft_strjoin*, a checking condition -

```C
if (!s1)
		return (ft_strdup(s2, source_len));
```

for this is inserted to duplicate (*ft_strdup*) the *buffer* into the 
static variable, *lines*. The return result is the static variable, *lines* whose address is passed as an argument to another helper function *final_lines*.

The purpose of the helper function, *final_lines* is to serch through the string and refine the output by returning the string read from the **fd** + *\n* and the left over is stored back inside the static variable, *lines* for the next run of the function.

## Memory management:
*BUFFER_SIZE* was defined for the variable, *buffer* is such that this is managed dynamically. No memory needs to be freed.

Checks are made in the parent function as marked at the [start](#error-controls) of this document.
This ensures that the static variable memory is freed and set to NULL if it fails.

When the helper function *ft_strjoin* is called, memory is allocated to
dynamically allocate sufficent memory for the function and freed if it fails.
Likewise, within *ft_strjoin* is another helper function *ft_strdup* that 
activates when the static variable passed as an argument is empty or at first run of the function. The function *ft_strdup* duplicates the string passed as an argument while dynamically allocating sufficient memory. Subsequently, the static variable passed as and argument (**s1**) for the function, *ft_strjoin* is freed of memory after a succesful operation.

From the helper function **static char final_lines** Memory allocated to the char pointer to a variable *temp_lines* used as a temporary storage to store the final out was bein freed due to the allocation from the utils function *ft_strdup* and same is made **NULL** after freeing the memory. This is good practice to prevent memory leaks.

## Utility functions:
The functions in the utility files **get_next_line_utils.c** are recycled function from my previous project called **FT_LIBFT**. These function are either used as they were or modified to fit the use within the **GNL** function.
For the **get_next_line** function (**GNL**), 5 helper functions are used to ensure the **GNL** functions as expected. The functions are listed as thus; 

**char  ft_strjoin** - This function performs a concactenation of two string 
character variables passed as an argument. It dynamically allocates memory to hold the result. 
Finally, it frees the memory of all the parameters to avoid leaks. It received the arguments, *lines* (static variable) and*buffer*from the mother function **get_next_line**.

**char   ft_strdup** - This function is called within *ft_strjoin* when a condtion of if the source parameter (*lines* or **s1**) os empty. This function duplicates the second parameter *buffer*or **s2** while dynamically allocating memory to the to the result that is returned. No freeing of memory occours here because no other allocation was done to the source but only the result.

**int   ft_strlen** - Our trusty function ;) is used at length in the utility file to determine the length of the string characters in bytes passed as an argument. It returns an Int variable, *count*.

**size_t    ft_strlcpy** - This function is used within *ft_strjoin* as a means to copy the destination parameter from *ft_strjoin* into the result passed as an argument from same. It receives char destination, char source, and size_t destination size as parameters.

**size_t    ft_strlcat** - This function is used as a final step in *ft_strjoin* to concatenate the source the content of the result from *ft_strlcpy*.

## Helper functions
The parent **GNL** file houses 2 helper functions that are made static. This means that these functions cannot be used outside of this file. The reason for having these 2 extra functions was to ensure a code that is legible, coherent, and understandable. The 2 static functions are;

**static int	nl_found** - This function receives a pointer to a string *lines* as a parameter to perform a simple function of checking for the *\n* character. The return values are either 1 for true or 0 for false. This function helps to break the loop of the **GNL** operation to keep reading from the **fd**.

**static char	final_lines** - This helper function receives the double pointer to a string (receiving the string as a whole) since it passed via a deference operation '&lines' from **GNL** parent function. The aim of this function is to clean up the string contained within the double array *(**lines)*. Cleaning up means the functions loops through the string while it exists and until it encounters the *\n* character. Since we need the *\n* to terminate each lines to be outputed, we also loop one more step forward. These are achieved with help of an indexer we declared 'Int i'.

The outcome of the loop is duplicated into a char pointer variable, result with the help of utils function *ft_strdup*. This result is our return value. However we need to help the static variable remember what needs to remain within it since we have taken what we need in the first run. So we duplicated the remaing string after the *\n* character into it.This will be remembered by the static variable and serve in the next run until another *\n* is encountered.
