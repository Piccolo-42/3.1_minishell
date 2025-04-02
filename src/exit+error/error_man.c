
// Command Not Found

Error Message: "command: command not found"
Exit Code: 127


// Permission Denied

Error Message: "permission denied"
Exit Code: 126


// No Such File or Directory

Error Message: "no such file or directory"
Exit Code: 2


// Invalid Syntax in Command

Error Message: "syntax error near unexpected token ..."
Exit Code: 2


// Redirection Errors

Ambiguous Redirect: "ambiguous redirect"
Cannot Open Input/Output File: "cannot open ... for reading/writing"
Exit Code: 1


// Too Many Arguments

Error Message: "too many arguments"
Exit Code: 1


// Numerical Argument Required

Error Message: "numeric argument required"
Exit Code: 2


// Builtin Command Errors

cd: "cd: ... no such file or directory"
exit: "exit: too many arguments"
Exit Code: 1


// Memory Allocation Failures

Error Message: "memory allocation failed"
Exit Code: 1


// Fork/Process Creation Failures

Error Message: "fork failed"
Exit Code: 1


// Pipe Creation Failures

Error Message: "pipe creation failed"
Exit Code: 1


// Signal-Related Errors

Segmentation Fault
Error Message: "Segmentation fault"
Exit Code: 139 (128 + SIGSEGV)


// Environment Variable Errors

"... not set"
Exit Code: 1


// Command Execution Errors

"exec failed"
Exit Code: 126



// Standard Exit Code Convention:

0: Successful execution
1-125: Command-specific error codes
126: Command found but not executable
127: Command not found
128-255: Fatal error signals (128 + signal number)