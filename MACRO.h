//https://stackoverflow.com/a/10227059/8428146

//wanna to get the value of the Macro
/* Some test definition here */
#define DEFINED_BUT_NO_VALUE
#define DEFINED_INT 3
#define DEFINED_STR "ABC"

/* definition to expand macro then apply to pragma message */
#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)

/* Some example here */
#pragma message(VAR_NAME_VALUE(NOT_DEFINED))
#pragma message(VAR_NAME_VALUE(DEFINED_BUT_NO_VALUE))
