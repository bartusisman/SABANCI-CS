#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

typedef struct DictionaryNode
{
    char *title;
    char *name;
    char *surname;
    struct DictionaryNode *next;
} DictionaryNode;

DictionaryNode* head, *findnode;

DictionaryNode * Addtodictionary(char titlepara, char*namepara, char *surnamepara)
{
    DictionaryNode *newNode= (DictionaryNode *)malloc(sizeof(DictionaryNode));
    newNode->title=(char *)malloc(sizeof(char)*4);
    
    if(titlepara=='f')
    {
        strcpy(newNode->title, "Ms.");
    }
    
    else
    {
        strcpy(newNode->title, "Mr.");
    }
    
    newNode->name= (char*)malloc(sizeof(char)*(strlen(namepara)+1));
    newNode->next=NULL;
    newNode->surname=(char*)malloc(sizeof(char)*(strlen(surnamepara)+1));
    
    strcpy(newNode->name,namepara);
    strcpy(newNode->surname,surnamepara);
    
    if(head==NULL)
    {   
        head=newNode;
        return head;
    }
    
    else
    {
        DictionaryNode* ptr=head;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        
        ptr->next=newNode;
        return head;
    }

}



void ReadDatabase()
{
    char inputstring[50], name[25],surname[30],gender;
    bool isnameread=false,istitleread=false;
    FILE * ptr = fopen("database.txt","r");
    
    while (fscanf(ptr,"%s",inputstring) != EOF)
    {
        if(!istitleread)
        {
            gender = inputstring[0];
            istitleread=true;
        }
        else if(!isnameread)
        {
            strcpy(name,inputstring);
            isnameread=true;
        }
        else
        {
            isnameread=false;
            istitleread=false;
            strcpy(surname, inputstring);
            head = Addtodictionary(gender, name, surname);
        }
    }
    fclose(ptr);
}

bool Dictionaryfind(char * namepara)
{
    DictionaryNode * ptr = head;
    while ( ptr!=NULL && strcmp(ptr->name,namepara) != 0 )
    {
        ptr=ptr->next;
    }
    
    if(ptr != NULL)
    {
        findnode = ptr;
        return true;
    }
    
    findnode = NULL;
    return false;
}

void correctfile(char* dir, char*dname)
{
    char word[256];
    char txtname[256];
    
    strcpy(txtname,dir);
    strcat(txtname,"/");
    strcat(txtname,dname);
    
    FILE * ptr = fopen(txtname, "r+");
    
    while (fscanf(ptr, "%s", word)!= EOF)
    {
        if(Dictionaryfind(word))
        {
            fseek(ptr,(-strlen(word)-4),SEEK_CUR);//beginning of title
            fputs(findnode->title,ptr);
            fseek(ptr,strlen(word)+2,SEEK_CUR);//beginning of surname
            fputs(findnode->surname,ptr);
        }
    }
    
    fclose(ptr);
}


void Destructor()
{
    DictionaryNode * ptr = head;
    DictionaryNode* temp;
    
    while(ptr != NULL)
    {
        temp = ptr->next;
        free(ptr->title);
        free(ptr->name);
        free(ptr->surname);
        free(ptr);
        ptr = temp;
    }
    
}

void Searcher(char *dir)
{
    struct dirent* directent;
    DIR *directory = opendir(dir);
    
    if (directory == NULL) 
    {
        printf("Error: Could not open directory %s\n", dir);
        return;
    }
    
    while((directent = readdir(directory)) != NULL)
    {
        if(directent->d_type == DT_REG)
        {
            correctfile(dir, directent->d_name);
        }
        
        else if (directent->d_type == DT_DIR && strcmp(directent->d_name, ".") != 0 && strcmp(directent->d_name, "..") != 0)
        {
            // DT_DIR indicates a directory, but we want to skip the "." and ".." directories
            char newdir[256];
            strcpy(newdir, dir);
            strcat(newdir, "/");
            strcat(newdir, directent->d_name);
            Searcher(newdir);
        }
    }
    
    closedir(directory);
}


int main()
{
    ReadDatabase();
    Searcher("."); // search the current directory
    Destructor();
    return 0;
}



