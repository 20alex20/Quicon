import json
from shutil import copy
from itertools import product
from files_txt import files_dict

tags = dict()
words = dict()
words2 = dict()
after_variable = dict()
operators_word = dict()
small_program = dict()
logs = False
cur_i = 0
old_string = ""
tabs = " \n\t\r"
text = "_'-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
symbols = "!\"("
numbers = "-0123456789"
operators = ({"*", "/", "%"}, {"+", "-"}, {"==", ">", "<", "!=", "<=", ">="},
             {"~"}, {"&"}, {"|"})
fatality = None
errors = [[]]
global_vars_write = [[]]
vars = [[]]
args = [[]]

all_args_names = set()
global_vars_read = []
data_additional = {"funcs": [], "args_names": all_args_names,
                   "classes": dict(), "global_vars": global_vars_read}
data_main = {"main_program": [], "classes": dict(), "global_vars": [], "global_func": []}
current_data = data_additional["funcs"]

is_global = False
name_realname = dict()
end = []
class_name = None
arg_class = []
doubles = dict()
cur_file = None
another_classes = dict()


def parse(string: str):
    answer = [""]
    for i in string:
        if i == '>':
            answer[-1] += i
            answer.append("")
        else:
            if i == '<':
                answer.append("")
            answer[-1] += i
    return answer


def skip_tabs():
    global cur_i
    old_cur_i = cur_i
    s = old_string[cur_i]
    while s in tabs:
        cur_i += 1
        s = old_string[cur_i]
    return old_cur_i


def skip_tabs_sample():
    i = cur_i
    s = old_string[i]
    while s in tabs:
        i += 1
        s = old_string[i]
    return i


def compare(element: str):
    global cur_i
    for j in element:
        if j == ' ':
            skip_tabs()
        else:
            if old_string[cur_i] != j:
                return True
            cur_i += 1
    return False


def fatal_error(s: str, s2=''):
    global fatality
    fatality = '@' + s.upper() + s2 + '@'
    return None


def error(s: str):
    errors[-1].append((cur_i, cur_file, s))
    return '@' + s + '@'


def fragment1(num):
    if len(num) <= 9 or (num[0] == '-' and len(num) <= 10):
        return "create__int(FALSE, " + num + ")"
    else:
        return "create__int(TRUE, \"" + num + "\")"


def fragment2(s="Неверно объявлена/использована переменная"):
    i = skip_tabs_sample()
    if old_string[i] in numbers:
        while old_string[i] in text:
            i += 1
        return i, error(s)
    s = ''
    while old_string[i] in text:
        s += old_string[i]
        i += 1
    if not s:
        return i, fatal_error("Переменная не найдена")
    return i, s


def fragment3():
    global cur_i
    skip_tabs()
    if old_string[cur_i] != '=':
        return fatal_error("Отсутствует присваивание в переменную")
    cur_i += 1
    skip_tabs()
    ans = recursia(words["<num_var>"])
    if ans is None:
        return None
    if old_string[cur_i] != ';':
        return fatal_error("Присваивание в глобальную переменную не окончено")
    cur_i += 1
    return ans


def parse_tag(element: str):
    global cur_i, fatality, all_args_names
    to_replace = []
    if element in tags:
        last_pos_args = False
        new_string = ""
        tag = tags[element]
        length = 0
        while True:
            boofer = recursia(tag)
            if boofer is None:
                return to_replace, None
            if element == "<nam_args>":
                if "named_arg" in boofer:
                    if not last_pos_args:
                        to_replace.append(("<len>", str(length)))
                        length = 0
                        last_pos_args = True
                elif last_pos_args:
                    boofer = error("Нельзя использовать позиционные аргументы после именованных")
            new_string += ', ' + boofer
            length += 1
            skip_tabs()
            if old_string[cur_i] != ',':
                break
            cur_i += 1
        if length == 1 and "empty_arg" in boofer:
            new_string = ''
            length -= 1
        if element == "<nam_args>" and not last_pos_args:
            to_replace.append(("<len>", str(length)))
            length = 0
        to_replace.append(("<len>", str(length)))
        return to_replace, new_string
    elif element[:4] == "<sth":
        new_string = ""
        tag = {"old": ["< ><arg1is_sth> ;"], "new": ["< ><arg1is_sth>;"]}
        errors.append([])
        while True:
            old_cur_i = cur_i
            boofer = recursia(tag)
            if boofer is None:
                fatality = None
                cur_i = old_cur_i
                break
            if len(boofer) > 2 and boofer[-2] == '}':
                boofer = boofer[:-1]
            new_string += boofer
            errors[-2].extend(errors[-1])
            errors[-1].clear()
        del errors[-1]
        if element == "<sth2>":
            to_replace.append(('a<sth2>', new_string))
            new_string = ''
        return to_replace, new_string
    elif element == "<v>":
        num = ''
        txt = ''
        skip_tabs()
        s = old_string[cur_i]
        while s in text:
            if not txt and s in numbers:
                num += s
            else:
                txt += s
            cur_i += 1
            s = old_string[cur_i]
        if num == '' and txt == '':
            return to_replace, fatal_error("Ничего не найдено")
        elif num == '-' or num.count('-') > 1:
            return to_replace, fatal_error("Символ '-' неправильно использован")
        elif txt == '':
            boofer = fragment1(num)
        elif txt == 'array':
            cur_i -= 5
            return to_replace, recursia(words["array"])
        else:
            boofer = txt
            i = skip_tabs_sample()
            if old_string[i] == '=' and old_string[i + 1] not in '><=':
                cur_i = i + 1
                if is_global:
                    global_vars_read.append(boofer)
                elif boofer not in vars[-1] and boofer not in global_vars_write[-1] and \
                        boofer not in args[-1]:
                    vars[-1].append(boofer)
                skip_tabs()
                a = arg()
                if a is None:
                    return to_replace, None
                return to_replace, "assign(" + boofer + ", " + a + ")"
            elif boofer not in args[-1] and boofer not in vars[-1] and \
                    boofer not in global_vars_read:
                boofer = error("Неверно объявлена/использована переменная")
        if old_string[cur_i] == ".":
            rec = recursia(after_variable[old_string[cur_i]])
            if rec is None:
                return to_replace, None
            st = ''
            for cname, arr, name in arg_class:
                if name == boofer:
                    if rec[:9] == "do_method":
                        index = rec.find(', ', 15)
                        var_name = rec[15:index]
                        if var_name in arr["vars"]:
                            boofer = error("Вызывать метод у класса нельзя")
                        else:
                            if "vars_instance" in arr and var_name not in arr["vars_instance"]:
                                arr["vars_instance"].append(var_name)
                            boofer = f"do_method_from_self{st}(" + var_name + rec[index:]
                    else:
                        var_name = rec[rec.index('f') + 10:rec.index(')')]
                        if var_name in arr["vars"]:
                            boofer = rec.replace('from(<v>, ', f'from_self_class{st}(')
                        else:
                            if "vars_instance" in arr and var_name not in arr["vars_instance"]:
                                arr["vars_instance"].append(var_name)
                            boofer = rec.replace('from(<v>, ', f'from_self{st}(')
                    break
                st = '_2'
            else:
                boofer = rec.replace("<v>", boofer)

        while old_string[cur_i] in ".[(":
            rec = recursia(after_variable[old_string[cur_i]])
            if rec is None:
                return to_replace, None
            boofer = rec.replace("<v>", boofer)
        if txt and num:
            return to_replace, "do_method(" + boofer + ", multiply, 1, 0, " + fragment1(num) + ")"
        return to_replace, boofer
    elif element == "<num>":
        old_cur_i = cur_i
        s = old_string[cur_i]
        if s not in numbers:
            return to_replace, error("Отсутствует число")
        while s in numbers:
            cur_i += 1
            s = old_string[cur_i]
        return to_replace, old_string[old_cur_i:cur_i]
    elif element == "< >":
        old_cur_i = skip_tabs()
        return to_replace, old_string[old_cur_i:cur_i]
    elif element == "<text>":
        d = {'\n': "\\n", '\r': "\\r", '\t': "\\t", '\0': "\\0", '\\': "\\\\"}
        ans = ''
        last = "\""
        s = old_string[cur_i]
        while s != "\"" or last == "\\":
            if s in d:
                s = d[s]
            ans += s
            last = s
            cur_i += 1
            s = old_string[cur_i]
        return to_replace, ans
    elif element[:4] == "<var":
        cur_i, new_string = fragment2()
        if new_string is None:
            return to_replace, None
        elif element == "<var_name>":
            return to_replace, new_string
        elif element == "<var>":
            for i in product(iter(vars[-1]), iter(global_vars_write[-1]), iter(args[-1])):
                if new_string == i:
                    break
            else:
                vars[-1].append(new_string)
            to_replace.append(("<var>", new_string))
        return to_replace, new_string
    elif element == "<vs>":
        del global_vars_write[-1]
        vs = vars.pop()
        if not vs:
            return to_replace, ""
        return to_replace, "object* " + " = NULL, * ".join(vs) + " = NULL;"
    elif element == "<vs2>":
        del global_vars_write[-1]
        vs = vars.pop()
        to_replace.append(("a<len>", str(len(vs))))
        del end[-1]
        if not vs:
            to_replace.extend([("a<vs>", ''), ("a<vs2>", '')])
            return to_replace, ""
        to_replace.extend([("a<vs>", ''.join(map(lambda x: ', ' + x, vs))),
                           ("a<vs2>", "object* " + " = NULL, * ".join(vs) + " = NULL;")])
        return to_replace, ""
    elif element[:6] == "<name_":
        i = cur_i
        if element == "<name_func>":
            cur_i, name = fragment2()
            if name is None:
                return to_replace, None
            for i in product(iter(vars[-1]), iter(global_vars_write[-1]), iter(args[-1])):
                if name == i:
                    break
            else:
                vars[-1].append(name)
        elif element == "<name_global_func>":
            cur_i, name = fragment2()
            if name is None:
                return to_replace, None
            if name in global_vars_read:
                name = error("Глобальная переменная с таким именем уже существует")
            else:
                global_vars_read.append(name)
        elif element == "<name_constructor>":
            cur_i = i
            name = class_name.lower()
            if name in global_vars_read:
                name = error("Глобальная переменная с таким именем уже существует")
            else:
                global_vars_read.append(name)
            up = name.upper()
            cap = name.capitalize()
            to_replace.extend([("a<class_name_capit>", cap), ("a<class_name_capit>", cap),
                               ("a<class_name_upper>", up), ("a<class_name_lower>", name)])
        else:
            if element == "<name_double>":
                cur_i = i
                skip_tabs()
                symbol = ''
                while old_string[cur_i] not in tabs:
                    symbol += old_string[cur_i]
                    cur_i += 1
                if symbol not in operators_word or operators_word[symbol]["type"] not in (1, 3):
                    return to_replace, fatal_error("Неверно построен метод двойного применения1")
                name = operators_word[symbol]["name"]
                cur_i, cname = fragment2("Откуда число?!!!")
                if cname is None or cname != 'with':
                    return to_replace, fatal_error("Неверно построен метод двойного применения2")
                cur_i, cname = fragment2("Данное для класса название невозможно")
                if cname is None:
                    return to_replace, fatal_error("Неверно построен метод двойного применения3")
                cname = cname.capitalize()
                if cname in data_additional["classes"]:
                    arg_class.append([cname, data_additional["classes"][cname]])
                elif cname in another_classes:
                    arg_class.append([cname, {"vars": another_classes[cname]}])
                else:
                    cname = error("Неизвестный класс")
                to_replace = [("a<class_name_upper2>", cname.upper()),
                              ("a<class_name_capit2>", cname.capitalize())]
                name += '_' + cname.lower()
            else:
                cur_i, name = fragment2()
                if name is None:
                    return to_replace, None
            real_name = '__' + name + '__' + class_name.lower()
            to_replace.extend([("a<class_name_capit>", class_name.capitalize()),
                               ("a<class_name_upper>", class_name.upper()),
                               ("a<real_name>", real_name), ("<real_name>", real_name)])
            return to_replace, name
        if name in name_realname:
            real_name = '__' + name + str(name_realname[name])
            name_realname[name] += 1
        else:
            real_name = '__' + name
            name_realname[name] = 1
        to_replace.extend([("<real_name>", real_name), ("a<real_name>", real_name)])
        return to_replace, name
    elif element[:10] == "<func_args":
        arr_num = "NULL"
        if element == "<func_args_double>":
            tag = {
                "old": ["< ><var_name> ,< ><var_name> "],
                "new": ["< ><var_name><>< ><var_name>"]
            }
            ans = recursia(tag)
            if ans is None:
                return to_replace, None
            args_names = [i.lstrip() for i in ans.split('<>')]
            args_values = ''
            end.append('returnf2')
            for i in range(len(arg_class)):
                arg_class[i].append(args_names[i])
            args.append(args_names)
            args_names2 = [(i.lstrip(), k + 1) for k, i in enumerate(args_names)]
            args_names2.sort()
            to_replace = [("<len>", str(len(args_names))),
                          ("a<func_args2>", ', '.join(map(lambda x: "object* " + x, args_names)))]
            all_args_names |= set(args_names)
            return to_replace, ''.join(args_values)
        else:
            tag = {
                "old": ["< ><var_name> = <arg1> ", "< ><var_name>[] ",
                        "< ><var_name>[] = <arg1> ", "< ><var_name> "],
                "new": ["<var_name><>< ><arg1>", "<var_name>[]<>< >NULL",
                        "<var_name>[]<>< ><arg1>", "<var_name><>< >NULL"]
            }
            args_names = []
            args_values = []
            while True:
                boofer = recursia(tag)
                if boofer is None:
                    if not args_names:
                        to_replace = [("<len>", '0'), ("a<func_args3>", ''), ("a<arr_num>", ''),
                                      ("a<func_args2>", ''), ("a<is_0>", '_0')]
                        fatality = None
                        end.append('returnf_0')
                        return to_replace, ''
                    return to_replace, None
                boofer = boofer.split('<>')
                if boofer[0][-2:] == '[]':
                    if boofer[1].lstrip() == "NULL":
                        boofer[1] = boofer[1][:-4] + "create__array(0)"
                    if arr_num != "NULL":
                        boofer[0] = error("Массив в аргументах можно использовать только один раз")
                    else:
                        boofer[0] = boofer[0][:-2]
                        arr_num = str(len(args_names) + 1)
                args_names.append(boofer[0])
                args_values.append("," + boofer[1])
                if old_string[cur_i] != ',':
                    break
                cur_i += 1
            end.append('returnf')
        for i in range(len(arg_class)):
            arg_class[i].append(args_names[i])
        args.append(args_names)
        args_names2 = [(i.lstrip(), k + 1) for k, i in enumerate(args_names)]
        args_names2.sort()
        boofer = ''.join(map(lambda x: f", arg({x[0]}), {x[1]}", args_names2))
        to_replace = [("<len>", str(len(args_names))), ("a<func_args3>", boofer),
                      ("a<arr_num>", arr_num), ("a<is_0>", ''),
                      ("a<func_args2>", ''.join(map(lambda x: ", object* " + x, args_names)))]
        all_args_names |= set(args_names)
        return to_replace, ''.join(args_values)
    elif element == "<global>":
        vars.append([])
        global_vars_write.append([])
        if old_string[cur_i] != '<':
            return to_replace, ""
        s = "<global:"
        i = 0
        while i < len(s):
            if old_string[cur_i + i] != s[i]:
                cur_i += i
                while old_string[cur_i] != '{':
                    cur_i += 1
                return to_replace, error("Не верно подключены глобальные переменные")
            i += 1
        cur_i += i
        while old_string[cur_i] == ',':
            skip_tabs()
            cur_i, s = fragment2()
            if s is None:
                fatality = None
                break
            global_vars_write[-1].append(s)
        while old_string[cur_i] != '{':
            cur_i += 1
        return to_replace, ""
    elif element == "<rec>":
        return to_replace, recursia()
    elif element == "<end>":
        if not end:
            return to_replace, error("Здесь нельзя использовать return")
        return to_replace, end[-1]
    else:
        b = "is_sth" in element
        return to_replace, arg(is_sth=b, q=b)


def arg(level=6, is_sth=False, q=False):
    global cur_i
    new_string = recursia(is_sth=is_sth, q=q)
    if level == 0 or new_string is None:
        return new_string
    while True:
        i = skip_tabs_sample()
        tt = {old_string[i], old_string[i] + old_string[i + 1]}
        for new_level, j in enumerate(operators[:level]):
            g = tt & j
            if g:
                g = g.pop()
                break
        else:
            return new_string
        cur_i = i + len(g)
        skip_tabs()
        boofer = arg(new_level)
        if boofer is None:
            return None
        word = operators_word[g]
        type = word["type"]
        if type == 1:
            new_string = "do_method(" + new_string + ", " + word["name"] + ", 1, 0, " + boofer + ")"
        elif type == 2:
            new_string = "not(do_method(" + new_string + ", " + word[
                "name"] + ", 1, 0, " + boofer + "))"
        else:
            new_string = word["name"] + "(" + new_string + ", " + boofer + ")"


def seach_word(is_sth: bool):
    i = skip_tabs_sample()
    s = old_string[i]
    if s in symbols:
        return words[s], False
    ans = ''
    while s in text:
        ans += s
        i += 1
        s = old_string[i]
    if ans == '':
        return fatal_error("Передан неизвестный символ"), False
    elif is_sth and ans in words2:
        return words2[ans], True
    elif ans in words:
        return words[ans], False
    else:
        return words["<num_var>"], False


def recursia(flag=None, is_sth=False, q=False):
    global fatality, cur_i
    if flag is None:
        word, is_sth = seach_word(is_sth)
        if word is None:
            return None
    else:
        word = flag
    if logs:
        print(word)
    if is_sth:
        if "it_is_for" in word:
            vars[-1].append("__iter")
        have_additional = "additional" in word
        if have_additional:
            parse_additional_string_original = parse(word["additional"])
    else:
        have_additional = False
    old_cur_i = cur_i
    errors.append([])
    for old, new in zip(word["old"], word["new"]):
        fatality = None
        cur_i = old_cur_i
        parse_old_string = parse(old)
        parse_new_string = parse(new)
        if have_additional:
            parse_additional_string = parse_additional_string_original.copy()
        for i, element in enumerate(parse_old_string):
            if element == "":
                continue
            elif element[0] != '<':
                if compare(element):
                    fatal_error("Не соответствие тексту маски", ' ' + str(word))
                    break
            else:
                a, string = parse_tag(element)
                if string is None:
                    break
                if have_additional and element == "< >":
                    parse_additional_string[parse_additional_string.index(element)] = string
                else:
                    parse_new_string[parse_new_string.index(element)] = string
                for j in a:
                    if have_additional and j[0][0] == 'a':
                        parse_additional_string[parse_additional_string.index(j[0][1:])] = j[1]
                    else:
                        parse_new_string[parse_new_string.index(j[0])] = j[1]
        else:
            if logs:
                print(parse_new_string)
            errors[-2].extend(errors[-1])
            del errors[-1]
            if have_additional:
                current_data.append(''.join(parse_additional_string))
            parse_new_string = ''.join(parse_new_string)
            if flag is None and not is_sth and q and parse_new_string.lstrip()[:6] != "assign":
                index = 0
                while parse_new_string[index] in tabs:
                    index += 1
                parse_new_string = parse_new_string[:index] + "__(" + parse_new_string[index:] + ')'
            return parse_new_string
        errors[-1].clear()
    del errors[-1]
    return None


def create_class(data_class, generate_class):
    global cur_i, class_name, current_data, arg_class
    skip_tabs()
    while old_string[cur_i] != '}':
        i, word = fragment2("Такое название конструкции не допустимо")
        if word is None:
            return None
        if word == "constructor":
            if data_class["constructor"]:
                return None
            current_data = data_class["constructor"]
            ans = recursia(small_program[word], True)
            if ans is None:
                return None
            name, start, num, endd = ans.split('<>')
            global_vars_read.append(name)
            global_vars_read.append(name.capitalize())
            ans = name + start + num + endd.replace('NULL', 'create__func(__create__' + name +
                                                    ', TRUE, 0)', 1)
            data_main["global_func"].append(ans)
        elif word in ("method", "double"):
            current_data = data_class[word]
            ans = recursia(small_program[word], True)
            if ans is None:
                return None
            name, ans = ans.split('<>')
            if word == "double":
                if len(arg_class) > 1:
                    arg_class = [arg_class[0]]
                index = name.index('_')
                double_name = '__' + name[:index] + '__' + class_name.lower()
                cname = name[index + 1:]
                name = '__' + name + '__' + class_name.lower()
                if double_name in doubles[class_name]:
                    if class_name.lower() == cname.lower():
                        doubles[class_name][double_name][0] = name
                else:
                    doubles[class_name][double_name] = [name if class_name.lower() == cname.lower() else "NULL"]
                doubles[class_name][double_name].append((name, cname.upper()))
            else:
                generate_class.append(ans)
                data_class["vars"].append(name)
        else:
            cur_i = i
            current_data = data_class["vars_instance"]
            ans = fragment3()
            if ans is None:
                return None
            data_class["vars"].append(word)
            generate_class.append(ans)
        skip_tabs()
        arg_class[0] = arg_class[0][:2]
    cur_i += 1
    return 'ok'


def program():
    global cur_i, is_global, class_name, current_data, cur_file
    while True:
        s = old_string[cur_i]
        while s in tabs:
            cur_i += 1
            s = old_string[cur_i]
        i, word = fragment2("Откуда число?!!!")
        if word is None:
            break
        if word == "class":
            cur_i = i
            cur_i, class_name = fragment2("Такое название класса не допустимо")
            cur_file = class_name.lower() + ".c"
            class_name = class_name.capitalize()
            skip_tabs()
            if old_string[cur_i] != '{':
                break
            cur_i += 1
            data_class = {"constructor": [], "vars": [], "vars_instance": [], "method": [], "double": []}
            data_additional["classes"][class_name] = data_class
            arg_class.append([class_name, data_class])
            generate_class = []
            data_main["classes"][class_name] = generate_class
            doubles[class_name] = dict()
            ans = create_class(data_class, generate_class)
            if ans is None:
                break
            arg_class.clear()
            class_name = None
        elif word == "resume":
            cur_i = i
            cur_i, class_name = fragment2("Откуда число?!!!")
            if class_name == 'class':
                cur_i, class_name = fragment2("Такое название класса конструкции не допустимо")
            cur_file = class_name.lower() + ".c"
            class_name = class_name.capitalize()
            skip_tabs()
            if old_string[cur_i] != '{' or class_name not in data_additional["classes"]:
                break
            cur_i += 1
            data_class = data_additional["classes"][class_name]
            arg_class.append([class_name, data_class])
            generate_class = data_main["classes"][class_name]
            ans = create_class(data_class, generate_class)
            if ans is None:
                break
            arg_class.clear()
            class_name = None
        elif word == "declare":
            cur_i = i
            cur_i, class_name = fragment2("Откуда число?!!!")
            if class_name == 'class':
                cur_i, class_name = fragment2("Такое название класса конструкции не допустимо")
            skip_tabs()
            if old_string[cur_i] != '{':
                break
            cur_i += 1
            i = cur_i
            while old_string[cur_i] != '}':
                cur_i += 1
            a = old_string[i:cur_i].strip().split()
            another_classes[class_name.capitalize()] = [i[:-1] if i[-1] == ',' else i for i in a]
            cur_i += 1
        elif word == "main_program":
            cur_file = "main.c"
            if data_main["main_program"]:
                break
            current_data = data_main["main_program"]
            ans = recursia(small_program["main_program"], True)
            if ans is None:
                break
            data_main["main_program"].append(ans)
        elif word == "func":
            cur_file = "functions.c"
            current_data = data_additional["funcs"]
            ans = recursia(small_program["global_func"], True)
            if ans is None:
                break
            data_main["global_func"].append(ans)
        else:
            cur_file = "start_program.c"
            cur_i = i
            is_global = True
            ans = fragment3()
            is_global = False
            if ans is None:
                break
            if word in global_vars_read:
                word = error("Глобальная переменная с таким именем уже существует")
            else:
                global_vars_read.append(word)
            data_main["global_vars"].append(word + ' = __enlon(' + ans + ')')


def files(directory: str):
    ss = files_dict["start_program.c"]["doubles"]
    for cname in data_additional["classes"]:
        doubles_new = data_additional['classes'][cname]["double"]
        for double_name, name_cname in doubles[cname].items():
            doubles_new.append(ss.format(double_name=double_name,
                                         doubles=', '.join(map(lambda x: x[0], name_cname[1:])),
                                         classes=', '.join(map(lambda x: x[1], name_cname[1:])),
                                         main_double=name_cname[0]))
            data_additional['classes'][cname]["vars"].append(double_name[2:double_name.index('_', 2)])
            data_main["classes"][cname].append(f"create__func({double_name}, FALSE, 2, NULL, NULL)")

    directories = []
    classes = files_dict["constants.h"]["class_name"]
    classes = classes[:3] + sorted(classes[3:] + list(data_additional["classes"].keys()))

    for file_name in ("constants_h.txt", "main_c.txt", "all_h.txt", "global_variables_h.txt",
                      "start_program_c.txt", "functions_c.txt"):
        with open("files/" + file_name, 'r') as file:
            file_string = file.read()
        if file_name == "constants_h.txt":
            file_string += "typedef enum {\n\t " + \
                           ', '.join(map(lambda x: x.upper(), classes)) + "\n} class_name;\n\n"
            names = sorted(files_dict["constants.h"]["named_args"] |
                           set(map(lambda x: '__' + x + '_arg', all_args_names)))
            file_string += "enum named_args {\n\t" + ', '.join(names) + '\n};'
        elif file_name == "main_c.txt":
            file_string += '\n\n'.join(data_main["main_program"])
        elif file_name == "all_h.txt":
            spisoks = [data_main["main_program"], data_additional["funcs"]]
            for cname in data_additional["classes"]:
                spisoks.append(data_additional["classes"][cname]["constructor"])
                spisoks.append(data_additional["classes"][cname]["method"])
                spisoks.append(data_additional["classes"][cname]["double"])
            for k, spisok in enumerate(spisoks):
                if k < 2 or (k + 1) % 3 == 0:
                    file_string += '\n'
                for i in spisok:
                    if "object* " in i:
                        sindex = i.find("object*")
                        fl = 1
                        while fl:
                            index = sindex + 7
                            while i[index] in text or i[index] in tabs:
                                index += 1
                            if i[index] == '(':
                                file_string += '\n' + i[sindex:i.index(')', index) + 1] + ';'
                            if "__create__" in i and fl == 1:
                                sindex = i.find("object*", i.index("#define __class"))
                                fl = 2
                            else:
                                fl = 0
        elif file_name == "functions_c.txt":
            file_string += '\n\n'.join(data_additional["funcs"])
        elif file_name == "global_variables_h.txt":
            file_string = file_string.replace('12', str(12 + len(data_main["classes"])))
            for cname in data_additional['classes']:
                spisok = data_additional["classes"][cname]
                if spisok["vars"]:
                    file_string += 'struct ' + cname.capitalize() + ' {\n\tobject* ' + \
                                   ", * ".join(spisok["vars"]) + ';\n};\n'
                if spisok["vars_instance"]:
                    file_string += 'struct ' + cname.upper() + ' {\n\tobject* ' + \
                                   ", * ".join(spisok["vars_instance"]) + ';\n};\n'
                file_string += '\n'

            var = files_dict["global_variables_h.txt"]["var"]
            for i in data_additional['classes'].values():
                var |= set(i["vars"]) | set(i["vars_instance"])
            file_string += "\nextern uint " + ', '.join(map(lambda x: f"var({x})[]", var)) + ';\n\n'

            file_string_part = "object* " + ', * '.join(map(lambda x: x.capitalize(), classes)) + \
                               ';\nobject* ' + ', * '.join(global_vars_read) + ';'
            file_string += file_string_part.replace("Type_iterator",
                                                    "TypeIterator").replace("Class_name","ClassName")
        elif file_name == "start_program_c.txt":
            for cname in data_main['classes']:
                file_string += f'\t{cname.capitalize()} = __enlon(create__class_name' \
                               f'({cname.upper()}, "{cname.capitalize()}", ' + \
                               str(len(data_additional["classes"][cname]["vars_instance"])) + ', ' +\
                               str(len(data_main["classes"][cname])) + \
                               ''.join(map(lambda x: ", " + x, data_main["classes"][cname])) +\
                               '));\n'
            file_string += '\n\n\t' + '\n\t'.join(map(lambda x: x + ';', data_main["global_func"]))
            file_string += '\n}\n\n\n'

            create_vars = files_dict['start_program.c']['create_vars']
            for cname in data_additional['classes']:
                for i, var in enumerate(data_additional['classes'][cname]["vars"]):
                    if var in create_vars:
                        create_vars[var].append((cname.upper(), i + 1, True))
                    else:
                        create_vars[var] = [(cname.upper(), i + 1, True)]
                for i, var_instance in enumerate(data_additional['classes'][cname]["vars_instance"]):
                    if var_instance in create_vars:
                        create_vars[var_instance].append((cname.upper(), i + 1, False))
                    else:
                        create_vars[var_instance] = [(cname.upper(), i + 1, False)]
            sp = ["NOTH", "BOOL", "CLASS_NAME"]
            for var in create_vars:
                sort = sorted(create_vars[var],
                              key=lambda x: x[0] if x[0] not in sp else str(sp.index(x[0])))
                mp = map(lambda x: f"{x[0]}, {x[1]} << 16" if x[2] else f"{x[0]}, {x[1]}", sort)
                file_string += f"create_var({var}, {len(create_vars[var])}, {', '.join(mp)});\n"

            var = files_dict["global_variables_h.txt"]["var"]
            for i in data_additional['classes'].values():
                var |= set(i["vars"])
            file_string += "\nuint * __to_another_type_arr[] = {" + \
                           ", ".join([f"var(to_{i.lower()})" if ('to_' + i.lower() in var)
                                      else "NULL" for i in classes]) + '};'
        if file_name[-5] == 'h' and file_name != 'global_variables_h.txt':
            file_string += '\n\n#endif'
        file_name = directory + file_name[:-6] + '.' + file_name[-5]
        directories.append(file_name)
        with open(file_name, 'w+', encoding='utf8') as file:
            file.write(file_string + '\n')
    for cname in data_additional["classes"]:
        file_string = f'#include "all.h"\n#define __FILE {cname.lower()}_c\n' \
                      f'char* {cname.lower()}_c = "{cname.lower()}.c";\n\n\n'
        file_string += '\n\n'.join(data_additional["classes"][cname]["constructor"]) + '\n\n\n' + \
                       '\n\n'.join(data_additional["classes"][cname]["method"]) + '\n\n\n' + \
                       '\n\n'.join(data_additional["classes"][cname]["double"])
        file_name = directory + cname.lower() + '.c'
        directories.append(file_name)
        with open(file_name, 'w+', encoding='utf8') as file:
            file.write(file_string + '\n')

    for name in ('array.c', 'bool.c', 'class_name.c', 'error.c', 'func.c', 'garbage_collector.c',
                 'hidden.c', 'int.c', 'range.c', 'string.c', 'type_iterator.c', 'to_ctype.c'):
        copy("constant_files/" + name, directory)
    return directories


def from_qc_to_c_2(string: str, directory: str):
    global tags, words, words2, old_string, after_variable, operators_word, small_program, cur_i, \
        logs, fatality, errors, global_vars_read, global_vars_write, vars, args, data_main, \
        current_data, is_global, name_realname, end, class_name, arg_class, doubles, cur_file, \
        another_classes, all_args_names, data_additional
    cur_i = 0
    fatality = None
    errors = [[]]
    global_vars_write = [[]]
    vars = [[]]
    args = [[]]
    all_args_names = set()
    data_additional = {"funcs": [], "args_names": all_args_names,
                       "classes": dict(), "global_vars": global_vars_read}
    data_main = {"main_program": [], "classes": dict(), "global_vars": [], "global_func": []}
    current_data = data_additional["funcs"]
    is_global = False
    name_realname = dict()
    end = []
    class_name = None
    arg_class = []
    doubles = dict()
    cur_file = None

    another_classes = files_dict["start_program.c"]["vars"]
    global_vars_read = list(files_dict["start_program.c"]["global_vars_read"])
    with open("data.json", "r") as read_file:
        data = json.load(read_file)
    words = data["words"]
    words2 = data["words2"]
    tags = data["tags"]
    after_variable = data["after_variable"]
    operators_word = data["operators"]
    small_program = data["program"]
    old_string = string

    try:
        program()
    except IndexError as e:
        directories = files(directory)
        # pprint(data_main, width=200)
        # pprint(data_additional, width=200)
        return "Трансляция произведена успешно", new_errors(), directories
    except Exception as e:
        return "Я без понятия, что ты в коде понаписал!", new_errors(), str(e)
    return "Что-то пошло не так...", new_errors(), fatality


def new_errors():
    global errors
    new_es = []
    cur_i = 0
    cur_n = 1
    for i, file, string in sorted(errors[0]):
        while cur_i != i:
            if old_string[cur_i] == '\n':
                cur_n += 1
            cur_i += 1
        new_es.append((file, cur_n, string))
    return sorted(new_es)


string = """
func passive is_leap (n, month) {
    if month != 2 {
        return 0;
    };
    if (n % 100 != 0 & n % 4 == 0) | n % 400 == 0 {
       return 1;
    };
    return 0;
}

func passive add_0 (n) {
    if n < 10 {
        return "0" + n.to_string();
    };
    return n.to_string();
}

declare class Dt_delta {
     
}

class Date_time {

arr_days = array[31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];

constructor (self, year=1970, month=1, day=1, hour=0, minute=0, second=0) {
    minute = minute + second / 60;
    self.second = second % 60;
    hour = hour + minute / 60;
    self.minute = minute % 60;
    day = day + hour / 24;
    self.hour = day % 24;
    year = year + (month - 1) / 12;
    month = (month - 1) % 12 + 1;

    cur_days = self.arr_days[month - 1] + is_leap(year, month);
    while day > cur_days {
        day = day - cur_days;
        month = month + 1;
        if month == 13 {
            year = year + 1;
            month = 1;
        };
        cur_days = self.arr_days[month - 1] + is_leap(year, month);
    };
    self.day = day;
    self.month = month;
    self.year = year;
    return self;
}

method today (self) {
    return date_time(year=1970, month=1, day=1);
}
method now (self) {
    return date_time(year=1970, month=1, day=1, hour=0, minute=0, second=0);
}
method to_string(self) {
    return add_0(self.day) + "." + add_0(self.month) + "." + self.year.to_string() + " " + add_0(self.hour) + ":" + add_0(self.minute) + ":" + add_0(self.second);
}

double method of + with Dt_delta (self, self2) {
    return date_time(year=self.year, month=self.month, day=self.day, hour=self.hour, minute=self.minute, second=self.second + self2.seconds);
}

}


class Dt_delta {

constructor (self, days=0, hours=0, minutes=0, seconds=0) {
    hours = days * 24 + hours;
    minutes = hours * 60 + minutes;
    self.seconds = minutes * 60 + seconds;
    return self;
}

double method of + with Dt_delta (self, self2) {
    return dt_delta(self.seconds + self2.seconds);
}
double method of + with Date_time (self, self2) {
    return date_time(year=self2.year, month=self2.month, day=self2.day, hour=self2.hour, minute=self2.minute, second=self2.second + self.seconds);
}

}

main_program {
    dt = date_time();
    print(dt.now());
    
    num = input().to_int();
    date = dt.today();
    while date.year < 2030 {
        print("year: ", date.year, ",\tmonth: ", date.month, ",\tday: ", date.day, between="");
        date = date + dt_delta( , num);
    };
}
"""

string1 = """
func passive is_sample (num) {
    if num == 2 {
        return TRUE;
    };
    if num % 2 == 0 {
        return FALSE;
    };
    i = 3;
    while i * i < num {
        if num % i == 0 {
            return FALSE;
        };
        i = i + 2;
    };
    if num % i == 0 {
        return FALSE;
    };
    return TRUE;
}

main_program {
    print2 = copy(print);
    print2.change( , array[]0, after=" - простое число\n"w1251);
    
    foreach i from range(start=3, stop=1000, step=2) {
        if is_sample(i) {
            print2(i);
        };
    };
}
"""

if __name__ == '__main__':
    logs = True
    print('', *from_qc_to_c_2(string, "test/"), sep='\n')
