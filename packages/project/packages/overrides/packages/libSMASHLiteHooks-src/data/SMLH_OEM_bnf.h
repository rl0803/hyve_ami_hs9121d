/*****************************************************************************
 * sample code for adding new verb 'debug'
 *****************************************************************************
 *
 * #define OEM_PARSE_SYMBOL_COUNT 30
 * #define OEM_BNF_AREA_BYTE_SIZE 200
 *
 * char * oem_symbls[] = {
 *  "SYM1001::=\"debug\"",
 *  "SYM1002::=\"-y\""
 * };
 *
 * char oem_cmds[] = { "debug-cmd " };
 *
 * char oem_verbs[] = { "debug-verb " };
 *
 * char oem_options[] = { "debug-options "};
 *
 * char *oem_cmd_syntax[] = {
 *  "(debug-option)::= SYM2 debug-optionName ",
 *  "(debug-cmd)::=debug-verb eol | debug-verb debug-option eol "
 * };
 *
 * char *oem_verb_syntax[] = { "(debug-verb)::= SYM1001 " };
 *
 * char *oem_option_names[] = { "(debug-optionName)::= SYM1002 " };
 *
 *****************************************************************************/

#define OEM_PARSE_SYMBOL_COUNT 1
#define OEM_BNF_AREA_BYTE_SIZE 50

char * oem_symbls[] = {
		"",
};

char oem_cmds[] = { "" };

char oem_verbs[] = { "" };

char oem_options[] = { ""};

char *oem_cmd_syntax[] = {
""
 };

char *oem_verb_syntax[] = { "" };

char *oem_option_names[] = { "" };
