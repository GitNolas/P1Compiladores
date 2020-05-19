#define PACKAGE 400 //package
#define IMPORT 401 //import
#define BREAK 402 //break
#define DEFAULT 403 //default
#define FUNC 404 //func
#define INTERFACE 405 //interface
#define SELECT 406 //select
#define CASE 407 //case
#define DEFER 408 //defer
#define GO 409 //go
#define MAP 410 //map
#define STRUCT 411 //struct
#define CHAN 412 //chan
#define ELSE 413 //else
#define GOTO 414 //goto
#define SWITCH 415 //switch
#define CONST 416 //const
#define FALLTRHOUGHT 417 //fallthrough
#define IF 418 //if
#define RANGE 419 //range
#define TYPE 420 //type
#define CONTINUE 421 //continue
#define FOR 422 //for
#define RETURN 423 //return
#define VAR 424 //var

#define NPALABRASRESERVADAS 25

static char *pReservadas[NPALABRASRESERVADAS]={"package","var","import","return","break","for","default","continue","func","type","interface","range",
                                               "select","if","case","fallthrough","defer","const","go","switch","goto","map","struct","else","chan"};
static int cLexicos[NPALABRASRESERVADAS]={PACKAGE, VAR, IMPORT, RETURN ,BREAK, FOR,DEFAULT, CONTINUE, FUNC, TYPE, INTERFACE, RANGE, SELECT, IF, CASE,
                                          FALLTRHOUGHT, DEFER, CONST, GO, SWITCH, GOTO, MAP, STRUCT, ELSE, CHAN};