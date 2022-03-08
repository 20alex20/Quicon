files_dict = {
    "start_program.c": {
        "create_vars": {
            'addout': [('INT', 4, True), ('STRING', 7, True)],
            'bin': [('INT', 13, True)],
            'change': [('FUNC', 2, True)],
            'current': [("RANGE", 1, False)],
            'divide': [('INT', 7, True)],
            'equal': [('BOOL', 4, True), ('INT', 9, True), ('STRING', 8, True)],
            'less': [('BOOL', 6, True), ('INT', 11, True), ('STRING', 10, True)],
            'module': [('INT', 12, True)],
            'more': [('BOOL', 5, True), ('INT', 10, True), ('STRING', 9, True)],
            'multiply': [('INT', 6, True)],
            'next': [("TYPE_ITERATOR", 2, True), ("RANGE", 2, True)],
            'numsign': [('INT', 14, True)],
            'pubi': [("ARRAY", 6, True)],
            'reverse': [('ARRAY', 4, True), ('STRING', 11, True)],
            'rod': [('INT', 8, True)],
            'slice': [("ARRAY", 7, True), ("STRING", 6, True)],
            'step': [("RANGE", 2, False)],
            'stop': [("RANGE", 3, False)],
            'subtractout': [('INT', 5, True)],
            'tabi': [("ARRAY", 5, True), ("STRING", 5, True)],
            'to_array': [('ARRAY', 1, True), ('STRING', 4, True)],
            'to_bool': [('BOOL', 1, True), ('ARRAY', 2, True), ('INT', 2, True),
                        ('STRING', 2, True)],
            'to_func': [('FUNC', 1, True)],
            'to_int': [('BOOL', 2, True), ('INT', 1, True), ('STRING', 3, True)],
            'to_range': [('RANGE', 1, True)],
            'to_string': [('BOOL', 3, True), ('ARRAY', 3, True), ('INT', 3, True),
                          ('STRING', 1, True)],
            'to_type_iterator': [('TYPE_ITERATOR', 1, True)],
            'to_utf8': [('STRING', 12, True)],
            'to_windows1251': [('STRING', 13, True)]
        },
        "vars": {
            'Int': ['bin', 'module', 'numsign', 'to_bool', 'to_int', 'to_string'],
            'String': ['reverse', 'to_bool', 'to_string', 'to_utf8', 'to_windows1251'],
            'TypeIterator': ['next', 'to_type_iterator'],
            'Range': ['next', 'to_range'],
            'Bool': ['to_bool', 'to_int', 'to_string'],
            'Array': ['reverse', 'to_array', 'to_bool', 'to_string'],
            'Noth': [],
            'ClassName': []
        },
        "global_vars_read": ["range", "print", "length", "copy", "type_of", "is_instance",
                             "to_another_type", "end_program", "return_self", "input",
                             "Int", "String", "Bool", "Noth", "ClassName", "Func", "Array",
                             "TypeIterator", "Range"],
        "doubles": """object* {double_name} (object* __func, object* self, object* self2, ...) {{
	start_func(NULL, arg(self), 1, arg(self2), 2);
	static uint class_names[] = {{ {classes} }};
	static object* (*functions[]) (object * self, object * self2) = {{ {doubles} }};
	return __create_distribution(self, self2, class_names, functions, {main_double});
}}"""
    },
    "constants.h": {
        "named_args": {"__after_arg", "__arr_arg", "__before_arg", "__between_arg", "__name_arg",
                       "__num_arg", "__self_arg", "__self2_arg", "__start_arg", "__step_arg",
                       "__sth_arg", "__stop_arg", "__str_arg", "__start_str_arg"},
        "class_name": ["NOTH", "BOOL", "CLASS_NAME", "ARRAY", "FUNC", "INT", "LIST", "STRING",
                       "TYPE_ITERATOR", "RANGE"]
    },
    "global_variables_h.txt": {
        "var": {'current', 'my', 'step', 'stop', 'next', 'change', 'tabi', 'pubi', 'slice',
                'reverse', 'to_string', 'to_int', 'to_bool', 'to_array', 'to_func',
                'to_type_iterator', 'to_range', 'addout', 'subtractout', 'equal', 'less', 'more',
                'multiply', 'rod', 'divide', 'bin', 'module', 'numsign', 'to_utf8', 'to_windows1251'}
    }
}
