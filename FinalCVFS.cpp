#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
//#include<io.h>

#define MAXINODE 50

#define READ 1
#define WRITE 2

#define MAXFILESIZE 2048

#define REGULAR 1
#define SPECIAL 2

#define START 0
#define CURRENT 1
#define END 2

typedef struct superblock
{
    int TotalInodes;
    int FreeInode;
}SUPERBLOCK, * PSUPERBLOCK;

typedef struct inode
{
    char FileName[MAXINODE];
    int InodeNumber;
    int FileSize;
    int FileActualSize;
    int FileType;
    char *Buffer;
    int LinkCount;
    int ReferenceCount;
    int permission;       // 1  23
    struct inode *next;
}INODE, *PINODE, **PPINODE;

typedef struct filetable
{
    int readoffset;
    int writeoffset;
    int count;
    int mode;   // 1  2  3
    PINODE ptrinode;
}FILETABLE, *PFILETABLE;

typedef struct ufdt
{
    PFILETABLE ptrfiletable;
}UFDT;

UFDT UFDTArr[MAXINODE];
SUPERBLOCK SUPERBLOCKobj;
PINODE head = NULL;


void man(char *name)
{
    if(name == NULL)return;
    
    if(strcmp(name,"create")==0)
    {
         printf("Description: Used to create new regular file\n");
         printf("Usage:create File_name Permission\n");
    }
    else if(strcmp(name,"read")==0)
    {
         printf("Description: Used to read data from regular file\n");
         printf("Usage:read File_name No_of_Bytes_To_Read\n");
    }
    else if(strcmp(name,"write")==0)
    {
         printf("Description : Used to write into regular file\n");
         printf("Usage : write File_Name \n After this enter the data that you want to write\n");
    }
    else if(strcmp(name,"ls")==0)
    {
         printf("Description : Used to list all information of files\n");
         printf("Usage:ls\n");
    }
    else if(strcmp(name,"stat")==0)
    {
         printf("Used to display information of files\n");
         printf("Usage : stat FIle_Name\n");
    }
    else if(strcmp(name,"fstat")==0)
    {
         printf("Description : Used to display information of file\n");
         printf("Usage : fstat File_Descriptor\n");
    }
    else if(strcmp(name,"truncate")==0)
    {
         printf("Descriptor : Used to remove data from file\n");
         printf("Usage : truncate File_Name\n");
    }
    else if(strcmp(name,"open")==0)
    {
         printf("Descriptor : Used to open existing File\n");
         printf("Usage : open File_name mode\n");
    }
    else if(strcmp(name,"close")==0)
    {
         printf("Descriptor : Used to close opened File\n");
         printf("Usage : close File_name\n");
    }
    else if(strcmp(name,"closeall")==0)
    {
         printf("Descriptor : Used to close all opened File\n");
         printf("Usage : closeall\n");
    }
    else if(strcmp(name,"lseek")==0)
    {
         printf("Description : Used to change file offset\n");
         printf("Usage : lseek File_Name ChangeInOffset StartPoint\n");
    }
    else if(strcmp(name,"rm")==0)
    {
         printf("Description : Used to delete the File\n");
         printf("Usage : rm File_Name\n");
    }
    else
    {
         printf("ERROR : No manual entry available\n");
    }  
}

void DisplayHelp()
{
    printf("ls : To List out all files\n");
    printf("clear : To clear console\n");
    printf("open : TO open the file\n");
    printf("close : To close the file\n");
    printf("closeall : To close all opened files\n");
    printf("read : To Read the contents from file\n");
    printf("write : To Write contents into file\n");
    printf("exit : To Terminate file system\n");
    printf("stat : To Display information of file using name\n");
    printf("fstat : To Display information using file descriptor\n");
    printf("truncate : To Remove all data from file\n");
    printf("rm To Delete the file\n");
}


/*
    Name Of Function : GetFDFromName()
    Input Parameter :  address of String
    Return Value of Function : Integer
    Decription of The function and its use in project : 
    	This function takes name from function who call this function.
    	Then it will take one parameter which will initialize with 0.
    	Then using while loop it will check UFDT array. In UFDT array we have stored address of filetables.
    	This while loop will check if UFDT arrays ith value is not NULL and it will also check if FileType is 0. Because we have provide 2 file types regular and special.
    	If both conditions are true then it will compare the name of file which we pass as argument and name of file which is stored in Inode's filename section.
    	if both the file are same it will return 0 and while loop will stop. Then this function will check is value of i == total Inodes(MAXINODE)
    	if it is true then this function will return -1 and if not it will return the index number(File Descriptor) where the while loop stop. 
*/

int GetFDFromName(char *name)
{
    int i = 0;
    
    while(i<MAXINODE)
    {
         if(UFDTArr[i].ptrfiletable != NULL)
         	if(strcmp((UFDTArr[i].ptrfiletable->ptrinode->FileName),name)==0)
         		break;
         i++;
    }
    
    if(i == MAXINODE) 
    {
         return -1;
    }
    else
    {
         return i;
    }
}


/*
    Name Of Function : Get_Inode()
    Input Parameter :  address of String
    Return Value of Function : Integer
    Decription of The function and its use in project : 
    	This function accept file name from the function from which this function get called.
    	In this function we store the address of first Inode in one temperory pointer.
    	Then it will check if name is null or not if it is null it will return null.
    	And if it is not then in while loop it will chech if temp value is null or not if it is null it will not enter in while loop.
    	and if it is not null then it will compare the name which is passed as argument is equal to the name which is stored in the Inode whose address is stored in temperory pointer.
    	if it is equal it will break the while loop and if not it will store the address of next Inode in temp.That address is in next pointer of that Inode.
    	After completion of while loop it will return	the address stored in the temp. and if temp contains null it will return null.
*/
PINODE Get_Inode(char * name)
{
     PINODE temp = head;
     int i = 0;
     
     if(name == NULL)
     	return NULL;
     	
     while(temp != NULL)
     {
         if(strcmp(name,temp->FileName)==0)
         	break;
         	
         temp = temp->next;
     }
     
     return temp;
}


/*
    Name Of Function : CreateDILB()
    Input Parameter :  None
    Return Value of Function : None
    Decription of The function and its use in project : 
    	This function will create Inodes.Memory will be allocate dunamically using malloc function.
    	When Inode gets created using malloc function the address of that Inode will store in pointer newn.
    	what size we have provided to the while loop that number of Inode gets created.
    	After Inode gets created all the fields of that Inode which we have mentioned in the inode structure are set to its default value.
    	Then in Inode's next pointer the address of next Inode is stored
*/
void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;
    
    while(i<=MAXINODE)
    {
        newn = (PINODE)malloc(sizeof(INODE));
        
        newn->LinkCount = 0;
        newn->ReferenceCount = 0;
        newn->FileType = 0;
        newn->FileSize = 0;
        
        newn->Buffer = NULL;
        newn->next = NULL;
        
        newn->InodeNumber = i;
        
        if(temp == NULL)
        {
           head = newn;
           temp = head;
        }
        else
        {
           temp->next = newn;
           temp = temp->next;
        }
        i++;
    }
    printf("DILB created successfully\n");
}


/*
    Name Of Function : InitializeSuperBlock()
    Input Parameter :  None
    Return Value of Function : None
    Decription of The function and its use in project : 
    	In this function we initialize UFDT array with null.
    	After that we initialize structure superblock's TotalInodes ,FreeInode variables with MAXINODE
*/
void InitializeSuperBlock()
{
    int i = 0;
    while(i<MAXINODE)
    {
        UFDTArr[i].ptrfiletable = NULL;
        i++;
    }
    
    SUPERBLOCKobj.TotalInodes = MAXINODE;
    SUPERBLOCKobj.FreeInode = MAXINODE;
}


/*
    Name Of Function : CreateFile()
    Input Parameter :  address of String, Integer
    Return Value of Function : Integer
    Decription of The function and its use in project : 
    	This file create is used to create the new file
    	This function will check the permission of file and then free node is available or not.
    	Then it will check file type of Inode is 0 or not and if 0 it will return from while loop with address of that Inode whose value type is 0. and that address is in temp.
    	Then it will check UFDT array on which index value is null.It will take the index number of that null value and then it will store the address of new filetable on that position.filetable gets memory dynamically using malloc.
    	In the filetable there is ptrinode pointer in that pointer we store address of Inode which is in temp.
    	After it will copy name of file which we have pass as argument to the file name field of Inode.
    	And then it will create the file and modify the fields of that Inode.
*/
int CreateFile(char *name, int permission)               // To create a file.
 {
	 int i = 0;
	 PINODE temp = head;
	 
	 if((name == NULL) || (permission == 0) || (permission > 3))
		 return -1;
	 
	 if(SUPERBLOCKobj.FreeInode == 0)
		 return -2;
	 
	 (SUPERBLOCKobj.FreeInode)--;
	 
	 if(Get_Inode(name) != NULL)
		 return -3;
	 
	 while(temp != NULL)
	 {
		 if(temp -> FileType == 0)
			 break;
		 temp = temp -> next;
	 }
	 
	 while(i < 50)
	 {
		 if(UFDTArr[i].ptrfiletable == NULL)
			 break;
		 i++;
	 }
	 
	 UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));
	 
	 UFDTArr[i].ptrfiletable -> count = 1;
	 UFDTArr[i].ptrfiletable -> mode = permission;
	 UFDTArr[i].ptrfiletable -> readoffset = 0;
	 UFDTArr[i].ptrfiletable -> writeoffset = 0;
	 
	 UFDTArr[i].ptrfiletable -> ptrinode = temp;
	 
	 strcpy(UFDTArr[i].ptrfiletable -> ptrinode -> FileName, name);
	 UFDTArr[i].ptrfiletable -> ptrinode -> FileType = REGULAR;
	 UFDTArr[i].ptrfiletable -> ptrinode -> ReferenceCount = 1;
	 UFDTArr[i].ptrfiletable -> ptrinode -> LinkCount = 1;
	 UFDTArr[i].ptrfiletable -> ptrinode -> FileSize = MAXFILESIZE;
	 UFDTArr[i].ptrfiletable -> ptrinode -> FileActualSize = 0;
	 UFDTArr[i].ptrfiletable -> ptrinode -> permission = permission;
	 UFDTArr[i].ptrfiletable -> ptrinode -> Buffer = (char *)malloc(MAXFILESIZE);
	 
	 return i;	 
 }
//rm_File("Demo.txt")

/*
    Name Of Function : rm_File()
    Input Parameter :  address of String
    Return Value of Function : Integer
    Decription of The function and its use in project : 
    	It will accept the name of the file
    	After that it will decrease LinkCount of that file using FD of that file
    	Then If linkcount is 0 then it will change file type to 0 and then delete the filetable of that Inodes.
    	And set it to null then it will increase the count of free Inode by 1.
*/
int rm_File(char *name)               //  To delete the file.
{
     int fd = 0;
     
     fd = GetFDFromName(name);
     if(fd == -1)
     	return -1;
     	
     (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount)--;
     
     if(UFDTArr[fd].ptrfiletable->ptrinode->LinkCount==0)
     {
          UFDTArr[fd].ptrfiletable->ptrinode->FileType=0;
          //free(UFDTArr[fd].ptrfiletable.ptrinode->Buffer);
          free(UFDTArr[fd].ptrfiletable);
     }
     UFDTArr[fd].ptrfiletable = NULL;
     (SUPERBLOCKobj.FreeInode)++;
}


/*
    Name Of Function : ReadFile()
    Input Parameter :  Integer, address of String, Integer
    Return Value of Function : Integer
    Decription of The function and its use in project : 
    	This function is used to read the data which is stored in that file.
    	First it will check if ftrfiletable is null or not, then it will check mode and permission of file, readoffset is equal to fileactualsize,is it regular file etc.
    	After that it will read the data in number of bytes we have passed to it.
    	
*/
int ReadFile(int fd,char *arr,int isize)            // TO read the file.
{
     int read_size = 0;
     
     if(UFDTArr[fd].ptrfiletable == NULL)     return -1;
     
     if(UFDTArr[fd].ptrfiletable->mode != READ && UFDTArr[fd].ptrfiletable->ptrinode->permission != READ + WRITE)  return -2;
     
     if(UFDTArr[fd].ptrfiletable->readoffset == UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)  return -3;
     
     if(UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR)  return -4;
     
     read_size = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) - (UFDTArr[fd].ptrfiletable->readoffset);
     
     if(read_size < isize)
     {
          strncpy(arr,(UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset),read_size);
          
          UFDTArr[fd].ptrfiletable->readoffset = UFDTArr[fd].ptrfiletable->readoffset + read_size;
     }
     else
     {
          strncpy(arr,(UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset),isize);
          
          UFDTArr[fd].ptrfiletable->readoffset = (UFDTArr[fd].ptrfiletable->readoffset) + isize;
     }
     
     return isize;   
}


/*
    Name Of Function : WriteFile()
    Input Parameter :  Integer, address of String, Integer
    Return Value of Function : Integer
    Decription of The function and its use in project :
    	This function is used to write the date in file
    	First it ill check all the conditions.
    	Then It will copy the data into the block whose address is stored in the buffer. 
    	Then we can add isize value with original writeoffset value
    	Then we can add isize value with original FileActualSize value

*/
int WriteFile(int fd,char *arr,int isize)       // To write a data into file.
{
     if(((UFDTArr[fd].ptrfiletable->mode) != WRITE) && ((UFDTArr[fd].ptrfiletable->mode)!=READ + WRITE)) return -1;
     
     if(((UFDTArr[fd].ptrfiletable->ptrinode->permission) != WRITE) && ((UFDTArr[fd].ptrfiletable->ptrinode->permission)!=READ + WRITE)) return -1;
     
     if((UFDTArr[fd].ptrfiletable->writeoffset)==MAXFILESIZE)  return -2;
     
     if((UFDTArr[fd].ptrfiletable->ptrinode->FileType)!=REGULAR)  return -3;
     
     strncpy((UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->writeoffset),arr,isize);
     
     (UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->writeoffset) + isize;
     
     (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + isize;
     
     return isize;
}


/*
    Name Of Function : OpenFile()
    Input Parameter :  address of String, Integer
    Return Value of Function : Integer
    Decription of The function and its use in project :
    	This function accept address of filename which we accept from user and mode of file
    	In temperory pointer temp we stored address of that Inode in which the file is present.
    	Using that Inode address we check the permission of file.If permission is less than mode we return to the function call.
    	If mode is read + write then it will intialise readoffset and writeoffset to 0
	If mode is write then it will intialise writeoffset to 0
	If mode is read then it will intialise readoffset to 0
	Then in pointer of file table we stored the value of temp
	Then we increase reference count of file by 1.
*/
int OpenFile(char *name,int mode)         // To open a file.
{
    int i=0;
    PINODE temp=NULL;

    if(name == NULL || mode <=0)
    {
        return -1;
    }
    temp=Get_Inode(name);
    if(temp == NULL)
    {
        return -2;
    }
    if(temp->permission < mode)
    {
        return -3;
    }

    while(i<MAXINODE)
    {
        if(UFDTArr[i].ptrfiletable == NULL)
            break;
        i++;
    }

    UFDTArr[i].ptrfiletable=(PFILETABLE)malloc(sizeof(FILETABLE));
    if(UFDTArr[i].ptrfiletable == NULL)   return -1;  
    UFDTArr[i].ptrfiletable->count=1;
    UFDTArr[i].ptrfiletable->mode=mode;
    if(mode == READ + WRITE)
    {
        UFDTArr[i].ptrfiletable->readoffset=0;
        UFDTArr[i].ptrfiletable->writeoffset=0;
    }
    else if(mode == READ)
    {
        UFDTArr[i].ptrfiletable->readoffset=0;
    }
    else if(mode == WRITE)
    {
        UFDTArr[i].ptrfiletable->writeoffset=0;
    }

    UFDTArr[i].ptrfiletable->ptrinode=temp;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)++;

    return i;
}


/*
    Name Of Function : CloseFileByName()
    Input Parameter :  Integer
    Return Value of Function : None
    Decription of The function and its use in project :
    	This function is used to Close the file using file name
    	This function accept file descriptor
    	Then we initialise readoffset, writeoffset to 0
    	Then we decrease the reference count of file .  	
*/
void CloseFileByName(int fd)                // To close file by using file descriptor of file.
{
    UFDTArr[fd].ptrfiletable->readoffset=0;
    UFDTArr[fd].ptrfiletable->writeoffset=0;
    (UFDTArr[fd].ptrfiletable->ptrinode->ReferenceCount)--;
}



/*
    Name Of Function : CloseFileByName()
    Input Parameter :  Address of string
    Return Value of Function : Integer
    Decription of The function and its use in project :
    	This function is used to Close the file using file name
    	This function accept address of string
    	Then it get file descriptor from GetFDFromName() function
    	Then we initialise readoffset, writeoffset to 0
    	Then we decrease the reference count of file . 	   	
*/
int CloseFileByName(char *name)          // To close file by using name of file.
{
    int i=0;
    i=GetFDFromName(name);

    if(i == -1)
    {
        return -1;
    }

    UFDTArr[i].ptrfiletable->readoffset=0;
    UFDTArr[i].ptrfiletable->writeoffset=0;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;

    return 0;
}


/*
    Name Of Function : CloseAllFile()
    Input Parameter :  None
    Return Value of Function : None
    Decription of The function and its use in project :
    	This function is used to Close the file using file name
    	In while loop we initialise readoffset, writeoffset to 0, decrease the reference count of file until prtfiletable becomes null
    		   	
*/
void CloseAllFile()                   // To close all files.
{
    int i=0;
    while(i<MAXINODE)
    {
        if(UFDTArr[i].ptrfiletable != NULL)
        {
            UFDTArr[i].ptrfiletable->readoffset=0;
            UFDTArr[i].ptrfiletable->writeoffset=0;
            (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;
            break;
        }
        i++;
    }
}


/*
    Name Of Function : LseekFile()
    Input Parameter :  Integer , Integer , Integer
    Return Value of Function : Integer
    Decription of The function and its use in project :
    	This function is used to read and write data from either start current end position.
    	This function accept file descriptor , size to read or write , position from read and write.   		   	
*/

int LseekFile(int fd,int size,int from)
{
    if((fd < 0) || (from > 2))
        return -1;
    if(UFDTArr[fd].ptrfiletable == NULL)
        return -1;

    if((UFDTArr[fd].ptrfiletable->mode==READ) || (UFDTArr[fd].ptrfiletable->mode==READ+WRITE))
    {
        if(from == CURRENT)
        {
           if(((UFDTArr[fd].ptrfiletable->readoffset)+size) > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
           return -1;

            if(((UFDTArr[fd].ptrfiletable->readoffset)+size) < 0)
            return -1;

            (UFDTArr[fd].ptrfiletable->readoffset)=(UFDTArr[fd].ptrfiletable->readoffset)+size;  
        }
        else if(from == START)
        {
            if(size > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
            return -1;

            if(size < 0)
                return -1;

            (UFDTArr[fd].ptrfiletable->readoffset)=size;
        }
        else if(from == END)
        {
            if((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)+size > MAXFILESIZE)
            return -1;

            if(((UFDTArr[fd].ptrfiletable->readoffset)+size) < 0)
            return -1;

            (UFDTArr[fd].ptrfiletable->readoffset)= (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) +size;
        }
    }
    else if(UFDTArr[fd].ptrfiletable->mode == WRITE)
    {
        if(from == CURRENT)
        {
            if(((UFDTArr[fd].ptrfiletable->writeoffset)+ size) > MAXFILESIZE)
                return -1;
            if(((UFDTArr[fd].ptrfiletable->writeoffset)+ size) < 0)
                return -1;

            if(((UFDTArr[fd].ptrfiletable->writeoffset)+ size) >  (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
            
                (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)=(UFDTArr[fd].ptrfiletable->writeoffset)+ size;

                (UFDTArr[fd].ptrfiletable->writeoffset)=(UFDTArr[fd].ptrfiletable->writeoffset)+ size;
        }
        else if(from == START)
        {
            if(size>MAXFILESIZE)
                return -1;
            if(size < 0)
                return -1;

            if(size >(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
                (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)=size;

            (UFDTArr[fd].ptrfiletable->writeoffset)=size;
        }
        else if(from == END)
        {
            if((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)+size > MAXFILESIZE)
                return -1;
            
            if(((UFDTArr[fd].ptrfiletable->writeoffset)+size) < 0)
                return -1;

            (UFDTArr[fd].ptrfiletable->writeoffset)=(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)+size;
        }
    }
}


/*
    Name Of Function : ls_file()
    Input Parameter :  None
    Return Value of Function : None
    Decription of The function and its use in project :
    	This function is used to display File Name, Inode number, File Size, Link Count of all files 
    	In one temperory pointer we store address of first Inode
    	Using while loop we display  File Name, Inode number, File Size, Link Count of all files until temp became null.  		   	
*/
void ls_file()                            // To give list of all files. 
{
    int i=0;
    PINODE temp=head;

    if(SUPERBLOCKobj.FreeInode == MAXINODE)
    {
        printf("ERROR : There is no files\n");
        return;
    }

    printf("\n File Name \t Inode number \t File Size \t Link Count \n");
    printf("---------------------------------------------------------------------\n");

    while(temp!=NULL)
    {
        if(temp->FileType != 0)
        {
            printf("%s \t\t %d \t\t %d \t\t %d\n",temp->FileName,temp->InodeNumber,temp->FileActualSize,temp->LinkCount);
        }
        temp=temp->next;
    }
    printf("---------------------------------------------------------------------\n");
}



/*
    Name Of Function : fstat_file()
    Input Parameter :  Integer
    Return Value of Function : Integer
    Decription of The function and its use in project :
    	This function is used to dsplay the File name Inode number, Filesize, FileActualSize, LinkCount, Reference count of file which is stored in Inode of that file.
    	This function accept file descriptor.
    	In Temperory pointer we store the address of That file's Inode whose information we have to display.
    	To get the address of that file's Inode we use file descriptor.
    	Using the address stored in temp we display information of file.
    	  		   	
*/
int fstat_file(int fd)             // To give statistical information about file stored in Inode.
{
    PINODE temp = head;
    int i = 0;
    
    if(fd < 0)   return -1;
    
    if(UFDTArr[fd].ptrfiletable == NULL)  return -2;
    
    temp = UFDTArr[fd].ptrfiletable->ptrinode;
    
    printf("\n-----Statistical Information about file---------\n");
    printf("File name :%s\n",temp->FileName);
    printf("Inode Number %d\n",temp->InodeNumber);
    printf("File Size : %d\n",temp->FileSize);
    printf("Actual File Size : %d\n",temp->FileActualSize);
    printf("Link count : %d\n",temp->LinkCount);
    printf("Reference Count : %d\n",temp->ReferenceCount);
    
    if(temp->permission == 1)
    	printf("File Permission : Read only\n");
    else if(temp->permission == 2)
    	printf("File Permission : Write\n");
    else if(temp->permission == 3)
    	printf("File Permission : Read & Write\n");
    	
    printf("-----------------------------------------------------\n");
    
    return 0;
}


/*
    Name Of Function : stat_file()
    Input Parameter :  address of string
    Return Value of Function : Integer
    Decription of The function and its use in project :
    	This function is used to display the information of file which is stored in Inode
    	This function accept the address of file name.
    	In this function we take one temperory pointer in which we stored the address of first Inode.
    	In while loop we compare the name of file whose address we took as argument which is accepted from user with the file name which is stored in Inode. If it is equal we break that loop and display all information of file which is in Inode of that file. and if not we store the address of next Inode in temperory pointer.
    	  		   	
*/
int stat_file(char * name)   // To give statistical information about file stored in Inode.
{
    PINODE temp = head;
    int i = 0;
    
    if(name == NULL)  return -1;
    
    while(temp != NULL)
    {
        if(strcmp(name,temp->FileName)==0)
        	break;
        temp = temp->next;
    }
    
    if(temp == NULL) return -2;
    
    printf("\n--------------Statistical Information about File--------------\n");
    printf("File Name : %s\n",temp->FileName);
    printf("Inode Number: %d\n",temp->InodeNumber);
    printf("File Size : %d\n",temp->FileSize);
    printf("Actual File Size : %d\n",temp->FileActualSize);
    printf("Link count : %d\n",temp->LinkCount);
    printf("Reference count : %d\n",temp->ReferenceCount);
    
    if(temp->permission == 1)
    	printf("File Permission : Read only\n");
    else if(temp->permission == 2)
    	printf("File Permission : Write\n");
    else if(temp->permission == 3)
    	printf("File Permission : Read & Write\n");
    	
    printf("-----------------------------------------------------\n");
    
    return 0;
    
}


/*
    Name Of Function : truncate_File()
    Input Parameter :  address of string
    Return Value of Function : Integer
    Decription of The function and its use in project :
    	This function is used to delete all data from block which is allocated for that file in data block section.
    	This function takes the address of file name as argument.
    	Then we get file discriptor of that file from GetFDFromName() function.
    	Using memset function we clear all data of block. The address of that block is in buffer pointer.
    	After that we set readoffset writeoffset FileActualSize to 0.
    	  		   	
*/
int truncate_File(char *name)   // To delete the data from file.
{
     int fd = GetFDFromName(name);
     if(fd == -1)
     	return -1;
     	
     memset(UFDTArr[fd].ptrfiletable->ptrinode->Buffer,0,1024);
     UFDTArr[fd].ptrfiletable->readoffset = 0;
     UFDTArr[fd].ptrfiletable->writeoffset = 0;
     UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = 0;
}

int main()
{
    char *ptr = NULL;
    int ret=0,fd=0,count=0;
    char command[4][80],str[80],arr[1024];
    
    InitializeSuperBlock();
    CreateDILB();
    
    while(1)
    {
         fflush(stdin);
         strcpy(str,"");
        
         printf("\nCustomised VFS : > ");
        
       fgets(str,80,stdin);     //Scanf("%[^'\n']s",str);
       
       count = sscanf(str,"%s %s %s %s",command[0],command[1],command[2],command[3]);
       
         if(count == 1)
         {
             if(strcmp(command[0],"ls")==0)
             {
                 ls_file();
             }
             else if(strcmp(command[0],"closeall")==0)
             {
                 CloseAllFile();
                 printf("All files closed successfully\n");
                 continue;
             }
             else if(strcmp(command[0],"clear")==0)
             {
                 system("cls");
                 continue;
             }
             else if(strcmp(command[0],"help")==0)
             {
                 DisplayHelp();
                 continue;
             }
             else if(strcmp(command[0],"exit")==0)
             {
                 printf("Terminating the Customised Virtual File System\n");
                 break;
             }
             else
             {
                 printf("Error : Command not found!!!\n");
                 continue;
             }
         }
         else if(count == 2)
         {
             if(strcmp(command[0],"stat")==0)
             {
                 ret = stat_file(command[1]);
                 
                 if(ret == -1)
                 	printf("Error : Incorrect Parameters\n");
                 	
                 if(ret == -2)
                 	printf("Error : There is no such file\n");
                 continue;  
             }
             else if(strcmp(command[0],"fstat")==0)
             {
                 ret = fstat_file(atoi(command[1]));
                 
                 if(ret == -1)
                 	printf("Error : Incorrect Parameters\n");
                 	
                 if(ret == -2)
                 	printf("Error : There is no such file\n");
                 continue;  
             }
             else if(strcmp(command[0],"close")==0)
             {
                 ret = CloseFileByName(command[1]);
                 if(ret == -1)
                 	printf("Error : There is no such file\n");
                 continue;  
             }
             else if(strcmp(command[0],"rm")==0)
             {
                 ret = rm_File(command[1]);
                 if(ret == -1)
                 	printf("Error : There is no such file\n");
                 continue;  
             }
             else if(strcmp(command[0],"man")==0)
             {
                 man(command[1]);
             }
             else if(strcmp(command[0],"write")==0)
             {
                 fd = GetFDFromName(command[1]);
                 if(fd == -1)
                 {
                     printf("Error : Incorrect Parameter\n");
                     continue;
                 }
                 printf("Enter the data : \n");
                 scanf("%[^'\n']",arr);
                 
                 ret = strlen(arr);
                 if(ret == 0)
                 {
                     printf("Error : Incorrect Parameter\n");
                     continue;
                 }
                 ret = WriteFile(fd,arr,ret);
                 if(ret == -1)
                 {
                     printf("Permission Denied\n");
                 }
                 if(ret == -2)
                 {
                     printf("There is no sufficient memory to write\n");
                 }
                 if(ret == -3)
                 {
                     printf("It is not regular file\n");
                 }
             }
             else if(strcmp(command[0],"truncate")==0)
             {
                 ret = truncate_File(command[1]);
                 if(ret == -1)
                 	printf("Error : Incorrect Parameter\n"); 
             }
             else
             {
                 printf("\nERROR : Command not found!!!\n");
                 	continue;
             }
         }
         else if(count == 3)
         {
             if(strcmp(command[0],"create") == 0)
             {
                 ret = CreateFile(command[1],atoi(command[2]));
                 if(ret >= 0)
                 	printf("File is successfully created with file descriptor:%d\n",ret);
                 	
                 if(ret == -1)
                 	printf("Error:Incorrect Parameters\n");
                 	
                 if(ret == -2)
                 	printf("Error:There is no inodes\n");
                 	
                 if(ret == -3)
                 	printf("Error:File already exists\n");
                 	
                 if(ret == -4)
                 	printf("Error:Memory allocation failure\n");
                 continue;
             }
             else if(strcmp(command[0],"open") == 0)
             {
                 ret = OpenFile(command[1],atoi(command[2]));
                 if(ret >= 0)
                 	printf("File is successfully opened with file descriptor:%d\n",ret);
                 	
                 if(ret == -1)
                 	printf("Error:Incorrect Parameters\n");
                 	
                 if(ret == -2)
                 	printf("Error:File not present\n");
                 	
                 if(ret == -3)
                 	printf("Error:Permission Denied\n");
                 continue;
             }
             else if(strcmp(command[0],"read")==0)
             {
                 fd = GetFDFromName(command[1]);
                 if(fd == -1)
                 {
                     printf("Error : Incomplete Parameter\n");
                     continue;
                 }
                 ptr = (char *)malloc(sizeof(atoi(command[2]))+1);
                 if(ptr == NULL)
                 {
                     printf("Error: Memory allocation Failure\n");
                     continue;
                 }
                 ret = ReadFile(fd,ptr,atoi(command[2]));
                 if(ret == -1)
                 	printf("Error : File not existing\n");
                 	
                 if(ret == -2)
                 	printf("Error:Permission Denied\n");
                 	
                 if(ret == -3)
                 	printf("Error : Reached at end of file\n");
                 	
                 if(ret == -4)
                 	printf("Error : It is not regular file\n");
                 	
                 if(ret > 0)
                 {
                       write(2,ptr,ret);
                 }
                 continue;
             }
             else
             {
                  printf("\nError : Command not found !!!\n");
                  continue;
             }
         }
         else if(count == 4)
         {
             if(strcmp(command[0],"lseek") == 0)
             {
                 fd = GetFDFromName(command[1]);
                 if(fd == -1)
                 {
                      printf("Error : Incorrect parameter\n");
                      continue;
                 }
                 ret = LseekFile(fd,atoi(command[2]),atoi(command[3]));
                 if(ret == -1)
                 {
                      printf("Error : Unable to perform lseek\n");
                 }
             }
             else
             {
                 printf("\nError : Command not found!!!\n");
                 continue;
             }
         }
         else
         {
             printf("\nError : Command not found !!!\n");
             continue;
         }
    }
    
    return 0;
}



