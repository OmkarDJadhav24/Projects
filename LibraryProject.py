class Library:
    def __init__(self,list,name):
        self.list=list
        self.name=name
        print("Welcome in",self.name)
        self.list2=[]

    def Display(self):
        print("We have following books in our",self.name)
        for book in self.list:
            print(book)
    def LendBook(self):
        self.value=input("Enter the book name you want to lend:")
        self.name=input("Please enter your name:")
        if self.value in self.list:
            if self.value not in self.list2:
                self.list2.append(self.value)
                print("Registration successful,You can take book now")
            else:
                print("Book is already on lend")
        else:
            print("This book is not available in our library")
    def AddBook(self):
        self.addB=input("Enter the book name you want to add:")
        self.list.append(self.addB)
        print("Book added to library")
    def ReturnBook(self):
        print("Enter the book name you want to return")
        ret=input()
        if ret not in self.list2:
            print("This book is not on lend")
        else:
            self.list2.remove(ret)
            print("Book return successfully")
def main():
    list=['C programming','Python Machine Learning','Artificial Intellegence','Python Automation CookBook','C++ the complete reference']
    name="Silent Library"
    obj=Library(list,name)
   

    while True:
        print("please select one option")
        print("1.Display the books")
        print("2.Lend book")
        print("3.Add Book")
        print("4.Return Book")
        value2=input()
        if value2 not in ["1","2","3","4"]:
            print("Please enter valid number")
            continue
        else:
            value2=int(value2)
        if value2==1:
            obj.Display()
        elif value2==2:
            obj.LendBook()
        elif value2==3:
            obj.AddBook()
        elif value2==4:
            obj.ReturnBook()
        else:
            print(not valid)


        print("Please select q for exit or c for continue")
        user_option=input()
        if user_option=='q':
            exit()
        elif user_option=='c':
            continue
        else:
            print("Enter the valid option")

if __name__=="__main__":
    main()