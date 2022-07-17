import java.lang.*;
import java.util.*;

//create table student(RID int,Name varchar(255),Salary int);
// Database table / schema
class Student
{
    public int RID;
    public String Name;
    public int Salary;
    public int Age;
    
    private static int Generator;
    private static int Cnt;
    
    static
    {
       Generator = 0;
       Cnt = 0;
    }
    
    public Student(String str,int value,int age)
    {
        this.RID = ++Generator;
        this.Name = str;
        this.Salary = value;
        this.Age = age;
    }
    
    public void DisplayData()
    {
        if(Cnt==0)
        {
            System.out.println("RID\t\t"+"Name\t"+"Salary\t"+"Age");
            Cnt++;
        }
        
    	System.out.println("------------------------------------------------------------");
        System.out.println(this.RID+"\t\t"+this.Name+"\t"+this.Salary+"\t"+this.Age);
    }
}

class DBMS
{
    public LinkedList<Student>lobj;
    
    public DBMS()
    {
        lobj = new LinkedList<>();
    }
    
    public void man()
    {
        System.out.println("To insert data : "+" insert into database_name student_name salary Age");
        System.out.println("To display information of all student : "+" select * from database name");
        System.out.println("To display information of specific student using name: "+" student name student_name");
        System.out.println("To display information of specific student using RID: "+" student rid student_rid");
        System.out.println("To delete information of specific student using name: "+" delete name student_name");
        System.out.println("To delete information of specific student using RID: "+" delete rid student_rid");
        System.out.println("To display maximum salary of student : "+" select maximum salary from student");
        System.out.println("To display minimum salary of student : "+" select minimum salary from student");
        System.out.println("To display sum of salary of students : "+" student salarysum");
        System.out.println("To display average of salary of students : "+" student salaryavg");
        System.out.println("To display count of students : "+" student count");  
        System.out.println("To display the salary using name : "+"student salary from name student_name");      
        System.out.println("To display the salary using rid : "+"student salary from rid student_rid"); 
    }
    
    // Insert into student omkar 1000;
    //select *from student
    public void StartDBMS()
    {
        Scanner scanobj = new Scanner(System.in);
        
        System.out.println("customised DBMS Started Successfully");
        String Query = "";
        
        while(true)
        {
            System.out.println("DBMS console >");
            Query = scanobj.nextLine();
            Query = Query.toLowerCase();
            
            String tokens[] = Query.split(" ");
            int QuerySize = tokens.length;
            
            if(QuerySize == 1)
            {
                if("help".equals(tokens[0]))
                {
                    System.out.println("This application is used to demostarte the customised DBMS");
                    System.out.println("Exit : Terminates DBMS");
                    System.out.println("Display all data : select * from student");
                    System.out.println("Insert Data : Insert into student Name Salary Age");
                }
                else if("exit".equals(tokens[0]))
                {
                    System.out.println("Thank you for using Marvellous DBMS");
                    break;
                }
                else if("man".equals(tokens[0]))
                {
                    man();
                }
            }
            else if(QuerySize == 2)
            {
                if("student".equals(tokens[0]))
                {
                    if("salarysum".equals(tokens[1]))
                    {
                        AggregateSum();
                    }
                    else if("salaryavg".equals(tokens[1]))
                    {
                        AggregateAvg();
                    }
                    else if("count".equals(tokens[1]))
                    {
                        AggregateCount();
                    }
                }
            }
            else if(QuerySize == 3)
            {
                if("student".equals(tokens[0]))
                {
                    if("name".equals(tokens[1]))
                    {
                        DisplaySpecific(tokens[2]);
                    }
                    else if("rid".equals(tokens[1]))
                    {
                        DisplaySpecific(Integer.parseInt(tokens[2]));
                    }
                 }
               else if("delete".equals(tokens[0]))
               {
                    if("name".equals(tokens[1]))
                    {
                        DeleteSpecific(tokens[2]);
                    }
                    else if("rid".equals(tokens[1]))
                    {
                        DeleteSpecific(Integer.parseInt(tokens[2]));
                    }
               }
                
            }
            else if(QuerySize == 4)
            {
                if("select".equals(tokens[0]))
                {
                    if("*".equals(tokens[1]))
                    {
                        DisplayAll();
                    }
                }
                
            }
            else if(QuerySize == 5)
            {
                if("select".equals(tokens[0]))
                {
                    if("maximum".equals(tokens[1]))
                    {
                        if("salary".equals(tokens[2]))
                        {
                            AggregateMax();
                        }
                    }
                    else if("minimum".equals(tokens[1]))
                    {
                        if("salary".equals(tokens[2]))
                        {
                            AggregateMin();
                        }
                    }
                }
                
                else if("student".equals(tokens[0]))
                {
                    if("salary".equals(tokens[1]))
                    {
                        if("name".equals(tokens[3]))
                        {
                            FindSalary(tokens[4]);
                        }
                        else if("rid".equals(tokens[3]))
                        {
                            FindSalary(Integer.parseInt(tokens[4]));
                        }
                    }
                }
            }
            else if(QuerySize == 6)
            {
                //Insert into student omkar 1000 32;
                if("insert".equals(tokens[0]))
                {
                     InsertData(tokens[3],Integer.parseInt(tokens[4]),Integer.parseInt(tokens[5]));
                }
            }

        }
    } 
    
    
    // To insert values.
    public void InsertData(String str, int value,int Age)
    {
        Student sobj = new Student(str,value,Age);
        lobj.add(sobj);
    }
    
    //Display By Name
    public void DisplayAll()
    {
        for(Student sref : lobj)
        {
            sref.DisplayData();
        }
    }
    
    //Display By RID
    public void DisplaySpecific(int rid)
    {
        for(Student sref : lobj)
        {
            if(sref.RID == rid)
            {
               sref.DisplayData();
               break;
            }
        }
    }
    
    
    // Display by name
    public void DisplaySpecific(String str)
    {
        int iCnt = 0;
        for(Student sref : lobj)
        {
            iCnt++;
            if(str.equals(sref.Name))
            {
               sref.DisplayData();
               iCnt--;
               break;  
            }
        }
        
        if(iCnt==lobj.size())
        {
            System.out.println("There is no such student with this name");
        }
        System.out.println();
    }
    
    //Delete By Id
    public void DeleteSpecific(int rid)
    {
        int index = 0;
        for(Student sref : lobj)
        {
            if(sref.RID == rid)
            {
               lobj.remove(index);
               break;
            }
            index++;
        }
    }
    
    //Delete By Name
    public void DeleteSpecific(String str)
    {
        int index = 0;
        for(Student sref : lobj)
        {
            if(str.equals(sref.Name))
            {
               lobj.remove(index);
               break;
            }
            index++;
        }
    }
    
    
    // To display Maximum salary.
    public void AggregateMax()
    {
        int iMax = 0;
        Student temp = null;
        
        for(Student sref : lobj)
        {
            if(sref.Salary>iMax)
            {
                iMax = sref.Salary;
                temp = sref;
            }
        }
        System.out.println("Information of student having maximum salary: ");
        temp.DisplayData();
    }
    
    
    // To display Minimum salary
    public void AggregateMin()
    {
        int iMin = (lobj.getFirst()).Salary;
        Student temp = lobj.getFirst();
        
        for(Student sref : lobj)
        {
            if(sref.Salary<iMin)
            {
                iMin = sref.Salary;
                temp = sref;
            }
        }
        System.out.println("Information of student having minimum salary: ");
        temp.DisplayData();
    }
    
    
    // To display Sum of all salaries.
    public void AggregateSum()
    {
       long iSum = 0;
        
        for(Student sref : lobj)
        {
            iSum = iSum + sref.Salary;
        }
        System.out.println("Summation of Salaries is : "+iSum);
    }
    
    
    // To display average salary
    public void AggregateAvg()
    {
       long iSum = 0;
        
        for(Student sref : lobj)
        {
            iSum = iSum + sref.Salary;
        }
        System.out.println("Avarage salary is : "+iSum/(lobj.size()));
    }
    
    
    // To count number of students
    public void AggregateCount()
    {
         System.out.println("Count is: "+lobj.size());
    }
    
    
    //Find salary of student using name
    public void FindSalary(String str)
    {
         int iSal = 0;
         for(Student sref : lobj)
         {
             if(str.equals(sref.Name))
             {
                 iSal = sref.Salary;
                 break;
             }
         }
         if(iSal == 0)
         {
             System.out.println("There is no such student with this name");
         }
         else
         {
             System.out.println("Salary of "+str+" is "+iSal);
         }
    }
    
    
    //Find salary of student using rid
    public void FindSalary(int rid)
    {
         int iSal = 0;
         for(Student sref : lobj)
         {
             if(sref.RID == rid)
             {
                 iSal = sref.Salary;
                 break;
             }
         }
         if(iSal == 0)
         {
             System.out.println("There is no such student with this name");
         }
         else
         {
             System.out.println("Salary of "+rid+" is "+iSal);
         }
    }
}



class FinalDBMS
{
    public static void main(String arg[])
    {
        DBMS dobj = new DBMS();
        dobj.StartDBMS();
        
    }

}


