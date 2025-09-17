///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Inclusion of header files
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User defined macros
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#define SUCCESS 0
#define FAILURE -1
#define ERR_INVALID_FILE_NAME -2
#define ERR_INVALID_PERMISSION -3
#define ERR_FILE_NOT_CREATED -4
#define ERR_UNABLE_TO_READ -5
#define ERR_UNABLE_TO_WRITE -6
#define ERR_UNABLE_TO_OPEN -7
#define ERR_UNABLE_TO_UNLINK -8

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Macros for value
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#define ALL_PERMS 0777
#define BELOW_ZERO 0
#define BUFFER_SIZE 1024

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function_name :         DeleteFolder 
//  Function_descriptor :   This function deletes folder
//  Parameters :            fName as character pointer
//  Return value :          Integer
//  Author :                Ritesh Kurambhatti
//  Date :                  7.Spet.2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

int DeleteFolder(char *fName)
{
    if(fName == NULL)
    {
        return ERR_INVALID_FILE_NAME;
    }

    int iRet = 0;

    iRet = rmdir(fName);

    if(iRet == 0)
    {
        return SUCCESS;
    }
    else
    {
        return ERR_UNABLE_TO_UNLINK;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function_name :         DeleteFile 
//  Function_descriptor :   This function deletes file
//  Parameters :            fName as character pointer
//  Return value :          Integer
//  Author :                Ritesh Kurambhatti
//  Date :                  7.Spet.2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

int DeleteFile(char *fName)
{
    if(fName == NULL)
    {
        return ERR_INVALID_FILE_NAME;
    }
    int iRet = 0;
    
    iRet = unlink(fName);

    if(iRet == 0)
    {
        return SUCCESS;
    }
    else
    {
        return ERR_UNABLE_TO_UNLINK;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function_name :         WriteIntoFile 
//  Function_descriptor :   This function writes data into the file
//  Parameters :            fName as character pointer, Character buffer to read
//  Return value :          Integer
//  Author :                Ritesh Kurambhatti
//  Date :                  7.Spet.2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

int WriteIntoFile(char *fName, char Buffer[])
{
    if(fName == NULL)
    {
        return ERR_INVALID_FILE_NAME;
    }

    int iFd = 0, iRet = 0;

    iFd = open(fName, O_CREAT | O_APPEND | O_RDWR, ALL_PERMS);

    if(iFd == -1)
    {
        return ERR_UNABLE_TO_OPEN;
    }
    if(Buffer == NULL) 
    {
        return ERR_UNABLE_TO_WRITE;
    }

    iRet = write(iFd,Buffer,strlen(Buffer));

    close(iFd);

    if(iRet == -1)
    {
        return ERR_UNABLE_TO_WRITE;
    }
    else
    {
        return iRet;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function_name :         ReadFromFile 
//  Function_descriptor :   This function reads data from the file
//  Parameters :            fName as character pointer, Character Empty buffer to read
//  Return value :          Integer
//  Author :                Ritesh Kurambhatti
//  Date :                  7.Spet.2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

int ReadFromFile(char *fName, char Buffer[])
{
    if(fName == NULL)
    {
        return ERR_INVALID_FILE_NAME;
    }

    int iFd = 0, iRet = 0;

    iFd = open(fName,O_RDONLY);

    if(iFd == -1)
    {
        return ERR_UNABLE_TO_OPEN;
    }

    while((iRet = read(iFd, Buffer, BUFFER_SIZE)) > 0)
    {
        write(1, Buffer, iRet);
        memset(Buffer, '\0', BUFFER_SIZE);
    }

    close(iFd);
    
    if(iRet == -1)
    {
        return ERR_UNABLE_TO_READ;
    }
    else
    {
        return SUCCESS;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function_name :         CreateFileX 
//  Function_descriptor :   This function creates a new file
//  Parameters :            FileName as character pointer, Integer as permission of the file
//  Return value :          Integer      
//  Author :                Ritesh Kurambhatti
//  Date :                  6.Spet.2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

int CreateFileX(char * FileName, int Mode)
{
    if(FileName == NULL)
    {
        return ERR_INVALID_FILE_NAME;
    }

    if((Mode > ALL_PERMS) || (Mode < BELOW_ZERO))
    {
        return ERR_INVALID_PERMISSION;
    }

    int iFd = 0;

    iFd = creat(FileName,Mode);

    if(iFd == -1)
    {
        return ERR_FILE_NOT_CREATED;
    }
    else
    {
        return iFd;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function_name :         MakeDirectory 
//  Function_descriptor :   This function creates a folder
//  Parameters :            2 Character array
//  Return value :          Integer      
//  Author :                Ritesh Kurambhatti
//  Date :                  4.Spet.2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

int MakeDirectory(char dir[], char fName[])
{
    char Command[100] = {'\0'};
    int iRet = 0;
    
    strcat(Command,dir);
    strcat(Command," ");
    strcat(Command,fName);

    iRet = system(Command);

    if(iRet == 0)
    {
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function_name :         Help 
//  Function_descriptor :   This function helps the user to use the command
//  Return :                Void
//  Author :               Ritesh Kurambhatti
//  Date :                  4.Spet.2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void Help()
{
    printf("-------------------------------------------help page---------------------------------------------\n");
    printf("clear : clears the screen\n");
    printf("ls : Lists all the files, folders and shows it to the end user\n");
    printf("pwd : Shows the current path in the terminal\n");
    printf("man : Shows the manual of the specific command\n");
    printf("mkdir : Creates new folder in the current directory\n");
    printf("touch : Creates new file in the current directory\n");
    printf("write : Writes data into the file\n");
    printf("read : Reads data from the file\n");
    printf("delete file filename : Deletes a file\n");
    printf("delete folder foldername : Deletes an empty folder\n");
    printf("exit : Exits the personal terminal\n");
    printf("-------------------------------------------help page---------------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function_name :         ManPage 
//  Function_descriptor :   This function is used to show the manual of specific command
//  Parameters :            Character pointer
//  Return :                It returns nothing
//  Author :                Ritesh Kurambhatti
//  Date :                  4.Spet.2025
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

void ManPage(char *str)
{
    if(strcmp(str,"clear") == 0)
    {
        printf("=========================================================================\n");
        printf("Command name : \n\t-clear\n");
        printf("Description :  \n\t-It clears the terminal screen\n");
        printf("SYNOPSIS : \n\t-clear\n");
        printf("=========================================================================\n");
    }
    else if(strcmp(str,"ls") == 0)
    {
        printf("=========================================================================\n");
        printf("Command name : \n\t-ls\n");
        printf("Description :  \n\t-It shows all the files and folders in the current directory\n");
        printf("SYNOPSIS : \n\t-ls\n");
        printf("=========================================================================\n");
    }
    else if(strcmp(str,"pwd") == 0)
    {
        printf("=========================================================================\n");
        printf("Command name : \n\t-pwd\n");
        printf("Description :  \n\t-It shows the current directory\n");
        printf("SYNOPSIS : \n\t-pwd\n");
        printf("=========================================================================\n");
    }
    else if(strcmp(str,"help") == 0)
    {
        printf("=========================================================================\n");
        printf("Command name : \n\t-help\n");
        printf("Description :  \n\t-It shows basic information about all commands\n");
        printf("SYNOPSIS : \n\t-help\n");
        printf("=========================================================================\n");
    }
    else if(strcmp(str,"man") == 0)
    {
        printf("=========================================================================\n");
        printf("Command name : \n\t-man\n");
        printf("Description :  \n\t-It shows the manual of the specific command\n");
        printf("SYNOPSIS : \n\t-man command\n\tWhere command is a inbuilt command of Operating system\n");
        printf("=========================================================================\n");
    }
    else if(strcmp(str,"mkdir") == 0)
    {
        printf("=========================================================================\n");
        printf("Command name : \n\t-mkdir folder_name\n");
        printf("Description :  \n\t-It creates a new folder in the current directory\n");
        printf("SYNOPSIS : \n\t-mkdir folder_name\n\tWhere mkdir is the command to create the folder and folder_name is the string\n");
        printf("=========================================================================\n");
    }

    else if(strcmp(str,"touch") == 0)
    {
        printf("=========================================================================\n");
        printf("Command name : \n\t-touch filename [permission]\n");
        printf("Description :  \n\t-Creates a new file.\n");
        printf("SYNOPSIS : \n\t-touch filename\n");
        printf("Note:\n");
        printf("\t-Default permission = 0777\n");
        printf("=========================================================================\n");
    }
    else if(strcmp(str,"write") == 0)
    {
        printf("=========================================================================\n");
        printf("Command name : \n\t-write filename\n");
        printf("Description :  \n\t-Writes data into the file.\n");
        printf("SYNOPSIS : \n\t-write filename\n");
        printf("=========================================================================\n");
    }
    else if(strcmp(str,"read") == 0)
    {
        printf("=========================================================================\n");
        printf("Command name : \n\t-read filename\n");
        printf("Description :  \n\t-Displays contents of the file.\n");
        printf("SYNOPSIS : \n\t-read filename\n");
        printf("=========================================================================\n");
    }
    else if(strcmp(str,"delete") == 0)
    {
        printf("=========================================================================\n");
        printf("Command name : \n\t-delete file OR folder name\n");
        printf("Description :  \n\t-Deletes a file or an empty folder.\n");
        printf("SYNOPSIS : \n\t-delete file filename\n\t-delete folder foldername\n");
        printf("=========================================================================\n");
    }

    else if(strcmp(str,"exit") == 0)
    {  
        printf("=========================================================================\n");
        printf("Command name : \n\t-exit\n");
        printf("Description :  \n\t-Terminates the personal terminal(Command Prompt)\n");
        printf("SYNOPSIS : \n\t-exit\n");
        printf("=========================================================================\n");
    }
    else
    {
        printf("Invalid command\nPlease refer help command\n");
    }
} // End of ManPage

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int iCount = 0;
    int iRet = 0;
    char Command[5][80] = {'\0'};
    char Buffer[BUFFER_SIZE] = {'\0'};
    char EmtpyBuffer[BUFFER_SIZE] = {'\0'};
    char cStr[40] = {'\0'};
    
    while(1)
    {
        memset(cStr,'\0',strlen(cStr));
        strcpy(cStr,"");   
        printf("\nPersonalCMD>>");
        fgets(cStr,sizeof(cStr),stdin);

        iCount = sscanf(cStr,"%s %s %s %s %s",Command[0],Command[1],Command[2],Command[3],Command[4]);

        if(iCount == 1)
        {
            if(strcmp(Command[0],"clear") == 0)
            {
                system("cls");  // Windows command to clear the screen
            }
            else if(strcmp(Command[0],"ls") == 0)
            {
                system("dir");  // Windows command to list files
            }
            else if(strcmp(Command[0],"pwd") == 0)
            {
                system("cd");   // Windows command to show current directory
            }
            else if(strcmp(Command[0],"help") == 0)
            {
                Help();
            }
            else if(strcmp(Command[0],"exit") == 0)
            {
                printf("Thank you for using our personal terminal\n");
                exit(0);
            }
        } // End of if(iCount == 1)
        else if(iCount == 2)
        {
            if(strcmp(Command[0],"man") == 0)
            {
                ManPage(Command[1]);
            }
            else if(strcmp(Command[0],"mkdir") == 0)
            {
                if(MakeDirectory(Command[0],Command[1]) == SUCCESS)
                {
                    printf("Folder successfully created with name %s\n",Command[1]);
                }
                else
                {
                    printf("Unable to create folder\n");
                }
            }
            else if(strcmp(Command[0],"touch") == 0)
            {
                iRet = CreateFileX(Command[1],ALL_PERMS);

                if(iRet == ERR_FILE_NOT_CREATED)
                {
                    printf("Unable to create file\n");
                }
                else if(iRet == ERR_INVALID_FILE_NAME)
                {
                    printf("Invalid file name\n");
                }
                else if(iRet == ERR_INVALID_PERMISSION)
                {
                    printf("Please give a valid permission to the file\n");
                }
                else
                {
                    printf("File is successfully created with File Descriptor : %d\n",iRet);
                }
            }
            else if(strcmp(Command[0],"read") == 0)
            {
                iRet = ReadFromFile(Command[1],EmtpyBuffer);

                if(iRet == ERR_UNABLE_TO_OPEN)
                {
                    printf("Unable to open the file\n");
                }

                if(iRet == ERR_UNABLE_TO_READ)
                {
                    printf("Unable to read into the file\n");
                }

                if(iRet == ERR_INVALID_FILE_NAME)
                {
                    printf("Invalid file name\n");
                }
            }
            else if(strcmp(Command[0],"write") == 0)
            {
                printf("What do you want to write into the file\n");
                scanf(" %[^'\n']s",Buffer);
                getchar(); 

                iRet = WriteIntoFile(Command[1],Buffer);

                if(iRet == ERR_INVALID_FILE_NAME)
                {
                    printf("Invalid file name\n");
                }

                if(iRet == ERR_UNABLE_TO_OPEN)
                {
                    printf("Unable to open the file\n");
                }
                
                if(iRet == ERR_UNABLE_TO_WRITE)
                {
                    printf("Unable to write into the file\n");
                }

                else
                {
                    printf("%d number of bytes gets written into the %s file\n",iRet,Command[1]);
                }
            }
        } // End of else if(iCount == 2)
        else if(iCount == 3)
        {
            if(strcmp(Command[0],"touch") == 0)
            {
                iRet = CreateFileX(Command[1],atoi(Command[2]));

                if(iRet == ERR_FILE_NOT_CREATED)
                {
                    printf("Unable to create file\n");
                }
                else if(iRet == ERR_INVALID_FILE_NAME)
                {
                    printf("Invalid file name\n");
                }
                else if(iRet == ERR_INVALID_PERMISSION)
                {
                    printf("Please give a valid permission to the file\n");
                }
                else
                {
                    printf("File is successfully created with File Descriptor : %d\n",iRet);
                }
            }
            else if(strcmp(Command[0],"delete") == 0)
            {
                if(strcmp(Command[1],"file") == 0)
                {
                    iRet = DeleteFile(Command[2]);

                    if(iRet == ERR_UNABLE_TO_UNLINK)
                    {
                        printf("Unable to delete the file\n");
                    }
                    else if(iRet == ERR_INVALID_FILE_NAME)
                    {
                        printf("Invalid file name\n");
                    }
                    else
                    {
                        printf("File deleted successfully\n");
                    }
                }
                else if(strcmp(Command[1],"folder") == 0)
                {
                    iRet = DeleteFolder(Command[2]);

                    if(iRet == ERR_UNABLE_TO_UNLINK)
                    {
                        printf("Unable to delete the folder\n");
                    }
                    else if(iRet == ERR_INVALID_FILE_NAME)
                    {
                        printf("Invalid folder name\n");
                    }
                    else
                    {
                        printf("Folder deleted successfully\n");
                    }
                }
            }
        }
        else
        {
            printf("Invalid command\n");
            printf("Please refer help command or man page\n");
        }
    } // End of while loop

} // End of entry point function

