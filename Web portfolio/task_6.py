from tkinter import *
from tkinter import messagebox
from tkinter import ttk

class Grading:
   def __init__(self, win):
       self.P_lbl = Label(win, text='Prelim Grade:')
       self.P_lbl.grid(row=0, column=0, padx=20)
       self.P_grade = Entry(width=45)
       self.P_grade.grid(row=0, column=1)


       self.M_lbl = Label(win, text='Midterm Grade:')
       self.M_lbl.grid(row=1, column=0, padx=20)
       self.M_grade = Entry(width=45)
       self.M_grade.grid(row=1, column=1)


       self.PF_lbl = Label(win, text='Pre Final Grade:')
       self.PF_lbl.grid(row=2, column=0, padx=20)
       self.PF_grade = Entry(width=45)
       self.PF_grade.grid(row=2, column=1)


       self.F_lbl = Label(win, text='Final Grade:')
       self.F_lbl.grid(row=3, column=0, padx=20)
       self.F_grade = Entry(width=45)
       self.F_grade.grid(row=3, column=1, columnspan=1)


       self.Option = Label(win, text='Choose an Option:', font=("Arial", 15))
       self.Option.grid(row=4, column=0, columnspan=1)


       self.cmb = ttk.Combobox(win, width=25, values=("Letter Grade", "NUMERIC GRADE"))
       #self.cmb.set("Letter Grade") based sa instruction feel ko not need
       self.cmb.grid(row=4, column=1,)


       self.text_area = Text(width=55,height=10)
       self.text_area.grid(row=5, columnspan=3)


       #mano mano place nalang ako sa grid na yan XD
       self.Comp = Button(win, text='Compute', command=self.compute, width=10)
       self.Comp.place(x=30,y=280)


       self.Reset = Button(win, text='Reset', command=self.reset, width=10)
       self.Reset.place(x=130,y=280)


       self.About = Button(win, text='About', command=self.about, width=10)
       self.About.place(x=230,y=280)


       self.Close = Button(win, text='Close', command=self.close, width=10)
       self.Close.place(x=330,y=280)








   def compute(self):
       try:
           P = float(self.P_grade.get())
           M = float(self.M_grade.get())
           PF = float(self.PF_grade.get())
           F = float(self.F_grade.get())
       except ValueError:
           self.text_area.delete('1.0', 'end')
           self.text_area.insert('end', "Invalid or Missing input."
                                      "\nPlease enter correct and/or complete numeric grades.")
           return


       if any(grade > 100 for grade in (P, M, PF, F)):
           self.text_area.delete('1.0', 'end')
           self.text_area.insert('end', "Invalid grade input. \nGrades must be a positive number no more than 100.")
           return


       GPA = (P + M + (PF + F)/2) / 3
       if 75 <= GPA <= 100:
           classification  = 'Passed'
       else:
           classification = 'Failed'
       if self.cmb.get() == 'Letter Grade':
           if 96 <= GPA <= 100:
               GPA_letter = 'A'
           elif 93 <= GPA < 96:
               GPA_letter = 'A-'
           elif 88 <= GPA < 93:
               GPA_letter = 'B'
           elif 83 <= GPA < 88:
               GPA_letter = 'B-'
           elif 78 <= GPA < 83:
               GPA_letter = 'C'
           elif 76 <= GPA < 78:
               GPA_letter = 'D'
           elif 75 <= GPA < 76: #same note sa baba
               GPA_letter = 'E'
           elif GPA < 75:
               GPA_letter = 'F'
           else:
               GPA_letter = 'INVALID'
           self.text_area.delete('1.0', 'end')
           self.text_area.insert('end', f"Transaction summary...\n\n"
                                        f"Prelim Grade: {P:.2f}\n"
                                        f"Midterm Grade: {M:.2f}\n"
                                        f"Pre Finals: {PF:.2f}\n"
                                        f"Finals: {F:.2f}\n"
                                        f"GPA is: {GPA:.2f}"
                                        f"\nLetter Grade: {GPA_letter}"
                                        f"\nRemarks: {classification}")
           if GPA_letter == 'INVALID':
               self.text_area.insert('end', f"\nplease ensure the inputted grades are correct.")
       elif self.cmb.get() == 'NUMERIC GRADE':
           if 97 <= GPA <= 100:
               GPA_NUM = 1.0
           elif 94 <= GPA < 97:
               GPA_NUM = 1.25
           elif 90 <= GPA < 94:
               GPA_NUM = 1.50
           elif 87 <= GPA < 90:
               GPA_NUM = 1.75
           elif 84 <= GPA < 87:
               GPA_NUM = 2.00
           elif 81 <= GPA < 84:
               GPA_NUM = 2.25
           elif 78 <= GPA < 81:
               GPA_NUM = 2.50
           elif 76 <= GPA < 78: #basically from 77.99 to 76 since pag ginawa 77 that leaves a gap?
               GPA_NUM = 2.75
           elif 75 <= GPA < 76: #made it like this since pag barely above 75 like 75.4 nag output dati ng invalid
               GPA_NUM = 3.0
           elif 65 <= GPA < 75:
               GPA_NUM = 5.0
           else:
               GPA_NUM = 'INVALID'
           self.text_area.delete('1.0', 'end')
           self.text_area.insert('end', f"Transaction summary...\n\n"
                                        f"Prelim Grade: {P:.2f}\n"
                                        f"Midterm Grade: {M:.2f}\n"
                                        f"Pre Finals: {PF:.2f}\n"
                                        f"Finals: {F:.2f}\n"
                                        f"GPA is: {GPA:.2f}"
                                        f"\nNUMERIC Grade: {GPA_NUM}"
                                        f"\nRemarks: {classification}")
           if GPA_NUM == 'INVALID':
               self.text_area.insert('end', f"please ensure the inputted grades are correct.")


   def reset(self):
       self.text_area.delete("1.0", 'end')
       self.M_grade.delete(0, 'end')
       self.F_grade.delete(0, 'end')
       self.P_grade.delete(0, 'end')
       self.PF_grade.delete(0, 'end')
       self.cmb.set("") # .delete no worky idk


   def about(self):
       messagebox.showinfo('about', "Hello I'm Katriel Cire I. Tongol")


   def close(self):
       if messagebox.askyesno(title='Close it', message='Are you sure you want to exit'):
           window.quit()




window = Tk()
mywin = Grading(window)
window.title('Grading Program')
window.geometry("440x400+10+10")
window.resizable(0, 0)
window.mainloop()
