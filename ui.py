import tkinter as tk
from tkinter import filedialog, messagebox, ttk
from PIL import ImageTk
from CustomNotebook import CustomNotebook
from ScrollFrame import ScrollFrame
from translator import from_qc_to_c_2
import pyperclip as pc

END = 'end'
END1C = 'end-1c'
simple_list = [("Программный файл (*.qc)", '.qc'),
               ("Программный файл (*.c)", '.c'),
               ("Текстовый документ (*.txt)", '.txt')]
notebooks = None
error = None
application_window = None


def parse(s: str):
    for i in range(len(s) - 1, 0, -1):
        if s[i] == '/':
            return s[i + 1:], s[:i + 1]  # name, directory


def parse_name(s: str):
    for i in range(len(s) - 1, 0, -1):
        if s[i] == '.':
            return s[:i], s[i:]  # name, type


def current_type_list(s: str):
    for i in range(len(simple_list)):
        if simple_list[i][1] == s:
            return [simple_list[i]] + simple_list[:i] + simple_list[i + 1:]


class App:
    def __init__(self):
        global notebooks, error, application_window
        self.root = tk.Tk()
        application_window = self.root
        self.root.geometry("680x500")
        self.root.state('zoomed')
        self.root.iconbitmap('images/icon.ico')
        self.root.title('QC-editor')

        s = ttk.Style()
        s.configure('TNotebook.Tab', font=('Verdena', '10'))
        self.frame = ttk.Frame(self.root)
        self.notebook1 = NoteAndButtons('Иные файлы', self.frame)
        self.notebook2 = NoteAndButtons('QC-файлы', self.frame)
        notebooks = (self.notebook1, self.notebook2)
        self.bottom = ttk.Notebook(self.root)
        self.image = ImageTk.PhotoImage(file="images/error24.png")
        error = Error()
        self.bottom.add(error, compound=tk.LEFT, image=self.image, text='Ошибки (0)',
                        sticky="NSWE")

        self.notebook1.pack(side=tk.LEFT, fill='both', expand=True)
        self.notebook2.pack(side=tk.RIGHT, fill='both', expand=True)
        self.frame.pack(side=tk.TOP, fill='both', expand=True)
        self.bottom.pack(side=tk.BOTTOM, fill='both', padx=5)
        self.root.bind("<Configure>", self.onWindowConfigure)

        menuBar = tk.Menu(self.root)
        fileMenu = tk.Menu(menuBar, tearoff=0)
        fileMenu.add_command(label="Создать", command=self.notebook1.note.add_tab)
        fileMenu.add_command(label="Открыть", command=self.open_file)
        fileMenu.add_command(label="Сохранить всё", command=self.save_all)
        menuBar.add_cascade(label="Файл", menu=fileMenu)
        fileMenu = tk.Menu(menuBar, tearoff=0)
        fileMenu.add_cascade(label="О программе", command=self.program)
        fileMenu.add_command(label="Контакты разработчика", command=self.me)
        menuBar.add_cascade(label="Cправка", menu=fileMenu)
        self.root.config(menu=menuBar)

    def onWindowConfigure(self, event):
        error.frame.canvas.configure(height=self.root.winfo_height()//4)

    def open_file(self):
        for name in filedialog.askopenfilename(filetypes=simple_list, multiple=True):
            file = open(name, 'r+', encoding='utf-8')
            if parse_name(name)[1] == '.qc':
                self.notebook2.note.add_tab(*parse(name), file.read())
            else:
                self.notebook1.note.add_tab(*parse(name), file.read())
            file.close()

    def save_all(self):
        global notebooks
        for j in range(2):
            tabs = notebooks[j].note.tab_list
            for i in range(notebooks[j].note.num_tabs):
                name, text = tabs[i].save_tab(False)
                file = open(name, 'w+', encoding='utf-8')
                file.write(text)
                file.close()

    def me(self):
        messagebox.showinfo("Контакты разработчика", "Quicon (quick and convenient)")

    def program(self):
        messagebox.showinfo("О программе", "Quicon (quick and convenient)")

    def run(self):
        self.root.mainloop()


class NoteAndButtons(ttk.Frame):
    def __init__(self, typ, *args, **kwargs):
        ttk.Frame.__init__(self, *args, **kwargs)
        self.note = MyNotebook(self)
        self.note.pack(fill="both", expand=True, side=tk.BOTTOM, padx=5, pady=2)
        self.menu = ttk.Frame(self)
        self.image = ImageTk.PhotoImage(file="images/new_file28.png")
        tk.Button(self.menu, image=self.image, command=self.note.add_tab, highlightthickness=0,
                  bd=0).pack(side=tk.LEFT, padx=5)
        self.image1 = ImageTk.PhotoImage(file="images/open28.png")
        tk.Button(self.menu, image=self.image1, command=self.note.open_file, highlightthickness=0,
                  bd=0).pack(side=tk.LEFT, padx=5)
        self.image2 = ImageTk.PhotoImage(file="images/save28.png")
        tk.Button(self.menu, image=self.image2, command=self.note.save, highlightthickness=0,
                  bd=0).pack(side=tk.LEFT, padx=5)
        if typ == 'QC-файлы':
            self.image3 = ImageTk.PhotoImage(file="images/c28.png")
            tk.Button(self.menu, image=self.image3, command=self.note.qc_in_c, highlightthickness=0,
                      bd=0).pack(side=tk.LEFT, padx=5)
        tk.Label(self.menu, font=("Verdena", 12), text=typ).pack(padx=5, fill='both')
        self.menu.pack(fill='both', side=tk.TOP, padx=5, pady=5)


class MyNotebook(CustomNotebook):
    def __init__(self, *args, **kwargs):
        CustomNotebook.__init__(self, *args, **kwargs)

        self.cur_tab = None
        self.num_tabs = 0
        self.tab_list = []

        self.bind("<<NotebookTabChanged>>", self.select_tab)
        self.bind("<<NotebookTabClosed>>", self.close_tab)

    def open_file(self):
        for name in filedialog.askopenfilename(filetypes=simple_list, multiple=True):
            file = open(name, 'r+', encoding='utf-8')
            self.add_tab(*parse(name), file.read())
            file.close()

    def add_tab(self, name=None, directory=None, text=''):
        if name is None:
            name = 'New ' + str(self.num_tabs + 1) + '.txt'
        tab = Tab(self, name, directory, text)
        self.tab_list.append(tab)
        self.add(tab, text=name, sticky="NSWE")
        self.select(self.num_tabs)
        self.num_tabs += 1

    def save_as(self):
        self.save(dialog=True)

    def save(self, dialog=False):
        if self.cur_tab is not None:
            name, text = self.cur_tab.save_tab(dialog)
            file = open(name, 'w+', encoding='utf-8')
            file.write(text)
            file.close()

    def qc_in_c(self):
        global notebooks, error
        if notebooks[1].note.cur_tab is not None:
            text = notebooks[1].note.cur_tab.text.get("1.0", END1C)
            ans = filedialog.askdirectory()
            message, errors, additional = from_qc_to_c_2(text, ans + '/')
            if message == "Трансляция произведена успешно":
                messagebox.showinfo("Информация", message)
                for name in additional:
                    file = open(name, 'r+', encoding='utf-8')
                    notebooks[0].note.add_tab(*parse(name), file.read())
                    file.close()
            elif message == "Что-то пошло не так...":
                messagebox.showinfo("Информация", message + '\n' + additional)
            else:
                messagebox.showinfo("Информация", "Критическая ошибка" + '\n' + additional)
            if errors:
                print(errors)
                error.add_all(errors)  # , self.cur_tab.name

    def select_tab(self, event):
        if self.num_tabs > 0:
            self.cur_tab = self.tab_list[self.index('current')]
        else:
            self.cur_tab = None

    def close_tab(self, event):
        del self.tab_list[self.active]
        self.num_tabs -= 1


class Tab(ttk.Frame):
    def __init__(self, root, name, directory, text):
        ttk.Frame.__init__(self, root)
        self.root = root
        self.name = name
        self.not_saved = directory is None
        self.directory = directory
        height = 1
        width = 1

        self.text = tk.Text(self, wrap='none', font=("Consolas", 13), yscrollcommand=self.onysco,
                            padx=5, width=width, height=height, bd=3)
        self.scrollby = ttk.Scrollbar(self, orient=tk.VERTICAL, command=self.scroll_command)
        self.numbers = tk.Text(self, font=("Consolas", 13), width=4, height=height, bg='lightgray',
                               state=tk.DISABLED, relief=tk.FLAT, padx=5, pady=3,
                               exportselection=False)
        self.scrollby2 = ttk.Scrollbar(self, orient=tk.HORIZONTAL, command=self.text.xview)
        self.text.configure(xscrollcommand=self.scrollby2.set)

        self.numbers.grid(row=0, column=0, sticky='NS')
        self.text.grid(row=0, column=1, sticky='NSWE')
        self.scrollby.grid(row=0, column=2, sticky='NS')
        tk.Label(self, bg='lightgray').grid(row=1, column=0, sticky='WE')
        self.scrollby2.grid(row=1, column=1, sticky='WE')
        self.grid_columnconfigure(1, weight=1)
        self.grid_rowconfigure(0, weight=1)

        self.text.insert(END, text)
        self.count_of_lines = 0
        self.numbers.tag_configure("r", justify='right')
        self.insert_numbers()
        self.text.bind('<<Modified>>', self.on_edit)

        self.menu = tk.Menu(tearoff=0)
        self.menu.add_command(label="Вырезать", command=self.cut)
        self.menu.add_command(label="Копировать", command=self.copy)
        self.menu.add_command(label="Вставить", command=self.paste)
        self.text.bind('<Button-3>', self.popup)
        # self.text.bind('<Control-x>', self.cut)
        # self.text.bind('<Control-c>', self.copy)
        # self.text.bind('<Control-v>', self.paste)

    def popup(self, event=None):
        self.menu.post(event.x_root, event.y_root)

    def copy(self, event=None):
        pc.copy(self.text.get(tk.SEL_FIRST, tk.SEL_LAST))

    def cut(self, event=None):
        self.copy()
        # self.text.delete(tk.SEL_FIRST, tk.SEL_LAST)

    def paste(self, event=None):
        self.text.insert(tk.INSERT, pc.paste())

    def scroll_command(self, *args):
        self.text.yview(*args)
        self.numbers.yview(*args)

    def onysco(self, *args):
        self.scrollby.set(*args)  # Синхронизация скролбара с текстовым полем
        self.numbers.yview_moveto(args[0])  # Синхронизация поля с номерами с текстовым полем

    def insert_numbers(self):
        count_of_lines = int(self.text.index(END1C).split('.')[0])
        if count_of_lines != self.count_of_lines:
            self.numbers.config(state=tk.NORMAL)
            self.numbers.delete('1.0', END)
            self.numbers.insert('1.0', '\n'.join(map(str, range(1, count_of_lines + 1))), "r")
            self.numbers.config(state=tk.DISABLED)
            self.count_of_lines = count_of_lines

    def on_edit(self, event):
        # Срабатывает при изменениях в текстовом поле
        self.insert_numbers()
        self.text.edit_modified(0)  # Сбрасываем флаг изменения текстового поля

    def save_tab(self, dialog):
        if dialog or self.not_saved:
            main_name, typ = parse_name(self.name)
            name = filedialog.asksaveasfilename(initialdir=self.directory, initialfile=main_name,
                                                defaultextension=typ,
                                                filetypes=current_type_list(typ))
            self.name, self.directory = parse(name)
            self.root.tab(self.root.index('current'), text=self.name)
            self.not_saved = False
        else:
            name = self.directory + self.name
        return name, self.text.get("1.0", END1C)


class Error(ttk.Frame):
    def __init__(self, *args, **kwargs):
        ttk.Frame.__init__(self, *args, **kwargs)
        self.number = 0
        self.header = ttk.Frame(self)
        tk.Label(self.header, font=("Verdena", 11), text="Код", padx=8, pady=3, bg='lightgray',
                 borderwidth=2, relief="ridge").grid(row=0, column=0, sticky='WE')
        tk.Label(self.header, font=("Verdena", 11), text="Описание", padx=8, pady=3, bg='lightgray',
                 borderwidth=2, relief="ridge").grid(row=0, column=1, sticky='WE')
        tk.Label(self.header, font=("Verdena", 11), text="Файл", padx=8, pady=3, bg='lightgray',
                 borderwidth=2, relief="ridge").grid(row=0, column=2, sticky='WE')
        tk.Label(self.header, font=("Verdena", 11), text="Стр...", padx=8, pady=3, bg='lightgray',
                 borderwidth=2, relief="ridge").grid(row=0, column=3, sticky='WE')
        tk.Label(self.header, padx=7, pady=4, bg='lightgray',
                 borderwidth=2, relief="ridge").grid(row=0, column=4)
        self.header.grid_columnconfigure(0, weight=10)
        self.header.grid_columnconfigure(1, weight=60)
        self.header.grid_columnconfigure(2, weight=10)
        self.header.grid_columnconfigure(3, weight=1)
        self.header.grid(row=0, column=0, sticky='we')

        self.frame = ScrollFrame(self)
        self.frame.viewPort.grid_columnconfigure(0, weight=10)
        self.frame.viewPort.grid_columnconfigure(1, weight=60)
        self.frame.viewPort.grid_columnconfigure(2, weight=10)
        self.frame.viewPort.grid_columnconfigure(3, weight=1)
        self.frame.grid(row=1, column=0, sticky='nswe')
        self.grid_columnconfigure(0, weight=1)
        self.grid_rowconfigure(1, weight=1)

    def add(self, file, line, text):
        tk.Label(self.frame.viewPort, font=("Consolas", 13), text="Ошибка трансляции",padx=8, pady=3,
                 bg='white', anchor='w').grid(row=self.number, column=0, sticky='WE')
        tk.Label(self.frame.viewPort, font=("Verdena", 12), text=text, padx=8, pady=3,
                 bg='white', anchor='w').grid(row=self.number, column=1, sticky='WE')
        tk.Label(self.frame.viewPort, font=("Consolas", 13), text=file, padx=8, pady=3,
                 bg='white', anchor='w').grid(row=self.number, column=2, sticky='WE')
        tk.Label(self.frame.viewPort, font=("Consolas", 13), text=line, padx=8, pady=3,
                 bg='white', anchor='e').grid(row=self.number, column=3, sticky='WE')

    def add_all(self, args: list):
        for i in args:
            self.add(*i)
            self.number += 1
        self.number = 0


if __name__ == '__main__':
    app1 = App()
    app1.run()
